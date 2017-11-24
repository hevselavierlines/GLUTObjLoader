//
//  Model.hpp
//  GlutA2
//
//  Created by Manuel Baumgartner on 23/11/2017.
//  Copyright © 2017 Hevselavier Lines Ver. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <GLUT/glut.h>

using namespace std;

class Vector3f {
public:
    typedef std::unique_ptr<Vector3f> Ref;
    float x, y, z;
};

class Index3i {
public:
    typedef std::unique_ptr<Index3i> Ref;
    int i1, i2, i3;
};

class Model {
public:
    typedef std::unique_ptr<Model> Ref;
    vector<Vector3f> vertices;
    vector<Index3i> faces;
    float rotX, rotY, rotZ;
    float scaleX, scaleY, scaleZ;
    float minX, minY, minZ, maxX, maxY, maxZ;
    int mode;
    
    Model() : scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f), mode(0) {};
    
    void draw();
    void load(string fileName);
    vector<string> split(string line, char split);
};

#endif /* Model_hpp */
