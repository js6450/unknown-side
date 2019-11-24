#include "ofApp.h"
#include <glm/gtx/fast_square_root.hpp>

/*

handshake-01: file cutoff is -180, xoffset is 75, -75

hug-01: file cuttof is -180, xoffset is 75, -75

pat-02: file cuttof is none, xoffset is 45, -45

z coordinate ranges between 1500 - 1700
 
 
 
 level one action: stand [0 - 2]
 level two action: handshake, hug [3 - 6]
 level three action: pat, linking, kiss, cuddle [7 - 18]
 avert action: walking [19 - 20]
*/

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(false);
    ofSetFrameRate(60);

	ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinect::Device::getInstalledCount() << " installed devices.";

	auto kinectSettings = ofxAzureKinect::DeviceSettings();
	kinectSettings.synchronized = false;
	kinectSettings.depthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
	kinectSettings.updateIr = false;
	kinectSettings.updateColor = false;
	//kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_1080P;
	kinectSettings.updateBodies = true;
	kinectSettings.updateWorld = true;
	kinectSettings.updateVbo = false;
	if (this->kinectDevice.open(kinectSettings))
	{
		this->kinectDevice.startCameras();
	}
    
/*    array<int, 44> selectedJoints {0, 1, 2, 4, 5, 6, 7, 8, 11,12,13,14,15,18,19,20,21,22,23,24,25,26,
    32,33,34,36,37,38,39,40,43,44,45,46,47,50,51,52,53,54,55,56,57,58};
                       0  pelvis,
                       1 spine,_naval,
                       2 spine_chest,
                       4 clavicle_left
                       5 shoulder_left
                       6 elbow_left
                       7 wrist_left
                       8 hand_left
                       11 clavicle_right
                       12 shoulder_right
                       13 elbow_right
                       14 wrist_right
                       15 hand_right
                       18 hip_left
                       19 knee_left
                       20 ankle_left
                       21 foor_left
                       22 hip_right
                       23 knee_right
                       24 ankle_right
                       25 foot_right
                       26 head
 */
   
    float w;
    float h;
    for (int i = 0; i < 64; i++){
            switch (i) {
                case 0:
                case 32:
                    w = 32; h = 20;
                break;
                case 1:
                case 2:
                case 33:
                case 34:
                    w = 18; h = 22;
                break;
                case 4:
                case 11:
                case 36:
                case 43:
                    w = 14; h = 6;
                break;
                case 5:
                case 12:
                case 37:
                case 44:
                    w = 14; h = 20;
                break;
                case 6:
				case 13:
                case 38:
                case 45:
                    w = 14; h = 14;
                break;
                case 7:
                case 14:
                case 39:
                case 46:
                    w = 10; h = 10;
                break;
                case 8:
                case 15:
                case 40:
                case 47:
                    w = 10; h = 10;
                break;
                case 18:
                case 22:
                case 50:
                case 54:
                    w = 14; h = 40;
                break;
                case 19:
                case 23:
                case 51:
                case 55:
                    w = 14; h = 60;
                break;
                case 20:
                case 24:
                case 52:
                case 56:
                    w = 10; h = 28;
                break;
                case 21:
                case 25:
                case 53:
                case 57:
                    w = 20; h = 10;
                break;
                case 26:
                case 58:
                    w = 20; h = 36;
                break;
              default:
                    w = 0.01; h = 0.01;
        }
          blobs.push_back(Blob(0, 0, w, h));
    }
    
    //load shader code

    shader.setupShaderFromSource(GL_VERTEX_SHADER, R"(
     #version 150

     uniform mat4 modelViewProjectionMatrix;
     in vec4 position;

     void main(){
         gl_Position = modelViewProjectionMatrix * position;
     }
    )");

    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, R"(
    #version 150

    #define NUM_BLOBS 64

    uniform vec4 blobs[NUM_BLOBS];

    out vec4 outputColor;
                                                        
    void main()
    {
                            
        float color = 0.0;
        float sum = 255.0;
        
        for(int i = 0; i < NUM_BLOBS; ++i)
        {
        vec2 blobPos = vec2(blobs[i].x, blobs[i].y);
        vec2 fragPos = vec2(gl_FragCoord.x, gl_FragCoord.y);
                                      
         //sum +=  5 * blobs[i].z / distance(blobPos,fragPos);

         sum -=  600 / ((( gl_FragCoord.x - blobs[i].x) * ( gl_FragCoord.x - blobs[i].x)) / (blobs[i].z/2 * blobs[i].z/2) + (( gl_FragCoord.y - blobs[i].y) * ( gl_FragCoord.y - blobs[i].y)) / (blobs[i].w/2 * blobs[i].w/2));
        }
        if (sum <= 256.0) {
        color = max(0.0, sum) / 255.0;
        } else {color = 0.0;}
        outputColor = vec4(color, color, color , 0.1);
                      
    }
    )");
    
    shader.linkProgram();
    
    //Load joint files
    
    for(int i = 1; i < 4; i++){
        string filename = "stand-0" + ofToString(i) + ".txt";
        
        ofBuffer buffer = ofBufferFromFile(filename);
        
        vector<string> currentBodies;

        for (auto line : buffer.getLines()) {
            currentBodies.push_back(line);
        }
        
        actions.push_back(currentBodies);
    }
    
    for(int i = 1; i < 5; i++){
        string filename = "leveltwo-" + ofToString(i) + ".txt";
        
        ofBuffer buffer = ofBufferFromFile(filename);
        
        vector<string> currentBodies;

        for (auto line : buffer.getLines()) {
            currentBodies.push_back(line);
        }
        
        actions.push_back(currentBodies);
        
    }
    
    for(int i = 1; i < 12; i++){
        string filename = "levelthree-" + ofToString(i) + ".txt";
        
        ofBuffer buffer = ofBufferFromFile(filename);
        
        vector<string> currentBodies;

        for (auto line : buffer.getLines()) {
            currentBodies.push_back(line);
        }
        
        actions.push_back(currentBodies);
        
    }
    
    for(int i = 1; i < 3; i++){
        string filename = "walk-0" + ofToString(i) + ".txt";
        
        ofBuffer buffer = ofBufferFromFile(filename);
        
        vector<string> currentBodies;

        for (auto line : buffer.getLines()) {
            currentBodies.push_back(line);
        }
        
        actions.push_back(currentBodies);
    }
    
    //setup gui
    
    bodyOne.set("body one x pos", ofGetWidth() / 4, 0, ofGetWidth() / 2);
    bodyTwo.set("body two x pos", ofGetWidth() * 3 / 4, ofGetWidth() / 2, ofGetWidth());
    dist.set("distance", ofGetWidth() / 2, 0, ofGetWidth());
    showAni.set("show shadow", false);
    triggerAni.set("show ani", false);
    autoAni.set("automate", true);
    
    gui.setup("Body Positions", "settings.json");

    gui.add(bodyOne);
    gui.add(bodyTwo);
    gui.add(dist);
    gui.add(showAni);
    gui.add(triggerAni);
    gui.add(autoAni);
    
    ofSetBackgroundAuto(false);

    ofBackground(255);
    
    cout << actions[19].size() << endl;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	this->kinectDevice.close();
}

