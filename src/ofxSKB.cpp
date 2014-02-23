/*--------------------------------------------------------------

By: digitalhack
Date: Feb 2014
Description: openFrameworks addon to create an on-screen keyboard.

Inspired by ofxSoftKeybaord by Jeffrey Crouse and hosted on 
github by Lensley.

--------------------------------------------------------------*/

#include "ofxSKB.h"

//--------------------------------------------------------------
ofxSKB::ofxSKB() {
  kbFontName = "";
  kbSetWidth = 0;
  kbSetWidthOld = 0;

  caps = false;
  shift = false;
  shift1KeyPressed = false;
  moveKeyboard = false;
  resizeKeyboard = false;

  textColor = 0x000000;
	textBGColor = 0x888888;
	borderColor = 0x000000;
	hoverColor = 0x999999;
	clickColor = 0xFF0000;

  kbBaseWidth = (DEFAULT_W * 13) + DELETE_W + (KEY_P * 28);
  kbBaseHeight = (KEY_H * 5) + (KEY_P * 10);

  addKey('~', '`'); addKey('1', '!'); addKey('2', '@');
  addKey('3', '#'); addKey('4', '$'); addKey('5', '%');
  addKey('6', '^'); addKey('7', '&'); addKey('8', '*');
  addKey('9', '('); addKey('0', ')'); addKey('-', '_');
  addKey('+', '='); addKey(OF_KEY_DEL,-1, true);

  addKey(OF_KEY_TAB, -1); addKey('q', 0); addKey('w', 0);
  addKey('e', 0); addKey('r', 0); addKey('t', 0);
  addKey('y', 0); addKey('u', 0); addKey('i', 0);
  addKey('o', 0); addKey('p', 0); addKey('[', 0);
  addKey(']', 0); addKey('|', 0, true);

  addKey(OFXSKB_KEY_CAPS, -1); ; addKey('a', 0); addKey('s', 0);
  addKey('d', 0); addKey('f', 0); addKey('g', 0);
  addKey('h', 0); addKey('j', 0); addKey('k', 0);
  addKey('l', 0); addKey(';', ':'); addKey('\'', '\"');
  addKey(OF_KEY_RETURN, -1, true);

  addKey(OF_KEY_SHIFT, -1); addKey('z', 0); addKey('x', 0);
  addKey('c', 0); addKey('v', 0); addKey('b', 0);
  addKey('n', 0); addKey('m', 0); addKey(',', '<');
  addKey('.', '>'); addKey('/', '?'); addKey(OF_KEY_SHIFT, -1, true);

  addKey(OFXSKB_KEY_MOVE, -1);

  addKey(' ', -1);
  keys.back().basePadLeft = SPACE_P - KEY_P - (DEFAULT_W*2);
  keys.back().basePadRight = SPACE_P - (KEY_P * 5) - (DEFAULT_W*4);
  keys.back().baseWidth = SPACE_W;

  addKey(OFXSKB_KEY_HIDE, -1);
  addKey(OFXSKB_KEY_RESIZE, -1);

  showKeyboard();
}

//--------------------------------------------------------------
ofxSKB::~ofxSKB() {
  hideKeyboard();
  keys.clear();
}

//--------------------------------------------------------------
void ofxSKB::addKey(int _key0, int _key1, bool lastInRow) {
  ofxSKBKeyType key;

  key.key[0] = _key0;
	if (_key1 == 0) {
    key.key[1] = (char)(_key0 - 32);
	} else {
	  key.key[1] = _key1;
	}

  key.isLastInRow = lastInRow;

	key.basePadTop = KEY_P;
	key.basePadRight = KEY_P;
	key.basePadBottom = KEY_P;
	key.basePadLeft = KEY_P;

 	switch(_key0) {
		case OF_KEY_SHIFT:
			key.label[0] = "shift";
			key.label[1] = "SHIFT";
			key.key[1] = OF_KEY_SHIFT;
			key.baseWidth = SHIFT_W;
			key.baseHeight = KEY_H;
			break;
		case OF_KEY_TAB:
			key.label[0] = "tab";
			key.label[1] = "TAB";
			key.key[1] = OF_KEY_TAB;
			key.baseWidth = TAB_W;
			key.baseHeight = KEY_H;
			break;
		case OFXSKB_KEY_CAPS:
			key.label[0] = "caps";
			key.label[1] = "CAPS";
			key.key[1] = OFXSKB_KEY_CAPS;
			key.baseWidth = CAPS_W;
			key.baseHeight = KEY_H;
			break;
		case OF_KEY_DEL:
			key.label[0] = "delete";
			key.label[1] = "DELETE";
			key.key[1] = OF_KEY_DEL;
			key.baseWidth = DELETE_W;
			key.baseHeight = KEY_H;
			break;
		case OF_KEY_RETURN:
			key.label[0] = "return";
			key.label[1] = "RETURN";
      key.key[1] = OF_KEY_RETURN;
			key.baseWidth = RETURN_W;
			key.baseHeight = KEY_H;
			break;
		case OFXSKB_KEY_MOVE:
			key.label[0] = "move";
			key.label[1] = "MOVE";
      key.key[1] = OFXSKB_KEY_MOVE;
			key.baseWidth = DEFAULT_W*2;
			key.baseHeight = KEY_H;
			break;
		case OFXSKB_KEY_HIDE:
			key.label[0] = "hide";
			key.label[1] = "HIDE";
      key.key[1] = OFXSKB_KEY_HIDE;
			key.baseWidth = DEFAULT_W*2;
			key.baseHeight = KEY_H;
			break;
		case OFXSKB_KEY_RESIZE:
			key.label[0] = "resize";
			key.label[1] = "RESIZE";
      key.key[1] = OFXSKB_KEY_RESIZE;
			key.baseWidth = DEFAULT_W*2;
			key.baseHeight = KEY_H;
			break;
		default:
			key.label[0] = string(1, key.key[0]);
			key.label[1] = string(1, key.key[1]);
			key.baseWidth = DEFAULT_W;
			key.baseHeight = KEY_H;
			break;
	}
	keys.push_back( key );
}

