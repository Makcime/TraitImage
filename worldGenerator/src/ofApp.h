#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define X_DIV 22
#define Y_DIV 22

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void devideImage();
		void writeConf();

		
		ofImage img, world;
		ofImage blobImg;

		ofxCvColorImage rgb,hsb;
	    ofxCvGrayscaleImage hue,sat,bri,filtered;    
    	ofxCvContourFinder contours;
    
	    int w,h;
	    int findHue;
	    int blobCnt;
	    int imgCnt;

	    string img_path = "images/img";
	    stringstream img_path_s;


	    bool done = false;

	    ofColor grid [X_DIV][Y_DIV];
	    string sgrid [X_DIV][Y_DIV];

	    ofPolyline line;


};
