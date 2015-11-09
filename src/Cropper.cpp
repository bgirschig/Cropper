//
//  Cropper.cpp
//  cropperApp
//
//  Created by bastien girschig on 23/09/2015.
//
//

#include "Cropper.h"

Cropper::Cropper() {
    // default settings
    canvasSettings.width = 100;
    canvasSettings.height = 100;
    canvasSettings.internalformat = GL_RGBA16F;

    setSource(0, 0, 100, 100);
    setTarget(0, 0, 100, 100);
    
    debug = false;
    autoClear = true;
    crop = true;
    
    fitMode = FILL;
    alignMode = CENTER;
}

void Cropper::set(float sx, float sy, float sw, float sh, float tx, float ty, float tw, float th) {
    source.set(sx, sy, sw, sh);
    target.set(tx, ty, tw, th);
}

void Cropper::begin() {
    // setting up the canvas size to target width and height
    if (crop && (canvasSettings.width != target.width || canvasSettings.height != target.height)) {
        canvasSettings.width = target.width; canvasSettings.height = target.height;
        canvas.allocate(canvasSettings);
    }
    
    // begin draw on canvas and clear its previous contents
    if (crop) canvas.begin();
    ofPushMatrix();
    if (!crop) ofTranslate(target.x, target.y);
    if(autoClear) ofClear(0, 0, 0);
    
    // go to the origin (depending on alignMode)
    if(     alignMode == TOP_LEFT)      ofTranslate(0,                  0);
    else if(alignMode == TOP_CENTER)    ofTranslate(target.width / 2,   0);
    else if(alignMode == TOP_RIGHT)     ofTranslate(target.width,       0);
    else if(alignMode == CENTER_LEFT)   ofTranslate(0,                  target.height / 2);
    else if(alignMode == CENTER)        ofTranslate(target.width / 2,   target.height / 2);
    else if(alignMode == CENTER_RIGHT)  ofTranslate(target.width,       target.height / 2);
    else if(alignMode == BOTTOM_LEFT)   ofTranslate(0,                  target.height);
    else if(alignMode == BOTTOM_CENTER) ofTranslate(target.width / 2,   target.height);
    else if(alignMode == BOTTOM_RIGHT)  ofTranslate(target.width,       target.height);
    
    // scale to fit/fill or stretch (depending on the fit mode)
    if (fitMode == FILL) {
        float scale;
        if (source.getAspectRatio() > target.getAspectRatio()) scale = (float)target.height / source.height;
        else scale = (float)target.width / source.width;
        ofScale(scale, scale);
    }
    else if (fitMode == FIT) {
        float scale;
        if (source.getAspectRatio() > target.getAspectRatio()) scale = target.width / source.width;
        else scale = target.height / source.height;
        ofScale(scale, scale);
    }
    else if (fitMode == STRETCH) {
        ofScale(target.width / source.width, target.height / source.height);
    }
    
    // center the source rectangle inside the cropper
    if(     alignMode == TOP_LEFT)      ofTranslate(-source.x,                      -source.y);
    else if(alignMode == TOP_CENTER)    ofTranslate(-source.width / 2 - source.x,   -source.y);
    else if(alignMode == TOP_RIGHT)     ofTranslate(-source.width - source.x,       -source.y);
    else if(alignMode == CENTER_LEFT)   ofTranslate(-source.x,                      -source.height / 2 - source.y);
    else if(alignMode == CENTER)        ofTranslate(-source.width / 2 - source.x,   -source.height / 2 - source.y);
    else if(alignMode == CENTER_RIGHT)  ofTranslate(-source.width - source.x,       -source.height / 2 - source.y);
    else if(alignMode == BOTTOM_LEFT)   ofTranslate(-source.x,                      -source.height - source.y);
    else if(alignMode == BOTTOM_CENTER) ofTranslate(-source.width / 2 - source.x,   -source.height - source.y);
    else if(alignMode == BOTTOM_RIGHT)  ofTranslate(-source.width - source.x,       -source.height - source.y);
    
}

