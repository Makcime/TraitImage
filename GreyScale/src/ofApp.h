#pragma once

#include "ofMain.h"

#define RED 0
#define GREEN 1
#define BLUE 2

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

		void computeGrayScale(ofImage *img, char * path, int lev);

		ofImage tdf_avg;
		ofImage tdf_eq;
		ofImage tdf_eq_base;

		int level;
		
};
