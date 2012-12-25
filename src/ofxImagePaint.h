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

#ifndef OFXIMAGEPAINT
#define OFXIMAGEPAINT

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxPaint.h"

class ofxImagePaint : public ofxPaint
{    
public:
    ofxImagePaint(ofxSuperPath *_path, ofImage *_refImage, float _opacity=255)
    {
        kind = OFX_PAINT_IMAGE;
        path = _path;
        opacity = _opacity; 
        refImage = _refImage; 
    }    
    
    ~ofxImagePaint()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Image Paint");                                                
    }
    
    void setOpacity(float _opacity)
    {
        opacity = _opacity; 
    }                                   
    
    virtual ofColor getColor(ofVec3f &pos, int index=0)
    {
        return ofColor(refImage->getColor(pos.x, pos.y), opacity);
    }

    virtual ofColor getColor(int x, int y, int index=0)
    {
        return ofColor(refImage->getColor(x, y), opacity);
    }
    
    ofImage *refImage; 
};



#endif
