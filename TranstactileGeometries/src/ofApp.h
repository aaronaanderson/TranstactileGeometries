#pragma once

#include "ofMain.h"
#include "Geometry.h"
#include "ofxATK.hpp"
#include "ofxGui.h"
#include "Navigator.h"
#include "ofxOsc.h"

#define SAMPLERATE 48000
#define BUFFERSIZE 512
#define PORT 7401



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void audioOut(float* buffer, int bufferSize, int nChannels);

private:
	Navigator* navigator;// (48000, 512, 2, 0);

	Geometry geometry;
	ofEasyCam camera;

	ofxFloatSlider frequency;
	ofxFloatSlider w;
	ofxFloatSlider x;
	ofxFloatSlider y;
	ofxFloatSlider z;

	ofxOscReceiver oscReceiver;

	ofxToggle applyWindow;
	ofxPanel gui;
		
};
