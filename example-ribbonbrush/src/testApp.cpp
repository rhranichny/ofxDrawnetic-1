#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetVerticalSync(true); 
    ofEnableSmoothing(); 
    path = new ofxSuperPath();
    path->reset();

    marking = NULL;
    brush = NULL;
    paint = NULL;
    
}
//--------------------------------------------------------------
void testApp::update()
{
    if(marking != NULL)
    {
        marking->update();
    }

    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->update();
    }

}
//--------------------------------------------------------------
void testApp::draw()
{
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    if(marking != NULL)
    {
        marking->draw();
    }
    
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->draw();
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    for(int i = 0; i < markings.size(); i++)
    {
        delete markings[i];
    }
    markings.clear();
    
    if(marking != NULL)
    {
        delete marking;
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

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
    path->lineTo(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    path = new ofxSuperPath();
    paint = new ofxPaint(path, ofColor(255), 100);
    brush = new ofxRibbonBrush(path, paint);
    brush->setDynamic(true);
    brush->setSpeed(6);
    brush->setUseAcceleration(false);


    marking = new ofxMarking(path, paint, brush);
    path->reset();
    path->lineStart(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    path->lineEnd(x,y,0, ofGetFrameNum(), -1, 0);
    marking->pathFinished();
    markings.push_back(marking);
    marking = NULL;
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