#ifndef PhysicalObjs_h
#define PhysicalObjs_h

#include "ofMain.h"
#include "ObjBase.h"
#include "ofxBox2d.h"
#include "CustomCircle.h"
#include "CustomRect.h"
#include "ConnectLines.h"


    void setup(){
        box2d.init();
        box2d.setGravity(0, 10);
        box2d.createBounds();
        box2d.setFPS(30);
        box2d.registerGrabbing();
    
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(box2d.getWorld(), ofGetWidth() / 2.0, 100, 40);
        
        rect.setPhysics(3.0, 0.53, 0.1);
        rect.setup(box2d.getWorld(), ofGetWidth() / 2.0, 100, 80, 80);
        
        lines.setup();
    }
    
    void update(float dt){
        box2d.update();
        circle.update();
        rect.update();
        
        points.clear();
        points.push_back(circle.getPosition());
        points.push_back(rect.getPosition());
        
        lines.update(points);
        
    }
    
    void draw(ofCamera& cam, bool frag){
        ofSetColor(0, 127, 255);
        circle.draw();
        rect.draw();
        
        //lines.draw();
    }

    
        if(ch == 1){
            // this case, do not use val
            //ofVec2f velocity = ofVec2f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).normalize();
            ofVec2f velocity = ofVec2f(ofRandom(-1.0, 1.0), -1.0).normalize();
            circle.addForce(velocity, 5000.0);
        }
        if(ch == 2){
            ofVec2f velocity = ofVec2f(ofRandom(-1.0, 1.0), -1.0).normalize();
            rect.addForce(velocity, 5000.0);
        }

    };
    
    
private:
    ofxBox2d box2d;
    CustomCircle circle;
    CustomRect rect;
    ConnectLine lines;
    
    vector<ofVec2f> points;
    
};



#endif /* PhysicalObjs_h */
