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

#ifndef OFXKINETICBRUSH
#define OFXKINETICBRUSH

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"
#include "ofxGenerative.h"


class ofxKineticBrush : public ofxBrush
{    
public:
    ofxKineticBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {
        kind = OFX_BRUSH_KINETIC; 
        path = _path;
        paint = _paint; 
        pathDone = false; 
        indexOfAcceleration = 0; 
        useAcceleration = true; 
        speedIncrement = 1;         
    }    
    
    ~ofxKineticBrush()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Kinetic Brush");                        
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = particles[i];
            delete p;             
        }
        particles.clear();
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Kinetic Brush");                        
    }

    
    virtual void update()
    {
        if(isDynamic)
        {            
            indexOfAcceleration+=speedIncrement; 
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = particles[i];
                int index = p->getID()+indexOfAcceleration; 
                index %= path->accelerations.size();
                if(useAcceleration)
                {
                    p->setAcc(path->accelerations[index]); //);
                }
                else
                {
                    p->setVel(path->velocities[index]);
                }
                p->update();
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
    
    void setSpeedIncrement(int _speedIncrement)
    {
        speedIncrement = _speedIncrement;
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
            if(useAcceleration)
            {
                p->setAcc(path->accelerations[i] + path->velocities[i]);
            }
            else
            {
                p->setAcc(path->velocities[i]);
            }
            p->setRadius(path->thicknesses[i].length());
            p->setColor(paint->getColor(pos.x, pos.y, i));         
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);                        
            p->setDamping(.99);
            particles.push_back(p);
            
        }
        pathDone = true;         
        indexOfAcceleration = 0; 
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
    int indexOfAcceleration;
    bool useAcceleration;   
    int speedIncrement; 
};

#endif
