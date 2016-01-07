#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
    Tresh = 127;

    sudoku.loadImage("images/sudoku.png");         
	computeBinarization(&sudoku, Tresh);
	computeHisto();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	sudoku.draw(0, 0);
	drawHisto(0, 600);

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


/**
 * @brief draw the histogram from the Histodata
 */
void ofApp::drawHisto(int start_x, int start_y){
	// draw a line for each elmt in the hestoData
	int x_pos = start_x, end_y;
    ofSetHexColor(0xffffff);

	for (std::vector<int>::iterator i = histDat.begin(); i != histDat.end(); ++i){
    	end_y = start_y - (*i);
    	// printf("%d\n", (*i));
    	ofLine(x_pos++, start_y, x_pos, end_y);
	}
}

void ofApp::computeHisto(){
  	ofColor col_hsb;
    int histo[255] = {0};

	unsigned char *data = sudoku.getPixels();
    int components = 3;

    int pixs = 0;

	for (int x=0; x<sudoku.width; x++) {
		for (int y=0; y<sudoku.height; y++) {
	        //Read pixel (x,y) color components
	        // int index = components * (x + x<sudoku.width * y);
	        // int red = data[ index ];
	        // int green = data[ index + 1 ];
	        // int blue = data[ index + 2 ];

	        ofColor c = sudoku.getColor(x, y);
	        if (c.getBrightness()  == 0){
	        	pixs++;
	        	// getchar();
	        }
        }
    	printf("%d  - ", pixs);
        histDat.push_back(pixs);
        pixs = 0;
    }
}


/**
 * @brief Binarize an image with a specific trshold
 * 
 * @param img poiter to the image to modify
 * @param tresh value of treshold for 0 to 255
 */
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
