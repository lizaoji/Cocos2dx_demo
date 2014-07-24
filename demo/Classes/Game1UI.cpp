//
//  Game1UI.cpp
//  demo
//
//  Created by li zaoji on 7/15/14.
//
//

#include "Game1UI.h"
#include "Game1Define.h"
#include "Game1Scene.h"

USING_NS_CC;

Layer * Game1UI::createLayer(){
    Layer * game1UILayer = Game1UI::create();
    return game1UILayer;
}

bool Game1UI::init(){
    if (!Layer::init()){
        return false;
    }
    else{
        //初始化游戏标题
        Label * gameTitle = Label::createWithSystemFont("2048 Demo", "Menlo-bold", 55);
        gameTitle->setColor(GAME1_COLOR_DARKFONT);
        gameTitle->setPosition(600, 518);
        gameTitle->setAnchorPoint(Vec2(0, 0));
        this->addChild(gameTitle);
        
        //score框
        LayerColor * scoreLayer = LayerColor::create(GAME1_COLOR_LABELBGCOLOR, 135, 70);
        Label * scoreLabel = Label::createWithSystemFont("SCORE", "Menlo", 20);
        scoreLabel->setColor(GAME1_COLOR_LABELFONTCOLOR);
        scoreLabel->setPosition(scoreLayer->getContentSize().width / 2, 50);
        scoreLayer->addChild(scoreLabel);
        Label * scoreNum = Label::createWithSystemFont("0", "Menlo-bold", 25);
        scoreNum->setTag(1);
        scoreNum->setColor(GAME1_COLOR_LIGHTFONT);
        scoreNum->setPosition(scoreLayer->getContentSize().width / 2, 22);
        scoreLayer->addChild(scoreNum);
        scoreLayer->setPosition(600, 430);
        scoreLayer->setTag(1);
        this->addChild(scoreLayer);
        
        //best框
        LayerColor * bestLayer = LayerColor::create(GAME1_COLOR_LABELBGCOLOR, 135, 70);
        Label * bestLabel = Label::createWithSystemFont("BEST", "Menlo", 20);
        bestLabel->setColor(GAME1_COLOR_LABELFONTCOLOR);
        bestLabel->setPosition(bestLayer->getContentSize().width / 2, 50);
        bestLayer->addChild(bestLabel);
        Label * bestNum = Label::createWithSystemFont("0", "Menlo-bold", 25);
        bestNum->setTag(1);
        bestNum->setColor(GAME1_COLOR_LIGHTFONT);
        bestNum->setPosition(bestLayer->getContentSize().width / 2, 22);
        bestLayer->addChild(bestNum);
        bestLayer->setPosition(755, 430);
        bestLayer->setTag(2);
        this->addChild(bestLayer);
        
        //new game按钮
        MenuItemImage * newGame = MenuItemImage::create("newgame.png", "newgame.png", CC_CALLBACK_1(Game1UI::newGame, this));
        newGame->setAnchorPoint(Vec2(0,0));
        newGame->setPosition(600, 345);
        MenuItemImage * back = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(Game1UI::back, this));
        back->setAnchorPoint(Vec2(0,0));
        back->setPosition(810, 345);
        Menu * menu = Menu::create(newGame, back, NULL);
        menu->setPosition(0, 0);
        this->addChild(menu);
        
        //game over
        Sprite * gameOver = Sprite::create("gameOver.png");
        gameOver->setAnchorPoint(Vec2(0, 0));
        gameOver->setPosition(600, 240);
        gameOver->setTag(3);
        this->addChild(gameOver);
        gameOver->setVisible(false);
        return true;
    }
}

void Game1UI::newGame(Ref* obj){
    Game1Scene * gameScene = (Game1Scene * )this->getParent();
    gameScene->newGame();
    log("new game");
}

void Game1UI::back(Ref* obj){
    log("back");
    Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

