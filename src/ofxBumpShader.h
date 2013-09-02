#pragma once

#include "ofMain.h"

class ofxBumpShader : public ofNode{
public:

    void setup(string texture);
    void begin();
    void transparency(float alpha = 1);
    void end();
    
private:
    
    ofImage textureMapImage;
    ofImage normalMapImage;
    ofImage diffuseMapImage;
    
    ofTexture textureMap;
    ofTexture normalMap;
    ofTexture diffuseMap;
    
    ofShader shader;
    
};