//  Cropper.h
//  cropperApp
//
//  Created by bastien girschig on 23/09/2015.
//
//

#ifndef __cropperApp__Cropper__
#define __cropperApp__Cropper__

#include "ofMain.h"


class Cropper{
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
    
        // fitmodes
        enum FitMode{
            FILL,
            FIT,
            STRETCH
        };
    
    
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
    
        void drawDebug();
};

#endif /* defined(__cropperApp__Cropper__) */
