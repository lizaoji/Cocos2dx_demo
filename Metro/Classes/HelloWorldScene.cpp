#include "HelloWorldScene.h"
#include "Passenger.h"
#include "Globel.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //背景层
    LayerColor * BgLayer = LayerColor::create(Color4B::WHITE, 960, 640);
    //车门
    BgLayer->setTag(1);
    Sprite * doorSprY = Sprite::create("door.png");
    doorSprY->setPosition(doorSprY->getContentSize().width / 2 + 10, doorSprY->getContentSize().height / 2 + 150) ;
    BgLayer->addChild(doorSprY);
    //Title
    Sprite * title = Sprite::create("title.png");
    title->setAnchorPoint(Vec2(0,0));
    title->setPosition(165, 550);
    BgLayer->addChild(title);
    //支架
    Sprite * zhijia = Sprite::create("zhijia.png");
    zhijia->setAnchorPoint(Vec2(1,1));
    zhijia->setPosition(960, 640);
    BgLayer->addChild(zhijia);
    //时间显示牌
    LayerColor * showBoard_Time = LayerColor::create(SHOWBOARD_TIME_LAYER_COLOR, 150, 80);
    showBoard_Time->setPosition(960 - zhijia->getContentSize().width, 640 - zhijia->getContentSize().height - showBoard_Time->getContentSize().height);
    showBoard_Time->setTag(1);
    Label * label_Time_Static = Label::createWithSystemFont("Count Down", "Futura.ttc", 18);
    label_Time_Static->setPosition(showBoard_Time->getContentSize().width / 2, 60);
    label_Time_Static->setColor(Color3B(SHOWBOARD_FONT_COLOR));
    showBoard_Time->addChild(label_Time_Static);
    
    Label * label_Time = Label::createWithSystemFont("999", "Futura.ttc", 30);
    label_Time->setPosition(showBoard_Time->getContentSize().width / 2, 30);
    label_Time->setColor(Color3B(SHOWBOARD_FONT_COLOR));
    label_Time->setTag(1);
    showBoard_Time->addChild(label_Time);
    
    //级别显示牌
    LayerColor * showBoard_Lvl = LayerColor::create(SHOWBOARD_LVL_LAYER_COLOR, 100, 80);
    showBoard_Lvl->setPosition(155 + 960 - zhijia->getContentSize().width, 640 - zhijia->getContentSize().height - showBoard_Lvl->getContentSize().height);
    showBoard_Lvl->setTag(2);
    Label * label_Lvl_Static = Label::createWithSystemFont("Level ", "Futura.ttc", 18);
    label_Lvl_Static->setPosition(showBoard_Lvl->getContentSize().width / 2, 60);
    label_Lvl_Static->setColor(Color3B(SHOWBOARD_FONT_COLOR));
    showBoard_Lvl->addChild(label_Lvl_Static);
    
    Label * label_Lvl = Label::createWithSystemFont("99", "Futura.ttc", 30);
    label_Lvl->setPosition(showBoard_Lvl->getContentSize().width / 2, 30);
    label_Lvl->setColor(Color3B(SHOWBOARD_FONT_COLOR));
    label_Lvl->setTag(1);
    showBoard_Lvl->addChild(label_Lvl);
    
    //最少分数显示牌
    LayerColor * showBoard_MinScore = LayerColor::create(SHOWBOARD_MIN_SCORE_LAYER_COLOR, 200, 100);
    showBoard_MinScore->setPosition(165, 425);
    showBoard_MinScore->setTag(3);
    Label * label_MinScore_Static = Label::createWithSystemFont("Min Score ", "Futura.ttc", 30);
    label_MinScore_Static->setPosition(showBoard_MinScore->getContentSize().width / 2, 72);
    label_MinScore_Static->setColor(Color3B::WHITE);
    showBoard_MinScore->addChild(label_MinScore_Static);
    
    Label * label_MinScore = Label::createWithSystemFont("9999", "Futura.ttc", 40);
    label_MinScore->setPosition(showBoard_MinScore->getContentSize().width / 2, 30);
    label_MinScore->setColor(Color3B::WHITE);
    label_MinScore->setTag(1);
    showBoard_MinScore->addChild(label_MinScore);
    
    //当前分数显示牌
    LayerColor * showBoard_CurScore = LayerColor::create(SHOWBOARD_CURRENT_SCORE_LAYER_COLOR, 200, 100);
    showBoard_CurScore->setPosition(400, 425);
    showBoard_CurScore->setTag(4);
    Label * label_CurScore_Static = Label::createWithSystemFont("Cur Score ", "Futura.ttc", 30);
    label_CurScore_Static->setPosition(showBoard_CurScore->getContentSize().width / 2, 72);
    label_CurScore_Static->setColor(Color3B::WHITE);
    showBoard_CurScore->addChild(label_CurScore_Static);
    
    Label * label_CurScore = Label::createWithSystemFont("9999", "Futura.ttc", 40);
    label_CurScore->setPosition(showBoard_CurScore->getContentSize().width / 2, 30);
    label_CurScore->setColor(Color3B::WHITE);
    label_CurScore->setTag(1);
    showBoard_CurScore->addChild(label_CurScore);
    
    BgLayer->addChild(showBoard_Lvl);
    BgLayer->addChild(showBoard_Time);
    BgLayer->addChild(showBoard_MinScore);
    BgLayer->addChild(showBoard_CurScore);
    this->addChild(BgLayer);

    //站台Layer，具体添加站台内容放在newPassenger
    LayerColor * stationLayer = LayerColor::create(STATION_COLOR, STATION_WIDTH, STATION_HEIGHT);
    stationLayer->setTag(2);
    stationLayer->setPosition(165, 150);
    this->addChild(stationLayer);
    
    //点击事件监听
    auto * listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch * touch, Event * event){
        auto point = convertTouchToNodeSpace(touch);
        for (int i = 0; i < PASSENGER_NUM; i++) {
            auto passenger = allPassenger.at(i);
            if (!passenger->isOnEnter) {
                Rect rect = Rect(passenger->getPositionX() + this->getChildByTag(2)->getPositionX(),
                                 passenger->getPositionY() + this->getChildByTag(2)->getPositionY(),
                                 PASSENGER_WIDTH,
                                 PASSENGER_HEIGHT);
                if(rect.containsPoint(point)){
                    letPassengerEnter(i);
                    return true;
                }
            }
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, stationLayer);
    
    //游戏主逻辑
    //往站台添加乘客，最开始全部重新添加
    updatePassenger(true);
    //初始化时间、界面
    this->time = 30 / UNIT_TIME;
    this->minScore = this->level * 10 + 30;
    this->curScore = 0;
    updateUI();
    //倒计时，后续逻辑处理交由schedule，0.1秒countdown一次
    schedule(schedule_selector(HelloWorld::countDown), UNIT_TIME, time / UNIT_TIME, 0);
    //判断适应
    return true;
}

