#pragma once

#include "ofMain.h"

class Geometry {

public:
	Geometry();

	void update(float w);
	void renderSlice(float w);
	void setApplyWindow(bool applyWindow) {
		this->applyWindow = applyWindow;
	}

private:

	void initializeSlice(float w);
	void calculateSlice(float w);
	float tukeyWindow(float w,float x,float y);//3D windowing function 

	ofMesh slice;
	static const unsigned resolution = 256;
	float offset = resolution * 0.5;
	bool applyWindow = true;
	
};