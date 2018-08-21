#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    finalFbo.allocate(ofGetWidth(), ofGetHeight());
    myGlitch.setup(&finalFbo);
    myGlitch.toggleFx(OFXPOSTGLITCH_GLOW);
    toggleGlitch = false;
    toggleNoise = false;
    toggleShaker = false;
    frameCounter = 0;
    frameCounter2 = 0;
    frameCounter3 = 0;
    stoggleGlitch = false;
    sframeCounter = 0;
    
    
    plotHeight = 128;
    bufferSize = 2048;
    
    fft.setup();
    
    /*
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    
    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());
    */
    
    ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
    
    decayRate = 0.05;
    minimumThreshold = 0.1;
    threshold = minimumThreshold;
    rms_flag = false;
    
    
    ofSetFrameRate(30);
    ofBackground(0);
    
    receiver.setup(PORT);
    //ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    
    
    shared_ptr<ObjBase> o0(new Fireworks());
    o0->setup();
    objs.push_back(o0);
    
    shared_ptr<ObjBase> o1(new Particles());
    o1->setup();
    objs.push_back(o1);
    
    shared_ptr<ObjBase> o2(new Lines());
    o2->setup();
    objs.push_back(o2);
    
    shared_ptr<ObjBase> o3(new VectorField());
    o3->setup();
    o3->setParam(6, 1);
    objs.push_back(o3);
    
    shared_ptr<ObjBase> o4(new RectLines());
    o4->setup();
    objs.push_back(o4);
    
    shared_ptr<ObjBase> o5(new Sector());
    o5->setup();
    objs.push_back(o5);
    
    shared_ptr<ObjBase> o6(new ParticleLines());
    o6->setup();
    objs.push_back(o6);
    
    shared_ptr<ObjBase> o7(new WalkThrough());
    o7->setup();
    objs.push_back(o7);
    
    vectorFieldShow = false;
    walkThroughShow = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        //cout << m.getAddress() << endl;
        for(int i = 0; i < m.getNumArgs(); i++){
            //cout << m.getArgAsString(i) << endl;
            if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                string instlMsg = m.getArgAsString(i);
                if(instlMsg == "hand"){
                    objs[0]->setParam(1, 1);
                }
                if(instlMsg == "808bd"){
                    objs[1]->setParam(2, 1);
                }
                if(instlMsg == "hh"){
                    objs[2]->setParam(4, 1);
                }
                if(instlMsg == "jazz"){
                    //objs[2]->setParam(5, 1);
                    objs[6]->setParam(8, 1);
                }
                if(instlMsg == "glitch"){
                    string opt = m.getArgAsString(i+2);
                    if(opt == "u" || opt == "i"){
                        objs[4]->setParam(7, 1);
                    }
                    float opt2 = m.getArgAsFloat(3);
                    //cout << "hoge : " << opt2 << endl;
                    if(opt2 == 2.0 || opt2 == 6.0 || opt2 == 7.0){
                        if(!toggleNoise){
                            toggleNoise = true;
                            myGlitch.setFx(OFXPOSTGLITCH_NOISE, true);
                        }
                    }
                    /*
                    if(!toggleGlitch) {
                        toggleGlitch = true;
                        //myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
                        myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
                    }
                    */
                }
                
                if(instlMsg == "scratch"){
                    if(!toggleGlitch) {
                        toggleGlitch = true;
                        //myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
                        myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
                    }
                }
                if(instlMsg == "u"){
                    objs[4]->setParam(7, 1);
                }
                if(instlMsg == "i"){
                    objs[4]->setParam(7, 1);
                }
                if(instlMsg == "808"){
                    vectorFieldShow = true;
                    objs[3]->setParam(6, 1);
                    string opt  = m.getArgAsString(i+1);
                    float opt2 = m.getArgAsFloat(i+2);
                    if(opt == "speed" && opt2 == -1) {
                        if(!toggleShaker){
                            toggleShaker = true;
                            myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
                        }
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < objs.size(); i++){
        objs[i]->update(dt.get());
        if(toggleGlitch){
            frameCounter++;
            if(frameCounter > 30){
                toggleGlitch = false;
                //myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
                myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
                frameCounter = 0;
            }
        }
        if(toggleNoise){
            frameCounter2++;
            if(frameCounter2 > 40){
                toggleNoise = false;
                myGlitch.setFx(OFXPOSTGLITCH_NOISE, false);
                frameCounter2 = 0;
            }
        }
        
        if(toggleShaker){
            frameCounter3++;
            if(frameCounter3 > 30){
                toggleShaker = false;
                myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
                frameCounter3 = 0;
            }
        }
    }
    
    fft.update();
    //float value = fft.getUnScaledLoudestValue();
    float value = fft.getLowVal();
    cout << value << endl;
    //cout << fft.getUnScaledLoudestValue() << endl;
    if(value > 12.) {
        rms_flag = true;
        cout << "TRUE" << endl;
    }else{
        rms_flag = false;
    }
    
    //if(threshold > 0.2){
    if(rms_flag){
        cout << "EFFECT ON" << endl;
        stoggleGlitch = true;
        myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
    }
    
    cout << "S FRAME COUNTER " << sframeCounter << endl;
    // sound glitch
    if(stoggleGlitch){
        sframeCounter++;
        if(sframeCounter > 10){
            stoggleGlitch = false;
            myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
            sframeCounter = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    finalFbo.begin();
    ofClear(0, 0, 0);
    
    for(int i = 0; i < objs.size(); i++){
        if(i == 3 || i == 7) continue;
        objs[i]->draw(true);
    }
    // looks good two times draw
    objs[3]->draw(vectorFieldShow);
    objs[3]->draw(vectorFieldShow);
    objs[7]->draw(walkThroughShow);
    
    finalFbo.end();
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    finalFbo.draw(0, 0);
    
    
    /*
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(16, 16);
    
    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();
    
    ofDrawBitmapString("Frequency Domain", 0, 0);
    plot(drawBins, -plotHeight, plotHeight / 2);
    ofPopMatrix();
    string msg = ofToString((int) ofGetFrameRate()) + " fps";
    ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
    */
    
    /*
    fft.drawBars();
    fft.drawDebug();
    
    ofNoFill();
    ofDrawRectangle(824, 0, 200, 200);
    ofDrawRectangle(824, 200, 200, 200);
    ofDrawRectangle(824, 400, 200, 200);
    ofDrawRectangle(824, 600, 200, 200);
    
    fft.drawHistoryGraph(ofPoint(824,0), LOW);
    fft.drawHistoryGraph(ofPoint(824,200),MID );
    fft.drawHistoryGraph(ofPoint(824,400),HIGH );
    fft.drawHistoryGraph(ofPoint(824,600),MAXSOUND );
    ofDrawBitmapString("LOW",850,20);
    ofDrawBitmapString("HIGH",850,420);
    ofDrawBitmapString("MID",850,220);
    ofDrawBitmapString("MAX VOLUME",850,620);
    
    ofSetColor(0);
    ofDrawBitmapString("Press 'r' or 'q' to toggle normalization of values", 20,320);
    */
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    /*
    if(key == 'a'){
        objs[0]->setParam(1, 1);
    }
    */
    if(key == 's'){
        objs[1]->setParam(2, 1);
    }
    /*
    if(key == 'd'){
        objs[2]->setParam(4, 1);
    }
    */
    if(key == 'f'){
        objs[2]->setParam(5, 1);
    }
    if(key == 'g'){
        objs[3]->setParam(6, 1);
    }
    if(key == 'h'){
        objs[4]->setParam(7, 1);
    }
    if(key == 'j'){
        objs[6]->setParam(8, 1);
    }
    if(key == 'z'){
        vectorFieldShow = !vectorFieldShow;
    }
    if(key == 'x'){
        walkThroughShow = !walkThroughShow;
    }
    
    
    if (key == 'q') myGlitch.toggleFx(OFXPOSTGLITCH_CONVERGENCE);
    //if (key == 'w') myGlitch.toggleFx(OFXPOSTGLITCH_GLOW);
    if (key == 'e') myGlitch.toggleFx(OFXPOSTGLITCH_SHAKER);
    if (key == 'r') myGlitch.toggleFx(OFXPOSTGLITCH_CUTSLIDER);
    if (key == 't') myGlitch.toggleFx(OFXPOSTGLITCH_TWIST);
    if (key == 'y') myGlitch.toggleFx(OFXPOSTGLITCH_OUTLINE);
    if (key == 'u') myGlitch.toggleFx(OFXPOSTGLITCH_NOISE);
    if (key == 'i') myGlitch.toggleFx(OFXPOSTGLITCH_SLITSCAN);
    if (key == 'o') myGlitch.toggleFx(OFXPOSTGLITCH_SWELL);
    //if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_INVERT);
    //if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_CR_RLINE);
    //if (key == 'p') myGlitch.toggleFx(OFXPOSTGLITCH_CR_MIRROR4);

    
    /*
    if(key=='1'){
        fft.setVolumeRange(100);
        fft.setNormalize(false);
    }
    if(key=='2'){
        fft.setNormalize(true);
    }
    */

}

void ofApp::plot(vector<float>& buffer, float scale, float offset) {
    ofNoFill();
    int n = buffer.size();
    ofDrawRectangle(0, 0, n, plotHeight);
    glPushMatrix();
    glTranslatef(0, plotHeight / 2 + offset, 0);
    ofBeginShape();
    for (int i = 0; i < n; i++) {
        ofVertex(i, sqrt(buffer[i]) * scale);
    }
    ofEndShape();
    glPopMatrix();
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    /*
    float maxValue = 0;
    for(int i = 0; i < bufferSize; i++) {
        if(abs(input[i]) > maxValue) {
            maxValue = abs(input[i]);
        }
    }
    for(int i = 0; i < bufferSize; i++) {
        input[i] /= maxValue;
    }
    
    fft->setSignal(input);
    
    float* curFft = fft->getAmplitude();
    memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
    
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(audioBins[i]) > maxValue) {
            maxValue = abs(audioBins[i]);
        }
    }
    for(int i = 0; i < fft->getBinSize(); i++) {
        audioBins[i] /= maxValue;
    }
    cout << maxValue << endl;
    
    soundMutex.lock();
    middleBins = audioBins;
    soundMutex.unlock();
    
    
    // modified from audioInputExample
    float rms = 0.0;
    int numCounted = 0;
    
    for (int i = 0; i < bufferSize / 2; i++){
        float leftSample = input[i * 2] * 0.5;
        float rightSample = input[i * 2 + 1] * 0.5;
        
        rms += leftSample * leftSample;
        rms += rightSample * rightSample;
        numCounted += 2;
    }
    
    rms /= (float)numCounted;
    rms = sqrt(rms);
    // rms is now calculated
    
    threshold = ofLerp(threshold, minimumThreshold, decayRate);
    
    if(rms > threshold) {
        // onset detected!
        threshold = rms;
    }
    
    //cout << threshold << endl;
    if(maxValue > 0.48){
        rms_flag = true;
    }else{
        rms_flag = false;
    }
    */
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
