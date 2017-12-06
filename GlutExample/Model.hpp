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

#include "smartpointer.hpp"

using namespace std;

class Vector3f {
public:
    typedef ofPtr<Vector3f> Ref;
    float x, y, z;
    
    Vector3f():x(0), y(0), z(0) {};
    Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
};

class Index3i {
public:
    typedef ofPtr<Index3i> Ref;
    int size;
    int i1, i2, i3, i4;
    vector<int> indices;
};

class Model {
public:
    typedef ofPtr<Model> Ref;
    vector<Vector3f::Ref> vertices;
    vector<Index3i::Ref> faces;
    float rotX, rotY, rotZ;
    float scaleX, scaleY, scaleZ;
    float minX, minY, minZ, maxX, maxY, maxZ;
    int mode;
    
    Model() : scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f), mode(0) {};
    
    void copy(Model::Ref copy);
    void draw();
    void load(string fileName);
    vector<string> split(string line, char split);
};

#endif /* Model_hpp */
