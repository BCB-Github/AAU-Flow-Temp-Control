/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Screen3ViewBase::Screen3ViewBase() :
    flexButtonCallback(this, &Screen3ViewBase::flexButtonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    flexDownVol.setBoxWithBorderPosition(0, 0, 50, 50);
    flexDownVol.setBorderSize(5);
    flexDownVol.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexDownVol.setPosition(25, 86, 50, 50);
    flexDownVol.setAction(flexButtonCallback);

    flexUpVol.setBoxWithBorderPosition(0, 0, 50, 50);
    flexUpVol.setBorderSize(5);
    flexUpVol.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexUpVol.setPosition(25, 14, 50, 50);
    flexUpVol.setAction(flexButtonCallback);

    upInput1.setBoxWithBorderPosition(0, 0, 30, 30);
    upInput1.setBorderSize(5);
    upInput1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    upInput1.setPosition(10, 165, 30, 30);
    upInput1.setAction(flexButtonCallback);

    upInput2.setBoxWithBorderPosition(0, 0, 30, 30);
    upInput2.setBorderSize(5);
    upInput2.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    upInput2.setPosition(40, 165, 30, 30);
    upInput2.setAction(flexButtonCallback);

    upInput3.setBoxWithBorderPosition(0, 0, 30, 30);
    upInput3.setBorderSize(5);
    upInput3.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    upInput3.setPosition(75, 165, 30, 30);
    upInput3.setAction(flexButtonCallback);

    downInput1.setBoxWithBorderPosition(0, 0, 30, 30);
    downInput1.setBorderSize(5);
    downInput1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    downInput1.setPosition(10, 215, 30, 30);
    downInput1.setAction(flexButtonCallback);

    downInput2.setBoxWithBorderPosition(0, 0, 30, 30);
    downInput2.setBorderSize(5);
    downInput2.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    downInput2.setPosition(40, 215, 30, 30);
    downInput2.setAction(flexButtonCallback);

    downInput3.setBoxWithBorderPosition(0, 0, 30, 30);
    downInput3.setBorderSize(5);
    downInput3.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    downInput3.setPosition(75, 215, 30, 30);
    downInput3.setAction(flexButtonCallback);

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    flexButton1.setBoxWithBorderPosition(0, 0, 124, 27);
    flexButton1.setBorderSize(5);
    flexButton1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(1, 68, 135), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton1.setPosition(343, 9, 124, 27);
    flexButton1.setAction(flexButtonCallback);

    textArea1.setXY(360, 13);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_U2DH));

    graphVol.setScale(10);
    graphVol.setPosition(183, 136, 297, 136);
    graphVol.setGraphAreaMargin(0, 20, 0, 0);
    graphVol.setGraphAreaPadding(10, 5, 5, 10);
    graphVol.setGraphRangeY(0, 20);

    graphVolMajorYAxisGrid.setScale(10);
    graphVolMajorYAxisGrid.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    graphVolMajorYAxisGrid.setInterval(4);
    graphVolMajorYAxisGrid.setLineWidth(1);
    graphVol.addGraphElement(graphVolMajorYAxisGrid);

    graphVolMajorYAxisLabel.setScale(10);
    graphVolMajorYAxisLabel.setInterval(4);
    graphVolMajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T___SINGLEUSE_S6BU));
    graphVolMajorYAxisLabel.setColor(touchgfx::Color::getColorFromRGB(6, 9, 10));
    graphVol.addLeftElement(graphVolMajorYAxisLabel);

    graphVolLine1Painter.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    graphVolLine1.setPainter(graphVolLine1Painter);
    graphVolLine1.setLineWidth(2);
    graphVol.addGraphElement(graphVolLine1);

    SPVol.setXY(28, 62);
    SPVol.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    SPVol.setLinespacing(0);
    Unicode::snprintf(SPVolBuffer, SPVOL_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_LERE).getText());
    SPVol.setWildcard(SPVolBuffer);
    SPVol.resizeToCurrentText();
    SPVol.setTypedText(touchgfx::TypedText(T___SINGLEUSE_UR5C));

    upVolImg.setBitmap(touchgfx::Bitmap(BITMAP_UP_ARROW_ID));
    upVolImg.setPosition(25, 14, 50, 50);
    upVolImg.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    downVolImg.setBitmap(touchgfx::Bitmap(BITMAP_DOWN_ARROW_ID));
    downVolImg.setPosition(25, 86, 50, 50);
    downVolImg.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    en3.setXY(87, 92);
    en3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    en3.setLinespacing(0);
    en3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GWT3));

    toggleVol.setBoxWithBorderPosition(0, 0, 30, 30);
    toggleVol.setBorderSize(3);
    toggleVol.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    toggleVol.setBitmaps(Bitmap(BITMAP_DISABLED_ID), Bitmap(BITMAP_DISABLED_ID));
    toggleVol.setBitmapXY(2, 2);
    toggleVol.setPosition(89, 59, 30, 30);
    toggleVol.setAction(flexButtonCallback);

    lim1.setXY(93, 105);
    lim1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    lim1.setLinespacing(0);
    lim1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_UZL2));

    textAreaSP.setXY(11, 0);
    textAreaSP.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaSP.setLinespacing(0);
    textAreaSP.setTypedText(touchgfx::TypedText(T___SINGLEUSE_E467));

    timeETA.setXY(383, 77);
    timeETA.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    timeETA.setLinespacing(0);
    touchgfx::Unicode::snprintf(timeETABuffer1, TIMEETABUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_KDAH).getText());
    timeETA.setWildcard1(timeETABuffer1);
    touchgfx::Unicode::snprintf(timeETABuffer2, TIMEETABUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_UQXR).getText());
    timeETA.setWildcard2(timeETABuffer2);
    timeETA.resizeToCurrentText();
    timeETA.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PDFB));

    textArea5.setXY(199, 77);
    textArea5.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea5.setLinespacing(0);
    textArea5.setTypedText(touchgfx::TypedText(T___SINGLEUSE_6CLK));

    timeElapsed.setXY(383, 49);
    timeElapsed.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    timeElapsed.setLinespacing(0);
    touchgfx::Unicode::snprintf(timeElapsedBuffer1, TIMEELAPSEDBUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_ZNIO).getText());
    timeElapsed.setWildcard1(timeElapsedBuffer1);
    touchgfx::Unicode::snprintf(timeElapsedBuffer2, TIMEELAPSEDBUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_KHKS).getText());
    timeElapsed.setWildcard2(timeElapsedBuffer2);
    timeElapsed.resizeToCurrentText();
    timeElapsed.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PLNT));

    textArea4.setXY(245, 49);
    textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea4.setLinespacing(0);
    textArea4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9ZAK));

    hoursElapsed.setXY(357, 49);
    hoursElapsed.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    hoursElapsed.setLinespacing(0);
    Unicode::snprintf(hoursElapsedBuffer, HOURSELAPSED_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_AKV7).getText());
    hoursElapsed.setWildcard(hoursElapsedBuffer);
    hoursElapsed.resizeToCurrentText();
    hoursElapsed.setTypedText(touchgfx::TypedText(T___SINGLEUSE_BUBU));

    hoursETA.setXY(357, 77);
    hoursETA.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    hoursETA.setLinespacing(0);
    Unicode::snprintf(hoursETABuffer, HOURSETA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_N7PY).getText());
    hoursETA.setWildcard(hoursETABuffer);
    hoursETA.resizeToCurrentText();
    hoursETA.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WTVE));

    textArea6.setXY(223, 108);
    textArea6.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea6.setLinespacing(0);
    textArea6.setTypedText(touchgfx::TypedText(T___SINGLEUSE_M22K));

    currentVol.setXY(357, 108);
    currentVol.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    currentVol.setLinespacing(0);
    Unicode::snprintf(currentVolBuffer, CURRENTVOL_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_FZ8F).getText());
    currentVol.setWildcard(currentVolBuffer);
    currentVol.resizeToCurrentText();
    currentVol.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SJCG));

    upFirstImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_UP_ARROW_ID));
    upFirstImg.setPosition(10, 170, 30, 20);
    upFirstImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    upSecondImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_UP_ARROW_ID));
    upSecondImg.setPosition(40, 170, 30, 20);
    upSecondImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    upThirdImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_UP_ARROW_ID));
    upThirdImg.setPosition(75, 170, 30, 20);
    upThirdImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    downFirstImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_DOWN_ARROW_ID));
    downFirstImg.setPosition(10, 220, 30, 20);
    downFirstImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    downSecondImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_DOWN_ARROW_ID));
    downSecondImg.setPosition(40, 220, 30, 20);
    downSecondImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    downThirdImg.setBitmap(touchgfx::Bitmap(BITMAP_SMALL_DOWN_ARROW_ID));
    downThirdImg.setPosition(75, 220, 30, 20);
    downThirdImg.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);

    textArea7.setXY(5, 151);
    textArea7.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea7.setLinespacing(0);
    textArea7.setTypedText(touchgfx::TypedText(T___SINGLEUSE_0ANE));

    volInput1.setXY(19, 192);
    volInput1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    volInput1.setLinespacing(0);
    Unicode::snprintf(volInput1Buffer, VOLINPUT1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_1VDA).getText());
    volInput1.setWildcard(volInput1Buffer);
    volInput1.resizeToCurrentText();
    volInput1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1DAN));

    volInput2.setXY(49, 192);
    volInput2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    volInput2.setLinespacing(0);
    Unicode::snprintf(volInput2Buffer, VOLINPUT2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_115H).getText());
    volInput2.setWildcard(volInput2Buffer);
    volInput2.resizeToCurrentText();
    volInput2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GP7I));

    volInput3.setXY(84, 192);
    volInput3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    volInput3.setLinespacing(0);
    Unicode::snprintf(volInput3Buffer, VOLINPUT3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_QP9Y).getText());
    volInput3.setWildcard(volInput3Buffer);
    volInput3.resizeToCurrentText();
    volInput3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1APN));

    textArea8.setXY(70, 192);
    textArea8.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea8.setLinespacing(0);
    textArea8.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8K8O));

    applyCalibration.setBoxWithBorderPosition(0, 0, 30, 30);
    applyCalibration.setBorderSize(3);
    applyCalibration.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    applyCalibration.setBitmaps(Bitmap(BITMAP_DISABLED_ID), Bitmap(BITMAP_DISABLED_ID));
    applyCalibration.setBitmapXY(2, 2);
    applyCalibration.setPosition(119, 185, 30, 30);
    applyCalibration.setAction(flexButtonCallback);

    textArea9.setXY(120, 218);
    textArea9.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea9.setLinespacing(0);
    textArea9.setTypedText(touchgfx::TypedText(T___SINGLEUSE_VO46));

    textArea9_1.setXY(109, 233);
    textArea9_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea9_1.setLinespacing(0);
    textArea9_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5WSV));

    calibrationFactor.setXY(3, 252);
    calibrationFactor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    calibrationFactor.setLinespacing(0);
    Unicode::snprintf(calibrationFactorBuffer, CALIBRATIONFACTOR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_U4W4).getText());
    calibrationFactor.setWildcard(calibrationFactorBuffer);
    calibrationFactor.resizeToCurrentText();
    calibrationFactor.setTypedText(touchgfx::TypedText(T___SINGLEUSE_TW7T));

    add(__background);
    add(flexDownVol);
    add(flexUpVol);
    add(upInput1);
    add(upInput2);
    add(upInput3);
    add(downInput1);
    add(downInput2);
    add(downInput3);
    add(box1);
    add(flexButton1);
    add(textArea1);
    add(graphVol);
    add(SPVol);
    add(upVolImg);
    add(downVolImg);
    add(en3);
    add(toggleVol);
    add(lim1);
    add(textAreaSP);
    add(timeETA);
    add(textArea5);
    add(timeElapsed);
    add(textArea4);
    add(hoursElapsed);
    add(hoursETA);
    add(textArea6);
    add(currentVol);
    add(upFirstImg);
    add(upSecondImg);
    add(upThirdImg);
    add(downFirstImg);
    add(downSecondImg);
    add(downThirdImg);
    add(textArea7);
    add(volInput1);
    add(volInput2);
    add(volInput3);
    add(textArea8);
    add(applyCalibration);
    add(textArea9);
    add(textArea9_1);
    add(calibrationFactor);
}

