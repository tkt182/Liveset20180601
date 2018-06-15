#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofHideCursor();
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    finalFbo.allocate(ofGetWidth(), ofGetHeight());
    myGlitch.setup(&finalFbo);
    myGlitch.toggleFx(OFXPOSTGLITCH_GLOW);
    toggleGlitch = false;
    frameCounter = 0;
    
    ofSetFrameRate(30);
    ofBackground(0);
    //ofSetWindowTitle("Insta");
    //ofBackground(0);
    
    receiver.setup(PORT);
    //ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    
    
    shared_ptr<ObjBase> o0(new Fireworks());
    o0->setup();
    objs.push_back(o0);
    
    shared_ptr<ObjBase> o1(new Particles());
    o1->setup();
    objs.push_back(o1);
    
    shared_ptr<ObjBase> o2(new Lines());
    o2->setup();
    objs.push_back(o2);
    
    shared_ptr<ObjBase> o3(new VectorField());
    o3->setup();
    o3->setParam(6, 1);
    objs.push_back(o3);
    
    shared_ptr<ObjBase> o4(new RectLines());
    o4->setup();
    objs.push_back(o4);
    
    shared_ptr<ObjBase> o5(new Sector());
    o5->setup();
    objs.push_back(o5);
    
    shared_ptr<ObjBase> o6(new ParticleLines());
    o6->setup();
    objs.push_back(o6);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        cout << m.getAddress() << endl;
        for(int i = 0; i < m.getNumArgs(); i++){
            cout << m.getArgAsString(i) << endl;
            if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                string instlMsg = m.getArgAsString(i);
                if(instlMsg == "hand"){
                    objs[0]->setParam(1, 1);
                }
                if(instlMsg == "808bd"){
                    objs[1]->setParam(2, 1);
                }
                if(instlMsg == "hh"){
                    objs[2]->setParam(4, 1);
                }
                if(instlMsg == "jazz"){
                    objs[2]->setParam(5, 1);
                }
                if(instlMsg == "glitch"){
                    /*
                    if(!toggleGlitch) {
                        toggleGlitch = true;
                        //myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
                        myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
                    }
                    */
                    string opt = m.getArgAsString(i+2);
                    if(opt == "u" || opt == "i"){
                        objs[4]->setParam(7, 1);
                    }
                }
                if(instlMsg == "u"){
                    objs[4]->setParam(7, 1);
                }
                if(instlMsg == "i"){
                    objs[4]->setParam(7, 1);
                }
                
                if(instlMsg == "808"){
                    objs[3]->setParam(6, 1);
                }
            }
        }
    }
    
    for(int i = 0; i < objs.size(); i++){
        objs[i]->update(dt.get());
        if(toggleGlitch){
            frameCounter++;
            if(frameCounter > 10){
                toggleGlitch = false;
                //myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
                myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
                frameCounter = 0;
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    finalFbo.begin();
    ofClear(0, 0, 0);
    
    for(int i = 0; i < objs.size(); i++){
        objs[i]->draw(true);
    }
    objs[3]->draw(true);
    finalFbo.end();
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    finalFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'a'){
        objs[0]->setParam(1, 1);
    }
    if(key == 's'){
        objs[1]->setParam(2, 1);
    }
    if(key == 'd'){
        objs[2]->setParam(4, 1);
    }
    if(key == 'f'){
        objs[2]->setParam(5, 1);
    }
    if(key == 'g'){
        objs[3]->setParam(6, 1);
    }
    if(key == 'h'){
        objs[4]->setParam(7, 1);
    }
    if(key == 'j'){
        objs[6]->setParam(8, 1);
    }
    
    
    if (key == 'q') myGlitch.toggleFx(OFXPOSTGLITCH_CONVERGENCE);
    //if (key == 'w') myGlitch.toggleFx(OFXPOSTGLITCH_GLOW);
    if (key == 'e') myGlitch.toggleFx(OFXPOSTGLITCH_SHAKER);
    if (key == 'r') myGlitch.toggleFx(OFXPOSTGLITCH_CUTSLIDER);
    if (key == 't') myGlitch.toggleFx(OFXPOSTGLITCH_TWIST);
    if (key == 'y') myGlitch.toggleFx(OFXPOSTGLITCH_OUTLINE);
    if (key == 'u') myGlitch.toggleFx(OFXPOSTGLITCH_NOISE);
    if (key == 'i') myGlitch.toggleFx(OFXPOSTGLITCH_SLITSCAN);
    if (key == 'o') myGlitch.toggleFx(OFXPOSTGLITCH_SWELL);
    //if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_INVERT);
    //if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_CR_RLINE);
    if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_CR_MIRROR4);
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
