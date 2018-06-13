#pragma once

#include "ofMain.h"
#include "Fireworks.h"
#include "Particles.h"
#include "Lines.h"
#include "VectorField.h"
#include "RectLines.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"

#define PORT 60000

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

private:
    vector<shared_ptr<ObjBase>> objs;
    
    ofParameter<float> dt;
    ofEasyCam cam;
    
    ofxOscReceiver receiver;
    string instlMsg;
    
    ofFbo          finalFbo;
    ofxPostGlitch  myGlitch;
    bool toggleGlitch;
    int frameCounter;

};
