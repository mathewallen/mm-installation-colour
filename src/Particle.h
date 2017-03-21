#pragma once

#include "ofApp.h"
#include "DataGrabber.h"

class Particle {
public:

	float theta, u;
	float vTheta, vU;
	float x, y, z, radius;
	float iX, iY, iZ;
	float target;
	ofVec3f location;
	ofVec3f velocity;
	ofVec3f heatvelocity;
	ofVec3f hvX, hvY, hvZ;

	Particle(float _theta = 0, float _u = 0) {
		radius = 150;
		theta = _theta;
		u = _u;
		vTheta = 0;
		vU = 0;
	}

	void setUpMe() {
		vTheta += ofRandom(-0.001, 0.001);
		theta += vTheta;

		if (theta<0 || theta>TWO_PI) {
			vTheta *= -1;
		}

		vU += ofRandom(-0.001, 0.001);
		u += vU;

		if (u<-1 || u>1) vU *= -1;

		vU *= 0.95;
		vTheta *= 0.95;

		x = radius*cos(theta)*sqrt(1 - (u*u));
		y = radius*sin(theta)*sqrt(1 - (u*u));
		z = radius*u;
		location.set(x, y, z);

		float midXdirection = 1;
		float midYdirection = 1;
		if (location.x < 0){ hvX.set(-1,0,0); } else {hvX.set(1,0,0);}
		if (location.y < 0){ hvY.set(0,-1,0); } else {hvY.set(0,1,0);}
		if (location.z < 0){ hvY.set(0,0,-1); } else {hvY.set(0,0,1);}

        heatvelocity = hvX + hvY + hvY;

		iX = radius*cos(theta)*sqrt(1 - (u*u));
		iY = radius*sin(theta)*sqrt(1 - (u*u));
		iZ = radius*u;

	}

	void update(float load, float humanload) {
        location = location + heatvelocity;
	}

	void draw() {
		ofPushMatrix();
		ofTranslate(location.x, location.y, location.z);
		ofDrawSphere(6, 6, 1);
		ofPopMatrix();
	}
};
