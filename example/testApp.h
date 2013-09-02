#pragma once

#include "ofMain.h"
#include "ofxBumpShader.h"
// include GUI to control
// some params (OF8.0)
#include "ofxGui.h"

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
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //
    //------------------------------------------------------
    //
    
    ofxBumpShader texture;

    // GUI params
    // if GUI is not included
    // use basic ints & floats (< OF8.0)
    ofxPanel gui;
    ofxFloatSlider lightX;
    ofxFloatSlider lightY;
    ofxFloatSlider lightZ;
    ofxFloatSlider lightShininess;
    // float lightX;
    // float lightY;
    // float lightZ;
    // float lightShininess;
        
};