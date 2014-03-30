//
//  BoardPartition.h
//  emptyExample
//
//  Created by Emmett Butler on 3/30/14.
//
//

#ifndef __emptyExample__BoardPartition__
#define __emptyExample__BoardPartition__

#include <iostream>
#include "GameObject.h"
#include "ofMain.h"
#include "BoardQuadrant.h"

#endif /* defined(__emptyExample__BoardPartition__) */

class Player;
class BulletPatternGroup;

class BoardPartition : public GameObject {
public:
    vector<BoardQuadrant *> quads;
    vector<Player*>* players;
    BulletPatternGroup* pattern_group;
    
    BoardPartition();
    
    void draw();
    void update(float deltatime);
    void setPlayersReference(vector<Player*>* players);
    void setGroupReference(BulletPatternGroup *pattern_group);
    void setDelegate(BoardQuadrantCollisionDelegate *delegate);
};