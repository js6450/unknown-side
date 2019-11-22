#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Blob.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
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

		vector<string> bodies;
        vector< vector<string> > actions;

		int bodyIndex = 0;
        int realSpeed = 1;
        int realIndex = 0;
        int currentBody = 0;
        float onemeter = 1280 / 4;
    
        int bufferCount = 0;
    
        float prevOne;
        float prevTwo;
        float moveOne;
        float moveTwo;
        ofParameter<float> bodyOne;
        ofParameter<float> bodyTwo;
        ofParameter<float> dist;
        ofParameter<bool> showShadow;
        ofParameter<bool> triggerAni;
        ofParameter<bool> autoAni;
    
        ofxPanel gui;
    
        void drawBody(int i);
        void drawReal(int i);
        
        ofImage canvas;
        std::vector<Blob> blobs;
    
        ofShader shader;
};
