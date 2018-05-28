#ifndef Lines_h
#define Lines_h

class Lines : public ObjBase {
public:
    void setup(){
        toggleDisplay = false;
        frameCounter = 0;
        width = 10;
    }
    
    void update(float dt){
        
    }
    
    void draw(bool isShow){
        if(toggleDisplay){
            ofSetColor(255,255,255,100);
            ofDrawRectangle(leftTop, 0, 50, ofGetHeight());
            frameCounter++;
            if(frameCounter > 3){
                toggleDisplay = false;
                frameCounter = 0;
            }
        }
    }
    
    void setParam(int ch, float val){
        if(ch == 4){
            if(!toggleDisplay) {
                toggleDisplay = true;
                leftTop = ofRandom(0, ofGetWidth() - 50);
            }
        }
    }
    
private:
    float leftTop;
    float width;
    bool toggleDisplay;
    int frameCounter;
};

#endif /* Lines_h */
