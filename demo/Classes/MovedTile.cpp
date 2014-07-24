//
//  MovedTiled.cpp
//  demo
//
//  Created by li zaoji on 7/12/14.
//
//

#include "MovedTile.h"

void MovedTile::showAt(int r, int c){
    this->setPosition( (GAME1_BLOCK_WIDTH + GAME1_PADDING ) * c + GAME1_PADDING , (GAME1_BLOCK_HEIGHT + GAME1_PADDING ) * r + GAME1_PADDING);
    this->mRow = r;
    this->mCol = c;
    movedTileColorLayer->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1), NULL));
    movedTileNumLabel->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1), NULL));
}

void MovedTile::moveTo(int r, int c){
    Vec2 newPosition = Vec2((c - this->mCol) * (GAME1_BLOCK_WIDTH + GAME1_PADDING), (r - this->mRow) * (GAME1_BLOCK_HEIGHT + GAME1_PADDING));
    this->mRow = r;
    this->mCol = c;
    this->runAction(MoveBy::create(0.1, newPosition));
}

void MovedTile::update(){
    //Tile update
    switch (mNumber) {
        case 2:
            movedTileColor = GAME1_COLOR_2_TILE;
            break;
        case 4:
            movedTileColor = GAME1_COLOR_4_TILE;
            break;
        case 8:
            movedTileColor = GAME1_COLOR_8_TILE;
            break;
        case 16:
            movedTileColor = GAME1_COLOR_16_TILE;
            break;
        case 32:
            movedTileColor = GAME1_COLOR_32_TILE;
            break;
        case 64:
            movedTileColor = GAME1_COLOR_64_TILE;
            break;
        case 128:
            movedTileColor = GAME1_COLOR_128_TILE;
            break;
        case 256:
            movedTileColor = GAME1_COLOR_256_TILE;
            break;
        case 512:
            movedTileColor = GAME1_COLOR_512_TILE;
            break;
        case 1024:
            movedTileColor = GAME1_COLOR_1024_TILE;
            break;
        case 2048:
            movedTileColor = GAME1_COLOR_2048_TILE;
            break;
        default:
            break;
    }
    movedTileColorLayer->setColor(Color3B(movedTileColor));
    
    //数字update
    if (mNumber < 8 ) {
        movedTileNumColor = GAME1_COLOR_DARKFONT;
    }
    else{
        movedTileNumColor = GAME1_COLOR_LIGHTFONT;
    }
    auto movedTileNumLabel = (Label *)this->getChildByTag(2);
    movedTileNumLabel->setString(StringUtils::toString(mNumber));
    movedTileNumLabel->setColor(movedTileNumColor);
    movedTileColorLayer->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1), NULL));
    movedTileNumLabel->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1), NULL));
}

bool MovedTile::init(){
    if (!Node::init()) {
        return false;
    }
    else{
        //先生成数字, 数字会决定颜色, 90%几率产生2, 10%几率产生4
        srand(time(NULL));
        this->mNumber = (rand() % 10) > 0 ? 2 : 4;
        switch (this->mNumber) {
            case 2:
                movedTileColor = GAME1_COLOR_2_TILE;
                movedTileNumColor = GAME1_COLOR_DARKFONT;
                break;
            case 4:
                movedTileColor = GAME1_COLOR_4_TILE;
                movedTileNumColor = GAME1_COLOR_DARKFONT;
            default:
                break;
        }
        //生成Tile的颜色图层
        movedTileColorLayer = LayerColor::create(movedTileColor, GAME1_BLOCK_WIDTH, GAME1_BLOCK_HEIGHT);
        movedTileColorLayer->setTag(1);
        movedTileColorLayer->setScale(0);
        this->addChild(movedTileColorLayer, 0);
        
        //生成Tile的数字Label
        movedTileNumLabel = Label::createWithSystemFont(StringUtils::toString(mNumber), "Menlo-bold", 50);
        movedTileNumLabel->setColor(movedTileNumColor);
        movedTileNumLabel->setPosition(GAME1_BLOCK_WIDTH / 2, GAME1_BLOCK_HEIGHT / 2);
        movedTileNumLabel->setTag(2);
        movedTileNumLabel->setScale(0);
        this->addChild(movedTileNumLabel, 1);
        return true;
    }
}
