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

#ifndef OFXSHATTERBRUSH
#define OFXSHATTERBRUSH

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"
#include "ofxGenerative.h"


class ofxShatterBrush : public ofxBrush
{    
public:
    ofxShatterBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {
        kind = OFX_BRUSH_SHATTER; 
        path = _path;
        paint = _paint;
        pathDone = false; 
        psys = new ofxParticleSystem();
        ssys = new ofxSpringSystem();        
        shatterForce = 0.5; 
        perVertex = true; 
    }    
    
    ~ofxShatterBrush()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Shatter Brush");                                
        delete ssys; 
        delete psys;
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Shatter Brush");                                
    }
    
    
    virtual void update()    
    {
        if(isDynamic)
        {
            vector<ofxParticle*> & particles = psys->getParticles();        
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = (ofxParticle *) particles[i];
                p->addForce(ofVec3f(ofRandom(-shatterForce,shatterForce),ofRandom(-shatterForce,shatterForce),0));
                p->update(); 
                p->elasticBorder(4.0);
            }            
            ssys->update();     
        }
    }
    
    void draw()
    {
        if(pathDone)
        {
            ofMesh mesh; 
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            vector<ofxParticle*> & particles = psys->getParticles();
            ofVec3f cPos = ((ofxParticle *) particles[0])->getPos();
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = (ofxParticle *) particles[i];
                ofVec3f pos = p->getPos();                                            
                if(perVertex)
                {
                    mesh.addColor(paint->getColor(pos.x, pos.y, p->getID()));                                    
                }
                else
                {
                    mesh.addColor(paint->getColor(cPos.x, cPos.y, (p->getID()-1)/6));                                    
                }   

                mesh.addVertex(pos);
                if(!perVertex && (p->getID()%3 == 0))
                {                
                    cPos = pos; 
                }
            }
            
            mesh.draw();        
        }
        else
        {        
            ofMesh mesh; 
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            
            for(int i = 0; i < path->positions.size()-1; i++)
            {
//                if(i == 0)  //because first point has a thickness of 0, vel = 0; acc = 0; 
//                {
//                    ofVec3f pos = path->positions[i];   
//                    ofVec3f posNext = path->positions[i+1];
//                    ofVec3f p3 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
//                    ofVec3f p4 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                 
//                    
//                    mesh.addColor(paint->getColor(pos.x, pos.y, i));
//                    mesh.addVertex(pos); 
//                    
//                    mesh.addColor(paint->getColor(p3.x, p3.y, i));
//                    mesh.addVertex(p3); 
//                    
//                    mesh.addColor(paint->getColor(p4.x, p4.y, i));
//                    mesh.addVertex(p4); 
//                    
//                }
//                else
//                {
                    ofVec3f pos = path->positions[i];   
                    ofVec3f posNext = path->positions[i+1];
                    
                    ofVec3f p1 = pos-(ofVec3f(path->thicknesses[i])*.5); 
                    ofVec3f p2 = pos+(ofVec3f(path->thicknesses[i])*.5);                 
                    
                    ofVec3f p3 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
                    ofVec3f p4 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                                     
                    
                    if(perVertex)
                    {
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p1); 
                        
                        mesh.addColor(paint->getColor(p2.x, p2.y, i+1));
                        mesh.addVertex(p2); 
                        
                        mesh.addColor(paint->getColor(p3.x, p3.y, i+2));
                        mesh.addVertex(p3); 
                        
                        mesh.addColor(paint->getColor(p3.x, p3.y, i+3));
                        mesh.addVertex(p3); 
                        
                        mesh.addColor(paint->getColor(p2.x, p2.y, i+4));
                        mesh.addVertex(p2); 
                        
                        mesh.addColor(paint->getColor(p4.x, p4.y, i+5));
                        mesh.addVertex(p4);                 
                    }
                    else
                    {
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p1); 
                        
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p2); 
                        
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p3); 
                        
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p3); 
                        
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p2); 
                        
                        mesh.addColor(paint->getColor(p1.x, p1.y, i));
                        mesh.addVertex(p4);                         
                    }
