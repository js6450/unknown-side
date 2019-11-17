#include "ofApp.h"

/*

handshake-01: file cutoff is -180, xoffset is 75, -75

hug-01: file cuttof is -180, xoffset is 75, -75

pat-02: file cuttof is none, xoffset is 45, -45

z coordinate ranges between 1500 - 1700
*/

//--------------------------------------------------------------
void ofApp::setup(){

	ofBuffer buffer = ofBufferFromFile("kiss-01.txt");


	for (auto line : buffer.getLines()) {
		bodies.push_back(line);
	}


}

//--------------------------------------------------------------
void ofApp::update(){
	if (bodyIndex < bodies.size() - 1) {
		bodyIndex++;
	}
	else {
		bodyIndex = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(255, 30);
	
	if (bodies.size() > 0) {


		auto joints = ofSplitString(bodies[bodyIndex], ";");


		for (auto joint : joints) {

			auto pos = ofSplitString(joint, ",");

			if (pos.size() == 3) {

				float x = ofMap(ofToInt(pos[0]), -ofGetWidth() * 2, ofGetWidth() * 2, 0, ofGetWidth()) - 45;
				float y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, 0, ofGetHeight());
				float z = ofMap(ofToFloat(pos[2]), 1500, 1700, 70, 30);

				/*
				cout << x << endl;
				cout << ", " << endl;
				cout << y << endl;
				*/

				ofSetColor(0, z);
				ofDrawEllipse(x, y, z, z);



				x = ofMap(ofToInt(pos[0]), ofGetWidth() * 2, -ofGetWidth() * 2, 0, ofGetWidth()) + 45;
				y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, 0, ofGetHeight());
				z = ofMap(ofToFloat(pos[2]), 1500, 1700, 70, 30);

				/*
				cout << x << endl;
				cout << ", " << endl;
				cout << y << endl;
				*/

				ofSetColor(0, z);
				ofDrawEllipse(x, y, z, z);
			}

		}

	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
