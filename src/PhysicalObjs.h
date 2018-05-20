#ifndef PhysicalObjs_h
#define PhysicalObjs_h

#include "ofMain.h"
#include "ObjBase.h"
#include "ofxBox2d.h"
#include "CustomCircle.h"

class PhysicalObjs : public ObjBase {
public:
    void setup(){
        box2d.init();
        box2d.setGravity(0, 10);
        box2d.createBounds();
        box2d.setFPS(30);
        box2d.registerGrabbing();
    
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(box2d.getWorld(), ofGetWidth() / 2.0, 100, 40);
    }
    
    void update(float dt){
        box2d.update();
        circle.update();
    }
    
    void draw(ofCamera& cam, bool frag){
        ofSetColor(0, 127, 255);
        circle.draw();
    }

    void setParam(int ch, float val){
        if(ch == 1){
            // this case, do not use val
            ofVec2f velocity = ofVec2f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).normalize();
            circle.addForce(velocity, 5000.0);
        }

    };
    
    
private:
    ofxBox2d box2d;
    CustomCircle circle;
    
    

};



#endif /* PhysicalObjs_h */
