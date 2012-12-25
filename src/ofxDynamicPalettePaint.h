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

#ifndef OFXDYNAMICPALETTEPAINT
#define OFXDYNAMICPALETTEPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxPalettePaint.h"

class ofxDynamicPalettePaint : public ofxPalettePaint
{    
public:        
    ofxDynamicPalettePaint(ofxSuperPath *_path, vector<ofColor> _colors, float _opacity=255) : ofxPalettePaint(_path, _colors, _opacity)
    {
        indexOffset = 0;
        kind = OFX_PAINT_DYNAMIC_COLOR_PALETTE;
        currentTime = ofGetElapsedTimeMillis(); 
        pastTime = currentTime; 
        dynamicRate =1.0;
    }    
    
    ~ofxDynamicPalettePaint()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Dynamic Palette Paint");                                                
    }
    
    virtual void update()
    {
        if(isDynamic)
        {
            currentTime = ofGetElapsedTimeMillis(); 
            if(currentTime-pastTime>(dynamicRate*1000))
            {
                pastTime = currentTime; 
                indexOffset++; 
            }
        }
    }
    
    void setDynamic(bool _isDynamic)
    {
        isDynamic = _isDynamic;
    }
    
    void setDynamicRate(float _dynamicRate)
    {
        dynamicRate = _dynamicRate;
    }
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        return ofColor(colors[(indexOffset+index)%colors.size()], opacity); 
    }
    
    virtual ofColor getColor(int x, int y, int index=0)
    {
        return ofColor(colors[(indexOffset+index)%colors.size()], opacity);
    }
    
    
    int indexOffset; 
    bool isDynamic;        
    float dynamicRate;
    int pastTime, currentTime; 
};



#endif