//--------------------------------------------------------------
void ofxSKB::setFont(string _kbFontName) {
  kbFontName = _kbFontName;
}

//--------------------------------------------------------------
void ofxSKB::setSize(float _width) {
  kbSetWidth = _width;
}

//--------------------------------------------------------------
float ofxSKB::getSize() {
  return kbSetWidth;
}

//--------------------------------------------------------------
void ofxSKB::setPosition(float _x, float _y) {
  x = _x;
  y = _y;
}

//--------------------------------------------------------------
ofVec2f ofxSKB::getPosition() {
  ofVec2f vtmp;
  vtmp.set(x, y);
  return vtmp;
}

//--------------------------------------------------------------
bool ofxSKB::keyboardVisible() {
  return kbShow;
}

//--------------------------------------------------------------
void ofxSKB::hideKeyboard() {
  if (kbShow) {
    kbShow = false;
    ofUnregisterMouseEvents(this);
  }
}

//--------------------------------------------------------------
void ofxSKB::showKeyboard() {
  if (!kbShow) {
    kbShow = true;
    ofRegisterMouseEvents(this);
  }
}

//--------------------------------------------------------------
int ofxSKB::shiftState(int _action, int _key) {
  if ((_key == OFXSKB_KEY_CAPS) || (_key == OF_KEY_SHIFT) || (shift)) {
    if ((_action == OFXSKB_PRESS) && (_key == OFXSKB_KEY_CAPS)) {
      caps = !caps;
      shift = 0;
      shift1KeyPressed = 0;
    } else if ((_action == OFXSKB_PRESS) && (_key == OF_KEY_SHIFT)) {
      shift = !shift;
      shift1KeyPressed = 0;
    } else if ((_action == OFXSKB_PRESS) && (shift)) {
      if (shift1KeyPressed) {
        shift = 0;
        shift1KeyPressed = 0;
      } else {
        shift1KeyPressed = 1;
      }
    } else if ((_action == OFXSKB_RELEASE) && (shift) && (shift1KeyPressed)) {
      shift = 0;
      shift1KeyPressed = 0;
      if (caps) {
        return 0;
      } else {
        return 1;
      }
    }
  }

  if (!caps) {
    if (!shift) { return 0; } else { return 1; }
  } else {
    if (!shift) { return 1; } else { return 0; }
  }
}

bool ofxSKB::keyTest(ofxSKBKeyType key, int tx, int ty) {
	return ((tx > key.x) && (tx < key.x + key.width) && (ty > key.y) && (ty < key.y + key.height));
}

