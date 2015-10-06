#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // arbitrary cam settings
    cam.height = 768; cam.width = 1024;
    detectedPos.set(1024/2,768/2);
    
    setMode(0);
    
    // Enable debugs
    camCropper.debug = true;
    artCropper.debug = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    normDetectedPos.set(detectedPos.x/cam.width,detectedPos.y/cam.height);
}

//--------------------------------------------------------------
void ofApp::draw(){
    camCropper.begin();
    ofFill(); ofSetColor(255, 0, 0); ofCircle(detectedPos.x, detectedPos.y, 50);
    camCropper.end();
    camCropper.draw();
    
    artCropper.begin();
    ofFill(); ofSetColor(0, 0, 255); ofCircle(detectedPos.x,detectedPos.y, 50);
    artCropper.end();
    artCropper.draw();
}


void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT) detectedPos.x -= 20;
    else if(key == OF_KEY_RIGHT) detectedPos.x+= 20;
    else if(key == OF_KEY_UP) detectedPos.y-=20;
    else if(key == OF_KEY_DOWN) detectedPos.y+=20;
    
    else if(key == ' '){
        currentMode = (currentMode+1)%5;
        setMode(currentMode);
    }
}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}

void ofApp::setMode(int mode){
    switch (currentMode) {
        case 0: // split mode
            camCropper.setTarget(0, 0, ofGetWidth()/2, ofGetHeight());
            artCropper.setTarget(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
            camCropper.setSource(0, 0, cam.width, cam.height); // full camera image
            artCropper.setSource(0, 0, cam.width, cam.height); // normalised space
            break;
        case 1: // overlap mode
            camCropper.setTarget(0, 0, ofGetWidth()/2, ofGetHeight());
            artCropper.setTarget(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
            camCropper.setSource(0, 0,cam.width/2,cam.height); // left half of camera
            artCropper.setSource(cam.width/2, 0, cam.width/2, cam.height); // right half of draw space
            break;
        case 2: // hangouts mode
            camCropper.setTarget(ofGetWidth()-200, ofGetHeight()-180, 180, 160);
            artCropper.setTarget(0, 0, ofGetWidth(), ofGetHeight());
            camCropper.setSource(0, 0,cam.width,cam.height);
            artCropper.setSource(0, 0, cam.width, cam.height);
            break;
        case 3: // full art mode
            camCropper.setTarget(-1, -1, 1, 1); // hide cam
            artCropper.setTarget(0, 0, ofGetWidth(), ofGetHeight());
            artCropper.setSource(0, 0, cam.width, cam.height);
            break;
        case 4: // full art on vertical screen
            camCropper.setTarget(-1, -1, 1, 1); // hide cam
            artCropper.setTarget(0, 0, ofGetWidth()/2, ofGetHeight());
            artCropper.setSource(cam.width/4, 0, cam.width/2, cam.height);
        default:
            break;
    }
}