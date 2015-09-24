#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	base_tdf.loadImage("images/tdf_1972_poster.jpg");
	x_pos = y_pos = pix_red = pix_green = pix_blue = 0;

	base_tdf.getColor(0, 0);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	base_tdf.draw(0, 0);
	int pos = base_tdf.height + 20;
	int a = 0;
    ofDrawBitmapStringHighlight("X     : " + ofToString(x_pos), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("Y     : " + ofToString(y_pos), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("red   : " + ofToString(pix_red), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("green : " + ofToString(pix_green ), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("blue  : " + ofToString(pix_blue), 10,pos + (a++ * 20));  
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

	if (x > base_tdf.width | y > base_tdf.height){
		pix_red = 0;
		pix_green = 0;
		pix_blue = 0;
	}
	else{
		ofColor pix_col = base_tdf.getColor(x, y);
		pix_red = pix_col.r;
		pix_green = pix_col.g;
		pix_blue = pix_col.b;

	}
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
