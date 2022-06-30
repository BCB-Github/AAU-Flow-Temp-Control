#ifndef BUFFERPOOLVIDEOCONTROLLER_HPP
#define BUFFERPOOLVIDEOCONTROLLER_HPP

#include <touchgfx/widgets/VideoWidget.hpp>
#include <MJPEGDecoder.hpp>
#include <touchgfx/Utils.hpp>

#include <string.h>

#include "cmsis_os.h"
#if defined(osCMSIS) && (osCMSIS < 0x20000)
#define MUTEX_CREATE() osMutexCreate(0)
#define MUTEX_LOCK(m) osMutexWait(m, osWaitForever)
#define MUTEX_TYPE osMutexId
#define MUTEX_UNLOCK(m) osMutexRelease(m)
#define SEM_CREATE() osSemaphoreCreate(0, 1)
#define SEM_POST(s) osSemaphoreRelease(s)
#define SEM_TYPE osSemaphoreId
#define SEM_WAIT(s) osSemaphoreWait(s, osWaitForever)
#else
#define MUTEX_CREATE() osMutexNew(0)
#define MUTEX_LOCK(m) osMutexAcquire(m, osWaitForever)
#define MUTEX_TYPE osMutexId_t
#define MUTEX_UNLOCK(m) osMutexRelease(m)
#define SEM_CREATE() osSemaphoreNew(1, 0, 0)
#define SEM_POST(s) osSemaphoreRelease(s)
#define SEM_TYPE osSemaphoreId_t
#define SEM_WAIT(s) osSemaphoreAcquire(s, osWaitForever)
#endif

template <uint32_t no_streams, uint32_t width, uint32_t height, uint32_t stride, touchgfx::Bitmap::BitmapFormat output_format>
class DoubleBufferedVideoController : public touchgfx::VideoController
{
public:
    DoubleBufferedVideoController()
        : VideoController(),
          bufferRGB(0), sizeBufferRGB(0), topBufferRGB(0), allowSkipFrames(true),
          semDecode(0), mutexBuffers(0)
    {
        assert((no_streams > 0) && "Video: Number of streams zero!");

        // Clear decoder array
        memset(mjpegDecoders, 0, sizeof(mjpegDecoders));

        // Initialize synchronization primitives
        semDecode = SEM_CREATE(); // Binary semaphore
        mutexBuffers = MUTEX_CREATE();
    }

    Handle registerVideoWidget(touchgfx::VideoWidget& widget)
    {
        // Running in UI thread

        // Find stream handle for Widget
        Handle handle = getFreeHandle();

        streams[handle].isActive = true;

        // Set Widget buffer format and address
        widget.setVideoBufferFormat(output_format, width, height);
        widget.setVideoBuffer((uint8_t*)0);

        streams[handle].frameNumberShown = 0;

        // Todo, make buffer size depending on widget
        const uint32_t sizeOfOneDecodeBuffer = height * stride;

        // Allocate two buffers for this stream, if possible
        if (topBufferRGB + 2 * sizeOfOneDecodeBuffer > (bufferRGB + sizeBufferRGB))
        {
            assert(0 && "registerVideoWidget: Unable to allocate two RGB buffers!");
            return 0xFFFFFFFF;
        }

        streams[handle].bufferA = (uint8_t*)topBufferRGB;
        topBufferRGB += sizeOfOneDecodeBuffer;
        streams[handle].bufferB = (uint8_t*)topBufferRGB;
        topBufferRGB += sizeOfOneDecodeBuffer;

        return handle;
    }

    void unregisterVideoWidget(const Handle handle)
    {
        // Running in UI thread

        // Reset active for this handle
        streams[handle].isActive = false;

        // If all handles are free, reset top pointer
        bool oneIsActive = false;
        for (uint32_t i = 0; i < no_streams; i++)
        {
            oneIsActive |= streams[i].isActive;
        }
        if (oneIsActive == false)
        {
            // Reset memory usage
            topBufferRGB = bufferRGB;
        }
    }

