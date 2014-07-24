#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Passenger.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    //游戏相关的函数
    //当点击以为乘客让其上车时，调用该函数
    void letPassengerEnter(int index);
    //时间倒计时函数，游戏相当一部分逻辑
    void countDown(float dt);
    //更新一批乘客
    void updatePassenger(bool allUpdate);
    //准备关卡
    void updateUI();
    
    //游戏相关的方法
    cocos2d::Vector<Passenger *> allPassenger;
    cocos2d::Vector<Passenger *> enterPassenger;
    int time = 30;
    int level = 1;
    int minScore = 0;
    int curScore = 0;
    
    
};

#endif // __HELLOWORLD_SCENE_H__
