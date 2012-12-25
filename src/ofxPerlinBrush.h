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

#ifndef OFXPERLINEBRUSH
#define OFXPERLINEBRUSH

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"
#include "ofxGenerative.h"


class ofxPerlinBrush : public ofxBrush
{    
public:
    ofxPerlinBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {
        kind = OFX_BRUSH_PERLIN;         
        path = _path;
        paint = _paint; 
        pathDone = false; 
        speed = 10.0; 
        noiseScale = 0.0001; 
        useAcceleration = true; 
    }    
    
    ~ofxPerlinBrush()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Perlin Brush");                                
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = particles[i];
            delete p;             
        }
        particles.clear();
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Perlin Brush");                                
    }
    
    
    void update()
    {
        if(isDynamic)
        {            
            float width = ofGetWidth(); 
            float height = ofGetHeight(); 
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = particles[i];            
                p->update(); 
                ofVec3f pos = p->getPos();      
                pos.x /=width; 
                pos.y /=height;
                if(useAcceleration)
                {
                    p->setAcc(speed*ofVec3f(ofSignedNoise((ofGetElapsedTimeMillis()+i*10)*noiseScale, pos.x),ofSignedNoise(pos.y, (ofGetElapsedTimeMillis()+i*10)*noiseScale),0));
                }
                else
                {
                    p->setVel(speed*ofVec3f(ofSignedNoise((ofGetElapsedTimeMillis()+i*10)*noiseScale, pos.x),ofSignedNoise(pos.y, (ofGetElapsedTimeMillis()+i*10)*noiseScale),0));
                }
                p->borders();
            }
        }
    }
    
    void draw()
    {
        if(pathDone)
        {
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = particles[i];
                ofVec3f pos = p->getPos();
                p->setColor(paint->getColor(pos.x, pos.y, p->getID()));
                p->draw();                 
            }         
        }
        else
        {
            for(int i = 0; i < path->positions.size(); i++)
            {
                ofVec3f pos = path->positions[i]; 
                ofxParticle p = ofxParticle(pos);
                p.setRadius(path->thicknesses[i].length());
                p.setColor(paint->getColor(pos.x, pos.y, i));
                p.draw();                
            }            
        }
    }
    
    void setSpeed(float _speed)
    {
        speed = _speed; 
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = particles[i];
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);            
        }        
    }

    void setNoiseScale(float _noiseScale)
    {
        noiseScale = _noiseScale;
    }
    
    void setUseAcceleration(bool _useAcceleration)
    {
        useAcceleration = _useAcceleration; 
    }
    
    void pathFinished()
    {
        for(int i = 0; i < path->positions.size(); i++)
        {
            ofVec3f pos = path->positions[i]; 
            ofxParticle *p = new ofxParticle(pos);
            p->setID(i);
            p->setAcc(path->accelerations[i]);
            p->setVel(path->velocities[i]);
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);            
            p->setRadius(path->thicknesses[i].length());
            p->setColor(paint->getColor(pos.x, pos.y, i));            
            p->setDamping(.1);
            particles.push_back(p);
            
        }
        pathDone = true;         
    }

    int getParticleCount()
    {
        if(pathDone)
        {
            return particles.size();            
        }
        else
        {
            return path->positions.size();
        }    
    }
    
    void killLastParticle()
    {        
        vector<ofxParticle *>::iterator it;                
        it=particles.begin();                
        ofxParticle *p = *it;
        particles.erase(it);
        delete p;            
    }
    
    vector<ofxParticle *> particles;     
    float noiseScale; 
    bool useAcceleration; 
};

#endif
