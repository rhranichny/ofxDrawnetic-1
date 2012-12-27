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
 README: This class is use to model the brush used in drawnetic, all other brushes 
 inherit from this class and virtual update and draw are what make drawnetic's 
 dynamic brushes possible. Each brush contains algorithms for each type of movement
 
 **********************************************************************************/

#ifndef OFXBRUSH
#define OFXBRUSH

#include "ofMain.h"
#include "ofxPaint.h"
#include "ofxSuperPath.h"

enum ofxBrushType
{
    OFX_BRUSH_BASE = 0,
	OFX_BRUSH_KINETIC = 1,
    OFX_BRUSH_PERLIN = 2,
    OFX_BRUSH_FLOCKING = 3,
    OFX_BRUSH_SCATTER = 4,
    OFX_BRUSH_VELOCITY = 5,
    OFX_BRUSH_ACCELERATION = 6,
    OFX_BRUSH_SHATTER = 7,
    OFX_BRUSH_RIBBON = 8,
    OFX_BRUSH_SHRINK = 9,
    OFX_BRUSH_B2D_CIRCLE = 10,
    OFX_BRUSH_B2D_POLYGON = 11,
    OFX_BRUSH_STATIC = 12
};

class ofxBrush
{    
public:
    
    ofxBrush()
    {
        path = NULL; 
        pathDone = false; 
        kind = OFX_BRUSH_BASE; 
        particleCount = 0; 
    }
    
    ofxBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {        
        path = _path;
        paint = _paint; 
        pathDone = false;
        particleCount = 0; 
    }        
    
    virtual ~ofxBrush()
    {

    }    
    
    virtual void update()
    {

    }
    
    virtual void draw()
    {        
        
    }
    
    virtual void setDynamic(bool _isDynamic)
    {
        isDynamic = _isDynamic;
    }
    
    virtual void setDead(bool _isDead)
    {
        isDead = _isDead;
    }
    
    virtual void setSpeed(float _speed)
    {
        speed = speed; 
    }    
    
    virtual void pathFinished()
    {
        pathDone = true;         
    }
    
    virtual int getKind()
    {
        return kind; 
    }
    
    virtual int getParticleCount()
    {
        return particleCount; 
    }
    
    virtual void killLastParticle()
    {
        
    }
    
    ofxSuperPath *path; 
    ofxPaint *paint; 
    bool pathDone;     
    bool isDynamic; 
    bool isDead;     
    int kind; 
    float speed; 
    int particleCount; 
};

#endif
