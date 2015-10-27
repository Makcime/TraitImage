#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

    font.loadFont("Courier New Bold.ttf", 9);
    
    // this set of characters comes from processing: 
    //http://processing.org/learning/library/asciivideo.html
    
	// changed order slightly to work better for mapping
    // asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
	
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidGrabber.draw(0,0);
    ofColor col_hsb;
    int histo[255] = {0};


    // ofPixelsRef pixelsRef = vidGrabber.getPixelsRef();
    // ofPixelsRef pixelsRef = vidGrabber.getPixelsRef();
	unsigned char *data = vidGrabber.getPixels();
    int components = 3;
    ofSetHexColor(0xffffff);

    int pixs = 0;

	for (int y=0; y<camHeight; y++) {
	    for (int x=0; x<camWidth; x++) {
	        //Read pixel (x,y) color components
	        int index = components * (x + camWidth * y);
	        int red = data[ index ];
	        int green = data[ index + 1 ];
	        int blue = data[ index + 2 ];

	        col_hsb.set(red, green, blue);

	        float L = col_hsb.getBrightness();
	        float S = col_hsb.getSaturation();
	        float H = col_hsb.getHue();

	        histDat.push_back({red, green, blue, L, S, H});

	        pixs++;

        }
    }

    ofSetHexColor(0xffffff);
    int pos_x, start_y, end_y;

    pos_x = camWidth + 10;
    start_y = camHeight;

    for (std::vector<histoData>::iterator i = histDat.begin(); i != histDat.end(); ++i){
    	// cout << (*i).R << "-" ;
    	switch(histoType){
    		case RED:
    			histo[(*i).R]++;
    		break;
    		case GREEN:
    			histo[(*i).G]++;
    		break;
  	  		case BLUE:
    			histo[(*i).B]++;
			break;
			case LIGHT:
    			histo[(*i).L]++;
			break;
			case SAT:
    			histo[(*i).S]++;
			break;
			case HUE:
    			histo[(*i).H]++;
			break;


    	}
    }
    histDat.clear();


    for (int i = 0; i < 255; ++i){
    	// cout << histo[i] << endl;
    	end_y = start_y - (histo[i]/50);
    	pos_x++;
    	ofLine(pos_x++, start_y, pos_x, end_y);
    }

    font.drawString(histoString[histoType], pos_x, start_y);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
    case OF_KEY_UP:
    	histoType++;
	    if (histoType > 5)
    		histoType = 0;
        break;
    case OF_KEY_DOWN:
    	histoType--;
	    if (histoType < 0)
    		histoType = 5;
        break;
    default:
        break;
    }


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
