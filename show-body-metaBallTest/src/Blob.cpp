//
//  Blob.cpp
//  show-body-blob-test1
//
//  Created by Ellie Lin on 11/18/19.
//

#include "Blob.h"

void Blob::setup(float x, float y, float w, float h)
{
    pos = glm::vec2(x, y);
    color = ofColor(0);
    width = w;
    height = h;
//
//
}

void Blob::draw()
{
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    ofSetColor(color);
    ofDrawEllipse(0, 0, width, height);
    glPopMatrix();
}


