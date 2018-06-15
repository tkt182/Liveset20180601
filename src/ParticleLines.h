#ifndef ParticleLines_h
#define ParticleLines_h

#include "ofMain.h"

class ParticleLine {
public:
    ParticleLine(){
        particleNum = 25;
        center = ofPoint(ofRandom(-ofGetWidth()/2 * 0.9, ofGetWidth()/2 * 0.9), ofRandom(-ofGetHeight()/2 * 0.9, ofGetHeight()/2 * 0.9));
        for(int i = 0; i < particleNum; i++){
            //ofPoint point = ofPoint(ofRandom(center.x - ofGetWidth()/100, center.x + ofGetWidth()/8), ofRandom(center.y - ofGetHeight()/8, center.y + ofGetHeight()/8));
            ofPoint point = ofPoint(ofRandom(center.x - ofGetWidth()/20, center.x + ofGetWidth()/20), ofRandom(center.y - ofGetHeight()/20, center.y + ofGetHeight()/20));
            particlePoints.push_back(point);
            mesh.addVertex(ofVec3f(point.x, point.y, 0.0));
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
        life = 10;
    }
    ~ParticleLine(){
        
    }
    
    void update(){
        life -= 0.5;
    }
    void draw(){
        mesh.draw(OF_MESH_POINTS);
    }
    
    int particleNum;
    ofPoint center;
    vector<ofPoint> particlePoints;
    float life;
    
    ofVboMesh mesh;
    
};


class ParticleLines : public ObjBase {
public:
    void setup(){
    }
    
    void update(float dt){
        for (int i = pls.size() - 1; i > -1; i--) {
            if(pls[i]->life < 0){
                pls.erase(pls.begin() + i);
            }
            
            pls[i]->life -= 0.5;
        }
        
        
        for(int i = 0; i < pls.size(); i++){
            pls[i]->update();
        }
    }
    
    void draw(bool isShow){
        for(int i = 0; i < pls.size(); i++){
            pls[i]->draw();
        }
    }
    
    void setParam(int ch, float val){
        if(ch == 8){
            pls.push_back(new ParticleLine());
        }
    }

private:
    
    vector<ParticleLine*> pls;


};


#endif /* ParticleLines_h */
