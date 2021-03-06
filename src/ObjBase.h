#ifndef ObjBase_h
#define ObjBase_h

#include "ofMain.h"

class ObjBase {
public:
    virtual void setup(){};
    virtual void update(float dt){};
    virtual void draw(bool isShadow){};
    //virtual void randomize(){};
    virtual void setParam(int ch, float val){};
    
    bool isEnable(){ return isEnabled; };
    void enable(){ isEnabled = true; };
    void disable(){ isEnabled = false; };
    
    void enableWireFrame(){ drawMode = OF_MESH_WIREFRAME; };
    void disableWireFrame(){ drawMode = OF_MESH_FILL; };
    
    bool isEnabled = false;
    ofPolyRenderMode drawMode = OF_MESH_FILL;
};

#endif /* ObjBase_h */
