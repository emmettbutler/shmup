//
//  Camera.h
//  emptyExample
//
//  Created by Emmett Butler on 5/5/14.
//
//

#ifndef __emptyExample__Camera__
#define __emptyExample__Camera__

#include <iostream>
#include "ofMain.h"

class BulletPatternGroup;
class GameObject;
class Background;

class Camera {
public:
    BulletPatternGroup *group;
    Background *background;
    vector<GameObject*> objects;
    ofVec2f scroll_direction, last_scroll_direction;
    bool paused;
    
    Camera();
    void setGroupReference(BulletPatternGroup *group);
    void setBackgroundReference(Background *background);
    void update(float deltatime);
    void startScrolling(ofVec2f dir);
    void stopScrolling();
    bool isScrolling();
    void move(ofVec2f dir);
    void pause();
    void unpause();
};

#endif /* defined(__emptyExample__Camera__) */
