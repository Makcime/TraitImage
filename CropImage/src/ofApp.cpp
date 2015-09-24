#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	base_tdf.loadImage("images/tdf_1972_poster.jpg");
	crop_tdf.loadImage("images/tdf_1972_poster.jpg");
	crop_resize_tdf.loadImage("images/tdf_1972_poster.jpg");
	int x, y, w, h;
	x = 100;
	y = 200;
	w = 125;
	h = 50;
	crop_tdf.crop(x, y, w, h);
	crop_resize_tdf.crop(x, y, w, h);
	crop_resize_tdf.resize(w * 3, h * 3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	base_tdf.draw(0, 0);
	crop_tdf.draw(500, 175);
	crop_resize_tdf.draw(800, 150);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
