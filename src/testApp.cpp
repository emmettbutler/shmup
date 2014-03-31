#include "testApp.h"
#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"
#include "Player.h"
#include "BulletPatternGroup.h"
#include "BoardPartition.h"

vector<BulletPatternGroup*> groups;
vector<BulletPatternGroup*>::iterator cur_group;
vector<Player*> players;
Player *player;
BoardPartition *board_partition;

//--------------------------------------------------------------
void testApp::setup(){
    ofxGamepadHandler::get()->enableHotplug();
    
    controlType control_type = kControlTypeKeyboard;
	if(ofxGamepadHandler::get()->getNumPads()>0){
        ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(0);
        ofAddListener(pad->onAxisChanged, this, &testApp::axisChanged);
        ofAddListener(pad->onButtonPressed, this, &testApp::buttonPressed);
        ofAddListener(pad->onButtonReleased, this, &testApp::buttonReleased);
        
        control_type = kControlTypeJoystick;
	}
    
    ofVec2f origin = ofVec2f(230,200);
    player = new Player(control_type);
    
    board_partition = new BoardPartition();
    BulletPatternGroup *group;
    
    group = new BulletPatternGroup();
    group->addPattern(new CyclicEllipseBulletPattern(30, origin, 7, .3));
    groups.push_back(group);
    
    group = new BulletPatternGroup();
    group->addPattern(new RadialBulletPattern(20, origin, 10, .085));
    group->addPattern(new FanOutBulletPattern(10, origin, 5, .2, PI/2, ofVec2f(0, 1), 0, 1, .5));
    groups.push_back(group);
    
    group = new BulletPatternGroup();
    float angle = 1;
    for(int i = 0; i < 10; i++){
        ofVec2f thispos = ofVec2f(200*sin(angle),200*cos(angle));
        group->addPattern(new TargetedBulletPattern(1, thispos+ofVec2f(300, 300), 5, .1, 2, .5));
        angle += (2*PI)/10;
    }
    groups.push_back(group);
    
    group = new BulletPatternGroup();
    group->addPattern(new FanOutBulletPattern(10, origin, 5, .2, PI/2, ofVec2f(0, 1), 0, 1, .5));
    group->addPattern(new TargetedBulletPattern(1, origin+ofVec2f(300, 300), 5, .1, 2, .5));
    group->addPattern(new OscillatingFanOutBulletPattern(10, origin, 5, .2, ofVec2f(0, 1)));
    groups.push_back(group);
    
    group = new BulletPatternGroup();
    group->addPattern(new OscillatingFanOutBulletPattern(10, origin, 5, .2, ofVec2f(0, 1)));
    group->addPattern(new OscillatingFanOutBulletPattern(15, origin+ofVec2f(200, 0), 5, .2, ofVec2f(0, 1)));
    groups.push_back(group);
    
    cur_group = groups.begin();
    
    players.push_back(player);
    
    board_partition->setPlayersReference(&players);
    board_partition->setGroupReference(*cur_group);
    board_partition->setDelegate(this);
    for(vector<BulletPatternGroup*>::iterator it = groups.begin(); it != groups.end(); ++it) {
        BulletPatternGroup* currentGroup = (BulletPatternGroup *)*it;
        for(vector<BulletPattern*>::iterator it2 = currentGroup->patterns.begin(); it2 != currentGroup->patterns.end(); ++it2) {
            BulletPattern* currentPattern = (BulletPattern *)*it2;
            currentPattern->setPlayersReference(&players);
        }
    }
}

void testApp::collided(GameObject *obj) {
}

//--------------------------------------------------------------
void testApp::update(){
    float deltatime = ofGetLastFrameTime();
    (*cur_group)->update(deltatime);
    player->update(deltatime);
    board_partition->update(deltatime);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);
    
    board_partition->draw();
    
    int r = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    int g = ofMap(mouseY, 0, ofGetHeight(), 0, 255);
    int b = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    
    player->draw();
    
    ofSetColor(r, g, b);
    ofFill();
    (*cur_group)->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    player->keyPressed(key);
    if (key == ' ') {
        if (cur_group == groups.end() - 1) {
            cur_group = groups.begin();
        } else {
            cur_group++;
        }
        board_partition->setGroupReference(*cur_group);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    player->keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    player->mouseMoved(x, y);
}

void testApp::axisChanged(ofxGamepadAxisEvent& e)
{
	player->axisChanged(e);
}

void testApp::buttonPressed(ofxGamepadButtonEvent& e)
{
	player->buttonPressed(e);
}

void testApp::buttonReleased(ofxGamepadButtonEvent& e)
{
	player->buttonReleased(e);
    if (cur_group == groups.end() - 1) {
        cur_group = groups.begin();
    } else {
        cur_group++;
    }
    board_partition->setGroupReference(*cur_group);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}