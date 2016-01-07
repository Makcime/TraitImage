#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	image.loadImage("images/test.jpg");
	dilate.loadImage("images/test.jpg");
	origin.loadImage("images/test.jpg");
	image.resize(image.width / 3, image.height / 3);
	dilate.resize(dilate.width / 3, dilate.height / 3);
	origin.resize(origin.width / 3, origin.height / 3);
	origin_data = image.getPixels();
	updateIm();
	dilateIm();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	origin.draw(0, 0);
	image.draw(origin.width+50, 0);
	dilate.draw((origin.width+50)*2, 0);

}

void ofApp::updateIm(){
	//image.loadImage("images/sud.jpeg");
	//tdf_original.loadImage("images/gilles.jpg");
	//Getting pointer to pixel array of image
	unsigned char *data = image.getPixels();
	//Calculate number of pixel components
	int components = image.bpp / 8;

		//Modify pixel array
	for (int y=0; y<image.height; y++) {
		for (int x=0; x<image.width; x++) {
			//Read pixel (x,y) color components
			int index = components * (x + image.width * y);
			

			int red = origin_data[ index ];
			int green = origin_data[ index + 1 ];
			int blue = origin_data[ index + 2 ];

			ofColor color;
			color.set(red,green,blue);
			int b; 
			b = color.getBrightness();

			if(b < 100){
			data[ index ] = 0 ;
			data[ index + 1 ] = 0;
			data[ index + 2 ] = 0;
			}else{
			data[ index ] = 255;
			data[ index + 1 ] = 255;
			data[ index + 2 ] = 255;
			}
			

		}
	}
	
	//Calling image.update() to apply changes
	image.update();
}

void ofApp::dilateIm(){
	//image.loadImage("images/sud.jpeg");
	//tdf_original.loadImage("images/gilles.jpg");
	//Getting pointer to pixel array of image
	unsigned char *data = dilate.getPixels();
	//Calculate number of pixel components
	int components = dilate.bpp / 8;

		//Modify pixel array
	for (int y=0; y<dilate.height; y++) {
		for (int x=0; x<dilate.width; x++) {
			//Read pixel (x,y) color components
			int index = components * (x + dilate.width * y);
			

			int red = origin_data[ index ];
			int green = origin_data[ index + 1 ];
			int blue = origin_data[ index + 2 ];

			ofColor color;
			color.set(red,green,blue);
			int b; 
			b = color.getBrightness();

			if(b < 126){
			dilate.setColor(x, y, ofColor::black);
			if(y<dilate.height) dilate.setColor(x, y+1, ofColor::black);
			if(y>0) dilate.setColor(x, y-1, ofColor::black);
			if(x<dilate.width) dilate.setColor(x+1, y, ofColor::black);
			if(x>0) dilate.setColor(x-1, y, ofColor::black);
			}else{
			data[ index ] = 255;
			data[ index + 1 ] = 255;
			data[ index + 2 ] = 255;
			}
			

		}
	}
	
	//Calling image.update() to apply changes
	dilate.update();
}

int ofApp::linearFilter(int index, int _x, int _y){

	int t=255;
	int* tab = new int[9];
	//int _x = list_pix[index].getX();
	//int _y = list_pix[index].getY();
	int components = image.bpp / 8;
	int it = 0;
	if(_x > 1 && _y > 1 && _x < image.width-2 && _y < image.height-2){
		for (int y=_y-1; y<_y+2; y++) {
			for (int x=_x-1; x<_x+2; x++) {
				int i = components * (x + image.width * y);

				int red = origin_data[ i ];
				int green = origin_data[ i + 1 ];
				int blue = origin_data[ i + 2 ];

				ofColor color;
				color.set(red,green,blue);
				int b; 
				b = color.getBrightness();

				tab[it]=b;
				it++;
				//sum += list_pix[i].getL();
			}
		}
		//sum=1000;
		//t = sum/400;
	}
	sort(tab, tab + 9);
	t = tab[4];
	//if(t>60) t = t-60;
	return t;
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
