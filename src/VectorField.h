#ifndef VectorField_h
#define VectorField_h

#include "PingPongBuffer.h"
#include "ofxGui.h"

class VectorField : public ObjBase {
public:
    void setup(){
        panel.setup();
        panel.add(m.set("m", 0.01, 0.001, 0.3));
        panel.add(t.set("t", 0.01, 0.001, 1.0));
        panel.add(w.set("w", 0.01, 0.001, 1.0));
        panel.add(center.set("center", ofVec2f(0,0), ofVec2f(-1,-1), ofVec2f(1,1)));
        panel.add(bSlow.setup(false));
        
        numParticle = 512 * 512;
        
        // load shader
        updatePos.load("shader/passthru.vert", "shader/posUpdate.frag");
        updateRenderer.load("shader/render.vert", "shader/render.frag");
        
        textureRes = (int)sqrt((float)numParticle);
        numParticle = textureRes * textureRes;
    
        // random seed value for shader
        vector<float> pos(numParticle * 3);
        for (int x = 0; x < textureRes; x++) {
            for (int y = 0; y < textureRes; y++) {
                int i = textureRes * y + x;
                
                pos[i*3 + 0] = ofRandom(1.0);
                pos[i*3 + 1] = ofRandom(1.0);
                pos[i*3 + 2] = 0.0;
            }
        }
        
        // IMPORTANT: set color type as 32 bit float for presice calclation
        posPingPong.allocate(textureRes, textureRes, GL_RGB32F);
        posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
        posPingPong.dist->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
        
        
        for (int x = 0; x < textureRes; x++) {
            for (int y = 0; y < textureRes; y++) {
                mesh.addVertex(ofVec3f(x, y));
                mesh.addTexCoord(ofVec2f(x, y));
                mesh.addColor(ofFloatColor(0.8, 0.6, 1.0, 0.5));
            }
        }
        
    }
    
    void update(float dt){
        
        if (bSlow) speed = 0.005;
        else speed = 0.03;
        
        // smoothly change variable
        m.set((tm - m) * speed + m);
        t.set((tt - t) * speed + t);
        w.set((tw - w) * speed + w);
        center.set( (toCenter - center.get()) * speed + center.get() );
        
        // calculate position in shader to bake in FBO
        posPingPong.dist->begin();
        ofClear(0, 0, 0);
        
        updatePos.begin();
        updatePos.setUniformTexture("prevPosData", posPingPong.src->getTexture(), 0);
        updatePos.setUniform1f("t", t);
        updatePos.setUniform1f("w", w);
        updatePos.setUniform2f("center", center);
        updatePos.setUniform1f("m", m);
        
        posPingPong.src->draw(0, 0);
        updatePos.end();
        
        posPingPong.dist->end();
        
        posPingPong.swap();
    }
    
    void draw(bool isShow){
        
        ofSetColor(255);
        cam.begin();
        
        updateRenderer.begin();
        updateRenderer.setUniformTexture("posTex", posPingPong.dist->getTexture(), 0);
        updateRenderer.setUniform2f("screen", ofGetWidth(), ofGetHeight());
        mesh.draw(OF_MESH_POINTS);
        
        updateRenderer.end();
        cam.end();
        
        panel.draw();
        
        if (bShowTex) {
            posPingPong.src->draw(textureRes, 0);
            posPingPong.dist->draw(textureRes, textureRes + 100);
        }

        
    }
    
private:
    
    ofShader updatePos;
    ofShader updateRenderer;
    
    PingPongBuffer posPingPong;
    
    ofFbo renderFBO;
    
    float timeStep;
    int textureRes;
    int numParticle;
    
    ofVboMesh mesh;
    
    ofxPanel panel;
    ofParameter<float> m;
    ofParameter<float> t;
    ofParameter<float> w;
    ofParameter<ofVec2f> center;
    ofxToggle bSlow;
    
    ofEasyCam cam;
    ofVec2f toCenter;
    
    // smooth change target
    float tm;
    float tt;
    float tw;
    
    float speed;
    
    bool bShowTex = false;
    
};


#endif /* VectorField_h */
