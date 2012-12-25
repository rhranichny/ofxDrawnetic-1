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

#ifndef OFXAUDIOPAINT
#define OFXAUDIOPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxPaint.h"

class ofxAudioPaint : public ofxPaint
{    
public:
    ofxAudioPaint()
    {

    }
    
    ofxAudioPaint(ofxSuperPath *_path, ofColor _color, float *_audioBuffer, int _bufferSize, float _opacity=255) : ofxPaint(_path, _color, _opacity)
    {
        kind = OFX_PAINT_AUDIO;
        audioBuffer = _audioBuffer; 
        bufferSize = _bufferSize; 
        range = 255; 
        effectHue = true; 
        effectOpacity = false; 
        effectSaturation = false;
        effectBrightness = false;          
    }    
    
    ~ofxAudioPaint()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Audio Paint");                                                
    }
    
    virtual void setOpacity(float _opacity)
    {
        opacity = _opacity; 
    }                                   
    
    virtual void update()
    {
        
    }
    
    void setEffectHue(bool _effectHue)
    {
        effectHue = _effectHue;         
    }

    void setEffectSaturation(bool _effectSaturation)
    {
        effectSaturation = _effectSaturation;         
    }

    void setEffectBrightness(bool _effectBrightness)
    {
        effectBrightness = _effectBrightness;         
    }

    void setEffectOpacity(bool _effectOpacity)
    {
        effectOpacity = _effectOpacity;         
    }
    
    void setRange(float _range)
    {
        range = _range; 
    }

    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        return getColor(pos.x, pos.y, index);
    }
    
    virtual ofColor getColor(int x, int y, int index=0)
    {
        ofColor clr = color; 
        if(effectHue)
        {
            float hue = color.getHue(); 
            hue+=range*abs(audioBuffer[index%bufferSize]);
            int ihue = hue; 
            ihue%=255;                 
            clr.setHue(ihue); 
        }
        if(effectSaturation)
        {
            float sat = range*(audioBuffer[index%bufferSize]);                           
            clr.setSaturation(sat);            
        }
        if(effectBrightness)
        {
            float bgt = range*audioBuffer[index%bufferSize];                            
            clr.setBrightness(bgt);    
        }
        if(effectOpacity)
        {
            float opcty = range*audioBuffer[index%bufferSize];    
            clr.a = opcty;
        }
        else
        {
            clr.a = opacity;
        }
        
        return clr;         
    }    
    
    float *audioBuffer; 
    int bufferSize; 
    float range;
    bool effectHue, effectOpacity, effectSaturation, effectBrightness; 
    
};



#endif
