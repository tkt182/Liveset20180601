#pragma once

#include "ofMain.h"
#include "Fireworks.h"
#include "Particles.h"
#include "Lines.h"
#include "VectorField.h"
#include "RectLines.h"
#include "Sector.h"
#include "ParticleLines.h"
#include "WalkThrough.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
#include "ofxFft.h"
#include "ofxProcessFFT.h"

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
    
    void plot(vector<float>& buffer, float scale, float offset);
    void audioReceived(float* input, int bufferSize, int nChannels);
    
    

private:
    vector<shared_ptr<ObjBase>> objs;
    
    ofParameter<float> dt;
    ofEasyCam cam;
    
    ofxOscReceiver receiver;
    string instlMsg;
    
    ofFbo          finalFbo;
    ofxPostGlitch  myGlitch;
    bool toggleGlitch, toggleNoise, toggleShaker;
    bool stoggleGlitch;
    bool vectorFieldShow, walkThroughShow;
    int frameCounter, frameCounter2, frameCounter3;
    int sframeCounter;

    int plotHeight, bufferSize;
    
    //ofxFft* fft;
    ProcessFFT fft;
    
    ofMutex soundMutex;
    vector<float> drawBins, middleBins, audioBins;
    bool rms_flag;
    float threshold;
    float minimumThreshold;
    float decayRate;
    
    
};
