

#include "Geometry.h"

Geometry::Geometry() {
	slice.setMode(OF_PRIMITIVE_TRIANGLES);
	slice.enableIndices();
	slice.enableColors();

	initializeSlice(4);

}


void Geometry::update(float w) {
	calculateSlice(w);
}

void Geometry::renderSlice(float w = 22) {
	slice.draw();
}

void Geometry::initializeSlice(float w = 22) {
	for (int i = 0; i < resolution; ++i) {
		float scaledXValue = (i * 2 / float(resolution - 1)) - 1.0f;//scale 0 - resolution-1 to -1,1
		for (int j = 0; j < resolution; ++j) {
			float scaledYValue = (j * 2 / float(resolution - 1)) - 1.0f;//scale 0 - resolution-1 to -1,1
			int index = i * resolution + j;//map 2D to linear array

			float z = cos((sin(4 * scaledXValue*scaledYValue)) / (pow(scaledXValue, 2) + pow(scaledYValue, 3)));;//depth at x, y, w

			ofColor sliceColor = { 100, 180, 180 };
			float colorScale = (z + 1.0f)*0.5;
			slice.addVertex(ofVec3f((scaledXValue * 100), (scaledYValue * 100), z * 20));
			slice.addColor(sliceColor * colorScale);

		}
	}
	//stitch vertices
	for (int i = 0; i < resolution-1; ++i) {
		for (int j = 0; j < resolution-1; ++j) {
			//bottom left triangle
			slice.addIndex(i + j * resolution);
			slice.addIndex((i + 1) + j * resolution);
			slice.addIndex(i + (j + 1) * resolution);

			//top right triangle
			slice.addIndex((i + 1) + j * resolution);
			slice.addIndex((i + 1) + (j +1 ) * resolution);
			slice.addIndex(i + (j + 1) * resolution);
		}
	}
}

void Geometry::calculateSlice(float w) {
	float scaledWValue = ((1.0f-fabsf(w)) * 12) ;//explained in notes.
	for (int i = 0; i < resolution; ++i) {
		float scaledXValue = (i * 2 / float(resolution - 1)) - 1.0f;//scale 0 - resolution-1 to -1,1
		for (int j = 0; j < resolution; ++j) {
			float scaledYValue = (j * 2 / float(resolution - 1)) - 1.0f;//scale 0 - resolution-1 to -1,1
			int index = i * resolution + j;//map 2D to linear array
			
			float z = cos((sin(scaledWValue * scaledXValue*scaledYValue)) / (pow(scaledXValue, 2) + pow(scaledYValue, 3)));;//depth at x, y, w
			float windowValue = tukeyWindow(w, scaledXValue, scaledYValue);
			if (applyWindow) {
				z *= windowValue;
			}
			
			float colorScale = (z + 1.0f)*0.5;
			ofColor sliceColor = { 100, 180, 180, (windowValue) * 255 };
			slice.setVertex(index, ofVec3f((scaledXValue * 100), (scaledYValue * 100), (z * 20) + (w*80)));
			slice.setColor(index, sliceColor * colorScale);

		}
	}
}

float Geometry::tukeyWindow(float w, float x, float y) {
	float scalingFactor = 1.0f;
	//ignore W for now --TODO - provide w in normalized range to make this accurate

	float distanceFromCenter = sqrtf((w*w)+(x*x) + (y*y));
	if (distanceFromCenter > 0.9375) {//if distance from center > 0.5
		scalingFactor = cos((std::min(distanceFromCenter, 1.0f) - 0.9375) * TWO_PI * 4);
		/*
		shortest range from outside of center is 0.5 while remaing in the cubic bounds. 
		this needs to be scaled up from 0 to 0.5 to 0 to PI/2. To do this, simply multiply
		by pi
		*/
	}

	return scalingFactor;
}