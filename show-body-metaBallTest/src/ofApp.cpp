#include "ofApp.h"

/*

handshake-01: file cutoff is -180, xoffset is 75, -75

hug-01: file cuttof is -180, xoffset is 75, -75

pat-02: file cuttof is none, xoffset is 45, -45

z coordinate ranges between 1500 - 1700
*/

//--------------------------------------------------------------
void ofApp::setup(){

    //canvas.allocate(ofGetWidth(), ofGetWindowHeight(), OF_IMAGE_GRAYSCALE);
    blur.setup(ofGetWindowWidth(), ofGetWindowHeight(), 10, .2, 2);
    blur.setScale(5);
    
    ofBuffer buffer = ofBufferFromFile("walk-02-100.txt");

    for (auto line : buffer.getLines()) {
        bodies.push_back(line);
    }
    

    
    ofBackground(255);


}

//--------------------------------------------------------------
void ofApp::update(){
    
//    auto pixCanvas = canvas.getPixels().getData();
//
//    for (int x = 0; x < canvas.getWidth(); x ++) {
//        for (int y = 0; y < canvas.getHeight(); y ++) {
//            int index = x + y * canvas.getWidth();
//
//            //pixCanvas.setColor(x, y, ofColor(255, 0, 0));
//            glm::vec2 idx = glm::vec2(x, y);
//
//            float sum = 0;
//            for (Blob& b : blobs) {
//                float dist = glm::fastDistance(b.pos, idx);
//                sum += 5 * b.r / dist;
//            }
//            pixCanvas[index] = sum;
//           // pixCanvas.setColor(x, y, ofColor(sum));
//        }
//    }
//
//    //canvas.setFromPixels(pixCanvas);
//    canvas.update();
    
    if (bodyIndex < bodies.size() - 100) {
        bodyIndex++;
    }
    else {
        bodyIndex = 0;
    }
    
}

//--------------------------------------------------------------

void ofApp::draw(){

    ofBackground(255, 30);

    if (bodies.size() > 0) {


        auto joints = ofSplitString(bodies[bodyIndex], ";");

        for(int i = 0; i < joints.size(); i++){
            auto pos = ofSplitString(joints[i], ",");


            if (pos.size() == 3) {

                float x = ofMap(ofToInt(pos[0]), -ofGetWidth() * 2, ofGetWidth() * 2, 0, ofGetWidth()) - 45;
                float y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, 0, ofGetHeight());
                float z = ofMap(ofToFloat(pos[2]), 1500, 1700, 70, 30);
                float w;
                float h;
                
                
                array<int, 20> selectedJoints {0,1,2,4,5,6,7,8,11,12,13,14,15,18,19,20,22,23,24,26};
                
                /* 0 0  pelvis,
                   1 1 spine,_naval,
                   2 2 spine_chest,
                   3 4 clavicle_left
                   4 5 shoulder_left
                   5 6 elbow_left
                   6 7 wrist_left
                   7 8 hand_left
                   8 11 clavicle_right
                   9 12 shoulder_right
                   10 13 elbow_right
                   11 14 wrist_right
                   12 15 hand_right
                   13 18 hip_left
                   14 19 knee_left
                   15 20 ankle_left
                   16 22 hip_right
                   17 23 knee_right
                   18 24 ankle_right
                   19 26 head
                */
                
               
                   for (int j = 0; j < selectedJoints.size(); j++) {
                        if ( i == selectedJoints[j]) {
                            switch (i) {
                                case 0:
                                    w = 80; h = 50;
                                break;
                                case 1:
                                case 2:
                                    w = 45; h = 55;
                                break;
                                case 4:
                                case 11:
                                    w = 35; h = 25;
                                break;
                                case 5:
                                case 12:
                                    w = 35; h = 35;
                                break;
                                case 6:
                                case 13:
                                    w = 35; h = 100;
                                break;
                                case 7:
                                case 14:
                                    w = 25; h = 25;
                                break;
                                case 8:
                                case 15:
                                    w = 25; h = 25;
                                break;
                                case 18:
                                case 22:
                                    w = 35; h = 100;
                                break;
                                case 19:
                                case 23:
                                    w = 35; h = 130;
                                break;
                                case 20:
                                case 24:
                                    w = 30; h = 30;
                                break;
                                case 26:
                                    w = 30; h = 50;
                                break;
                                    
                              default:
                                    w = 30; h = 10;
                            }
                           
                            addBlob(x, y, w, h);
                            
                            
                         }
                    }

                /*
                cout << x << endl;
                cout << ", " << endl;
                cout << y << endl;
                */


//                ofSetColor(255, 100);
//
//
//                ofDrawEllipse(x, y, z, z);

               // addBlob(x, y);

                /*
                x = ofMap(ofToInt(pos[0]), ofGetWidth() * 2, -ofGetWidth() * 2, 0, ofGetWidth()) + 45;
                y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, 0, ofGetHeight());
                z = ofMap(ofToFloat(pos[2]), 1500, 1700, 70, 30);
                 */

//                cout << x << endl;
//                cout << ", " << endl;
//                cout << y << endl;

            }
        }



    }
    //canvas.draw(0,0);
}

//--------------------------------------------------------------

void ofApp::addBlob(float x, float y, float w, float h)
{
    blobs.push_back(Blob());
    blobs.back().setup(x, y, w, h);
    
    blur.begin();
    ofBackground(255);
    blobs.back().draw();
    blur.end();
    
    blur.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
