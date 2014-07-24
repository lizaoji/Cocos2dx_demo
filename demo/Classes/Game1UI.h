//
//  Game1UI.h
//  demo
//
//  Created by li zaoji on 7/15/14.
//
//

#ifndef _GAME_1_UI_H_
#define _GAME_1_UI_H_

#include "cocos2d.h"

class Game1UI: public cocos2d::Layer{
public:
    bool init();
    static cocos2d::Layer * createLayer();
    CREATE_FUNC(Game1UI);
    void newGame(Ref* obj);
    void back(Ref* obj);
    
};

#endif