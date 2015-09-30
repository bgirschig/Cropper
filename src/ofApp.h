#pragma once

#include "ofMain.h"
#include "Cropper.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
    
        void setMode(int mode);
    
        Cropper camCropper;
        Cropper artCropper;
        int currentMode;
    
        // simulation of detection
        ofPoint detectedPos;
        ofPoint normDetectedPos;
    
        // simulation of cam settings
        ofRectangle cam;
};
