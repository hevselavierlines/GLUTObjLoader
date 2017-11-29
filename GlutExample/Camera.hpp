//
//  Camera.hpp
//  GlutA2
//
//  Created by Manuel Baumgartner on 29/11/2017.
//  Copyright © 2017 Hevselavier Lines Ver. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GLUT/glut.h>

#include "Model.hpp"

class Camera {
public:
    Vector3f position;
    float rotateX, rotateY, rotateZ;
    
    Camera() : position({0, 0, -100.0f}) {}
    void render(Model* model);
};

#endif /* Camera_hpp */
