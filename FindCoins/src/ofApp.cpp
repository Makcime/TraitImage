    #include "ofApp.h"

    //--------------------------------------------------------------
    void ofApp::setup(){
		ofBackground(0,0,0);
    
    	ofSetVerticalSync(true);
    	frameByframe = false;

    	// Uncomment this to show movies with alpha channels
    	// fingerMovie.setPixelFormat(OF_PIXELS_RGBA);

		fingerMovie.loadMovie("movies/coins.mov");
	    fingerMovie.play();
	    
	    frameImg.allocate(fingerMovie.getWidth(), fingerMovie.getHeight(), OF_IMAGE_COLOR);
	    Tresh = 140;          
    }

    //--------------------------------------------------------------
    void ofApp::update(){
        fingerMovie.update();
    }

    //--------------------------------------------------------------
    void ofApp::draw(){

    	ofSetHexColor(0xFFFFFF);

        // fingerMovie.draw(20,20);
        
        unsigned char * pixels = fingerMovie.getPixels();
        frameImg.setFromPixels(pixels, fingerMovie.getWidth(), fingerMovie.getHeight(), OF_IMAGE_COLOR);
        frameImg.crop(100, 0, fingerMovie.getWidth() - 175, fingerMovie.getHeight());

		computeBinarization(&frameImg, Tresh);

        frameImg.draw(20,20);

        
        ofSetHexColor(0x000000);
        int nChannels = fingerMovie.getPixelsRef().getNumChannels();
        
        // let's move through the "RGB(A)" char array
        // using the red pixel to control the size of a circle.
        // for (int i = 4; i < 320; i+=8){
        //     for (int j = 4; j < 240; j+=8){
        //         unsigned char r = pixels[(j * 320 + i)*nChannels];
        //         float val = 1 - ((float)r / 255.0f);
        //         ofCircle(400 + i,20+j,10*val);
        //     }
        // }


     //    ofSetHexColor(0x000000);
    	// ofDrawBitmapString("press f to change",20,320);
     //    if(frameByframe) ofSetHexColor(0xCCCCCC);
     //    ofDrawBitmapString("mouse speed position",20,340);
     //    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
     //    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
     //    ofSetHexColor(0x000000);

     //    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
     //    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
     //    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);

        if(fingerMovie.getIsMovieDone()){
            ofSetHexColor(0xFF0000);
            ofDrawBitmapString("end of movie",20,440);
        }
    }

    //--------------------------------------------------------------
    void ofApp::keyPressed  (int key){
        switch(key){
            case 'f':
                frameByframe=!frameByframe;
                fingerMovie.setPaused(frameByframe);
            break;
            case OF_KEY_LEFT:
                fingerMovie.previousFrame();
            break;
            case OF_KEY_RIGHT:
                fingerMovie.nextFrame();
            break;
            case '0':
                fingerMovie.firstFrame();
            break;
        }
    }

    //--------------------------------------------------------------
    void ofApp::keyReleased(int key){

    }

    //--------------------------------------------------------------
    void ofApp::mouseMoved(int x, int y ){
    	// if(!frameByframe){
     //        int width = ofGetWidth();
     //        float pct = (float)x / (float)width;
     //        float speed = (2 * pct - 1) * 5.0f;
     //        fingerMovie.setSpeed(speed);
    	// }
    }

    //--------------------------------------------------------------
    void ofApp::mouseDragged(int x, int y, int button){
    	// if(!frameByframe){
     //        int width = ofGetWidth();
     //        float pct = (float)x / (float)width;
     //        fingerMovie.setPosition(pct);
    	// }
    }

    //--------------------------------------------------------------
    void ofApp::mousePressed(int x, int y, int button){
    	// if(!frameByframe){
     //        fingerMovie.setPaused(true);
    	// }
    }


    //--------------------------------------------------------------
    void ofApp::mouseReleased(int x, int y, int button){
    	// if(!frameByframe){
     //        fingerMovie.setPaused(false);
    	// }
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