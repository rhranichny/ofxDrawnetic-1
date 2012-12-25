/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

/********************************************************************************** 
 README: This class is used to represent a marking. A marking is composed of a brush, 
 paint and path. The brush contains information about how the marking moves and is 
 rendered. The paint contains information about the color used in the brush. The path 
 contains the positions, velocities and other information related to the actual marking
 path. 
 
 **********************************************************************************/

#ifndef OFXMARKING
#define OFXMARKING

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"

class ofxMarking 
{    
public:
    ofxMarking(ofxSuperPath *_path, ofxPaint *_paint, ofxBrush*_brush)
    {
        path = _path; 
        paint = _paint; 
        brush = _brush; 
        isDead = false; 
    }
    
    ~ofxMarking()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Marking");                                                        
        delete path;  
        delete paint; 
        delete brush;
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Marking");                                                        
    }
    
    void update()
    {
        paint->update();
        brush->update();        
    }
    
    void draw()
    {
        brush->draw();
//        drawDebug();        
    }    
    
    void drawDebug()
    {
        ofSetColor(0);
        ofSetLineWidth(2);
        path->draw();
        path->drawColors();    
        
//        ofSetColor(0);    
//        glPointSize(4);
//        path->drawPositions();      
//        path->drawVelocities();
//        path->drawAccelerations();
//        path->drawThicknesses();    
    }
    
    ofxBrush *getBrush()
    {
        return brush; 
    }
    
    ofxPaint *getPaint()
    {
        return paint; 
    }
    
    ofxSuperPath *getPath()
    {
        return path; 
    }
    
    void pathFinished()
    {
        brush->pathFinished();
    }
    
    void setMarkingID(int _markingID)
    {
        markingID = _markingID;
    }
    
    int getMarkingID()
    {
        return markingID; 
    }        
    
    void killLastParticle()
    {
        cout << "pcount: " << brush->getParticleCount() << endl; 
        if(brush->getParticleCount() > 0)
        {
            brush->killLastParticle();        
        }
        else
        {
            isDead = true; 
        }
    }
    
    ofxSuperPath *path;         //contains path information, positions, velocities, accelerations, thicknesses
    ofxPaint *paint; 
    ofxBrush *brush;     //contains movement instructions / algorithm, i.e. Perlin, Flocking, attractors, automata, particles, etc
    int markingID; 
    bool isDead; 
};

#endif