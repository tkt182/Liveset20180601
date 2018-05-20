#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    receiver.setup(PORT);
    
    
    shared_ptr<ObjBase> o0(new PhysicalObjs());
    o0->setup();
    objs.push_back(o0);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
    
        if(m.getAddress() == "/sound/instl"){
            instlMsg = m.getArgAsString(0);
            
            if(instlMsg == "hh"){
                objs[0]->setParam(1, ofRandom(-1.0, 1.0));
            }
        }
    }
    
    
    for(int i = 0; i < objs.size(); i++){
        objs[i]->update(dt.get());
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < objs.size(); i++){
        objs[i]->draw(cam, true);
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
