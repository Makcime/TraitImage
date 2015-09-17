#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	base_tdf.loadImage("images/tdf_1972_poster.jpg");	

	level = 1;
	computeGrayScale(&tdf_eq_base , "images/tdf_1972_poster.jpg", level);
	computeGrayScale(&tdf_eq , "images/tdf_1972_poster.jpg", level);
	keepRed(&tdf_red, "images/tdf_1972_poster.jpg");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	base_tdf.draw(0, 0);
	tdf_red.draw(400, 0);
	tdf_eq.draw(800, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
    case OF_KEY_UP:
    	level++;
    	if (level > 255){ level = 255;}
		computeGrayScale(&tdf_eq, "images/tdf_1972_poster.jpg", level);
        break;
    case OF_KEY_DOWN:
    	level--;
    	if (level < 1){ level = 1;}
		computeGrayScale(&tdf_eq, "images/tdf_1972_poster.jpg", level);
        break;
    default:
        break;
    }

    printf("level : %d\n", 256 / level);
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

//--------------------------------------------------------------
void ofApp::computeGrayScale( ofImage *img, char * path, int lev){
	img->loadImage(path);	
	// tdf.setImageType(OF_IMAGE_GRAYSCALE);   // now I am grayscale;

	//Getting pointer to pixel array of tdf
	unsigned char *data = img->getPixels();
	//Calculate number of pixel components
	int components = img->bpp / 8;
	//Modify pixel array
	for (int y=0; y<img->height; y++) {
	    for (int x=0; x<img->width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + img->width * y);
	        int red = data[ index ];
	        int green = data[ index + 1 ];
	        int blue = data[ index + 2 ];

	        int eq = 0.299 * red + 0.587 * green + 0.114 * blue;

	        eq -= eq % lev; 

	        //Set red 
	        data[ index + RED] = eq ;
	        //Set green 
	        data[ index + GREEN ] = eq;
	        //Set blue 
	        data[ index + BLUE] = eq;

	    }
	}
	//Calling img.update() to apply changes
	img->update();
}

void ofApp::keepRed(ofImage *img, char * path){
	img->loadImage(path);	
	// tdf.setImageType(OF_IMAGE_GRAYSCALE);   // now I am grayscale;

	//Getting pointer to pixel array of tdf
	unsigned char *data = img->getPixels();
	//Calculate number of pixel components
	int components = img->bpp / 8;
	//Modify pixel array
	for (int y=0; y<img->height; y++) {
	    for (int x=0; x<img->width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + img->width * y);
	        int red = data[ index ];
	        int green = data[ index + 1 ];
	        int blue = data[ index + 2 ];

	        int eq = 0.299 * red + 0.587 * green + 0.114 * blue;

	        //Set red 
	        data[ index + RED] = red ;
	        //Set green 
	        data[ index + GREEN ] = eq;
	        //Set blue 
	        data[ index + BLUE] = eq;

	    }
	}
	//Calling img.update() to apply changes
	img->update();
}