void HelloWorld::letPassengerEnter(int index){
    //把上车乘客加入到上车队列中，并且修改status和提高一些位置
    auto passenger = allPassenger.at(index);
    enterPassenger.pushBack(passenger);
    passenger->isOnEnter = true;
    auto status_position = passenger->getChildByTag(2)->getPosition();
    passenger->removeChildByTag(2);
    Sprite * status = Sprite::create("enter.png");
    status->setTag(2);
    status->setPosition(status_position);
    passenger->addChild(status);
    passenger->setPositionY(passenger->getPositionY() + 30);
}

void HelloWorld::updateUI(){
    //准备游戏的各种变动UI
    auto BgLayer = this->getChildByTag(1);
    auto label_time = (Label *)(BgLayer->getChildByTag(1)->getChildByTag(1));
    label_time->setString(StringUtils::toString(this->time));
    auto label_lvl = (Label *)(BgLayer->getChildByTag(2)->getChildByTag(1));
    label_lvl->setString(StringUtils::toString(this->level));
    auto label_minScore = (Label *)(BgLayer->getChildByTag(3)->getChildByTag(1));
    label_minScore->setString(StringUtils::toString(this->minScore));
    auto label_CurScore = (Label *)(BgLayer->getChildByTag(4)->getChildByTag(1));
    label_CurScore->setString(StringUtils::toString(this->curScore));
}

void HelloWorld::countDown(float dt){
    //更新时间,删除已上车乘客
    time--;
    if (enterPassenger.size() > 0){
        for (int i = 0; i < enterPassenger.size(); i++){
            auto passenger = enterPassenger.at(i);
            passenger->costTime++;
            if (passenger->costTime >= passenger->needTotalTime) {
                log("%d乘客已经上车",passenger->col);
                //加分并移除该乘客
                this->curScore += passenger->value;
                this->getChildByTag(2)->removeChild(passenger);
                allPassenger.eraseObject(passenger);
                enterPassenger.eraseObject(passenger);
            }
        }
    }
    //死亡判定
    if (time == 0) {
        if (curScore < minScore) {
            log("你输了，未达到最低分数");
        }
        else if (enterPassenger.size() >= 0){
            log("你输了，有乘客被夹到");
        }
        else{
            log("你赢了");
        }
    }
    //如果时间还未到0，移动剩下的乘客，更新新乘客进来
    else{
        updateUI();
        updatePassenger(false);
        
    }
}

void HelloWorld::updatePassenger(bool allUpdate){
    auto stationLayer = this->getChildByTag(2);
    if (allUpdate) {
        allPassenger.clear();
        stationLayer->removeAllChildren();
    }
    //如果不是全部重新添加，要移动位置变动后的乘客
    else{
        for(int i = 0; i < allPassenger.size(); i++){
            auto passenger = allPassenger.at(i);
            if (passenger->col != i) {
                passenger->moveTo(i);
            }
        }
    }
    srand(std::time(NULL));
    for (int i = 0 + allPassenger.size(); i < PASSENGER_NUM; i++) {
        auto passenger = Passenger::create(rand() % CHARACTOR_NUM, i);
        stationLayer->addChild(passenger);
        allPassenger.pushBack(passenger);
    }
}
void HelloWorld::menuCloseCallback(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
