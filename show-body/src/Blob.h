//
//  Blob.hpp
//  show-body
//
//  Created by Jiwon Shin on 11/18/19.
//

#ifndef Blob_h
#define Blob_h

#include <stdio.h>
#include "ofMain.h"

class Blob{
public:
    
    glm::vec2 pos;
    float r;
    glm::vec2 vel;
    
    Blob(float x, float y, float w, float h);
//    void update();
    
    float width;
    float height;
    
};

#endif /* Blob_hpp */