//--------------------------------------------------------------
void ofxSKB::draw() {
	float xpos = x;
	float ypos = y;

  if (kbShow) {
    if (kbSetWidth != kbSetWidthOld) {
      if (kbSetWidth == 0) {
        ofLogError() << "Screen Keyboard size not set call ofxSKB::setSize()";
        ofExit();
      }

      if (kbFontName == "") {
        ofLogError() << "Screen Keyboard font not set call ofxSKB::setFont()";
        ofExit();
      }

      kbSizer = kbSetWidth / kbBaseWidth;

      kbWidth = kbBaseWidth * kbSizer;
      kbHeight = kbBaseHeight * kbSizer;

      if (kbFont.isLoaded()) kbFont.unbind();
      kbFont.loadFont(kbFontName, 2*kbSizer);
      for(unsigned int i=0; i<keys.size(); i++) {
        keys[i].width = keys[i].baseWidth*kbSizer,
        keys[i].height = keys[i].baseHeight*kbSizer;
        keys[i].padTop = keys[i].basePadTop*kbSizer;
        keys[i].padRight = keys[i].basePadRight*kbSizer;
        keys[i].padBottom = keys[i].basePadBottom*kbSizer;
        keys[i].padLeft = keys[i].basePadLeft*kbSizer;
      }
    }
    ofSetHexColor(borderColor);
    ofRect(x, y, kbWidth, kbHeight);

    ypos += keys[0].padTop;

    for(unsigned int i=0; i<keys.size(); i++) {
      xpos += keys[i].padLeft;

      keys[i].x = xpos;
      keys[i].y = ypos;

      if (keyTest(keys[i], ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY)) {
        ofSetHexColor(hoverColor);
      } else {
        ofSetHexColor(textBGColor);
      }

     	ofFill();
      ofRect(xpos, ypos, keys[i].width, keys[i].height);

      // Draw the outline.
      ofNoFill();
      ofSetHexColor(borderColor);
      ofRect(xpos, ypos, keys[i].width, keys[i].height);

      // Draw the actual letter
      ofSetHexColor(textColor);

      int tmp = shiftState();
      kbFont.drawString(keys[i].label[tmp], xpos+keys[i].padLeft,
                         (ypos+(keys[i].height))-keys[i].padTop);
#ifdef TARGET_SUNXI_MFB
#pragma message ("ofEnableAlphaBlending() inserted")
      ofEnableAlphaBlending();
#endif
      if(keys[i].isLastInRow) {
        xpos  = x;
        ypos += keys[i].height + keys[i].padBottom + keys[i].padTop;
      } else {
        xpos += keys[i].width + keys[i].padRight;
      }
    }
  }
}

//???Need to work on boundaries

//--------------------------------------------------------------
void ofxSKB::mouseDragged(ofMouseEventArgs& args){
  if (resizeKeyboard) {
    if (((args.x + 10) < ofGetWidth()) && ((args.y + 10) < ofGetHeight())) {
      float tkbSetWidth;
      tkbSetWidth = kbSetWidth - (previousX - args.x);
      if ((tkbSetWidth > 100) || (tkbSetWidth > kbSetWidth)) {
        kbSetWidth = tkbSetWidth;
      }
    }
  } else if (moveKeyboard) {
    if ((args.x + kbWidth) < ofGetWidth()) {
      x = x - (previousX - args.x);
    }
    if ((args.y +10) < ofGetHeight()) {
      y = y - (previousY - args.y);
    }
  }
  previousX = args.x;
  previousY = args.y;
};

//--------------------------------------------------------------
void ofxSKB::mouseMoved(ofMouseEventArgs& args){
  previousX = args.x;
  previousY = args.y;
}

//--------------------------------------------------------------
void ofxSKB::mousePressed(ofMouseEventArgs& args){
  for(unsigned int i=0; i<keys.size(); i++) {
    if (keyTest(keys[i], ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY)) {
        int tmp = shiftState(OFXSKB_PRESS, keys[i].key[0]);

        switch(keys[i].key[tmp]) {
          case OF_KEY_SHIFT:
            break;
          case OF_KEY_TAB:
            ofNotifyKeyPressed('\t');
            break;
          case OFXSKB_KEY_CAPS:
            break;
          case OF_KEY_DEL:
            ofNotifyKeyPressed(OF_KEY_BACKSPACE);
            break;
          case OF_KEY_RETURN:
            ofNotifyKeyPressed('\n');
            break;
          case OFXSKB_KEY_MOVE:
            moveKeyboard = true;
            break;
          case OFXSKB_KEY_HIDE:
            hideKeyboard();
            break;
          case OFXSKB_KEY_RESIZE:
            resizeKeyboard = true;
            break;
          default:
            ofNotifyKeyPressed(keys[i].key[tmp]);
            break;
        }
      break;
    }
  }
}

//--------------------------------------------------------------
void ofxSKB::mouseReleased(ofMouseEventArgs& args){
  moveKeyboard = false;
  resizeKeyboard = false;
  for(unsigned int i=0; i<keys.size(); i++) {
    if (keyTest(keys[i], ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY)) {
        int tmp = shiftState(OFXSKB_RELEASE, keys[i].key[0]);

        switch(keys[i].key[tmp]) {
          case OF_KEY_SHIFT:
            break;
          case OF_KEY_TAB:
            ofNotifyKeyReleased('\t');
            break;
          case OFXSKB_KEY_CAPS:
            break;
          case OF_KEY_DEL:
            ofNotifyKeyReleased(OF_KEY_BACKSPACE);
            break;
          case OF_KEY_RETURN:
            ofNotifyKeyReleased('\n');
            break;
          case OFXSKB_KEY_MOVE:
          case OFXSKB_KEY_HIDE:
          case OFXSKB_KEY_RESIZE:
            break;
          default:
            ofNotifyKeyReleased(keys[i].key[tmp]);
            break;
        }
      break;
    }
  }
}