    uint32_t getCurrentFrameNumber(const Handle handle)
    {
        assert(handle < no_streams);
        const Stream& stream = streams[handle];
        return stream.frameNumberShown;
    }

    void setFrameRate(const Handle handle, uint32_t ui_frames, uint32_t video_frames)
    {
        // Running in UI thread

        assert(handle < no_streams);
        Stream& stream = streams[handle];

        // Reset counters
        stream.tickCount = 0;
        stream.frameCount = 0;

        // Save requested frame rate ratio
        stream.frame_rate_ticks = ui_frames;
        stream.frame_rate_video = video_frames;
    }

    void setVideoData(const Handle handle, const uint8_t* movie, const uint32_t length)
    {
        // Running in UI thread

        mjpegDecoders[handle]->setVideoData(movie, length);

        clearState(handle);
    }

    void setVideoData(const Handle handle, VideoDataReader& reader)
    {
        // Running in UI thread
        mjpegDecoders[handle]->setVideoData(reader);

        clearState(handle);
    }

    void setCommand(const Handle handle, Command cmd, uint32_t param)
    {
        // Running in UI thread

        assert(handle < no_streams);
        Stream& stream = streams[handle];

        switch (cmd)
        {
        case PLAY:
            // Cannot Play without movie
            if (mjpegDecoders[handle]->hasVideo())
            {
                MUTEX_LOCK(mutexBuffers);
                stream.isPlaying = true;
                stream.cancelDecoding = false;
                // Reset counters
                stream.frameCount = 0;
                stream.tickCount = 0;
                // Seek to start of video if stopped
                if (stream.isStopped)
                {
                    stream.seek_to_frame = 1;
                }
                stream.isStopped = false;
                // Kick decoder if next buffer is available
                stream.skip_frames = 0;
                if (stream.nextBuffer == 0)
                {
                    stream.doDecodeNewFrame = true;
                    SEM_POST(semDecode);
                }
                MUTEX_UNLOCK(mutexBuffers);
            }
            break;
        case PAUSE:
            stream.isPlaying = false;
            stream.isStopped = false;
            break;
        case SEEK:
            stream.seek_to_frame = param;
            // Reset counters
            stream.frameCount = 0;
            stream.tickCount = 0;
            break;
        case SHOW:
            stream.seek_to_frame = param;
            // Reset counters
            stream.frameCount = 0;
            stream.tickCount = 0;
            stream.isStopped = false;
            break;
        case STOP:
            stream.isPlaying = false;
            stream.isStopped = true;
            break;
        case SET_REPEAT:
            stream.repeat = (param > 0);
            break;
        }
    }

    /**
     * Called by VideoWidget::handleTickEvent.
     * Update frame counters.
     * Decide if widget should be invalidated.
     */
    bool updateFrame(const Handle handle, touchgfx::VideoWidget& widget)
    {
        // Running in UI thread

        assert(handle < no_streams);
        Stream& stream = streams[handle];

        // Increase tickCount if playing
        if (stream.isPlaying)
        {
            stream.tickCount += HAL::getInstance()->getLCDRefreshCount();
        }

        // Assume more frames are available, flag is lowered once, when changing to the last frame
        bool hasMoreFrames = true;

        // See if we have a nextBuffer and if next frame of specific frame is to be decoded
        if (stream.nextBuffer && (decodeForNextTick(stream) || stream.seek_to_frame > 0))
        {
            MUTEX_LOCK(mutexBuffers);

            // Do nothing if seek to frame
            if (stream.seek_to_frame > 0)
            {
                stream.nextBuffer = 0;
            }

            if (stream.nextBuffer != 0)
            {
                // Use nextBuffer as current
                stream.currentBuffer = stream.nextBuffer;
                stream.nextBuffer = 0;

                // Copy frameNumber, increase count
                stream.frameNumberShown = stream.frameNumberNext;
                stream.frameCount++;

                hasMoreFrames = stream.hasMoreFramesAfterNext;

                // Update widget to show current buffer
                widget.setVideoBuffer(stream.currentBuffer);
                widget.invalidate();

                if (!hasMoreFrames && !stream.repeat)
                {
                    stream.isPlaying = false;
                }
            }

            MUTEX_UNLOCK(mutexBuffers);
        }

        // Kick decoder if playing or seeking frame and next buffer is ready
        if ((stream.isPlaying || stream.seek_to_frame > 0) && (stream.nextBuffer == 0))
        {
            stream.doDecodeNewFrame = true;
            SEM_POST(semDecode);
        }

        return hasMoreFrames;
    }

