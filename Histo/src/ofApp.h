#pragma once

#include "ofMain.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define LIGHT 3
#define SAT 4
#define HUE 5

struct histoData
{
	int R, G, B, L, S, H;
	
};

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

		ofVideoGrabber 		vidGrabber;
		int 				camWidth;
		int 				camHeight;

        ofTrueTypeFont  font;
        std::vector<histoData> histDat;

        int histoType = 0;

        string histoString[6]=
        {
			"RED",
			"GREEN",
			"BLUE",
			"LIGHT",
			"SAT",
			"HUE"
        };

        int pos_x, start_y;
		
};
