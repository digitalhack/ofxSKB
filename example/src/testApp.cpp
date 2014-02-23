#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofSetLogLevel(LOGLEVEL);
  ofLogToConsole();
  ofLogVerbose() << "Starting...";
  ofLogVerbose() << "ofApp::setup";

	ofSetFrameRate(60);

	statusFont.loadFont("verdana.ttf", 10);

	kbSize = 700;
	oldKbSize = 700;

 	message = "";

  keyboard.setFont("verdana.ttf");
  keyboard.setSize(kbSize);
  keyboard.setPosition(10, 100);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
  char tMsg[80];

//==============================================================
	keyboard.draw();
//==============================================================

	ofSetColor(0, 0, 0);
  sprintf(tMsg, "kbSize: %d", kbSize);
  statusFont.drawString(tMsg, 10, 30);
	statusFont.drawString(eventString, 10, 50);
	statusFont.drawString(message, 10, 70);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	sprintf(eventString, "keyPressed = %c (ASCII %i)", key, key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	sprintf(eventString, "keyReleased = %c (ASCII %i)", key, key);

	if(key == OF_KEY_BACKSPACE) {
		message = message.substr(0, message.size()-1);
	} else {
		message += (char)key;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  //ofLogVerbose() << "mousePressed: " << button;
  if (button == 2) {
    if (keyboard.keyboardVisible()) {
      keyboard.hideKeyboard();
    } else {
      keyboard.showKeyboard();
    }
  }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

