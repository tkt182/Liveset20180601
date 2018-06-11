#ifndef Lines_h
#define Lines_h

class Lines : public ObjBase {
public:
    void setup(){
        toggleDisplay = false;
        frameCounter = 0;
        width = 70;
    }
    
    void update(float dt){
        
    }
    
    void draw(bool isShow){
        if(toggleDisplay){
            ofFill();
            ofSetColor(ofRandom(256),255,255,100);
            ofBeginShape();
            ofVertex(leftTop.x, leftTop.y);
            ofVertex(leftTop.x + 120, leftTop.y);
            ofVertex(leftTop.x + 120 - 50, leftTop.y - 70);
            ofVertex(leftTop.x - 50, leftTop.y - 70);
            ofEndShape();
            //ofDrawRectangle(leftTop, 0, 50, ofGetHeight());
            frameCounter++;
            if(frameCounter > 3){
                toggleDisplay = false;
                frameCounter = 0;
            }
        }
        
        if(toggleDisplay2){
            ofNoFill();
            ofSetColor(ofRandom(256),255,255,100);
            ofBeginShape();
            ofVertex(leftTop2.x, leftTop2.y);
            ofVertex(leftTop2.x + 120, leftTop2.y);
            ofVertex(leftTop2.x + 120 - 50, leftTop2.y - 70);
            ofVertex(leftTop2.x - 50, leftTop2.y - 70);
            ofVertex(leftTop2.x, leftTop2.y);
            ofEndShape();
            //ofDrawRectangle(leftTop, 0, 50, ofGetHeight());
            frameCounter2++;
            if(frameCounter2 > 3){
                toggleDisplay2 = false;
                frameCounter2 = 0;
            }
        }
        
    }
    
    void setParam(int ch, float val){
        if(ch == 4){
            if(!toggleDisplay) {
                toggleDisplay = true;
                
                float leftTopX = ofRandom(50, ofGetWidth() - 50);
                float leftTopY = ofRandom(0, ofGetHeight() - 50);
                leftTop = ofVec2f(leftTopX, leftTopY);
            }
        }
        if(ch == 5){
            if(!toggleDisplay2) {
                toggleDisplay2 = true;
                
                float leftTopX = ofRandom(50, ofGetWidth() - 50);
                float leftTopY = ofRandom(0, ofGetHeight() - 50);
                leftTop2 = ofVec2f(leftTopX, leftTopY);
            }
        }
    }
    
private:
    //float leftTop, leftButtom;
    ofVec2f leftTop, leftTop2, leftButtom;
    
    float width;
    bool toggleDisplay, toggleDisplay2;
    int frameCounter, frameCounter2;
};

#endif /* Lines_h */
