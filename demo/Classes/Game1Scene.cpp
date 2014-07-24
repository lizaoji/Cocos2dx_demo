//
//  Game1Scene.cpp
//  demo
//
//  Created by li zaoji on 7/12/14.
//
//

#include "Game1Scene.h"
#include "Game1UI.h"

Scene * Game1Scene::createScene(){
    Scene * gameScene = Scene::create();
    Layer * gameLayer = Game1Scene::create();
    gameScene->addChild(gameLayer);
    return gameScene;
}

bool Game1Scene::init(){
    if (!LayerColor::initWithColor(GAME1_COLOR_APPCOLOR)) {
        return false;
    }
    else{
        //初始化游戏UI
        auto gameUI = Game1UI::createLayer();
        gameUI->setTag(999);
        this->addChild(gameUI);
        
        //初始化游戏背景
        Size gameBoardSize = Size(GAME1_BLOCK_WIDTH * GAME1_COLS + GAME1_PADDING * (GAME1_COLS + 1),
                                      GAME1_BLOCK_HEIGHT * GAME1_ROWS + GAME1_PADDING * (GAME1_ROWS + 1));
        gameBoard = LayerColor::create(GAME1_COLOR_BOARDCOLOR, gameBoardSize.width, gameBoardSize.height);
        Point gameBoardPoint = Point(70,(GAME1_WIN_SIZE_HEIGHT - gameBoardSize.height) / 2);
        gameBoard->setPosition(gameBoardPoint);
        this->addChild(gameBoard);
        //初始化Block
        for (int r = 0; r < GAME1_ROWS; r++) {
            for (int c = 0; c < GAME1_COLS; c++) {
                LayerColor * block = LayerColor::create(GAME1_COLOR_BLOCKCOLOR, GAME1_BLOCK_WIDTH, GAME1_BLOCK_HEIGHT);
                block->setPosition(c * (GAME1_BLOCK_WIDTH + GAME1_PADDING) + GAME1_PADDING, r * (GAME1_BLOCK_HEIGHT + GAME1_PADDING) + GAME1_PADDING);
                gameBoard->addChild(block);
            }
        }
        //初始化map
        for (int r = 0; r < GAME1_ROWS; r++) {
            for (int c = 0; c < GAME1_COLS; c++) {
                map[r][c] = -1;
            }
        }
        //初始化第一块Tile
        createOneTile();
        
        //操作监控
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [&](Touch * touch, Event * event){
            //触摸开始时，记录下位置，作为后续触摸距离超过10像素的比较初始点
            this->touchStartPoint = touch->getLocationInView();
            log("touch began");
            //设置标志位，表示新一轮开始，并且还没进行处理
            this->touchIsEffective = false;
            return true;
        };
        listener->onTouchMoved = [&](Touch * touch, Event * event){
            //如果还没进行处理，才进行后续逻辑判断
            if (!this->touchIsEffective) {
                //判断移动位置是否超过10像素，如果超过则证明当次移动已经有效，否则该移动无效
                Vec2 touchCurrentPoint = touch->getLocationInView();
                if (abs(touchCurrentPoint.x - this->touchStartPoint.x) >= GAME1_TOUCH_EFFECTIVE_DIS || abs(touchCurrentPoint.y - this->touchStartPoint.y) >= GAME1_TOUCH_EFFECTIVE_DIS) {
                    this->touchIsEffective = true;
                    log("touch is effect");
                }
                //如果移动有效
                if (this->touchIsEffective) {
                    //判断移动的方向
                    if(touchCurrentPoint.x - this->touchStartPoint.x >= GAME1_TOUCH_EFFECTIVE_DIS){
                        this->currentDirection = RIGHT;
                        //log("RIGHT");
                    }
                    else if(this->touchStartPoint.x - touchCurrentPoint.x >= GAME1_TOUCH_EFFECTIVE_DIS){
                        this->currentDirection = LEFT;
                        //log("LEFT");
                    }
                    else if(touchCurrentPoint.y - this->touchStartPoint.y >= GAME1_TOUCH_EFFECTIVE_DIS){
                        this->currentDirection = DOWN;
                        //log("DOWN");
                    }
                    else if(this->touchStartPoint.y - touchCurrentPoint.y >= GAME1_TOUCH_EFFECTIVE_DIS){
                        this->currentDirection = UP;
                        //log("UP");
                    }
                    else{
                        this->currentDirection = NODIR;
                        //log("NODIR");
                        //exit(1);
                    }
                    //进行一轮游戏逻辑的操作，该轮后续的滑动不再处理
                    this->oneRound();
                }
            }
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        return true;
    }
}

void Game1Scene::oneRound(){
    //核心游戏逻辑
    //1. 移动且消除Tile
    moveAllTile();
    //2. 随机生成新Tile
    createOneTile();
    //3. 播放声音
    
    //4. 界面UI变化，分数等
    //在mergeTile方法里面实现
    
    //5. 死亡逻辑判断
    if(!isGameOver && totalTiles == GAME1_ROWS * GAME1_COLS){
        gameOverCheck();
        if (isGameOver) {
            this->getChildByTag(999)->getChildByTag(3)->setVisible(true);
        }
    }
}

void Game1Scene::createOneTile(){
    //已经满了，则不再产生新Tile，直接跳出
    if (totalTiles == GAME1_ROWS * GAME1_COLS) {
        return ;
    }
    srand(time(NULL));
    int newIndex = rand() % (GAME1_ROWS * GAME1_COLS - totalTiles);
    int count = 0;
    bool findRandBlock = false;
    for (int r = 0; r < GAME1_ROWS; r++) {
        for (int c = 0; c < GAME1_COLS; c++) {
            if (map[r][c] == -1) {
                if (count == newIndex) {
                    findRandBlock = true;
                    MovedTile * movedTile = MovedTile::create();
                    movedTile->showAt(r, c);
                    gameBoard->addChild(movedTile);
                    allTile[r][c] = movedTile;
                    map[r][c] = movedTile->mNumber;
                    totalTiles++;
                    break;
                }
                count++;
            }
        }
        if (findRandBlock) {
            break;
        }
    }
}

void Game1Scene::moveAllTile(){
    switch (currentDirection) {
        case UP:
            for (int r = GAME1_ROWS - 2; r >= 0; r--) {
                for (int c = 0; c < GAME1_COLS; c++) {
                    //如果当前位置本身是有Tile的
                    if (map[r][c] != -1) {
                        //标志位：只合并一次
                        bool hasMergedOnce = false;
                        for (int r_up = r + 1; r_up < GAME1_ROWS; r_up++) {
                            //如果上一行是空的，则直接移动
                            if (map[r_up][c] == -1) {
                                map[r_up][c] = map[r_up - 1][c];
                                allTile[r_up][c] = allTile[r_up - 1][c];
                                map[r_up - 1][c] = -1;
                                allTile[r_up - 1][c] = nullptr;
                                allTile[r_up][c]->moveTo(r_up, c);
                            }
                            //如果上一行有Tile，但数字不同，则移动不了，检查下一列
                            else if (map[r_up][c] != map[r_up - 1][c]){
                                break;
                            }
                            //否则说明上一行有相同数字的Tile，合并。如果合并过一次，则不再合并
                            else if(!hasMergedOnce){
                                mergeTile(r_up - 1, c, r_up, c);
                                hasMergedOnce = true;
                            }
                        }
                    }
                    //如果当前位置本身就是空的，则不需要移动，检查下一列
                    else{
                        continue;
                    }
                }
            }
            break;
        case DOWN:
            for (int r = 1; r < GAME1_ROWS; r++) {
                for (int c = 0; c < GAME1_COLS; c++) {
                    //如果当前位置本身是有Tile的
                    if (map[r][c] != -1) {
                        bool hasMergedOnce = false;
                        for (int r_down = r - 1; r_down >=0; r_down--) {
                            //如果下一行是空的，则直接移动
                            if (map[r_down][c] == -1) {
                                map[r_down][c] = map[r_down + 1][c];
                                allTile[r_down][c] = allTile[r_down + 1][c];
                                map[r_down + 1][c] = -1;
                                allTile[r_down + 1][c] = nullptr;
                                allTile[r_down][c]->moveTo(r_down, c);
                            }
                            //如果上一行有Tile，但数字不同，则移动不了，检查下一列
                            else if (map[r_down][c] != map[r_down + 1][c]){
                                break;
                            }
                            //否则说明上一行有相同数字的Tile，合并
                            else if(!hasMergedOnce){
                                mergeTile(r_down + 1, c, r_down, c);
                                hasMergedOnce = true;
                            }
                        }
                    }
                    //如果当前位置本身就是空的，则不需要移动，检查下一列
                    else{
                        continue;
                    }
                }
            }
            break;
        case LEFT:
            for (int c = 1; c < GAME1_COLS; c++) {
                for (int r = 0; r < GAME1_ROWS; r++) {
                    //如果当前位置本身是有Tile的
                    if (map[r][c] != -1) {
                        bool hasMergedOnce = false;
                        for (int c_left = c - 1; c_left >=0; c_left--) {
                            //如果左一列是空的，则直接移动
                            if (map[r][c_left] == -1) {
                                map[r][c_left] = map[r][c_left + 1];
                                allTile[r][c_left] = allTile[r][c_left + 1];
                                map[r][c_left + 1] = -1;
                                allTile[r][c_left + 1] = nullptr;
                                allTile[r][c_left]->moveTo(r, c_left);
                            }
                            //如果左一列有Tile，但数字不同，则移动不了，检查下一行
                            else if (map[r][c_left] != map[r][c_left + 1]){
                                break;
                            }
                            //否则说明上一行有相同数字的Tile，合并
                            else if(!hasMergedOnce){
                                mergeTile(r, c_left + 1, r, c_left);
                                hasMergedOnce = true;
                            }
                        }
                    }
                    //如果当前位置本身就是空的，则不需要移动，检查下一列
                    else{
                        continue;
                    }
                }
            }
            break;
        case RIGHT:
            for (int c = GAME1_COLS - 2; c >= 0; c--) {
                for (int r = 0; r < GAME1_ROWS; r++) {
                    //如果当前位置本身是有Tile的
                    if (map[r][c] != -1) {
                        bool hasMergedOnce = false;
                        for (int c_right = c + 1; c_right < GAME1_COLS; c_right++) {
                            //如果左一列是空的，则直接移动
                            if (map[r][c_right] == -1) {
                                map[r][c_right] = map[r][c_right - 1];
                                allTile[r][c_right] = allTile[r][c_right - 1];
                                map[r][c_right - 1] = -1;
                                allTile[r][c_right - 1] = nullptr;
                                allTile[r][c_right]->moveTo(r, c_right);
                            }
                            //如果左一列有Tile，但数字不同，则移动不了，检查下一行
                            else if (map[r][c_right] != map[r][c_right - 1]){
                                break;
                            }
                            //否则说明上一行有相同数字的Tile，合并
                            else if(!hasMergedOnce){
                                mergeTile(r, c_right - 1, r, c_right);
                                hasMergedOnce = true;
                            }
                        }
                    }
                    //如果当前位置本身就是空的，则不需要移动，检查下一列
                    else{
                        continue;
                    }
                }
            }
            break;
        default:
            break;
    }
}

void Game1Scene::mergeTile(unsigned int src_r, unsigned int src_c, unsigned int dst_r, unsigned int dst_c){
    gameBoard->removeChild(allTile[src_r][src_c]);
    allTile[src_r][src_c] = nullptr;
    map[src_r][src_c] = -1;
    allTile[dst_r][dst_c]->mNumber = map[dst_r][dst_c] *= 2;
    allTile[dst_r][dst_c]->update();
    totalTiles--;
    
    auto scoreLabel =(Label *) this->getChildByTag(999)->getChildByTag(1)->getChildByTag(1);
    auto bestLabel = (Label *) this->getChildByTag(999)->getChildByTag(2)->getChildByTag(1);
    score += map[dst_r][dst_c];
    scoreLabel->setString(StringUtils::toString(score));
    if (best < score) {
        best = score;
        bestLabel->setString(StringUtils::toString(best));
    }
}

void Game1Scene::updateTileNum(){
    int count = 0;
    for (int r = 0; r < GAME1_ROWS; r++) {
        for (int c = 0; c < GAME1_COLS; c++) {
            if (map[r][c] != -1) {
                count++;
            }
        }
    }
    totalTiles = count;
}

void Game1Scene::newGame(){
    for (int r = 0; r < GAME1_ROWS; r++) {
        for (int c = 0; c < GAME1_COLS; c++) {
            map[r][c] = -1;
            gameBoard->removeChild(allTile[r][c]);
            allTile[r][c] = nullptr;
            totalTiles = 0;
        }
    }
    score = 0;
    auto scoreLabel =(Label *) this->getChildByTag(999)->getChildByTag(1)->getChildByTag(1);
    scoreLabel->setString(StringUtils::toString(score));
    createOneTile();
    isGameOver = false;
    this->getChildByTag(999)->getChildByTag(3)->setVisible(false);
}

void Game1Scene::gameOverCheck(){
    bool stillAlive = false;
    for (int r = 0; r < GAME1_ROWS; r++) {
        for (int c = 0; c < GAME1_COLS; c++) {
            if (r <  GAME1_ROWS - 1 && map[r][c] == map[r+1][c]) {
                stillAlive = true;
                return;
            }
            else if(c < GAME1_COLS - 1 && map[r][c] == map[r][c+1]){
                stillAlive = true;
                return;
            }
        }
    }
    isGameOver = true;
}