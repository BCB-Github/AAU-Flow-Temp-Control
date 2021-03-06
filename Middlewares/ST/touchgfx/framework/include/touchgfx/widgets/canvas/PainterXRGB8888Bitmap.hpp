/******************************************************************************
* Copyright (c) 2018(-2022) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.19.1 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/widgets/canvas/PainterXRGB8888Bitmap.hpp
 *
 * Declares the touchgfx::PainterXRGB8888Bitmap class.
 */
#ifndef TOUCHGFX_PAINTERXRGB8888BITMAP_HPP
#define TOUCHGFX_PAINTERXRGB8888BITMAP_HPP

#include <touchgfx/Bitmap.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/canvas/AbstractPainterARGB8888.hpp>

namespace touchgfx
{
/**
 * PainterXRGB8888Bitmap will take the color for a given point in the shape from a bitmap.
 * Please be aware, the the bitmap is used by the CanvasWidgetRenderer (not Shape), so
 * any rotation you might specify for a Canvas Widget (e.g. Shape) is not applied to the
 * bitmap as CWR is not aware of this rotation.
 *
 * @see AbstractPainter
 */
class PainterXRGB8888Bitmap : public AbstractPainterARGB8888
{
public:
    /**
     * Initializes a new instance of the PainterXRGB8888Bitmap class.
     *
     * @param  bmp   (Optional) The bitmap, default is #BITMAP_INVALID.
     */
    PainterXRGB8888Bitmap(const Bitmap& bmp = Bitmap(BITMAP_INVALID))
        : AbstractPainterARGB8888(),
          bitmapARGB8888Pointer(0), bitmapRGB888Pointer(0), bitmapRGB565Pointer(0),
          bitmap(), bitmapRectToFrameBuffer(),
          xOffset(0), yOffset(0), isTiled(false)
    {
        setBitmap(bmp);
    }

    /**
     * Sets a bitmap to be used when drawing the CanvasWidget.
     *
     * @param  bmp The bitmap.
     */
    void setBitmap(const Bitmap& bmp);

    /** @copydoc PainterRGB565Bitmap::setTiled() */
    virtual void setTiled(bool tiled);

    /** @copydoc PainterRGB565Bitmap::setOffset() */
    virtual void setOffset(int16_t x, int16_t y);

    virtual void render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers);

protected:
    virtual bool renderInit();

    const uint32_t* bitmapARGB8888Pointer; ///< Pointer to the bitmap (ARGB8888)
    const uint8_t* bitmapRGB888Pointer;    ///< Pointer to the bitmap (RGB888)
    const uint16_t* bitmapRGB565Pointer;   ///< Pointer to the bitmap (RGB565)

    Bitmap bitmap;                ///< The bitmap to be used when painting
    Rect bitmapRectToFrameBuffer; ///< Bitmap rectangle translated to framebuffer coordinates

    int16_t xOffset; ///< The x offset of the bitmap
    int16_t yOffset; ///< The y offset of the bitmap
    bool isTiled;    ///< True if bitmap should be tiled, false if not
};

} // namespace touchgfx

#endif // TOUCHGFX_PAINTERXRGB8888BITMAP_HPP
