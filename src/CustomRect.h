#ifndef CustomRect_h
#define CustomRect_h

class CustomRect : public ofxBox2dRect {
public:
    void draw(){
        float width    = getWidth();
        float height   = getHeight();
        float rotation = getRotation();
                
        float scale = 0.7;
        ofPushMatrix();
        {
            glTranslatef(getPosition().x, getPosition().y, 0);
            ofRotateZ(rotation);
            ofPushMatrix();
            {
                glTranslatef(-width / 2.0, -height / 2.0, 0);
                ofSetColor(31,255,127,100);
                ofDrawRectangle(0, 0, width, height);
                ofSetColor(31,255,127,200);
                ofDrawRectangle(width/2.0 - (width*scale/2.0), height/2.0 - (height*scale/2.0), width*scale, height*scale);
                scale = 0.4*sin(ofGetElapsedTimef());
                ofSetColor(31,255,200,200);
                ofDrawRectangle(width/2.0 - (width*scale/2.0), height/2.0 - (height*scale/2.0), width*scale, height*scale);
            }
            ofPopMatrix();
        }
        ofPopMatrix();
        
    }
};


#endif /* CustomRect_h */
