#ifndef Sector_h
#define Sector_h

class Sector : public ObjBase {
public:
    void setup(){
    }
    
    void update(float dt){
        xRotate += 0.5;
        yRotate += 0.5;
        zRotate += 0.5;
    }
    
    void draw(bool isShow){
        ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
        
        int x_index = 0;
        int y_index = 0;
        
        ofPoint location(x_index * 230, y_index * 230);
                
        ofPushMatrix();
        ofTranslate(location);
        ofRotateX(xRotate);
        ofRotateY(yRotate);
        ofRotateZ(zRotate);
                
        //for (int radius = 30; radius < 100; radius += 8) {
        for (int radius = 30; radius < 100; radius += 800) {
                    
            ofColor color;
            color.setHsb(ofRandom(255), 239, 239);
                    
            int start_noise = ofNoise(location.x * 0.1, radius * 0.05, ofGetFrameNum() * 0.005) * 360;
            int end_noise = ofMap(ofNoise(location.y * 0.1, radius * 0.05, ofGetFrameNum() * 0.01), 0, 1, -90, 360);
            int start_deg = ofRandom(360) + start_noise;
            int end_deg = start_deg + end_noise;
                    
            if (start_deg > end_deg) {
                continue;
            }
                    
            std::vector<ofPoint> vertices;
            for (int deg = start_deg; deg < end_deg; deg += 1) {
                vertices.push_back(ofPoint(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
            }
                    
            ofFill();
            ofSetColor(color, 32);
                    
            ofBeginShape();
            ofVertices(vertices);
            ofVertex(0, 0);
            ofEndShape(true);
                    
            ofNoFill();
            ofSetColor(color);
                    
            ofBeginShape();
            ofVertices(vertices);
            ofEndShape();
        }

        ofPopMatrix();
    }
    
private:
    
    float xRotate, yRotate, zRotate;
    
};

#endif /* Sector_h */
