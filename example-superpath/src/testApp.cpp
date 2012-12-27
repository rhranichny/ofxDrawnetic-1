#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofEnableSmoothing(); 
    path = new ofxSuperPath();
    thicknessType = OFX_PATH_PRESSURE_DISTANCE;
    path->setPathPressureType(thicknessType);   //by default this is enable so this call isn't necessary
    path->reset();
}
//--------------------------------------------------------------
void testApp::update()
{

}
//--------------------------------------------------------------
void testApp::draw()
{
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDrawBitmapString("ofxSuperpath: inherits from ofPolyline. It keeps track of velocities and accelerations.", 10, 20);
    ofDrawBitmapString("It also stores the path's thickness, which can be based on the distance between points, input pressure or a fixed thickness.", 10, 40);
    
    ofSetColor(100);
    ofDrawBitmapString("Press 1 for Thickness based on Distance.", 10, 60);
    ofDrawBitmapString("Press 2 for thickness on Sinusoidal Pressure.", 10, 80);
    ofDrawBitmapString("Press 3 for a Fixed Thickness.", 10, 100);
    
    path->drawPositions();
    path->drawThicknesses();
    path->drawVelocities();
    path->drawAccelerations();
    ofSetColor(0,200);
    path->drawPointNumbers(); 
}
//--------------------------------------------------------------
void testApp::exit()
{
    delete path;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key)
    {
        case '1':
            thicknessType = OFX_PATH_PRESSURE_DISTANCE;
            break;

        case '2':
            thicknessType = OFX_PATH_PRESSURE_PRESSURE; 
            break;

        case '3':
            thicknessType = OFX_PATH_PRESSURE_FIXED; 
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    path->lineTo(x,y,0, ofFloatColor(0), ofGetFrameNum(), sinPressure);
    
    if(thicknessType == OFX_PATH_PRESSURE_PRESSURE)
    {
        sinPressure = 100*fabs(sin(theta));
        theta+=PI*.1;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    path->reset();
    path->setPathPressureType(thicknessType);
    
    switch (thicknessType)
    {
        case OFX_PATH_PRESSURE_DISTANCE:
            //nothing needs to be set 
            break;
            
        case OFX_PATH_PRESSURE_PRESSURE:
            theta = 0; 
            sinPressure = 0;    //this could be set using touch screen pressure if you have access to that
                                //instead we are going to use a sin wave to modulate the pressure
            break;
            
        case OFX_PATH_PRESSURE_FIXED:
            path->setFixedThickness(70);
            break;
            
        default:
            break;
    }
 
    path->lineStart(x,y,0, ofFloatColor(0), ofGetFrameNum(), sinPressure);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    path->lineEnd(x,y,0, ofGetFrameNum(), -1, sinPressure);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}