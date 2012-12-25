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

#ifndef OFXTRIPPAINT
#define OFXTRIPPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxPaint.h"

class ofxTripPaint : public ofxPaint
{    
public:
    ofxTripPaint(ofxSuperPath *_path, ofColor _color, float _opacity=255)
    {
        kind = OFX_PAINT_DYNAMIC_COLOR;
        path = _path;
        opacity = _opacity; 
        color = _color; 
        increment = 1.0; 
        isDynamic = true; 
        perVertex = true; 
        perVertexIncrement = 0; 
    }    
    
    ~ofxTripPaint()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Trip Paint");                                                
    }
    
    void setIncrement(float _increment)
    {
        increment = _increment; 
    }
    
    void setDynamic(bool _isDynamic)
    {
        isDynamic = _isDynamic;
    }

    void setPerVertex(bool _perVertex)
    {
        perVertex = _perVertex;
    }

    void setPerVertexIncrement(float _perVertexIncrement)
    {
        perVertexIncrement = _perVertexIncrement;
    }
    
    void update()
    {
        if(isDynamic)
        {            
            float hue = color.getHue();
            hue+=increment; 
            if(hue > 255)
            {
                hue = 0; 
            }
            color.setHue(hue);
        }
    }
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        if(perVertex)
        {
            float hue = color.getHue();
            hue+=index*perVertexIncrement; 
            int ihue = (int)hue; 
            ihue%=255; 
            hue = ihue; 
            ofColor clr = color; 
            clr.setHue(hue);
            return ofColor(clr, opacity);             
        }
        else
        {
            return ofColor(color, opacity); 
        }
    }
    
    virtual ofColor getColor(int x, int y, int index=0)
    {
        if(perVertex)
        {
            float hue = color.getHue();
            hue+=index*perVertexIncrement; 
            int ihue = (int)hue; 
            ihue%=255; 
            hue = ihue; 
            ofColor clr = color; 
            clr.setHue(hue);
            return ofColor(clr, opacity);             
        }
        else
        {
            return ofColor(color, opacity); 
        }
    }

    float increment; 
    float perVertexIncrement;
    bool isDynamic; 
    bool perVertex; 
    
};



#endif