    void draw(const Handle handle, const touchgfx::Rect& invalidatedArea, const touchgfx::VideoWidget& widget)
    {
        // Running in UI thread

        // Nothing in this decoder
    }

    void setRGBBuffer(uint8_t* buffer, size_t sizeOfBuffer)
    {
        // Running in UI thread / main

        bufferRGB = buffer;
        topBufferRGB = bufferRGB;
        sizeBufferRGB = sizeOfBuffer;
    }

    void addDecoder(MJPEGDecoder& decoder, uint32_t index)
    {
        // Running in UI thread / main

        assert(index < no_streams);
        mjpegDecoders[index] = &decoder;
    }

    void endFrame()
    {
        // Running in UI thread
        // Nothing to do
    }

    void decoderTaskEntry()
    {
        // Running in Decoder thread!!

        while (1)
        {
            // Look for a stream to decode
            uint32_t stream_index = getStreamIndexToDecode();

            if ((stream_index == NO_STREAM))
            {
                // All streams decoded, wait for synchronisation signal from UI thread
                SEM_WAIT(semDecode);

                // Try from the beginning
                continue;
            }

            // Lock out UI by taking the mutex
            MUTEX_LOCK(mutexBuffers);

            // Now decode the stream
            Stream& stream = streams[stream_index];

            // Select the unused buffer for decoding
            uint8_t* decodeBuffer = (stream.currentBuffer == stream.bufferA) ? stream.bufferB : stream.bufferA;

            MJPEGDecoder* const decoder = mjpegDecoders[stream_index];
            // Seek or increment video frame
            if (stream.seek_to_frame > 0)
            {
                decoder->gotoFrame(stream.seek_to_frame);
                stream.seek_to_frame = 0;
                stream.cancelDecoding = false;
            }
            else
            {
                if (stream.skip_frames > 0)
                {
                    decoder->gotoFrame(decoder->getCurrentFrameNumber() + stream.skip_frames);
                    stream.frameCount += stream.skip_frames;
                    stream.skip_frames = 0;
                }
            }

            // Unlock mutex while decoding
            MUTEX_UNLOCK(mutexBuffers);

            // Decode frame
            const bool hasMoreFrames = decoder->decodeNextFrame(decodeBuffer, width, height, stride);

            MUTEX_LOCK(mutexBuffers);

            // Save new frame in stream unless cancelled
            if (stream.cancelDecoding)
            {
                stream.cancelDecoding = false;
            }
            else
            {
                stream.nextBuffer = decodeBuffer;
                if (hasMoreFrames)
                {
                    stream.frameNumberNext = decoder->getCurrentFrameNumber() - 1; // Points to frame after this
                }
                else
                {
                    stream.frameNumberNext = 1;
                }
                stream.hasMoreFramesAfterNext = hasMoreFrames;

                // Lower decode flag
                stream.doDecodeNewFrame = false;
            }

            // Release the mutex
            MUTEX_UNLOCK(mutexBuffers);
        }
    }

    void getVideoInformation(const Handle handle, touchgfx::VideoInformation* data)
    {
        assert(handle < no_streams);
        mjpegDecoders[handle]->getVideoInfo(data);
    }

    bool getIsPlaying(const Handle handle)
    {
        assert(handle < no_streams);
        Stream& stream = streams[handle];
        return stream.isPlaying;
    }

