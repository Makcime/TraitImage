#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	base_tdf.loadImage("images/tdf_1972_poster.jpg");
	x_pos = y_pos = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	base_tdf.draw(0, 0);
    ofDrawBitmapString("X : " + ofToString(x_pos), 10,520);  
    ofDrawBitmapString("Y : " + ofToString(y_pos), 10,540);  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	x_pos = x;
	y_pos = y;

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
