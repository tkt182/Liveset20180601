#ifndef ParticleLines_h
#define ParticleLines_h

#include "ofMain.h"

class ParticleLine {
public:
    ParticleLine(){
        particleNum = 25;
        center = ofPoint(ofRandom(-ofGetWidth()/2 * 0.6, ofGetWidth()/2 * 0.6), ofRandom(-ofGetHeight()/2 * 0.6, ofGetHeight()/2 * 0.6));
        for(int i = 0; i < particleNum; i++){
            ofPoint point = ofPoint(ofRandom(center.x - ofGetWidth()/14, center.x + ofGetWidth()/14), ofRandom(center.y - ofGetHeight()/14, center.y + ofGetHeight()/14));
            particlePoints.push_back(ofVec3f(point.x, point.y, 0.0));
            mesh.addVertex(ofVec3f(point.x, point.y, 0.0));
        
            velocity.push_back(ofVec2f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)));
        
        }
        life = 10;
        vxRotate = ofRandom(-0.7, 0.7);
        vyRotate = ofRandom(-0.7, 0.7);
        vzRotate = ofRandom(-0.7, 0.7);
        xRotate  = 0.0;
        yRotate  = 0.0;
        zRotate  = 0.0;
        scale = ofRandom(1.0, 1.5);
    }
    ~ParticleLine(){
    }
    
    void update(){
        life -= 0.5;
        for(int i = 0; i < particleNum; i++){
            particlePoints[i].x += velocity[i].x;
            particlePoints[i].y += velocity[i].y;
        }
    }
    
    void draw(){
        
        ofSetColor(150, 200, 255, 200);
        glLineWidth(3.0);
        ofPushMatrix();
        ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
        ofScale(scale,scale,scale);
        ofRotateX(xRotate);
        ofRotateY(yRotate);
        //ofRotateZ(zRotate);
        
        
        for(int i = 0; i < particleNum - 2; i++){
            ofVec3f p1 = particlePoints[i];
            ofVec3f p2 = particlePoints[i + 1];
            ofVec3f p3 = particlePoints[i + 2];
            
            float distance1 = p1.distance(p2);
            float distance2 = p1.distance(p3);
            //cout << distance << endl;
            if(distance1 < 50.0 && distance2 < 50.0){
                glBegin(GL_LINES);
                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p3.x, p3.y, p3.z);
                glVertex3f(p3.x, p3.y, p3.z);
                glVertex3f(p1.x, p1.y, p1.z);
                glEnd();
            }
        }
        
        ofPopMatrix();
        xRotate += vxRotate;
        yRotate += vyRotate;
        //zRotate += vzRotate;
    }
    
    int particleNum;
    ofPoint center;
    vector<ofVec3f> particlePoints;
    vector<ofVec2f> velocity;
    float life;
    
    float scale, xRotate, yRotate, zRotate;
    float vxRotate, vyRotate, vzRotate;
    
    
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
