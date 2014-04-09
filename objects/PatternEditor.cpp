#include "PatternEditor.h"

#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"

#include "BulletPatternGroup.h"

PatternEditor::PatternEditor(BulletPatternGroup *group)
{
    this->group = group;
    this->typeString =  "";
}

PatternEditor::~PatternEditor()
{
    //dtor
}

void PatternEditor::draw() {
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(this->typeString, 100, 100, 0);
}

void PatternEditor::mouseReleased(int x, int y, int button){
    ofVec2f pos = ofVec2f(x, y);
    if(this->keys._1) {
        this->group->addPattern(new CyclicEllipseBulletPattern(30, pos, 7, .3));
    }
    if(this->keys._2) {
        this->group->addPattern(new RadialBulletPattern(20, pos, 10, .085));
    }
    if(this->keys._3) {
        this->group->addPattern(new FanOutBulletPattern(10, pos, 5, .2, PI/2, ofVec2f(0, 1), 0, 1, .5));
    }
    if(this->keys._4) {
        this->group->addPattern(new TargetedBulletPattern(1, pos, 5, .1, 2, .5));
    }
    if(this->keys._5) {
        this->group->addPattern(new OscillatingFanOutBulletPattern(10, pos, 5, .2, ofVec2f(0, 1)));
    }
    if(this->keys._6) {

    }
    for(vector<BulletPattern*>::iterator it2 = this->group->patterns.begin(); it2 != this->group->patterns.end(); ++it2) {
        BulletPattern* currentPattern = (BulletPattern *)*it2;
        currentPattern->setPlayersReference(this->players);
    }
}

void PatternEditor::setPlayersReference(vector<Player*>* players) {
    this->players = players;
}

void PatternEditor::keyPressed(int key) {
    cout << "key: " << key << endl;
    if (key == 49) {
        this->keys._1 = true;
        this->typeString = "Cyclic Ellipse";
    } else if (key == 50) {
        this->keys._2 = true;
        this->typeString = "Radial";
    } else if (key ==  51) {
        this->keys._3 = true;
        this->typeString = "Fan Out";
    } else if (key == 52) {
        this->keys._4 = true;
        this->typeString = "Targeted";
    } else if (key == 53) {
        this->keys._5 = true;
        this->typeString = "Oscillating Fan Out";
    } else if (key == 54) {
        this->keys._6 = true;
    }
    if (key == 100) {
        this->group->patterns.clear();
    }
}

void PatternEditor::keyReleased(int key) {
    if (key == 49) {
        this->keys._1 = false;
        this->typeString = "";
    } else if (key == 50) {
        this->keys._2 = false;
        this->typeString = "";
    } else if (key ==  51) {
        this->keys._3 = false;
        this->typeString = "";
    } else if (key == 52) {
        this->keys._4 = false;
        this->typeString = "";
    } else if (key == 53) {
        this->keys._5 = false;
        this->typeString = "";
    } else if (key == 54) {
        this->keys._6 = false;
        this->typeString = "";
    }
}
