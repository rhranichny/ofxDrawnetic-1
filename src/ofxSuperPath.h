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
 README: Contains path information. This class calculates meta-properties about 
 paths, things like velocities and accelerations are recorded. In addition frames,  
 time, pressure, and color is also recorded.
 
 **********************************************************************************/

#ifndef OFXSUPERPATH
#define OFXSUPERPATH

#include "ofMain.h"

enum ofxPathPressureType
{
    OFX_PATH_PRESSURE_FIXED = 0,
    OFX_PATH_PRESSURE_PRESSURE = 1,
    OFX_PATH_PRESSURE_DISTANCE = 2 
};


class ofxSuperPath : public ofPolyline
{    
public:
    ofxSuperPath() 
    {
        thicknessPathColor = ofColor(0,150); 
        positionPathColor = ofColor(0,150);
        velocityPathColor = ofColor(255,0,0,150); 
        accelerationPathColor = ofColor(0,0,255,150); 

        thicknessPath.setFilled(false);
        velocityPath.setFilled(false);
        accelerationPath.setFilled(false);        
        pressureType = OFX_PATH_PRESSURE_DISTANCE;
        fixedThickness = 1.0;
    } 

    void setFixedThickness(float _fixedThickness)
    {
        fixedThickness = _fixedThickness; 
    }
    
    void setPathPressureType(int _pressureType, float _fixedThickness=1)
    {
        pressureType = _pressureType; 
        fixedThickness = _fixedThickness;
    }
    
    void drawPositions()
    {
//        drawPoints();
    }
    
    void drawPointNumbers()
    {
        for(int i = 0; i < positions.size(); i++)
        {
            ofDrawBitmapString(ofToString(i, 0), positions[i].x+5,positions[i].y+5,positions[i].z);
        }        
    }

    void drawPointTimes()
    {
        for(int i = 0; i < positions.size(); i++)
        {
            ofDrawBitmapString(ofToString(times[i], 4), positions[i].x+5,positions[i].y+5,positions[i].z);
        }        
    }
    
    void drawVelocities()
    {
        velocityPath.draw();
    }
    
    void drawAccelerations()
    {
        accelerationPath.draw();
    }
    
    void drawThicknesses()
    {
        thicknessPath.draw();
    }
    
    void drawColors()
    {
        glPointSize(10);
        ofMesh mesh = ofMesh(OF_PRIMITIVE_POINTS, positions);
        mesh.addColors(colors);
        mesh.draw();
    }

    void lineStart(float x, float y, float z=0, ofFloatColor _color=ofFloatColor(0), int frame =0, float pressure = 0)
    {
        thickness.set(0); 
        pthickness = thickness; 
        pastTime = ofGetElapsedTimef();
        currentTime = pastTime;  
        
        color = _color; 
        pcolor = color; 
        
        pos = ofVec3f(x, y, z);
        ppos = pos; 
        
        vel.set(0);
        pvel = vel;

        acc.set(0);
        pacc = acc; 

        times.push_back(currentTime);
        frames.push_back(frame);
        colors.push_back(_color);
        thicknesses.push_back(thickness);
        positions.push_back(pos);
        velocities.push_back(vel); 
        accelerations.push_back(pvel-vel);
                
        addVertex(x,y,z);            
        addPointToVelocityPath(x,y);
        addPointToAccelerationPath(x, y);
        addPointToThicknessPath(pos.x, pos.y, thickness*.5);
    }
    
    void lineTo(float x, float y, float z=0, ofFloatColor _color=ofFloatColor(0), int frame =0, float pressure = 0)
    {
        pos.set(x, y, z);
        currentTime = ofGetElapsedTimef();
        float deltaT = (currentTime-pastTime);
        color = _color; 
        vel = .025*(pos-ppos)/deltaT;     
        acc = .025*(vel-pvel)/deltaT; 
        
        thickness = (pos-ppos).crossed(ofVec3f(0,0,1));        
        switch (pressureType) 
        {
            case OFX_PATH_PRESSURE_DISTANCE:
                //return 
                break;

            case OFX_PATH_PRESSURE_PRESSURE:
            	thickness.normalize()*=pressure;
                break;

            case OFX_PATH_PRESSURE_FIXED:
                thickness.normalize()*=fixedThickness;
                break;

            default:
                break;
        }
        
        times.push_back(currentTime);
        frames.push_back(frame);        
        colors.push_back(_color);
        thicknesses.push_back(thickness);
        positions.push_back(pos);
        velocities.push_back(vel);
        accelerations.push_back(acc);
                
        velocityPath.lineTo(ppos.x+vel.x, ppos.y+vel.y, 0);
        accelerationPath.lineTo(ppos.x+acc.x, ppos.y+acc.y, 0);
        
        addVertex(pos.x, pos.y, pos.z);    
        addPointToVelocityPath(pos.x,pos.y);
        addPointToAccelerationPath(pos.x,pos.y);        
        addPointToThicknessPath(pos.x, pos.y, thickness*.5);

        pcolor = color; 
        ppos = pos; 
        pvel = vel; 
        pacc = acc; 
        pthickness = thickness; 
        pastTime = currentTime; 
    }
    
