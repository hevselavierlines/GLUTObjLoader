//
//  Camera.cpp
//  GlutA2
//
//  Created by Manuel Baumgartner on 29/11/2017.
//  Copyright © 2017 Hevselavier Lines Ver. All rights reserved.
//

#include "Camera.hpp"

void Camera::render(Model* model) {
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        model->draw();
    glPopMatrix();
}

