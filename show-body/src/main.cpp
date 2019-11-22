#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
    
    
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(1280, 720);
    settings.resizable = true;
    settings.decorated = true;
    ofCreateWindow(settings);
    
//    int width = 1280;
//    int height = 720;
//    
//    ofGLFWWindowSettings settings;
//    settings.setGLVersion(3, 2);
//    settings.setSize(width, height);
//    
//    ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
