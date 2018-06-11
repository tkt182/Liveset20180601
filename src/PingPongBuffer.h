#ifndef PingPongBuffer_h
#define PingPongBuffer_h

#pragma once
#include "ofMain.h"
#include "ofxGui.h"

struct PingPongBuffer {
public:
    void allocate(int _w, int _h, int _internalformat = GL_RGBA){
        
        for (int i = 0; i < 2; i++) {
            FBOs[i].allocate(_w, _h, _internalformat);
            FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        }
        clear();
    };
    void swap(){
        std::swap(src, dist);
    };
    void clear(){
        for (int i = 0; i < 2; i++) {
            FBOs[i].begin();
            ofClear(0,255);
            FBOs[i].end();
        }
    };
    
    ofFbo& operator []( int n ){ return FBOs[n]; };
    ofFbo * src = &FBOs[0];
    ofFbo * dist = &FBOs[1];
private:
    ofFbo FBOs[2];
};

#endif /* PingPongBuffer_h */
