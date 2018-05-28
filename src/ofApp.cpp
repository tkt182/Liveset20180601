#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofBackground(0);
    //ofSetWindowTitle("Insta");
    //ofBackground(0);
    //receiver.setup(PORT);
    
    
    shared_ptr<ObjBase> o0(new Fireworks());
    o0->setup();
    objs.push_back(o0);
    
    shared_ptr<ObjBase> o1(new Particles());
    o1->setup();
    objs.push_back(o1);
}

//--------------------------------------------------------------
void ofApp::update(){

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
    
    objs[0]->setParam(1, 1);

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
