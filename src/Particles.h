#ifndef Particles_h
#define Particles_h


class Particle {
public:
    Particle() : Particle(ofVec2f(0, 0), ofVec2f(0, 0)) { }
    Particle(ofVec2f location, ofVec2f velocity){
        this->location = location;
        this->velocity = velocity * 2.0;
        this->alpha = 255;
        this->body_size = velocity.length();
        this->body_color.setHsb(ofRandom(255), 255, 255);
    }
    ~Particle(){
        
    }
    
    void update(){
        this->location += this->velocity;
        this->alpha -= 3;
    }
    void draw(){
        //ofSetColor(this->body_color, this->alpha);
        ofSetColor(this->body_color, 255);
        ofDrawEllipse(this->location, this->body_size, this->body_size);
    }
    
    ofVec2f get_location(){
        return this->location;
    }
    bool isDead(){
        return this->alpha < 0;
    }
private:
    ofVec2f location;
    ofVec2f velocity;
    
    float    body_size;
    ofColor body_color;
    int        alpha;
};


class Cleator
{
public:
    Cleator(){
        this->location = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        //this->velocity = ofVec2f(0, 0);
        this->velocity = ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10));
        this->acceleration = ofVec2f(0, 0);
        
        this->max_speed = 10;
        this->max_force = 3;
        this->radius = 30;
        this->angle = ofRandom(360);
    }
    ~Cleator(){
        
    }
    
    void applyForce(ofVec2f force){
        this->acceleration += force;
        
    }
    void seek(ofVec2f target){
        ofVec2f desired = this->location - target;
        float distance = desired.length();
        desired.normalize();
        if (distance < this->radius)
        {
            float m = ofMap(distance, 0, this->radius, 0, this->max_speed);
            desired *= m;
        }
        else
        {
            desired *= this->max_speed;
        }
        
        ofVec2f steer = this->velocity - desired;
        steer.limit(this->max_force);
        applyForce(steer);
    }
    
    void update(){
        this->future.set(this->velocity);
        this->future.normalize();
        this->future *= 60;
        this->future += this->location;
        
        this->angle = ofRandom(0, 360);
        float x = 60 * cos(this->angle * DEG_TO_RAD) + future.x;
        float y = 60 * sin(this->angle * DEG_TO_RAD) + future.y;
        this->target = ofVec2f(x, y);
        
        this->seek(this->target);
        
        this->velocity += this->acceleration;
        this->velocity.limit(max_speed);
        this->location += this->velocity;
        
        if (this->location.x < -ofGetWidth() / 2) {
            this->location.x = -ofGetWidth() / 2;
            this->velocity.x *= -1;
        }
        else if (this->location.x > ofGetWidth() / 2) {
            this->location.x = ofGetWidth() / 2;
            this->velocity.x *= -1;
        }
        
        if (this->location.y < -ofGetHeight() / 2) {
            this->location.y = -ofGetHeight() / 2;
            this->velocity.y *= -1;
        }
        else if (this->location.y > ofGetHeight() / 2) {
            this->location.y = ofGetHeight() / 2;
            this->velocity.y *= -1;
        }
        
        this->acceleration *= 0;
        this->velocity *= 0.98;
    }
    void draw(){
        
    }
    
    ofVec2f get_location(){
        return this->location;
    }
    ofVec2f get_velocity(){
        return this->velocity;
    }
    
private:
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f future;
    ofVec2f target;
    float max_speed;
    float max_force;
    float radius;
    float angle;
};


class Particles : public ObjBase {
public:
    void setup(){
        /*
        for (int i = 0; i < 2; i++) {
            this->cleators.push_back(new Cleator());
        }
        */
        this->lineEnable = 1;
    }
    
    void update(float dt){
        for(int i = this->cleators_life.size() - 1; i > -1; i--){
            this->cleators_life[i] -= 16.0;
        
            if(this->cleators_life[i] < 0){
                this->cleators.erase(this->cleators.begin() + i);
                this->cleators_life.erase(this->cleators_life.begin() + i);
            }
        
        }
        
        for (int i = 0; i < this->cleators.size(); i++) {
            
            ofVec2f location = this->cleators[i]->get_location();
            ofVec2f velocity = this->cleators[i]->get_velocity();
            
            if (velocity.length() > 0.1) {
                this->particles.push_back(new Particle(location, velocity ));
            }
        }
        
        for (int i = this->particles.size() - 1; i > -1; i--) {
            this->particles[i]->update();
            
            if (this->particles[i]->isDead()) {
                delete this->particles[i];
                this->particles.erase(this->particles.begin() + i);
            }
        }
        
        for (int i = 0; i < this->cleators.size(); i++) {
            this->cleators[i]->update();
        }
    }
    
    void draw(bool isShow){
        
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        float distance;
        for (int i = 0; i < this->particles.size(); i++) {
            this->particles[i]->draw();
            for (int j = i; j < this->particles.size(); j++) {
                distance = this->particles[i]->get_location().distance(this->particles[j]->get_location());
                if (this->lineEnable && distance < 70) {
                    ofDrawLine(this->particles[i]->get_location(), this->particles[j]->get_location());
                }
            }
        }
        ofPopMatrix();
    }
    
    void setParam(int ch, float val){
        if(ch == 2){
            this->cleators.push_back(new Cleator());
            this->cleators_life.push_back(255);
        }
        if(ch == 3){
            this->lineEnable = 0;
            this->cleators.push_back(new Cleator());
            this->cleators_life.push_back(255);
        }
    }
    
private:
    vector<Particle*> particles;
    vector<Cleator*> cleators;
    vector<float> cleators_life;
    int lineEnable;
};

#endif /* Particles_h */
