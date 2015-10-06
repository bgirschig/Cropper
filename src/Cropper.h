//  Cropper.h
//  cropperApp
//
//  Created by bastien girschig on 23/09/2015.
//
//

// TODO: use matrices instead of succesive transforms and scales.
// save the original one and compute the transformed one when a parameter is modified.

#ifndef __cropperApp__Cropper__
#define __cropperApp__Cropper__

#include "ofMain.h"


class Cropper {
public:
    Cropper();
    
    ofFbo canvas;
    void begin();
    void end();
    void draw();
    
    // set all parameters at once
    void set(float sx, float sy, float sw, float sh, float tx, float ty, float tw, float th);
    
    // target handlers
    void setTarget(float x, float y, float w, float h);
    void setTargetShape(float w, float h);
    void setTargetPos(float x, float y);
    
    // source handlers
    void setSource(float x, float y, float w, float h);
    void setSourceShape(float w, float h);
    void setSourcePos(float x, float y);
    
    // draws debug info if true
    bool debug;
    // clears fbo on begin if true
    bool autoClear;
    // if false, no FBO is used. this only resizes the "contents"
    bool crop;
    
    // fitmodes
    enum FitMode {
        FILL,
        FIT,
        STRETCH
    };
    // align modes
    enum AlignMode{
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };
    AlignMode alignMode;
    
    
    // getters & setters
    ofRectangle* getTarget();
    ofRectangle* getSource();
    void setFitMode(FitMode mode);
    FitMode getFitMode();
    
private:
    ofFbo::Settings canvasSettings;
    ofRectangle source;
    ofRectangle target;
    FitMode fitMode;
    
    void drawDebug(int part);
};

#endif /* defined(__cropperApp__Cropper__) */