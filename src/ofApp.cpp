#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofBackground(0);
    //ofSetWindowTitle("Insta");
    //ofBackground(0);
    
    receiver.setup(PORT);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    
    
    shared_ptr<ObjBase> o0(new Fireworks());
    o0->setup();
    objs.push_back(o0);
    
    shared_ptr<ObjBase> o1(new Particles());
    o1->setup();
    objs.push_back(o1);
    
    shared_ptr<ObjBase> o2(new Particles());
    o2->setup();
    objs.push_back(o2);
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
                    objs[0]->setParam(2, 1);
                }
            }
        }
        
        /*
         if(m.getAddress() == "/sound/instl"){
         instlMsg = m.getArgAsString(0);
         
         if(instlMsg == "hh"){
         objs[0]->setParam(1, ofRandom(-1.0, 1.0));
         }
         }
         */
    }
    
    for(int i = 0; i < objs.size(); i++){
        objs[i]->update(dt.get());
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < objs.size(); i++){
        objs[i]->draw(true);
    }
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
        objs[2]->setParam(3, 1);
    }
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