//--------------------------------------------------------------
void ofApp::update(){

	auto& bodySkeletons = this->kinectDevice.getBodySkeletons();

	totalBodies = bodySkeletons.size();

	if (totalBodies > 1) {
		spineOne = glm::vec2(0, 0);
		spineTwo = glm::vec2(ofGetWidth(), 0);

		for (int s = 0; s < bodySkeletons.size(); s++) {

			float mappedX = ofMap(bodySkeletons[s].joints[2].position.xyz.x, ofGetWidth() * 2, -ofGetWidth() * 2, 0, ofGetWidth());
			float mappedY = ofMap(bodySkeletons[s].joints[2].position.xyz.y, -ofGetHeight() * 2, ofGetHeight() * 2, 0, ofGetHeight());

			if (bodySkeletons[s].joints[2].position.xyz.x > 0) {
				// left = spineOne
				spineOne = glm::vec2(mappedX, mappedY);
			}
			else {
				// right = spineTwo
				spineTwo = glm::vec2(mappedX, mappedY);
			}

			/*
			if (s == 0) {
				spineOne = glm::vec2(bodySkeletons[s].joints[2].position.xyz.x, bodySkeletons[s].joints[2].position.xyz.y);
			}
			else if (s == 1) {
				spineTwo = glm::vec2(bodySkeletons[s].joints[2].position.xyz.x, bodySkeletons[s].joints[2].position.xyz.y);
			}
			*/
		}

		if (abs(glm::distance(prevSpineOne, spineOne)) < 5 && abs(glm::distance(prevSpineTwo, spineTwo)) < 5) {
			dist = abs(glm::distance(spineOne, spineTwo));

			if (bufferCount > 30) {

				showAni = true;
				/*
				 level one action: stand [0 - 2]
				 level two action: handshake, hug [3 - 6]
				 level three action: pat, linking, kiss, cuddle [7 - 18]
				 avert action: walking [19 - 20]
				 */
				if (triggerAni) {
					bodyIndex = 0;

					if (dist < onemeter) {
						currentBody = ofRandom(7, 18);
					}
					else if (dist >= onemeter && dist < onemeter * 2) {
						currentBody = ofRandom(3, 7);
					}
					else if (dist >= onemeter * 2 && dist < onemeter * 3) {
						currentBody = ofRandom(0, 3);
					}

					triggerAni = false;
					bufferCount = 0;
				}
			}
			bufferCount++;
		}else {
			triggerAni = true;
		}
	}
	else {
		showAni = false;
	}

	//showAni can only be true if there is more than one body
	if (!showAni) {
		for (int s = 0; s < bodySkeletons.size(); s++) {
			if (s < 2) {

				//right
				int bIndex = 0;

				//left
				if (bodySkeletons[s].joints[2].position.xyz.x > 0) {
					bIndex += 32;
				}

				for (int i = 0; i < K4ABT_JOINT_COUNT; ++i) {
					auto joint = bodySkeletons[s].joints[i];

					float x = joint.position.xyz.x;
					float y = joint.position.xyz.y;
					float z = joint.position.xyz.z;

					float mappedx = ofMap(x, ofGetWidth() * 2, -ofGetWidth() * 2, 0, ofGetWidth());
					float mappedy = ofMap(y, -ofGetHeight() * 2, ofGetHeight() * 2, -ofGetHeight() / 2, ofGetHeight() / 2);

					blobs[bIndex + i].pos.x = mappedx;

					// move the head up
					if (i == 26) {
						blobs[bIndex + i].pos.y = ofGetHeight() - (mappedy + ofGetHeight() / 2) + 26;
					}
					else {
						blobs[bIndex + i].pos.y = ofGetHeight() - (mappedy + ofGetHeight() / 2);
					}
				}

			}

		}
	}
	
	else {
		if (actions.size() > 0) {

			auto joints = ofSplitString(actions[currentBody][bodyIndex], ";");

			for (int i = 0; i < joints.size(); i++) {

				auto pos = ofSplitString(joints[i], ",");

				if (pos.size() == 3) {

					float targetX, targetY;
					float x, y, z;

					//left side

					x = ofMap(ofToInt(pos[0]), -ofGetWidth() * 2, ofGetWidth() * 2, -ofGetWidth() / 2, ofGetWidth() / 2) - 45;
					y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, -ofGetHeight() / 2, ofGetHeight() / 2);
					z = ofMap(ofToFloat(pos[2]), 1500, 1700, 70, 30);

				    targetX = spineOne.x + dist / 2;
					targetY = ofGetHeight() - (y + ofGetHeight() / 2);

					blobs[i + 32].pos.x = ofLerp(blobs[i + 32].pos.x, targetX + x, 0.05);
					
					if (i == 26) {
						blobs[i + 32].pos.y = ofLerp(blobs[i + 32].pos.y, targetY + 26, 0.05);
					}
					else {
						blobs[i + 32].pos.y = ofLerp(blobs[i + 32].pos.y, targetY, 0.05);
					}


					// right side

					x = ofMap(ofToInt(pos[0]), ofGetWidth() * 2, -ofGetWidth() * 2, -ofGetWidth() / 2, ofGetWidth() / 2) + 45;
					y = ofMap(ofToInt(pos[1]), -ofGetHeight() * 2, ofGetHeight() * 2, -ofGetHeight() / 2, ofGetHeight() / 2);
					z = ofMap(ofToFloat(pos[2]), 1500, 1700, 200, 30);

					targetX = spineTwo.x - dist / 2;
					targetY = ofGetHeight() - (y + ofGetHeight() / 2);

					blobs[i].pos.x = ofLerp(blobs[i].pos.x, targetX + x, 0.05);

					if (i == 26) {
						blobs[i].pos.y = ofLerp(blobs[i].pos.y, targetY + 26, 0.05);
					}
					else {
						blobs[i].pos.y = ofLerp(blobs[i].pos.y, targetY, 0.05);
					}

				}

			}

		}
	}
	

	if (bodyIndex < actions[currentBody].size() - 1) {
        if(showAni){
            bodyIndex++;
        }
	}
	else {
		//bodyIndex = 0;
        showAni = false;
	}
    
	prevSpineOne = spineOne;
	prevSpineTwo = spineTwo;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 10);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    shader.begin();

    // Use a pointer instead of an array so that we can use a variable size.
    float* v = new float[blobs.size() * 4];
    for (int i = 0; i < blobs.size(); i++)
    {
        v[i * 4 + 0] = blobs[i].pos.x;
        v[i * 4 + 1] = blobs[i].pos.y;
        v[i * 4 + 2] = blobs[i].width;
        v[i * 4 + 3] = blobs[i].height;
        
    }
    shader.setUniform4fv("blobs", v, 48 * 4);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();

    // Delete the pointer when done (Remember, every "new" needs a matching "delete").
    delete[] v;
    
	/*
    ofSetColor(255, 0, 0);
	ofDrawEllipse(blobs[0].pos.x, blobs[0].pos.y, 50, 50);

	//blue is always on the left
	ofSetColor(0, 0, 255);
	ofDrawEllipse(blobs[32].pos.x, blobs[32].pos.y, 50, 50);

	ofSetColor(255, 0, 0);
	ofDrawRectangle(spineOne.x, spineOne.y, 50, 50);

	//blue is always on the left
	ofSetColor(0, 0, 255);
	ofDrawRectangle(spineTwo.x, spineTwo.y, 50, 50);
	*/

    ofDrawBitmapStringHighlight(ofToString(currentBody), ofGetWidth() - 100, 20);
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2), ofGetWidth() - 100, 50);

    //gui.draw();
}

void ofApp::drawBody(int i){

	//combine this to update()
    
   
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
