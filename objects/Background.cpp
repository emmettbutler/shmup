//
//  Background.cpp
//  emptyExample
//
//  Created by Emmett Butler on 5/5/14.
//
//

#include "Background.h"

Background::Background() {
    this->infinite = true;
    this->tile_height = ofGetWidth()/8;
    this->size = ofVec2f(ofGetWidth(), ofGetHeight());
    this->pos = ofVec2f(0, this->tile_height * -2);
}

void Background::update(float deltatime) {
    if (this->infinite) {
        if (this->pos.y > 0 || this->pos.y < this->tile_height * -4) {
            this->pos.y = this->tile_height * -2;
        }
    }
}

void Background::draw() {
    int horiz_tiles = (int)this->size.x / (int)this->tile_height;
    int vert_tiles = (int)this->size.y / (int)this->tile_height;
    bool shade = false;
    for (int i = 0; i < horiz_tiles + 1; i++) {
        for (int j = 0; j < vert_tiles + 3; j++) {
            int x = this->pos.x + i*tile_height;
            int y = this->pos.y + j*tile_height;
            shade = !shade;
            if (shade) {
                ofSetColor(200, 200, 200);
            } else {
                ofSetColor(255, 255, 255);
            }
            ofRect(x, y, this->tile_height, this->tile_height);
        }
    }
}