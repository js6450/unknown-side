//
//  Blob.cpp
//  show-body
//
//  Created by Jiwon Shin on 11/18/19.
//

#include "Blob.h"

Blob::Blob(float x, float y, float w, float h){
    pos = glm::vec2(x, y);
//    vel = glm::vec2(ofRandomf(), ofRandomf());
//    vel *= ofRandom(2, 5);
    width = w;
    height = h;
	r = 10;
//    r = 10;
}

//void Blob::update(){
//    pos += vel;
//    if (pos.x > ofGetWidth() || pos.x < 0)
//    {
//        vel.x *= -1;
//    }
//    if (pos.y > ofGetHeight() || pos.y < 0)
//    {
//        vel.y *= -1;
//    }
//}
