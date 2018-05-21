#ifndef ConnectLines_h
#define ConnectLines_h

#include "ofMain.h"

class ConnectLine {
public:
    void setup(){
        lines.setMode(OF_PRIMITIVE_LINES);
    }
    
    void update(vector<ofVec2f> &points){
        lines.clear();
        
        vector<ofVec2f>::iterator itr;
        for(itr = points.begin(); itr != points.end(); itr++){
            lines.addVertex(*(itr));
            lines.addColor(ofColor(255, 255, 255, 255));
        }
    }
    
    void draw(){
        lines.draw();
    }
    
private:
    ofVboMesh lines;

};

#endif /* ConnectLines_h */
