#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    //ofSetupOpenGL(1024,768,OF_FULLSCREEN);
    //ofSetupOpenGL(1920,1080,OF_FULLSCREEN);
    //ofSetupOpenGL(1280,720,OF_WINDOW);
    //ofSetupOpenGL(1280,720,OF_FULLSCREEN);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    //ofGLFWWindowSettings settings;
    //settings.setGLVersion(3,2);
    //settings.width = 1024;
    //settings.height = 768;
    //ofCreateWindow(settings);
    ofRunApp(new ofApp());

}
