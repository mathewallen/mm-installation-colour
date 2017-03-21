#pragma once

#include "Particle.h"

#define NUM_PARTICLES 3000

class ParticleBall {
public:

	Particle particles[NUM_PARTICLES];

	ParticleBall() {
		for (int i = 0; i < NUM_PARTICLES; i++) {
			float theta = ofRandom(0, TWO_PI);
			float u = ofRandom(-1, 1);
			particles[i] = Particle(theta, u);
		}
	}

	void setUpParticles() {
		for (int i = 0; i < NUM_PARTICLES; i++) {
			particles[i].setUpMe();
		}
	}

	void update(float load, float humanload) {
		for (int i = 0; i < NUM_PARTICLES; i++) {
			particles[i].update(load, humanload);
		}
	}

	void draw() {

		ofSetColor(255, 255, 255, 50);
		for (int i = 0; i < NUM_PARTICLES; i++) {
			particles[i].draw();
		}
	}
};

