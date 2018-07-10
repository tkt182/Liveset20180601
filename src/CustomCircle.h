#ifndef CustomCircle_h
#define CustomCircle_h

#include "ofMain.h"
#include "ofxBox2d.h"

class CustomCircle : public ofxBox2dCircle {
public:
    void draw(){
        float radius = getRadius();

        glPushMatrix();
        glTranslatef(getPosition().x, getPosition().y, 0);
        ofFill();
        ofSetColor(31,127,255,100);
        ofDrawCircle(0, 0, radius);
        ofSetColor(31,127,255,200);
        ofDrawCircle(0, 0, radius*0.7);
        ofSetColor(127,200,255,200);
        ofDrawCircle(0, 0, radius*0.4*sin(ofGetElapsedTimef()));
        
        glPopMatrix();
    }



};

#endif /* CustomCircle_h */