void Cropper::end() {
    // draw debug part one (using cropper's transformations)
    if (debug) drawDebug(0);
    
    // reset transformations
    ofPopMatrix();
    
    // draw debug part 2 (not using transformations)
    if (debug) drawDebug(1);
    
    // end canvas
    if (crop) canvas.end();
}
void Cropper::draw() {
    if (crop) canvas.draw(target.x, target.y);
    else ofLog(OF_LOG_WARNING) << "cropper: this cropper's crop value is set to false. there is no need for the draw() function";
}

void Cropper::drawDebug(int part) {
    ofSetColor(255);
    ofPushStyle();
    ofEnableAlphaBlending();
    
    if (part == 0) { // to be drawn using the cropper's transformation
        // mark cropper's boundaries and diagonals
        ofSetColor(0, 0, 255); ofNoFill();
        ofDrawRectangle(0, 0, source.width, source.height);
        ofDrawLine(0, 0, source.width, source.height);
        ofDrawLine(0, source.height, source.width, 0);
    }
    else if (part == 1) { // to be drawn without the cropper's transformations
        string debugInfo;
        
        debugInfo += "fitmode: ";
        if (fitMode == FIT) debugInfo += "Fit";
        else if (fitMode == STRETCH) debugInfo += "Stretch";
        else if (fitMode == FILL) debugInfo += "Fill";
        debugInfo += "\n\n";
        debugInfo += "source position: " + ofToString(source.x) + ", " + ofToString(source.y) + "\n";
        debugInfo += "source shape: " + ofToString(source.width) + ", " + ofToString(source.height);
        debugInfo += "\n\n";
        debugInfo += "cropper position: " + ofToString(target.x) + ", " + ofToString(target.y) + "\n";
        debugInfo += "cropper shape: " + ofToString(target.width) + ", " + ofToString(target.height);
        
        // fill cropper area with translucent color
        ofSetColor(255, 0, 0, 20); ofFill(); ofDrawRectangle(0, 0, target.width, target.height);
        // mark cropper's boundaries and diagonals
        ofSetColor(255, 0, 0); ofNoFill();
        ofDrawRectangle(0, 0, target.width, target.height);
        ofDrawLine(0, 0, target.width, target.height);
        ofDrawLine(0, target.height, target.width, 0);
        
        // debug text background
        ofFill(); ofSetColor(255, 255, 255, 180); ofDrawRectangle(0, 0, 250, 130);
        // debug text
        ofSetColor(0); ofDrawBitmapString(debugInfo, ofPoint(10, 18));
    }
    ofPopStyle();
}

ofRectangle* Cropper::getSource() { return &source; }
ofRectangle* Cropper::getTarget() { return &target; }

void Cropper::setFitMode(FitMode mode) { fitMode = mode; }
Cropper::FitMode Cropper::getFitMode() { return fitMode; }

void Cropper::setAlignMode(AlignMode mode){ alignMode = mode; }
Cropper::AlignMode Cropper::getAlignMode(){ return alignMode; }

// target handlers
void Cropper::setTarget(ofRectangle _target){
  target.set(_target);
}
void Cropper::setTarget(float x, float y, float w, float h) {
    target.set(x, y, w, h);
}
void Cropper::setTargetShape(float w, float h) {
    target.width = w;
    target.height = h;
}
void Cropper::setTargetPos(float x, float y) {
    target.setPosition(x, y);
}

// source handlers
void Cropper::setSource(ofRectangle _source){
  source.set(_source);
}
void Cropper::setSource(float x, float y, float w, float h) {
    source.set(x, y, w, h);
}
void Cropper::setSourceShape(float w, float h) {
    source.width = w;
    source.height = h;
}
void Cropper::setSourcePos(float x, float y) {
    source.setPosition(x, y);
}