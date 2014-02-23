#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSKB.h"

#define LOGLEVEL OF_LOG_VERBOSE
//#define LOGLEVEL OF_LOG_WARNING

class testApp : public ofBaseApp{

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



		ofTrueTypeFont 	statusFont;
		char eventString[255];
		string message;

		int kbSize;
		int oldKbSize;
};

#endif
