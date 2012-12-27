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

#ifndef OFXPALETTEPAINT
#define OFXPALETTEPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxPaint.h"

class ofxPalettePaint : public ofxPaint
{    
public:
    ofxPalettePaint()
    {
        
    }
    
    ofxPalettePaint(ofxSuperPath *_path, vector<ofColor> _colors, float _opacity=255)
    {
        path = _path;
        opacity = _opacity; 
        colors = _colors; 
        for(int i = 0; i < colors.size(); i++)
        {
            opacities.push_back(opacity);
        }
    }    
    
    virtual void setOpacity(float _opacity)
    {
        opacity = _opacity; 
        opacities.clear(); 
        for(int i = 0; i < colors.size(); i++)
        {
            opacities.push_back(opacity);
        }
    }    
    
    virtual void setOpacities(vector<float> _opacities)
    {
        opacities.clear(); 
        opacities = _opacities; 
    }
    
    
    virtual void update()
    {
        
    }
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        return ofColor(colors[index%colors.size()], opacity); 
    }
    
    virtual ofColor getColor(int x, int y, int index=0)
    {
        return ofColor(colors[index%colors.size()], opacity);
    }
    
    vector<ofColor> colors;
    vector<float> opacities;
};



#endif
