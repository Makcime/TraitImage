#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup(); // most of the time you don't need a name
	gui.add(Tresh.setup( "Treshold", 128, 0, 255 ));
	computeGrayScale(&base_tdf, "images/tdf_1972_poster.jpg", 1);
	computeBinarization(&base_tdf, Tresh);


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	computeGrayScale(&base_tdf, "images/tdf_1972_poster.jpg", 1);
	computeBinarization(&base_tdf, Tresh);
	base_tdf.draw(350, 0);
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

void ofApp::computeBinarization(ofImage *img, int tresh){

	//Getting pointer to pixel array of tdf
	unsigned char *data = img->getPixels();
	//Calculate number of pixel components
	int components = img->bpp / 8;
	//Modify pixel array
	for (int y=0; y<img->height; y++) {
	    for (int x=0; x<img->width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + img->width * y);
	        int gray = data[ index ];

	        int bin = 0;

	        if (gray > tresh)
	        	bin = 255;

	        //Set red 
	        data[ index + RED] = bin ;
	        //Set green 
	        data[ index + GREEN ] = bin;
	        //Set blue 
	        data[ index + BLUE] = bin;

	    }
	}
	//Calling img.update() to apply changes
	img->update();	
}