    void lineEnd(float x, float y, float z=0, int frame =0, float time = -1, float pressure = 0)
    {
        
    }
    
    void lineStart(float x, float y, float z=0, ofFloatColor _color=ofFloatColor(0), float time = -1, float pressure = 0)
    {
        thickness.set(0);
        pthickness = thickness; 
        pastTime = time;
        currentTime = time;  
        
        color = _color; 
        pcolor = color; 
        
        pos = ofVec3f(x, y, z);
        ppos = pos; 
        
        vel.set(0);
        pvel = vel;
        
        acc.set(0);         
        pacc = acc; 
        
        times.push_back(currentTime);
        colors.push_back(_color);
        thicknesses.push_back(thickness);
        positions.push_back(pos);
        velocities.push_back(vel); 
        accelerations.push_back(pvel-vel);
        
        addVertex(x,y,z);            
        addPointToVelocityPath(x,y);
        addPointToAccelerationPath(x, y);
        addPointToThicknessPath(pos.x, pos.y, thickness*.5);
    }
    
    void lineTo(float x, float y, float z=0, ofFloatColor _color=ofFloatColor(0), float time = -1, float pressure = 0)
    {
        pos.set(x, y, z);
        currentTime = time; 
        float deltaT = (currentTime-pastTime);
        color = _color; 
        vel = .025*(pos-ppos)/deltaT;     
        acc = .025*(vel-pvel)/deltaT; 
        
        thickness = (pos-ppos).crossed(ofVec3f(0,0,1));        
        switch (pressureType) 
        {
            case OFX_PATH_PRESSURE_DISTANCE:
                //return 
                break;
                
            case OFX_PATH_PRESSURE_PRESSURE:
            	thickness.normalize()*=pressure;
                break;
                
            case OFX_PATH_PRESSURE_FIXED:
                thickness.normalize()*=fixedThickness;
                break;
                
            default:
                break;
        }
        
        times.push_back(currentTime);     
        colors.push_back(_color);
        thicknesses.push_back(thickness);
        positions.push_back(pos);
        velocities.push_back(vel);
        accelerations.push_back(acc);
        
        velocityPath.lineTo(ppos.x+vel.x, ppos.y+vel.y, 0);
        accelerationPath.lineTo(ppos.x+acc.x, ppos.y+acc.y, 0);
        
        addVertex(pos.x, pos.y, pos.z);    
        addPointToVelocityPath(pos.x,pos.y);
        addPointToAccelerationPath(pos.x,pos.y);        
        addPointToThicknessPath(pos.x, pos.y, thickness*.5);
        
        pcolor = color; 
        ppos = pos; 
        pvel = vel; 
        pacc = acc; 
        pthickness = thickness; 
        pastTime = currentTime; 
    }
    
    void lineEnd(float x, float y, float z=0, int frame =0, float time = -1)
    {
        
    }    
    
    void addPointToVelocityPath(float x, float y)
    {
        velocityPath.setColor(velocityPathColor);
        velocityPath.setStrokeWidth(2);
        velocityPath.newSubPath();
        velocityPath.lineTo(x, y, 0);                
    }

    void addPointToAccelerationPath(float x, float y)
    {
        accelerationPath.setColor(accelerationPathColor);
        accelerationPath.setStrokeWidth(2);
        accelerationPath.newSubPath();
        accelerationPath.lineTo(x, y, 0);                
    }
    
    void addPointToThicknessPath(float x, float y, ofVec3f t)
    {
        thicknessPath.setColor(thicknessPathColor);
        thicknessPath.setStrokeWidth(2);
        thicknessPath.newSubPath();
        thicknessPath.lineTo(x-t.x, y-t.y, 0);                        
        thicknessPath.lineTo(x+t.x, y+t.y, 0);                                
    }
    
    void reset()
    {
        clear(); 

        times.clear(); 
        frames.clear();         
        positions.clear(); 
        colors.clear();
        velocities.clear(); 
        accelerations.clear();
        thicknesses.clear();

        velocityPath.clear(); 
        accelerationPath.clear();         
        thicknessPath.clear();
        
    }
    
    vector<ofFloatColor> colors; 
    vector<ofVec3f> positions; 
    vector<ofVec3f> velocities; 
    vector<ofVec3f> accelerations;
    vector<ofVec3f> thicknesses; 
    vector<float> times; 
    vector<int> frames; 
        
    ofPath thicknessPath;
    ofPath velocityPath; 
    ofPath accelerationPath;         
    
    ofVec3f thickness; 
    ofVec3f pthickness;     
    
    ofVec3f pos; 
    ofVec3f ppos; 
    
    ofVec3f vel; 
    ofVec3f pvel; 
    
    ofVec3f acc; 
    ofVec3f pacc;
    
    ofFloatColor color; 
    ofFloatColor pcolor; 
    
    float currentTime; 
    float pastTime; 
    
    int pressureType; 
    ofColor thicknessPathColor;
    ofColor positionPathColor; 
    ofColor velocityPathColor; 
    ofColor accelerationPathColor; 
    
    float fixedThickness; 
};


#endif
