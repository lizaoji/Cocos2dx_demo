//
//  Passenger.cpp
//  Metro
//
//  Created by li zaoji on 7/23/14.
//
//

#include "Passenger.h"
#include "Globel.h"

USING_NS_CC;

void Passenger::moveTo(int col){
    if (this->isOnEnter) {
        //this->setPosition(col * (PASSENGER_WIDTH + PADDING) + PADDING, PADDING + 30);
        this->runAction(MoveTo::create(0.1, Vec2(col * (PASSENGER_WIDTH + PADDING) + PADDING, PADDING + 30)));
    }
    else{
        //this->setPosition(col * (PASSENGER_WIDTH + PADDING) + PADDING, PADDING);
        this->runAction(MoveTo::create(0.1, Vec2(col * (PASSENGER_WIDTH + PADDING) + PADDING, PADDING)));
    }
    this->col = col;
}

void Passenger::showAt(int col){
    this->setPosition(col * (PASSENGER_WIDTH + PADDING) + PADDING, PADDING);
    this->getChildByTag(1)->runAction(Sequence::create(ScaleTo::create(0.1, 0.8),
                                     ScaleTo::create(0.1, 1.2),
                                     ScaleTo::create(0.1, 1),
                                     NULL));
    //this->getChildByTag(2)->
}

Passenger * Passenger::create(int index, int col){
    Passenger * pRet = new Passenger();
    pRet->index = index;
    pRet->col = col;
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Passenger::init(){
    if (!Node::init()) {
        return false;
    }
    else{
        Sprite * personSprY = NULL;
        switch (this->index) {
            case CONAN:
                personSprY = Sprite::create("conan_4_4.png");
                this->velocity = 4 * UNIT_VELOCITY;
                this->value = 4 * UNIT_VALUE;
                break;
            case BOY:
                personSprY = Sprite::create("boy_2_3.png");
                this->velocity = 2 * UNIT_VELOCITY;
                this->value = 3 * UNIT_VALUE;
                break;
            case GRANDMA:
                personSprY = Sprite::create("grandma_1_5.png");
                this->velocity = 1 * UNIT_VELOCITY;
                this->value = 5 * UNIT_VALUE;
                break;
            case GREENGIANT:
                personSprY = Sprite::create("greengiant_1_1.png");
                this->velocity = 1 * UNIT_VELOCITY;
                this->value = 1 * UNIT_VALUE;
                break;
            case HINADA:
                personSprY = Sprite::create("hinada_5_1.png");
                this->velocity = 5 * UNIT_VELOCITY;
                this->value = 1 * UNIT_VALUE;
            case LIN:
                personSprY = Sprite::create("lin_3_4.png");
                this->velocity = 3 * UNIT_VELOCITY;
                this->value = 4 * UNIT_VALUE;
                break;
            case MFC:
                personSprY = Sprite::create("mfc_2_5.png");
                this->velocity = 2 * UNIT_VELOCITY;
                this->value = 5 * UNIT_VALUE;
                break;
            case MOMO:
                personSprY = Sprite::create("momo_4_3.png");
                this->velocity = 4 * UNIT_VELOCITY;
                this->value = 3 * UNIT_VALUE;
                break;
            case NARUTO:
                personSprY = Sprite::create("naruto_5_5.png");
                this->velocity = 5 * UNIT_VELOCITY;
                this->value = 5 * UNIT_VALUE;
                break;
            case OUTMAN:
                personSprY = Sprite::create("outman_5_4.png");
                this->velocity = 5 * UNIT_VELOCITY;
                this->value = 4 * UNIT_VALUE;
                break;
            case SAW:
                personSprY = Sprite::create("saw_1_3.png");
                this->velocity = 1 * UNIT_VELOCITY;
                this->value = 3 * UNIT_VALUE;
                break;
            case SNAKEWOMAN:
                personSprY = Sprite::create("snakewoman_2_2.png");
                this->velocity = 2 * UNIT_VELOCITY;
                this->value = 2 * UNIT_VALUE;
                break;
            case YIN:
                personSprY = Sprite::create("yin_2_3.png");
                this->velocity = 2 * UNIT_VELOCITY;
                this->value = 3 * UNIT_VALUE;
                break;
            case YINGMU:
                personSprY = Sprite::create("yingmu_4_2.png");
                this->velocity = 4 * UNIT_VELOCITY;
                this->value = 2 * UNIT_VALUE;
                break;
            case JINZHENGEN:
                personSprY = Sprite::create("jinzhengen_2_5.png");
                this->velocity = 2 * UNIT_VELOCITY;
                this->value = 5 * UNIT_VALUE;
                break;
            default:
                log("no nameIndex");
                exit(-1);
                break;
        }
        //所需上车时间= 距离 / 速度 / 时间单位
        this->needTotalTime = (col + 1) * UNIT_DIS / this->velocity / UNIT_TIME;
        this->costTime = 0.0;
        personSprY->setPosition(personSprY->getContentSize().width / 2, personSprY->getContentSize().height / 2);
        personSprY->setTag(1);
        this->addChild(personSprY);
        
        Sprite * status = Sprite::create("wait.png");
        status->setPosition(personSprY->getPositionX(), personSprY->getContentSize().height + status->getContentSize().height / 2);
        status->setTag(2);
        this->addChild(status);
        showAt(this->col);
        return true;
    }
}