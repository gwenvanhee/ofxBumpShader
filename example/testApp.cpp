#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    texture.setup("myTexture");

    gui.setup();
    gui.add(lightX.setup("light.x", 0, -3000, 3000));
    gui.add(lightY.setup("light.y", 0, -3000, 3000));
    gui.add(lightZ.setup("light.z", 0, -3000, 3000));
    gui.add(lightShininess.setup("light.shininess", 64, 0, 128));

}

//--------------------------------------------------------------
void testApp::update(){
                  
}

//--------------------------------------------------------------
void testApp::draw(){

    enableLights();

    texture.begin();
    ofSphere(0, 0, 0, 100);
    texture.end();

}

//--------------------------------------------------------------
void testApp::enableLights(){

    // light params
    GLfloat position[]   = { lightX, lightY, lightZ, 1 };
    GLfloat ambient[]    = { .05, .05, .05, 1 };
    GLfloat diffuse[]    = { 1, 1, 1, .5 };
    GLfloat specular[]   = { 1, 1, 1, 1 };
    GLfloat reflection[] = { 1, 1, 1, 1 };
    GLfloat material[]   = { 1, 1, 1, 1 };
    
    // light components
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    // material components
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reflection);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, lightShininess);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
        
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
