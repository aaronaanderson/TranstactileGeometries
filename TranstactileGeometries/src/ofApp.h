#pragma once

#include "ofMain.h"
#include "Geometry.h"
#include "ofxATK.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void audioOut(float* buffer, int bufferSize, int nChannels);

private:
	Geometry geometry;
	ofEasyCam camera;

	ofxFloatSlider w;
	ofxToggle applyWindow;
	ofxPanel gui;
		
};
