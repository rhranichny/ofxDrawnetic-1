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

#ifndef OFXDYNAMICRAINBOWPAINT
#define OFXDYNAMICRAINBOWPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxRainbowPaint.h"

class ofxDynamicRainbowPaint : public ofxRainbowPaint
{    
public:
    ofxDynamicRainbowPaint(ofxSuperPath *_path, ofColor _color, float _opacity=255) : ofxRainbowPaint(_path, _color)
    {
        kind = OFX_PAINT_DYNAMIC_RAINBOW;
        isDynamic = true; 
    }    
    
    ~ofxDynamicRainbowPaint()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Dynamic Rainbow Paint");                                                
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
    
    void setDynamic(bool _isDynamic)
    {
        isDynamic = _isDynamic;
    }
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        float hue = color.getHue();
        hue+=index; 
        int ihue = (int)hue; 
        ihue%=255; 
        hue = ihue; 
        ofColor clr = color; 
        clr.setHue(hue);
        return ofColor(clr, opacity); 
    }
    
    virtual ofColor getColor(int x, int y, int index=0)
    {      
        float hue = color.getHue();
        hue+=index; 
        int ihue = (int)hue; 
        ihue%=255; 
        hue = ihue; 
        ofColor clr = color; 
        clr.setHue(hue);
        return ofColor(clr, opacity); 
    }
    
    //from Parent Class
    //float increment; 
    bool isDynamic;     
};



#endif
