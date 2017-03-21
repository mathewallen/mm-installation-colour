#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	humantemp = 0;
	humanload = 0;

	bSendSerialMessage = true;
	ofBackground(122, 122, 122);
	ofSetLogLevel(OF_LOG_VERBOSE);

	font.loadFont("DIN.otf", 20);

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	int baud = 9600;
	serial.setup("COM3", baud); // windows example

	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);

	ball.setUpParticles();
	datagrabber.getSource(); //Defines the name of the .CSV file to load from the current date to match OpenHardware naming convention
}

//--------------------------------------------------------------
void ofApp::update(){



		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to
		// read as much as we can in groups of three...

		nTimesRead = 0;
		nBytesRead = 0;
		int nRead = 0;  // a temp variable to keep count per read

		unsigned char bytesReturned[3];

		memset(bytesReadString, 0, 20);
		memset(bytesReturned, 0, 3);

		while ((nRead = serial.readBytes(bytesReturned, 3)) > 0){
			nTimesRead++;
			nBytesRead = nRead;
		};

		memcpy(bytesReadString, bytesReturned, 3);

		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();


	temp = datagrabber.readProcess(0); //Reads CSV file with data
	load = datagrabber.readProcess(1);



	if (strncmp(bytesReadString, "A", 1) == 0){
		humantemp = -1;
	}
	else if (strncmp(bytesReadString, "C", 1) == 0){
		humantemp = 1;
	}
	else {
		int checkHumanLoad;
		string tempHumanLoad = ofToString(bytesReadString);
		istringstream(tempHumanLoad) >> checkHumanLoad;
		if (checkHumanLoad > 9 && checkHumanLoad < 100) {
			humanload = checkHumanLoad;
		}
	}


	ball.update(load,humanload);	//Moves the balls

}

//--------------------------------------------------------------
void ofApp::draw(){

	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		ofSetColor(0);
	}
	else {
		ofSetColor(220);
	}
	string msg;

	msg += "read: " + ofToString(bytesReadString) + "\n";
	msg += "Runtime " + ofToString(readTime, 3) + "\n";
	msg += "CPU LOAD " + ofToString(load) + "\n";
	msg += "CPU TEMP " + ofToString(temp) + "\n";
	msg += "HUMAN LOAD " + ofToString(humanload) + "\n";
	msg += "HUMAN TEMP " + ofToString(humantemp) + "\n";
	font.drawString(msg, 50, 100);

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ball.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

