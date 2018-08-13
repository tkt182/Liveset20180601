#ifndef Buildings_h
#define Buildings_h

#include "ofMain.h"

class Buildings {
public:
    Buildings() {
        r1();
        mesh.setVertexData(vs.data(), vs.size(), GL_STATIC_DRAW);
        mesh.setIndexData(is.data(), is.size(), GL_STATIC_DRAW);
    };
    void draw() {
        
        //ofSetColor(0.6, 0.8, 1.0, 50);
        ofSetColor(150, 200, 255, 7);
        //ofFill();
        //mesh.drawElements( GL_TRIANGLES, is.size());
        
        ofNoFill();
        mesh.drawElements( GL_TRIANGLES, is.size());
        
    };
    void r1(){
        for (int x = -11; x < 11; x++) {
            for (int z = -11; z < 11; z++) {
                
                ofMatrix4x4 mat;
                if(abs(x) > 8 || abs(z) > 8){
                    mat.glTranslate(x * 100 + 50, 0, z * 100 + 50);
                }else{
                    mat.glTranslate(x * 100, 0, z * 100);
                }

                r2(&mat, 0);
                
            }
        }
    };
    void r2(ofMatrix4x4 *mat, int level){
        if (level == 10) return;
        
        float coin = ofRandom(1.0);
        ofMatrix4x4 _mat;
        _mat = *mat;
        
        if (coin < 0.2) {
            return;
        } else if (coin < 0.6) {
            _mat.glTranslate(0, 10, 0);
            //_mat.glScale(1.2, 1.2, 1.2);
            _mat.glScale(1.3, 1.3, 1.3);
        } else {
            _mat.glTranslate(0, 10, 0);
            //_mat.glScale(0.8, 0.8, 0.8);
            _mat.glScale(0.9, 0.9, 0.9);
        }
        
        r2(&_mat, level++);
        r3(&_mat);
        
    };
    void r3(ofMatrix4x4 *mat){
        
        float coin = ofRandom(1.0);
        
        for (int x = 0; x < 3; x++) {
            for (int z = 0; z < 3; z++) {
                for (int y = 0; y < 2; y++) {
                    
                    ofMatrix4x4 _mat = *mat;
                    //_mat.glTranslate(20*x, 10*y, 20*z);
                    _mat.glTranslate(20*x, 10*y, 2*z);
                    addBox(&_mat);
                }
            }
        }
        
    };
    void addBox(ofMatrix4x4 *mat){
        
        float coin = ofRandom(1.0);
        float size = 1.5;
        ofMesh _mesh;
        
        if (coin < 0.3) {
            //_mesh = ofMesh::box(15, 5, 2, 1, 1, 1);
            _mesh = ofMesh::box(20*size, 15*size, 15*size, 1, 1, 1);
        } else if (coin < 0.6) {
            //_mesh = ofMesh::box(3, 15, 2, 1, 1, 1);
            _mesh = ofMesh::box(10*size, 20*size, 10*size, 1, 1, 1);
        } else {
            //_mesh = ofMesh::box(8, 15, 13, 1, 1, 1);
            _mesh = ofMesh::box(8*size, 15*size, 20*size, 1, 1, 1);
        }
        
        vector<ofVec3f> v = _mesh.getVertices();
        vector<ofIndexType> ind = _mesh.getIndices();
        int iNum = vs.size();
        
        for (int i = 0; i < v.size(); i++) {
            vs.push_back(v[i] * *mat);
        }
        
        for (int i = 0; i < ind.size(); i++) {
            is.push_back((int)ind[i] + iNum);
        }
        
    };
    
private:
    ofVbo mesh;
    vector<ofVec3f> vs;
    vector<ofIndexType> is;
};


#endif /* Buildings_h */
