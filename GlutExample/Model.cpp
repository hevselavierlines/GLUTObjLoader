//
//  Model.cpp
//  GlutA2
//
//  Created by Manuel Baumgartner on 23/11/2017.
//  Copyright © 2017 Hevselavier Lines Ver. All rights reserved.
//

#include <cmath>
#include "Model.hpp"

void Model::load(string fileName) {
    fstream inStream;
    inStream.open(fileName, ios::in);
    if (inStream.fail())
        return;
    std::string str;
    while(std::getline(inStream, str)){
        vector<string> splits = split(str, ' ');
        if(splits.size() >= 3) {
            string type = splits[0];
            if(type.compare("v") == 0) {
                Vector3f::Ref vertex = Vector3f::Ref(new Vector3f());
                vertex->x = std::stof(splits[1]);
                vertex->y = std::stof(splits[2]);
                vertex->z = std::stof(splits[3]);
                if(vertex->x < minX) {
                    minX = vertex->x;
                }
                if(vertex->y < minY) {
                    minY = vertex->y;
                }
                if(vertex->z < minZ) {
                    minZ = vertex->z;
                }
                if(vertex->x > maxX) {
                    maxX = vertex->x;
                }
                if(vertex->y > maxY) {
                    maxY = vertex->y;
                }
                if(vertex->z > maxZ) {
                    maxZ = vertex->z;
                }
                
                vertices.push_back(vertex);
                
            } else if(type.compare("f") == 0) {
                Index3i::Ref index = Index3i::Ref(new Index3i());
                index->i1 = std::stoi(split(splits[1], '/')[0]) - 1;
                index->i2 = std::stoi(split(splits[2], '/')[0]) - 1;
                index->i3 = std::stoi(split(splits[3], '/')[0]) - 1;
                faces.push_back(index);
            }
        }
        
    }
    inStream.close();
    scaleX = (float)100 / (abs(minX) + abs(maxX)) / 2;
    scaleY = (float)100 / (abs(minY) + abs(maxY)) / 2;
    scaleZ = (float)100 / (abs(minZ) + abs(maxZ)) / 2;
    
    if(scaleX <= scaleY && scaleX <= scaleZ) {
        scaleY = scaleX;
        scaleZ = scaleX;
    }
    
    if(scaleY <= scaleX && scaleY <= scaleZ) {
        scaleX = scaleY;
        scaleZ = scaleY;
    }
    
    if(scaleZ <= scaleX && scaleZ <= scaleY) {
        scaleX = scaleZ;
        scaleY = scaleZ;
    }
}

vector<string> Model::split(string line, char split) {
    vector<string> elems;
    int currElem = 0;
    elems.push_back("");
    for(int i = 0; i < line.length(); i++) {
        char elem = line.at(i);
        if(elem == split) {
            currElem++;
            elems.push_back("");
        } else {
            elems[currElem].append(sizeof(char), elem);
        }
    }
    return elems;
}

void Model::copy(Model::Ref copy) {
    vertices = copy->vertices;
    faces = copy->faces;
    minX = copy->minX;
    minY = copy->minY;
    minZ = copy->minZ;
    maxX = copy->maxX;
    maxY = copy->maxY;
    maxZ = copy->maxZ;
    rotX = copy->rotX;
    rotY = copy->rotY;
    rotZ = copy->rotZ;
    scaleX = copy->scaleX;
    scaleY = copy->scaleY;
    scaleZ = copy->scaleZ;
}

void Model::draw() {
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    if(mode == 0) {
        glPolygonMode(GL_FRONT,GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
    }
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < faces.size(); i++) {
        Index3i::Ref index = faces[i];
        
        Vector3f::Ref elem1 = vertices[index->i1];
        glVertex3f(elem1->x, elem1->y, elem1->z);
        
        Vector3f::Ref elem2 = vertices[index->i2];
        glVertex3f(elem2->x, elem2->y, elem2->z);
        
        Vector3f::Ref elem3 = vertices[index->i3];
        glVertex3f(elem3->x, elem3->y, elem3->z);
    }
    glEnd();
    if(mode == 0) {
        glPolygonMode(GL_FRONT,GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
    glPopMatrix();
}