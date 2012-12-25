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

#ifndef OFXRIBBONBRUSH
#define OFXRIBBONBRUSH

#include "ofMain.h"
#include "ofxSuperPath.h"
#include "ofxBrush.h"
#include "ofxGenerative.h"
#include "ofxFace.h"

class ofxRibbonBrush : public ofxBrush
{    
public:
    
    ofxRibbonBrush(ofxSuperPath *_path, ofxPaint *_paint)
    {
        kind = OFX_BRUSH_RIBBON; 
        path = _path;
        paint = _paint; 
        pathDone = false; 
        psys = new ofxParticleSystem();
//      ssys = new ofxSpringSystem();        
//      springConstant = 1.0; 
        isDynamic = true; 
        isDead = false;         
        perVertex = true;
        useAcceleration = true; 
    }    
    
    ~ofxRibbonBrush()
    {
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETING Ribbon Brush");                                
//        delete ssys; 
        delete psys;
        ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic: DELETED Ribbon Brush");                                        
    }
    
    
    virtual void update()
    {
        if(isDynamic)
        {
            vector<ofxParticle*> & particles = psys->getParticles();
            indexOfAcceleration++; 
            indexOfAcceleration%=path->accelerations.size(); 
            
            for(int i = 0; i < particles.size(); i++)
            {
                    ofxParticle *p = (ofxParticle *) particles[i];                
                    
                    int index = p->getID()+indexOfAcceleration; 
                    index%=path->accelerations.size();
                    if(useAcceleration)
                    {
                        p->setAcc(p->getVel()+path->accelerations[index]);
                    }
                    else
                    {
                        p->setVel(p->getVel()+path->velocities[index]);
                    }

                    p->update();
                    p->borders();                    

                
//                    ofxParticle *p1 = (ofxParticle *) particles[i];                
////                    p1->setVel(p1->getVel()+path->velocities[index]);
//                    p1->setAcc(path->velocities[index]);                    
//                    //                    p1->addForce(path->velocities[index]);        
//                    p1->update();
//                    p1->borders();                    
//                    
//                    
//                    ofxParticle *p2 = (ofxParticle *) particles[i+1];                
////                    p2->setVel(p2->getVel()+path->velocities[index]);
//                    p2->setAcc(path->velocities[index]);                    
//                    //                    p2->addForce(path->velocities[index]);        
//                    p2->update();
//                    p2->borders();                    
//                    
//                    i++;
//                }
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
                ofxFace *face = faces[0];          
                ofVec3f *posPtr = face->getPos(0);
                ofVec3f cPos = ofVec3f(posPtr->x, posPtr->y, posPtr->z);                    
                
                for(int i = 0; i < faces.size(); i++)
                {
                    ofxFace *f = faces[i];           
                    ofVec3f *posPtr1 = f->getPos(0);
                    ofVec3f *posPtr2 = f->getPos(1);
                    ofVec3f *posPtr3 = f->getPos(2);
                        
                    float width = ofGetWidth()*.72;
                    if(posPtr1->distance(*posPtr2) > width || posPtr2->distance(*posPtr3) > width || posPtr3->distance(*posPtr1) > width)
                    {

                    }
                    else
                    {
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
            p->setAccerationLimit(speed*.5);
            p->setVelocityLimit(speed);
        }
    }
        
    void setPerVertex(bool _perVertex)
    {
        perVertex = _perVertex; 
    }
    
    void setUseAcceleration(bool _useAcceleration)
    {
        useAcceleration = _useAcceleration;
    }
    
    void pathFinished()
    {
        ofxParticle *lastLeft = NULL;
        ofxParticle *lastRight = NULL;
        int count = 0; 
        for(int i = 0; i < path->positions.size()-1; i++)
        {
            if(i == 0)  //because first point has a thickness of 0, vel = 0; acc = 0; 
            {
                
                ofVec3f pos = path->positions[i];   
                ofVec3f posNext = path->positions[i+1];
                ofVec3f p2 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
                ofVec3f p3 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                                      
                
                ofxParticle *particle1 = new ofxParticle(pos);
                ofxParticle *particle2 = new ofxParticle(p2);
                ofxParticle *particle3 = new ofxParticle(p3);                

                particle1->setColor(paint->getColor(pos.x, pos.y, i));
                particle2->setColor(paint->getColor(p2.x, p2.y, i));
                particle3->setColor(paint->getColor(p3.x, p3.y, i));                
                
                psys->addParticle(particle1);                
                particle1->setID(psys->particles.size());
                psys->addParticle(particle2);
                particle2->setID(psys->particles.size());                
                psys->addParticle(particle3);
                particle3->setID(psys->particles.size());                
                
                lastLeft = particle2; 
                lastRight = particle3;
                
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
                
                ofVec3f p3 = posNext-(ofVec3f(path->thicknesses[i+1])*.5);                 
                ofVec3f p4 = posNext+(ofVec3f(path->thicknesses[i+1])*.5);                 
                
                ofxParticle *particle3 = new ofxParticle(p3);                
                ofxParticle *particle6 = new ofxParticle(p4);
                
                particle3->setColor(paint->getColor(p3.x, p3.y, i));
                particle6->setColor(paint->getColor(p4.x, p4.y, i));
                
                psys->addParticle(particle3);
                particle3->setID(psys->particles.size());                
                psys->addParticle(particle6);
                particle6->setID(psys->particles.size());                
                            
                ofxFace *face1 = new ofxFace();
                
                face1->push_back(lastLeft->getPosPtr());
                face1->push_back(lastRight->getPosPtr());
                face1->push_back(particle3->getPosPtr());
                
                faces.push_back(face1);                                                                
                face1->setID(count);
                count++;
                ofxFace *face2 = new ofxFace();
                
                face2->push_back(lastRight->getPosPtr());
                face2->push_back(particle3->getPosPtr());
                face2->push_back(particle6->getPosPtr());
                
                faces.push_back(face2);            
                face2->setID(count);                
                count++;                 
                lastLeft = particle3; 
                lastRight = particle6;                 
            }            
        }                        
        vector<ofxParticle*> & particles = psys->getParticles();        
        for(int i = 0; i < particles.size(); i++)
        {
            ofxParticle *p = (ofxParticle *) particles[i];                
            p->setDamping(.1);
            p->setAccerationLimit(speed*.5);
            p->setVelocityLimit(speed);
        }
        pathDone = true;         
        indexOfAcceleration = 0; 
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
        for(int i = 0; i < 1; i++)
        {                      
            it=particles.begin();                
            ofxParticle *p = *it;
            particles.erase(it);
            delete p;           
        }                    

        vector<ofxFace *>::iterator itf;      
        itf=faces.begin();                
        ofxFace *f = *itf;
        delete f; 
        faces.erase(itf);        
    }    
    
    int indexOfAcceleration;    
    ofxParticleSystem *psys; 
    vector<ofxFace *> faces;
    ofMesh triangles; 
    int numberOfTriangles;   
    bool perVertex; 
    bool useAcceleration; 
};

#endif