    void setFrameRateCompensation(bool allow)
    {
        allowSkipFrames = allow;
    }

private:
    class Stream
    {
    public:
        Stream() : frameCount(0), frameNumberNext(0), frameNumberShown(0), tickCount(0),
            frame_rate_video(0), frame_rate_ticks(0),
            seek_to_frame(0), skip_frames(0),
            currentBuffer(0), nextBuffer(0), bufferA(0), bufferB(0),
            isActive(false), isPlaying(false),
            doDecodeNewFrame(false), cancelDecoding(false),
            hasMoreFramesAfterNext(false), repeat(true), isStopped(false)
        {}
        uint32_t frameCount;         // Video frame count since play/speed change
        uint32_t frameNumberNext;    // Next Video frame number (if any)
        uint32_t frameNumberShown;   // Shown Video frame number
        uint32_t tickCount;          // UI frames since play
        uint32_t frame_rate_video;   // Ratio of frames wanted counter
        uint32_t frame_rate_ticks;   // Ratio of frames wanted divider
        uint32_t seek_to_frame;      // Requested next frame number
        uint32_t skip_frames;        // Number of frames to skip to keep frame rate
        uint8_t* currentBuffer;      // Current Video frame, used for drawing
        uint8_t* nextBuffer;         // Already decode next video frame, or zero
        uint8_t* bufferA;            // One buffer allocated for this stream
        uint8_t* bufferB;            // Another buffer allocated for this stream
        bool isActive;
        bool isPlaying;
        bool doDecodeNewFrame;
        bool cancelDecoding;
        bool hasMoreFramesAfterNext;
        bool repeat;
        bool isStopped;
    };

    enum
    {
        NO_STREAM = 0xFFFF
    };

    MJPEGDecoder* mjpegDecoders[no_streams];
    Stream streams[no_streams];
    uint8_t* bufferRGB;
    size_t sizeBufferRGB;        // Size in Bytes
    uint8_t* topBufferRGB;       // Pointer to unused memory in buffer
    bool allowSkipFrames;

    SEM_TYPE semDecode;          // Post by UI, wait by Decoder thread
    MUTEX_TYPE mutexBuffers;     // Mutual exclusion of the video buffers and stream data

    /* return true, if new video frame should be decoded for the next tick (keep video decode framerate low) */
    bool decodeForNextTick(Stream& stream)
    {
        // Running in UI thread

        // Compare tickCount/frameCount to frame_rate_ticks/frame_rate_video
        if ((stream.tickCount * stream.frame_rate_video) >= (stream.frame_rate_ticks * stream.frameCount))
        {
            if (allowSkipFrames)
            {
                stream.skip_frames = (stream.tickCount * stream.frame_rate_video - stream.frame_rate_ticks * stream.frameCount) / stream.frame_rate_ticks;
                if (stream.skip_frames > 0)
                {
                    stream.skip_frames--;
                }
            }
            return true;
        }
        return false;
    }

    Handle getFreeHandle()
    {
        // Running in UI thread

        for (uint32_t i = 0; i < no_streams; i++)
        {
            if (streams[i].isActive == false)
            {
                // Reset stream parameters
                streams[i] = Stream();

                return static_cast<VideoController::Handle>(i);
            }
        }

        assert(0 && "Unable to find free video stream handle!");
        return static_cast<VideoController::Handle>(0);
    }

    uint32_t getStreamIndexToDecode()
    {
        for (uint32_t i = 0; i < no_streams; i++)
        {
            Stream& stream = streams[i];
            if (stream.doDecodeNewFrame) // Marked by UI for decoding
            {
                return i;
            }
        }
        return NO_STREAM;
    }

    void clearState(const Handle handle)
    {
        // Stop playing, and clear next buffer if any, cancel ongoing decoding
        setCommand(handle, STOP, 0);

        MUTEX_LOCK(mutexBuffers);

        Stream& stream = streams[handle];
        if (stream.nextBuffer != 0)
        {
            // Ignore any decoded buffer
            stream.nextBuffer = 0;
        }
        stream.cancelDecoding = true;
        stream.isPlaying = false;

        MUTEX_UNLOCK(mutexBuffers);
    }

};

#endif // TOUCHGFX_BUFFERPOOLVIDEOCONTROLLER_HPP
