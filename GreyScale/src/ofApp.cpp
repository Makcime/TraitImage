#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	tdf_avg.loadImage("images/tdf_1972_poster.jpg");	
	// tdf.setImageType(OF_IMAGE_GRAYSCALE);   // now I am grayscale;

	//Getting pointer to pixel array of tdf
	unsigned char *data = tdf_avg.getPixels();
	//Calculate number of pixel components
	int components = tdf_avg.bpp / 8;
	//Modify pixel array
	for (int y=0; y<tdf_avg.height; y++) {
	    for (int x=0; x<tdf_avg.width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + tdf_avg.width * y);
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
	//Calling tdf_avg.update() to apply changes
	tdf_avg.update();

	tdf_eq.loadImage("images/tdf_1972_poster.jpg");	
	// tdf.setImageType(OF_IMAGE_GRAYSCALE);   // now I am grayscale;

	//Getting pointer to pixel array of tdf
	data = tdf_eq.getPixels();
	//Calculate number of pixel components
	components = tdf_eq.bpp / 8;
	//Modify pixel array
	for (int y=0; y<tdf_eq.height; y++) {
	    for (int x=0; x<tdf_eq.width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + tdf_eq.width * y);
	        int red = data[ index ];
	        int green = data[ index + 1 ];
	        int blue = data[ index + 2 ];

	        int eq = 0.299 * red + 0.587 * green + 0.114 * blue;

	        //Set red 
	        data[ index + RED] = eq ;
	        //Set green 
	        data[ index + GREEN ] = eq;
	        //Set blue 
	        data[ index + BLUE] = eq;

	    }
	}
	//Calling tdf_eq.update() to apply changes
	tdf_eq.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	tdf_avg.draw(0, 0);
	tdf_eq.draw(400, 0);
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
