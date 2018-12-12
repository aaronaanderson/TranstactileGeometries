#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	

	camera.setGlobalPosition(ofVec3f(0, -30, 20));
	camera.setTarget(ofVec3f(0, 0, 0));
	camera.setDistance(210);
	camera.setNearClip(1.0f);

	gui.setup();
	gui.add(frequency.setup("Frequency", 2, 0.1, 80));
	gui.add(w.setup("W", 0.0, -1.0, 1.0));
	gui.add(x.setup("X", 0.0, -1.0, 1.0));
	gui.add(y.setup("Y", 0.0, -1.0, 1.0));
	gui.add(z.setup("Z", 0.0, -1.0, 1.0));

	oscReceiver.setup(PORT);

	ofEnableDepthTest();
	ofSetFullscreen(true);

	navigator = new Navigator(SAMPLERATE, BUFFERSIZE, 2, 1);

	ofSoundStreamSetup(2, 0, SAMPLERATE, BUFFERSIZE, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	navigator->setFrequency(frequency);

	while (oscReceiver.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);

		if (m.getAddress() == "/TrackerOne/Location") {
			x = m.getArgAsFloat(0);
			w = m.getArgAsFloat(1);
			z = m.getArgAsFloat(2);
		}
	}
	
	geometry.setApplyWindow(applyWindow);
	//w = -1.0f * cos(ofGetFrameNum() * 0.01 );
	//if (w >= 0.999) {ofExit();}
	geometry.update(w);
	ofVec3f location = { x,y,w };
	ofQuaternion orientation;
	navigator->update(location, orientation);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	camera.begin();
	ofEnableDepthTest();
	geometry.renderSlice(1.0);
	camera.end(); 
	ofDisableDepthTest();
	
	//ofSaveFrame();
	gui.draw();
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {

	navigator->process(buffer);
}
//--------------------------------------------------------------
void ofApp::exit() {
	ofSoundStreamClose();
	delete navigator;
}