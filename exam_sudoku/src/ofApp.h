#pragma once

#include "ofMain.h"

#include "ofxGui.h"

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

		void computeBinarization(ofImage *img, int tresh);
		void drawHisto(int start_x, int start_y);
		void computeHisto();

		ofImage sudoku;
		int Tresh;

        std::vector<int> histDat;

		
};