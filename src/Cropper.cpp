//
//  Cropper.cpp
//  cropperApp
//
//  Created by bastien girschig on 23/09/2015.
//
//

#include "Cropper.h"

Cropper::Cropper(){
    // ??
    // canvasSettings.internalformat = GL_RGBA16F;
    
    // default settings
    canvasSettings.width = 100;
    canvasSettings.height = 100;
    setSource(0, 0, 100, 100);
    setTarget(0, 0, 100, 100);
    debug = false;
    fitMode = FILL;
}

void Cropper::set(float sx, float sy, float sw, float sh, float tx, float ty, float tw, float th){
    source.set(sx, sy, sw, sh);
    target.set(tx, ty, tw, th);
}

void Cropper::begin(){
    // setting up the canvas size to target width end height
    if(canvasSettings.width != target.width || canvasSettings.height != target.height){
        canvasSettings.width = target.width; canvasSettings.height = target.height;
        canvas.allocate(canvasSettings);
    }
    
    // begin draw on canvas and clear its previous contents
    canvas.begin();
    ofPushMatrix();
    ofClear(255, 255, 255);
    
    // get to the center of the cropper area
    ofTranslate(target.width/2, target.height/2);
    
    // scale to fit/fill or stretch (depending on the fit mode)
    if(fitMode == FILL){
        float scale;
        if(source.getAspectRatio() > target.getAspectRatio()) scale = (float)target.height / source.height;
        else scale = (float)target.width / source.width;
        ofScale(scale, scale);
    }
    else if(fitMode == FIT){
        float scale;
        if(source.getAspectRatio() > target.getAspectRatio()) scale = target.width / source.width;
        else scale = target.height / source.height;
        ofScale(scale, scale);
    }
    else if (fitMode == STRETCH){
        ofScale(target.width/source.width, target.height/source.height);
    }
    
    // center the source rectangle inside the cropper
    ofTranslate(-source.width/2-source.x, -source.height/2-source.y);
    
}

void Cropper::end(){
    // reset transformations
    ofPopMatrix();

    // draw debug on top of eveything, outside of any transformation
    if(debug) drawDebug();
    
    // end canvas and draw it
    canvas.end();
}
void Cropper::draw(){
    canvas.draw(target.x, target.y);
}

void Cropper::drawDebug(){
    string debugInfo;
    
    debugInfo += "fitmode: ";
    if(fitMode==FIT) debugInfo += "Fit";
    else if(fitMode==STRETCH) debugInfo += "Stretch";
    else if(fitMode==FILL) debugInfo += "Fill";
    debugInfo += "\n\n";
    debugInfo += "source position: " + ofToString(source.x) + ", " +ofToString(source.y)+"\n";
    debugInfo += "source shape: " + ofToString(source.width) + ", " +ofToString(source.height);
    debugInfo += "\n\n";
    debugInfo += "cropper position: " + ofToString(target.x) + ", " +ofToString(target.y)+"\n";
    debugInfo += "cropper shape: " + ofToString(target.width) + ", " +ofToString(target.height);

    ofSetColor(255);
    ofPushStyle();
    ofEnableAlphaBlending();
    
    // fill cropper area with translucent color
    ofSetColor(255, 0, 0, 80); ofFill(); ofRect(0, 0, target.width, target.height);
    // mark cropper's boundaries
    ofSetColor(255, 0, 0); ofNoFill(); ofRect(0, 0, target.width, target.height);
    // diagonals
    ofLine(0, 0, target.width, target.height);
    ofLine(0, target.height, target.width, 0);
    
    // debug text background
    ofFill(); ofSetColor(255,255,255,180); ofRect(0,0,250,130);
    // debug text
    ofSetColor(0); ofDrawBitmapString(debugInfo, ofPoint(10,18));
    
    ofPopStyle();
}

ofRectangle* Cropper::getSource(){ return &source; }
ofRectangle* Cropper::getTarget(){ return &target; }

void Cropper::setFitMode(FitMode mode){ fitMode = mode;}
Cropper::FitMode Cropper::getFitMode(){ return fitMode; }

// target handlers
void Cropper::setTarget(float x, float y, float w, float h){
    target.set(x, y, w, h);
}
void Cropper::setTargetShape(float w, float h){
    target.width = w;
    target.height = h;
}
void Cropper::setTargetPos(float x, float y){
    target.setPosition(x, y);
}

// source handlers
void Cropper::setSource(float x, float y, float w, float h){
    source.set(x, y, w, h);
}
void Cropper::setSourceShape(float w, float h){
    source.width = w;
    source.height = h;
}
void Cropper::setSourcePos(float x, float y){
    source.setPosition(x, y);
}