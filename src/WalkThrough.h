#ifndef WalkThrough_h
#define WalkThrough_h

#include "ofMain.h"
#include "Buildings.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"
#include "ofxTrackingCamera.h"
#include "ofxGLFog.h"


class WalkThrough : public ObjBase {
public:
    WalkThrough(){
        
    }
    ~WalkThrough(){
    }

    void setup(){
        target = ofVec3f(1.0, 20.0, 0.0);
        
        float angle = 0.0;
        percent = 0.00;
        /*
        while (angle < TWO_PI ) {
            cameraPath.curveTo(100*cos(angle), 20, 100*sin(angle));
            //cameraPath.curveTo(300*cos(angle), 300, 300*sin(angle));
            angle += TWO_PI / 10;
        }
        */
        
        /*
        cameraPath.curveTo(-100, 20, 0);
        cameraPath.curveTo(-100, 20, 200);
        cameraPath.curveTo(0, 20, 250);
        cameraPath.curveTo(100, 20, 200);
        cameraPath.curveTo(100, 20, 0);
        cameraPath.curveTo(100, 20, -200);
        cameraPath.curveTo(0, 20, -250);
        cameraPath.curveTo(-100, 20, -200);
        //cameraPath.curveTo(-100, 20, 0);
        cameraPath.close();
        */
         
        cameraPath.curveTo(-400, 20, 0);
        cameraPath.curveTo(-400, 20, 200);
        cameraPath.curveTo(0, 20, 300);
        cameraPath.curveTo(400, 20, 200);
        cameraPath.curveTo(400, 20, 0);
        cameraPath.curveTo(400, 20, -200);
        cameraPath.curveTo(0, 20, -300);
        cameraPath.curveTo(-400, 20, -200);
        cameraPath.curveTo(-400, 20, -1);
        cameraPath.close();
         
        cameraPath = cameraPath.getSmoothed(10, 0);
        
        /*
        cameraPath.curveTo(-400, 20, -350);
        cameraPath.curveTo(-400, 20, 200);
        cameraPath.curveTo(-350, 20, 250);
        cameraPath.curveTo(-100, 20, 250);
        cameraPath.curveTo(-50., 20, 300);
        cameraPath.curveTo(0., 20, 400);
        cameraPath.curveTo(150, 20, 400);
        cameraPath.curveTo(200, 20, 350);
        cameraPath.curveTo(200, 20, -350);
        cameraPath.curveTo(250, 20, -400);
        cameraPath.curveTo(350, 20, -400);
        cameraPath.curveTo(400, 20, -350);
        cameraPath.curveTo(400, 20, 0.);
        cameraPath.curveTo(350, 20, 50);
        cameraPath.curveTo(100, 20, 50);
        cameraPath.curveTo(50, 20, 0);
        cameraPath.curveTo(50, 20, -350);
        cameraPath.curveTo(0, 20, -400);
        cameraPath.curveTo(-350, 20, -400);
        cameraPath.curveTo(-400, 20, -350);
        */
        /*
        cameraPath.curveTo(-400, 20, -350);
        cameraPath.curveTo(-400, 20, 200);
        cameraPath.curveTo(-300, 20, 300);
        cameraPath.curveTo(-100, 20, 300);
        cameraPath.curveTo(0, 20, 400);
        cameraPath.curveTo(100, 20, 500);
        cameraPath.curveTo(200, 20, 500);
        cameraPath.curveTo(300, 20, 400);
        
        cameraPath.curveTo(200, 20, -350);
        cameraPath.curveTo(250, 20, -400);
        cameraPath.curveTo(350, 20, -400);
        cameraPath.curveTo(400, 20, -350);
        cameraPath.curveTo(400, 20, 0.);
        cameraPath.curveTo(350, 20, 50);
        cameraPath.curveTo(100, 20, 50);
        cameraPath.curveTo(50, 20, 0);
        cameraPath.curveTo(50, 20, -350);
        cameraPath.curveTo(0, 20, -400);
        cameraPath.curveTo(-350, 20, -400);
        cameraPath.curveTo(-400, 20, -350);
        */
        
        
        /*
        cameraPath.addVertex(-100, 20, 0);
        cameraPath.addVertex(-100, 20, 200);
        cameraPath.addVertex(0, 20, 250);
        cameraPath.addVertex(100, 20, 200);
        cameraPath.addVertex(100, 20, 0);
        cameraPath.addVertex(100, 20, -200);
        cameraPath.addVertex(0, 20, -250);
        cameraPath.addVertex(-100, 20, -200);
        cameraPath.addVertex(-100, 20, 0);
        */
        /*
        cameraPath.addVertex(-100, 20, -200);
        cameraPath.addVertex(-100, 20, 0);
        cameraPath.addVertex(-100, 20, 200);
        cameraPath.curveTo(0, 20, 250);
        cameraPath.curveTo(100, 20, 200);
        cameraPath.addVertex(100, 20, 0);
        cameraPath.addVertex(100, 20, -200);
        cameraPath.curveTo(0, 20, -250);
        cameraPath.curveTo(-100, 20, -200);
        */
        ofFloatColor fogColor = ofFloatColor(0., 0., 0.);
        float fogStart = -10000.;
        float fogEnd = 20000.;
        fog.setFogColor(fogColor);
        fog.setFogStart(fogStart);
        fog.setFogEnd(fogEnd);
        
         
    }
    
    void update(float dt){
        //target.z -= 1.5;
        //target.z = anim.
        pointAnim.update(0.1f);
        //cout << target.z << endl;
        //cout << pointAnim.getCurrentPosition() << endl;
        
        if (percent >= 1.) percent = 0.;
        
        float findex = cameraPath.getIndexAtPercent(percent);
        //findex = findex * 100;
        
        trackingCamera.updateCameraSettings(cameraPath.getPointAtIndexInterpolated(findex), cameraPath.getTangentAtIndexInterpolated(findex), -5.0);
        percent += 0.001;

    }
    
    void draw(bool isShow){
        if(!isShow) return;
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        //ofEnableDepthTest();
        trackingCamera.begin();
        //fog.enable();
        buildings.draw();
        //fog.disable();
        //cameraPath.draw();
        trackingCamera.end();
        //ofDisableDepthTest();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    
    Buildings buildings;
    ofVboMesh mesh;
    ofShader shader;
    
    ofxAnimatableFloat anim;
    ofxAnimatableOfPoint    pointAnim;
    ofxTrackingCamera trackingCamera;
    ofVec3f target;
    float dt;
    
    ofPolyline cameraPath;
    float percent;
    
    ofxGLFog fog;
    
private:
    
};


#endif /* WalkThrough_h */