void Screen3ViewBase::setupScreen()
{

}

void Screen3ViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexDownVol)
    {
        //clickVolDown
        //When flexDownVol clicked call virtual function
        //Call decrementVol
        decrementVol();
    }
    else if (&src == &flexUpVol)
    {
        //clickVolUp
        //When flexUpVol clicked call virtual function
        //Call incrementVol
        incrementVol();
    }
    else if (&src == &upInput1)
    {
        //upInput1
        //When upInput1 clicked call virtual function
        //Call incrementDigit1
        incrementDigit1();
    }
    else if (&src == &upInput2)
    {
        //upInput2
        //When upInput2 clicked call virtual function
        //Call incrementDigit2
        incrementDigit2();
    }
    else if (&src == &upInput3)
    {
        //upInput3
        //When upInput3 clicked call virtual function
        //Call incrementDigit3
        incrementDigit3();
    }
    else if (&src == &downInput1)
    {
        //downInput1
        //When downInput1 clicked call virtual function
        //Call decrementDigit1
        decrementDigit1();
    }
    else if (&src == &downInput2)
    {
        //downInput2
        //When downInput2 clicked call virtual function
        //Call decrementDigit2
        decrementDigit2();
    }
    else if (&src == &downInput3)
    {
        //downInput3
        //When downInput3 clicked call virtual function
        //Call decrementDigit3
        decrementDigit3();
    }
    else if (&src == &flexButton1)
    {
        //Interaction1
        //When flexButton1 clicked change screen to Screen1
        //Go to Screen1 with no screen transition
        application().gotoScreen1ScreenNoTransition();
    }
    else if (&src == &toggleVol)
    {
        //toggleVol
        //When toggleVol clicked call virtual function
        //Call limitVol
        limitVol();
    }
    else if (&src == &applyCalibration)
    {
        //applyCorrection
        //When applyCalibration clicked call virtual function
        //Call enableCorrection
        enableCorrection();
    }
}
