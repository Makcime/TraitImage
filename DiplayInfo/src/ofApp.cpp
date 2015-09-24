#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	base_tdf.loadImage("images/tdf_1972_poster.jpg");
	x_pos = y_pos = pix_red = pix_green = pix_blue = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	base_tdf.draw(0, 0);
	int pos = base_tdf.height + 20;
	int a = 0;
    ofDrawBitmapStringHighlight("X : " + ofToString(x_pos), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("Y : " + ofToString(y_pos), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("red : " + ofToString(pix_red), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("green  : " + ofToString(pix_green ), 10,pos + (a++ * 20));  
    ofDrawBitmapStringHighlight("blue : " + ofToString(pix_blue), 10,pos + (a++ * 20));  
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
	getPixInfo(x, y);
}

void ofApp::getPixInfo(int _x, int _y){
	//Getting pointer to pixel array of tdf
	unsigned char *data = base_tdf.getPixels();
	//Calculate number of pixel components
	int components = base_tdf.bpp / 8;
	//Modify pixel array
	for (int y=0; y<base_tdf.height; y++) {
	    for (int x=0; x<base_tdf.width; x++) {

	    	if (x == _x && y == _y){
		        //Read pixel (x,y) color components
		        int index = components * (x + base_tdf.width * y);
		        pix_red = data[ index ];
		        pix_green = data[ index + 1 ];
		        pix_blue = data[ index + 2 ];
	    	}
	    }
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
