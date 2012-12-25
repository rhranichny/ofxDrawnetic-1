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

#ifndef OFXFLOCKINGBRUSH
#define OFXFLOCKINGBRUSH

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"
#include "ofxGenerative.h"
#include "ofxFace.h"

class ofxFlockingBrush : public ofxBrush
{    
public:    
    ofxFlockingBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {
        kind = OFX_BRUSH_FLOCKING; 
        path = _path;
        paint = _paint; 
        pathDone = false; 
        psys = new ofxParticleSystem();
        ssys = new ofxSpringSystem();   
        bsys = new ofxBoidSystem();
        perVertex = true;         
        refineShape = false; 
        shapeSize = 10; 
    }    
    
    ~ofxFlockingBrush()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Flocking Brush");                                                
        delete ssys; 
        delete psys;
        delete bsys; 
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Flocking Brush");                                                
    }
    
    
    virtual void update()
    {
        if(isDynamic)
        {
            bsys->update();        
            ssys->update(); 
            vector<ofxParticle*> & particles = psys->getParticles();
            for(int i = 0; i < particles.size(); i++)
            {
                ofxParticle *p = (ofxParticle *) particles[i];
                p->update(); 
                p->elasticBorder(4.0);
            }
        }
    }
    
    void draw()
    {
        if(pathDone)
        {
            ofMesh mesh; 
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
           
            if(faces.size() > 0)
            {
                ofxFace *firstface = faces[0];          
                ofVec3f *posPtr = firstface->getPos(0);
                ofVec3f cPos = ofVec3f(posPtr->x, posPtr->y, posPtr->z);                    
                
                for(int i = 0; i < faces.size(); i++)
                {
                    ofxFace *f = faces[i];                
                    for(int j = 0; j < f->size(); j++)
                    {
                        ofVec3f *posPtr = f->getPos(j);
                        ofVec3f pos = ofVec3f(posPtr->x, posPtr->y, posPtr->z);                    
                        if(perVertex)
                        {
                            mesh.addColor(paint->getColor(pos.x, pos.y, f->getID()+j));                        
                        }
                        else
                        {
                            mesh.addColor(paint->getColor(cPos.x, cPos.y, (f->getID()+1)/2));                        
                        }
                        mesh.addVertex(pos);                    
                    }
                    if(!perVertex && (f->getID())%2 == 0)
                    {                    
                        ofxFace *fce = faces[i];          
                        ofVec3f *posPtr = fce->getPos(0);
                        cPos = ofVec3f(posPtr->x, posPtr->y, posPtr->z);                                        
                    }                
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
    
    void setPerVertex(bool _perVertex)
    {
        perVertex = _perVertex; 
    }

    void setJitter(float _jitter)
    {
        jitter = _jitter; 
        for(int i = 0; i < ssys->springs.size(); i++)
        {
            ofxSpring *s = ssys->springs[i]; 
            s->setK(jitter);
            //            s->setRestDistance(25);
        }        
    }
    
    void setRefineShape(bool _refineShape)
    {
        refineShape = _refineShape; 
        for(int i = 0; i < ssys->springs.size(); i++)
        {
            ofxSpring *s = ssys->springs[i]; 
            if(refineShape)
            {                
                s->setRestDistance(shapeSize);
            }
        }                
    }
    
    void setShapeSize(float _shapeSize)
    {
        shapeSize = _shapeSize; 
        for(int i = 0; i < ssys->springs.size(); i++)
        {
            ofxSpring *s = ssys->springs[i]; 
            if(refineShape)
            {                
                s->setRestDistance(shapeSize);
            }
        }                        
    }
    
    void pathFinished()
    {            
        int count =0; 
        for(int i = 0; i < path->positions.size()-1; i++)
        {            
            if(i == 0)  //because first point has a thickness of 0, vel = 0; acc = 0; 
            {
                
                ofVec3f pos = path->positions[i];   
                ofVec3f posNext = path->positions[i+1];
                ofVec3f p2 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
                ofVec3f p3 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                                      
                
                ofxBoidParticle *particle1 = new ofxBoidParticle(pos);
                ofxParticle *particle2 = new ofxParticle(p2);
                ofxParticle *particle3 = new ofxParticle(p3);
                
                particle1->setColor(paint->getColor(pos.x, pos.y, i));
                particle2->setColor(paint->getColor(p2.x, p2.y, i));
                particle3->setColor(paint->getColor(p3.x, p3.y, i));                
                
                bsys->addParticle(particle1);                
                particle1->setParticlesRef(&bsys->getParticles());
                
                psys->addParticle(particle2);
                psys->addParticle(particle3);
                
                ofxSpring *s1 = new ofxSpring(particle1->getPosPtr(), particle2->getPosPtr(), (pos-p2).length(), 1.0);      //1-2
                ofxSpring *s2 = new ofxSpring(particle1->getPosPtr(), particle3->getPosPtr(), (pos-p3).length(), 1.0);      //1-3
                ofxSpring *s3 = new ofxSpring(particle2->getPosPtr(), particle3->getPosPtr(), (p2-p3).length(), 1.0);      //2-3 
                
                ssys->addSpring(s1);
                ssys->addSpring(s2);
                ssys->addSpring(s3);               
                
//                particle1->addSpringForce(s1->getForcePtr(0));
                particle2->addSpringForce(s1->getForcePtr(1));                
                
                particle1->addSpringForce(s2->getForcePtr(0));
                particle3->addSpringForce(s2->getForcePtr(1));                
                
                particle2->addSpringForce(s3->getForcePtr(0));
                particle3->addSpringForce(s3->getForcePtr(1));    
                
                ofxFace *face = new ofxFace();
                face->setID(count);
                count++; 
                
                face->push_back(particle1->getPosPtr());
                face->push_back(particle2->getPosPtr());
                face->push_back(particle3->getPosPtr());

                faces.push_back(face);                                
            }
            else
            {
                ofVec3f pos = path->positions[i];   
                ofVec3f posNext = path->positions[i+1];
                
                ofVec3f p1 = pos-(ofVec3f(path->thicknesses[i])*.5); 
                ofVec3f p2 = pos+(ofVec3f(path->thicknesses[i])*.5);                 
                
                ofVec3f p3 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
                ofVec3f p4 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                 
                
                ofxBoidParticle *particle1 = new ofxBoidParticle(p1);
                ofxParticle *particle2 = new ofxParticle(p2);
                ofxParticle *particle3 = new ofxParticle(p3);
                
                ofxParticle *particle4 = new ofxParticle(p3);
                ofxParticle *particle5 = new ofxParticle(p2);
                ofxBoidParticle *particle6 = new ofxBoidParticle(p4);
                
                particle1->setColor(paint->getColor(p1.x, p1.y, i));
                particle2->setColor(paint->getColor(p2.x, p2.y, i));
                particle3->setColor(paint->getColor(p3.x, p3.y, i));
                
                particle4->setColor(paint->getColor(p3.x, p3.y, i));
                particle5->setColor(paint->getColor(p2.x, p2.y, i));
                particle6->setColor(paint->getColor(p4.x, p4.y, i));
                
                bsys->addParticle(particle1);                
                particle1->setParticlesRef(&bsys->getParticles());

                psys->addParticle(particle2);
                psys->addParticle(particle3);
                
                psys->addParticle(particle4);                
                psys->addParticle(particle5);
                
                bsys->addParticle(particle6);
                particle6->setParticlesRef(&bsys->getParticles());
                
                ofxSpring *s1 = new ofxSpring(particle1->getPosPtr(), particle2->getPosPtr(), (p1-p2).length(), 1.0);      //1-2
                ofxSpring *s2 = new ofxSpring(particle1->getPosPtr(), particle3->getPosPtr(), (p1-p3).length(), 1.0);      //1-3
                ofxSpring *s3 = new ofxSpring(particle2->getPosPtr(), particle3->getPosPtr(), (p2-p3).length(), 1.0);      //2-3 
                
//                particle1->addSpringForce(s1->getForcePtr(0));
                particle2->addSpringForce(s1->getForcePtr(1));                
                
                particle1->addSpringForce(s2->getForcePtr(0));
                particle3->addSpringForce(s2->getForcePtr(1));                
                
                particle2->addSpringForce(s3->getForcePtr(0));
                particle3->addSpringForce(s3->getForcePtr(1));                
                
                
                ofxSpring *s4 = new ofxSpring(particle4->getPosPtr(), particle5->getPosPtr(), (p3-p2).length(), 1.0);      //4-5
                ofxSpring *s5 = new ofxSpring(particle4->getPosPtr(), particle6->getPosPtr(), (p3-p4).length(), 1.0);      //4-6
                ofxSpring *s6 = new ofxSpring(particle5->getPosPtr(), particle6->getPosPtr(), (p2-p4).length(), 1.0);      //5-6 
                
                particle4->addSpringForce(s4->getForcePtr(0));
                particle5->addSpringForce(s4->getForcePtr(1));                
                
                particle4->addSpringForce(s5->getForcePtr(0));
                particle6->addSpringForce(s5->getForcePtr(1));                
                
                particle5->addSpringForce(s6->getForcePtr(0));
//                particle6->addSpringForce(s6->getForcePtr(1));                
                                
                ssys->addSpring(s1);
                ssys->addSpring(s2);
                ssys->addSpring(s3);                            
                
                ssys->addSpring(s4);
                ssys->addSpring(s5);
                ssys->addSpring(s6);                                                        
                
                ofxFace *face = new ofxFace(); 
                
                face->push_back(particle1->getPosPtr());
                face->push_back(particle2->getPosPtr());
                face->push_back(particle3->getPosPtr());
                face->setID(count);
                count++; 
                
                faces.push_back(face);

                ofxFace *face2 = new ofxFace(); 
                
                face2->push_back(particle4->getPosPtr());
                face2->push_back(particle5->getPosPtr());
                face2->push_back(particle6->getPosPtr());
                face2->setID(count);
                count++;                 
                faces.push_back(face2);

            }
        }                                                          
        vector<ofxParticle*> & particles = psys->getParticles();        
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = (ofxParticle *) particles[i];                
            p->setDamping(0.9);
            p->setVelocityLimit(speed);
            p->setAccerationLimit(speed*.5);
        }
        pathDone = true;         
        
        //sets the option to get nice boids
        for(int i = 0; i < ssys->springs.size(); i++)
        {
            ofxSpring *s = ssys->springs[i]; 
            s->setK(jitter);
            if(refineShape)
            {                
                s->setRestDistance(shapeSize);
            }
        }
        
    }
    
    int getParticleCount()
    {
        if(pathDone)
        {
            return faces.size();
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
        for(int i = 0; i < 2; i++)
        {                      
            it=particles.begin();                
            ofxParticle *p = *it;
            particles.erase(it);
            delete p;           
        }
        
        vector<ofxParticle*> & bparticles = bsys->getParticles();          
        vector<ofxParticle *>::iterator itb;      
        for(int i = 0; i < 1; i++)
        {                      
            itb=bparticles.begin();                
            ofxBoidParticle *bp = (ofxBoidParticle *) *itb;
            bparticles.erase(itb);
            delete bp;           
        }        
        
        vector<ofxSpring *> & springs = ssys->getSprings();
        vector<ofxSpring *>::iterator its;      
        for(int i = 0; i < 3; i++)
        {                      
            its=springs.begin();                
            ofxSpring *s = *its;
            springs.erase(its);
            delete s;           
        }        
            
        vector<ofxFace *>::iterator itf;      
        itf=faces.begin();                
        ofxFace *f = *itf;
        delete f; 
        faces.erase(itf);           
    }
    
    ofxBoidSystem *bsys; 
    ofxParticleSystem *psys; 
    ofxSpringSystem *ssys; 
    vector<ofxFace *> faces;
    ofMesh triangles; 
    int numberOfTriangles;     
    bool perVertex; 
    float jitter; 
    bool refineShape; 
    float shapeSize; 
};

#endif