//                }
            }            
            
            mesh.draw();
        }
    }
    
    void setSpeed(float _speed)
    {
        speed = _speed; 
        vector<ofxParticle*> & particles = psys->getParticles();
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = (ofxParticle *) particles[i];
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);            
        }        
    }

    void setShatterForce(float _shatterForce)
    {
        shatterForce = _shatterForce;        
    }
    
    void setPerVertex(bool _perVertex)
    {
        perVertex = _perVertex; 
    }
    
    void pathFinished()
    {            
        for(int i = 0; i < path->positions.size()-1; i++)
        {
            ofVec3f pos = path->positions[i];   
            ofVec3f posNext = path->positions[i+1];
            
            ofVec3f p1 = pos-(ofVec3f(path->thicknesses[i])*.5); 
            ofVec3f p2 = pos+(ofVec3f(path->thicknesses[i])*.5);                 
            
            ofVec3f p3 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
            ofVec3f p4 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                 
            
            ofxParticle *particle1 = new ofxParticle(p1);
            ofxParticle *particle2 = new ofxParticle(p2);
            ofxParticle *particle3 = new ofxParticle(p3);
            
            ofxParticle *particle4 = new ofxParticle(p3);
            ofxParticle *particle5 = new ofxParticle(p2);
            ofxParticle *particle6 = new ofxParticle(p4);
            
            particle1->setColor(paint->getColor(p1.x, p1.y, i));
            particle2->setColor(paint->getColor(p2.x, p2.y, i));
            particle3->setColor(paint->getColor(p3.x, p3.y, i));
            
            particle4->setColor(paint->getColor(p3.x, p3.y, i));
            particle5->setColor(paint->getColor(p2.x, p2.y, i));
            particle6->setColor(paint->getColor(p4.x, p4.y, i));
            
            psys->addParticle(particle1);
            psys->addParticle(particle2);
            psys->addParticle(particle3);
            
            psys->addParticle(particle4);
            psys->addParticle(particle5);
            psys->addParticle(particle6);
            
            ofxSpring *s1 = new ofxSpring(particle1->getPosPtr(), particle2->getPosPtr(), (p1-p2).length(), 1.0);      //1-2
            ofxSpring *s2 = new ofxSpring(particle1->getPosPtr(), particle3->getPosPtr(), (p1-p3).length(), 1.0);      //1-3
            ofxSpring *s3 = new ofxSpring(particle2->getPosPtr(), particle3->getPosPtr(), (p2-p3).length(), 1.0);      //2-3 
            
            particle1->addExternalForce(s1->getForcePtr(0));
            particle2->addExternalForce(s1->getForcePtr(1));                
            
            particle1->addExternalForce(s2->getForcePtr(0));
            particle3->addExternalForce(s2->getForcePtr(1));                
            
            particle2->addExternalForce(s3->getForcePtr(0));
            particle3->addExternalForce(s3->getForcePtr(1));                
            
            
            ofxSpring *s4 = new ofxSpring(particle4->getPosPtr(), particle5->getPosPtr(), (p3-p2).length(), 1.0);      //4-5
            ofxSpring *s5 = new ofxSpring(particle4->getPosPtr(), particle6->getPosPtr(), (p3-p4).length(), 1.0);      //4-6
            ofxSpring *s6 = new ofxSpring(particle5->getPosPtr(), particle6->getPosPtr(), (p2-p4).length(), 1.0);      //5-6 
            
            particle4->addExternalForce(s4->getForcePtr(0));
            particle5->addExternalForce(s4->getForcePtr(1));                
            
            particle4->addExternalForce(s5->getForcePtr(0));
            particle6->addExternalForce(s5->getForcePtr(1));                
            
            particle5->addExternalForce(s6->getForcePtr(0));
            particle6->addExternalForce(s6->getForcePtr(1));                
            
            
            ssys->addSpring(s1);
            ssys->addSpring(s2);
            ssys->addSpring(s3);                            
            
            ssys->addSpring(s4);
            ssys->addSpring(s5);
            ssys->addSpring(s6);                                                        
        }             
        
        vector<ofxParticle*> & particles = psys->getParticles();
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = (ofxParticle *) particles[i];
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);                        
        }
        
        pathDone = true;         
    }
    
    
    
    int getParticleCount()
    {
        if(pathDone)
        {
            return (psys->getParticles().size())/3;
        }
        else
        {
            return (path->positions.size()-1)*2;
        }
    }
    
    void killLastParticle()
    {        
        vector<ofxParticle*> & particles = psys->getParticles();          
        vector<ofxParticle *>::iterator it;      
        for(int i = 0; i < 3; i++)
        {                      
            it=particles.begin();                
            ofxParticle *p = *it;
            particles.erase(it);
            delete p;           
        }

        
        vector<ofxSpring*> & springs = ssys->getSprings();
        vector<ofxSpring *>::iterator its;      
        for(int i = 0; i < 3; i++)
        {                      
            its=springs.begin();                
            ofxSpring *p = *its;
            springs.erase(its);
            delete p;           
        }
        
    }

    
    ofxParticleSystem *psys; 
    ofxSpringSystem *ssys; 
    ofMesh triangles; 
    int numberOfTriangles; 
    float shatterForce; 
    bool perVertex; 
    
};

#endif
