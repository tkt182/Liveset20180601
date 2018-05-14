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
        ofCircle(0, 0, radius);
        ofSetColor(31,127,255,200);
        ofCircle(0, 0, radius*0.7);
        glPopMatrix();
    }
};

#endif /* CustomCircle_h */
