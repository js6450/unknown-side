#pragma once

#include "ofMain.h"
#include "ofxAzureKinect.h"
#include "ofxGui.h"
#include "Blob.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void exit();

		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

//		vector<string> bodies;
        vector< vector<string> > actions;
    
        vector<string> firstBody;
        vector<string> secondBody;

		int bodyIndex = 0;
        int realSpeed = 1;
        int realIndex = 0;
        int currentBody = 0;
        float onemeter = 1280 / 4;
    
        int bufferCount = 0;

		glm::vec2 spineOne;
		glm::vec2 spineTwo;
		glm::vec2 prevSpineOne = glm::vec2(0, 0);
		glm::vec2 prevSpineTwo = glm::vec2(1280, 0);

		float spineOneX = 0;
		float spineOneY = 0;
		float spineTwoX = 0;
		float spineTwoY = 0;
    
        float prevOne;
        float prevTwo;
        float moveOne;
        float moveTwo;
        ofParameter<float> bodyOne;
        ofParameter<float> bodyTwo;
        ofParameter<float> dist;
        ofParameter<bool> showAni;
        ofParameter<bool> triggerAni;
        ofParameter<bool> autoAni;
    
        ofxPanel gui;
    
        void drawBody(int i);

        ofImage canvas;
        std::vector<Blob> blobs;
    
        ofShader shader;

		int totalBodies = 0;

private:
	ofxAzureKinect::Device kinectDevice;
};
