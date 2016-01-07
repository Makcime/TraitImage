#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    w = 320;
    h = 240;
    
    imgCnt = 0;
    img_path_s << img_path << imgCnt << ".jpg";
    img.loadImage(img_path_s.str());
    img.resize(w, h);
    blobImg = img;
    world = img;
    for (int x = 0; x < world.width; ++x){
        for (int y = 0; y < world.height; ++y){
    		world.setColor(x, y, ofColor::white);
        }
    
	}
	world.update();
    // w = img.width;
    // h = img.height;
    //reserve memory for cv images
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
   
    rgb.draw(0,0);
    contours.draw(0,0);
    // world.draw(500, 0);

   	if (contours.nBlobs > 0){
   		if(blobCnt == contours.nBlobs)
   			blobCnt = 0;
	   	blobImg = img;
		ofRectangle r = contours.blobs[blobCnt].boundingRect;
		blobImg.crop(r.x, r.y, r.width, r.height);

    	blobImg.draw(50, ofGetHeight() / 2);
    	contours.blobs[blobCnt].draw();
	    line = contours.blobs[blobCnt].pts;
	    ofFill();
	    ofSetColor(ofColor::red);
	    line.draw();
	}
    
    ofSetColor(255,255,255);
    world.draw(500, 0);
    // img.draw(0,0);

	float recW = 20;
	float recH = 20;
    recW = world.width / X_DIV;
    recH = world.height / Y_DIV;

   	for (int x = 0; x < X_DIV; ++x){
        for (int y = 0; y < Y_DIV; ++y){
			// ofSetColor(world.getColor(x * recW, y * recH));
			ofSetColor(grid[x][y]);
		    ofFill();
			ofRect(x*(recW+2) +  500, y*(recH+2) + ofGetHeight() / 2, recW, recH);

        }
    }
    // cv::drawContours(img, contours.blobs[blobCnt].pts, 0, (0,255,0), 3);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
    	case OF_KEY_UP:
    		findHue++;
    		break;
    	case OF_KEY_DOWN:
    		findHue--;
            break;
        case OF_KEY_RETURN:
        	done = true;
        	writeConf();
        	imgCnt++;
        	printf("imgCnt = %d\n", imgCnt);
        	if(imgCnt == 5)
        		std::exit(EXIT_SUCCESS);
        	img_path_s.clear();//clear any bits set
			img_path_s.str(std::string());
    	    img_path_s << img_path << imgCnt << ".jpg";
		    img.loadImage(img_path_s.str());
		    img.resize(w, h);
		    blobImg = img;
		    world = img;
		    for (int x = 0; x < world.width; ++x){
		        for (int y = 0; y < world.height; ++y){
		    		world.setColor(x, y, ofColor::white);
		        }
		    
			}
			world.update();
        	break;
        case '+':
            if (contours.nBlobs > 0){
			    ofPoint p;
			    for (int x = 0; x < rgb.width; ++x){
			        for (int y = 0; y < rgb.height; ++y){
			        	p.x = x, p.y = y;
			        	if (line.inside(p)){
			        		ofColor c;
			        		if(findHue>20 && findHue < 35 )
			        			c = ofColor::yellow;
			        		else if(findHue>170 && findHue < 185 )
			        			c = ofColor::red;
			        		else if(findHue>75 && findHue < 90 )
			        			c = ofColor::darkGreen;
			        		else if(findHue>105 && findHue < 120 )
			        			c = ofColor::blue;
			        		else if(findHue>0 && findHue < 10 )
			        			c = ofColor::brown;
			        		else 
			        			c = ofColor::black;

			        		world.setColor(x, y, c);
			        	}
			        }
		        
		    	}
				world.update();
		    }
        	devideImage();
        	break;
        case OF_KEY_TAB:
            // colorImgCroped.saveImage("test.jpg");
        	if (blobCnt++ == contours.nBlobs)
        		blobCnt = 0;
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
    //calculate local mouse x,y in image
    int mx = x % w;
    int my = y % h;
    blobCnt = 0;
    //get hue value on mouse position
    findHue = hue.getPixels()[my*w+mx];
    printf("Hue = %d\n", findHue);
    // findHue = 20;

    //copy webcam pixels to rgb image
    // rgb.setFromPixels(movie.getPixels(), w, h);
    rgb.setFromPixels(img.getPixels(), w, h);
    
    //mirror horizontal
    // rgb.mirror(false, true);
    
    //duplicate rgb
    hsb = rgb;
    
    //convert to hsb
    hsb.convertRgbToHsv();
    
    //store the three channels as grayscale images
    hsb.convertToGrayscalePlanarImages(hue, sat, bri);
    
    //filter image based on the hue value were looking for
    for (int i=0; i<w*h; i++) {
        filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue-5,findHue+5) ? 255 : 0;
    }

    filtered.flagImageChanged();
    //run the contour finder on the filtered image to find blobs with a certain hue
    contours.findContours(filtered, 25, w*h/6, 10, false);
}
void ofApp::devideImage(){

	// float recW = w / X_DIV;
	// float recH = h / Y_DIV;
    float recW = world.width / X_DIV;
	float recH = world.height / Y_DIV;
    for (int x = 0; x < X_DIV; ++x){
        for (int y = 0; y < Y_DIV; ++y){
        	grid[x][y] = world.getColor(x * recW + (recW / 2), y * recH + (recH / 2));
        	int hue = grid[x][y].getHue();
    		if(grid[x][y] == ofColor::yellow)
    			sgrid[x][y] = "yellow";
    		else if(grid[x][y] == ofColor::red)
    			sgrid[x][y] = "red";
    		else if(grid[x][y] == ofColor::darkGreen)
    			sgrid[x][y] = "green";
    		else if(grid[x][y] == ofColor::blue)
    			sgrid[x][y] = "blue";
    		else if(grid[x][y] == ofColor::brown )
    			sgrid[x][y] = "brown";
    		else if(grid[x][y] == ofColor::black )
    			sgrid[x][y] = "black";
    		else
    			sgrid[x][y] = "empty";


        }
    }
}

void ofApp::writeConf(){
	 ofstream fs;
	  fs.open ("data/world.txt", ios_base::app | ios_base::ate);
      for (int x = 0; x < X_DIV; ++x){
        for (int y = 0; y < Y_DIV; ++y){
        	// if (sgrid[x][y] != "empty")
        		fs << x + (imgCnt * X_DIV) << "," << y << ',' << sgrid[x][y] << "\n";
        	sgrid[x][y] = "empty";
	  		// fs << "Writing this to a file.\n";
		}
	}
	  fs.close();
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
