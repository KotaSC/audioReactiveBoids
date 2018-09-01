#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    particle.load("images/particle.png");
    
    bgm.load("bgm/n118.mp3");
    bgm.play();
    
    fft.setup();
    fft.setNumFFTBins(16);
    fft.setNormalize(true);
    
    flock = Flock(300);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fft.update();
    
    float sepValue = ofMap(fft.getLowVal(), 0.0, 1.0, 0.0, 12.0);
    float aliValue = ofMap(fft.getMidVal(), 0.0, 1.0, 0.0, 0.5);
    float cohValue = ofMap(fft.getHighVal(), 0.0, 1.0, 0.0, 100.0);
    
    flock.update(sepValue, aliValue, cohValue);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    particle.resize(50, 50);
    flock.display(particle);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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

