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
 README: This class is use to model the paint used in drawnetic, all other paints 
 inherit from this class and virtual set and get color are what make drawnetic's 
 dynamic paint possible.
 
 **********************************************************************************/

#ifndef OFXPAINT
#define OFXPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"

enum ofxPaintType
{
    OFX_PAINT_BASE = 0,
	OFX_PAINT_COLOR = 1,          //Done
    OFX_PAINT_IMAGE = 2, 
    OFX_PAINT_DYNAMIC_COLOR = 3,
    OFX_PAINT_RAINBOW = 4, 
    OFX_PAINT_DYNAMIC_RAINBOW = 5,
    OFX_PAINT_COLOR_PALETTE = 6,
    OFX_PAINT_DYNAMIC_COLOR_PALETTE = 7, 
    OFX_PAINT_AUDIO = 8,
    OFX_PAINT_AUDIO_FADE = 9,
    OFX_PAINT_AUDIO_HUE = 10,
    OFX_PAINT_AUDIO_BRIGHTNESS = 11,
    OFX_PAINT_AUDIO_OPACITY = 12
};

class ofxPaint
{    
public:
    ofxPaint()
    {
        kind = OFX_PAINT_BASE;         
    }
    
    ofxPaint(ofxSuperPath *_path, ofColor _color, float _opacity=255)
    {
        path = _path;
        opacity = _opacity; 
        color = _color; 
        kind = OFX_PAINT_BASE; 
    }    
    
    virtual ~ofxPaint()
    {
        
    }
    
    virtual void setColor(ofColor _color)
    {
        color = _color; 
    }
    
    virtual void setOpacity(float _opacity)
    {
        opacity = _opacity; 
    }                                   
                                       
    virtual void update()
    {
        
    }
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        return ofColor(color, opacity); 
    }
     
    virtual ofColor getColor(int x, int y, int index=0)
    {
        return ofColor(color, opacity);
    }

    virtual int getKind()
    {
        return kind; 
    }
    
    ofColor color; 
    float opacity; 
    ofxSuperPath *path;
    int kind; 
    
};



#endif
