#ifndef RectLines_h
#define RectLines_h

#include "ofMain.h"

class RectLine {
public:
    RectLine() {
        life = 30.0;
    }
    ~RectLine() {}
    
    float life;

};

class RectLines : public ObjBase {
public:
    void setup(){
    }

    void update(float dt){
        yAngle += 0.5;
        zAngle += 0.5;
    }
    
    void draw(bool isShow){
        
        glLineWidth(3.0);
        for (int i = 0; i < lines.size(); i++){
            if(lines[i]->life < 0) {
                lines.erase(lines.begin() + i);
            }
        }
        
        float len = 240;
        
        cam.begin();
        ofRotateX(120);
        ofRotateY(yAngle);
        ofRotateZ(zAngle);
        
        //for (int z = 0; z <= len; z += 360) {
        for (int i = 0; i < lines.size(); i++){
            
            int z = i * 25;
            for(int line = 0; line < 180; line += 1){
                
                ofPoint p1 = this->make_rect_point(len, ofGetFrameNum() + z + line, z - len * 0.5);
                ofPoint p2 = this->make_rect_point(len, ofGetFrameNum() + z + line + 15, z - len * 0.5);
                
                //ofSetColor(239, ofMap(line, 0, 120, 0, 255));
                ofSetColor(239, ofMap(line / 2, 0, 120, 0, 255));
                ofDrawLine(p1, p2);
            }
            
            //ofDrawSphere(this->make_rect_point(len, ofGetFrameNum() + z + 180, z - len * 0.5), 5);
        //}
            lines[i]->life -= 10.;
        }
        cam.end();
    }

    void setParam(int ch, float val){
        if(ch == 7){
            lines.push_back(new RectLine());
            lines.push_back(new RectLine());
            lines.push_back(new RectLine());
        }
        
    }

    ofPoint make_rect_point(float len, int deg, int z = 0) {
        
        int half_len = len * 0.5;
        int param = (deg + 45) / 90;
        
        ofPoint point;
        
        switch (param % 4) {
            
            case 0:
            
            return ofPoint(half_len, ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), z);
            case 1:
            
            return  ofPoint(ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), half_len, z);
            case 2:
            
            return ofPoint(-half_len, ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), z);
            case 3:
            
            return ofPoint(ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), -half_len, z);
            default:
            
            return ofPoint(0, 0, 0);
        }
    }
    
private:

    vector<RectLine*> lines;
    
    // Make Member
    ofEasyCam cam;
    
    vector<float> lines_life;
    float yAngle, zAngle;
    
};

#endif /* RectLines_h */
