#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	

	camera.setGlobalPosition(ofVec3f(0, -30, 20));
	camera.setTarget(ofVec3f(0, 0, 0));
	camera.setDistance(210);
	camera.setNearClip(1.0f);

	gui.setup();
	gui.add(w.setup("W", 0.0, -1.0, 1.0));
	gui.add(applyWindow.setup("ApplyWindow", true));

	ofEnableDepthTest();
	ofSetFullscreen(true);
	ofSoundStreamSetup(2, 0, 48000, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	geometry.setApplyWindow(applyWindow);
	w = -1.0f * cos(ofGetFrameNum() * 0.01 );
	if (w >= 0.999) {ofExit();}
	geometry.update(w);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	camera.begin();
	ofEnableDepthTest();
	geometry.renderSlice(1.0);
	camera.end(); 
	ofDisableDepthTest();
	ofSaveFrame();
	gui.draw();
}

void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {

}

void ofApp::exit() {
	ofSoundStreamClose();
}