//
//  Game1Scene.h
//  demo
//
//  Created by li zaoji on 7/12/14.
//
//
#ifndef _GAME_1_SCENE_H_
#define _GAME_1_SCENE_H_

#include "cocos2d.h"
#include "Game1Define.h"
#include "MovedTile.h"

USING_NS_CC;

class Game1Scene: public LayerColor{
private:
    Vec2 touchStartPoint = Vec2(0.0, 0.0);
    bool touchIsEffective = false;
    enum touchEnumDirection{ UP, DOWN, LEFT, RIGHT, NODIR };
    touchEnumDirection currentDirection = NODIR;
    int map[GAME1_ROWS][GAME1_COLS];
    MovedTile * allTile[GAME1_ROWS][GAME1_COLS] = {nullptr};
    LayerColor * gameBoard;
    bool init();
    unsigned int totalTiles = 0;
    unsigned int best = 0;
    unsigned int score = 0;
    bool isGameOver = false;
    
public:
    //类生成相关方法
    static Scene * createScene();
    CREATE_FUNC(Game1Scene);
    
    //一轮游戏主逻辑函数
    void oneRound();
    //生成一个Tile
    void createOneTile();
    
    //移动Tile的方法
    void moveAllTile();
    
    //用src的Tile合并dst的Tile，最后在dst显示数字double后的新Tile
    void mergeTile(unsigned int src_r, unsigned int src_c, unsigned int dst_r, unsigned int dst_c);
    
    //更新当前在场Tile的数目
    void updateTileNum();
    
    //new game
    void newGame();
    
    //game over 判断
    void gameOverCheck();
    
    
};

#endif