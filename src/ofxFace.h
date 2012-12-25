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
 README: models a face using ofVec3fs. Used in drawnetic to help brushes with rendering 
 triangle face with easy. 

 **********************************************************************************/

#ifndef OFX_FACE
#define OFX_FACE

#include "ofMain.h"
#include <vector>

class ofxFace
{
public:
    ofxFace()
    {
        
    }
    
    ~ofxFace()
    {
        
    }
    
    void push_back(ofVec3f * pos)
    {
        faces.push_back(pos);
    }
    
    ofVec3f *getPos(int index)
    {
        return faces[index];
    }
    
    int size()
    {
        return faces.size();
    }
    
    int getID()
    {
        return faceID; 
    }
    
    void setID(int _faceID)
    {
        faceID = _faceID; 
    }
    
    int faceID;    
    vector<ofVec3f *> faces; 
};




#endif
