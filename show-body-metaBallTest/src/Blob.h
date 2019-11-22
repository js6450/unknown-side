//
//  Blob.h
//  show-body-blob-test1
//
//  Created by Ellie Lin on 11/18/19.
//

#ifndef Blob_h
#define Blob_h

#include <stdio.h>
#include "ofMain.h"


class Blob
{
public:
    void setup(float x, float y, float w, float h);
    void draw();
    glm::vec2 pos;
    ofColor color;
    float width;
    float height;
};

#endif /* Blob_h */
