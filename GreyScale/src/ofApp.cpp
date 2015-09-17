#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	tdf.loadImage("images/tdf_1972_poster.jpg");	
	// tdf.setImageType(OF_IMAGE_GRAYSCALE);   // now I am grayscale;

	//Getting pointer to pixel array of tdf
	unsigned char *data = tdf.getPixels();
	//Calculate number of pixel components
	int components = tdf.bpp / 8;
	//Modify pixel array
	for (int y=0; y<tdf.height; y++) {
	    for (int x=0; x<tdf.width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + tdf.width * y);
	        int red = data[ index ];
	        int green = data[ index + 1 ];
	        int blue = data[ index + 2 ];

	        int avg = (red + green + blue ) / 3;

	        //Set red 
	        data[ index + RED] = avg ;
	        //Set green 
	        data[ index + GREEN ] = avg;
	        //Set blue 
	        data[ index + BLUE] = avg;

	    }
	}
	//Calling tdf.update() to apply changes
	tdf.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	tdf.draw(0, 0);
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
