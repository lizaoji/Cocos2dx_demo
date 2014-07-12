#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void onEnter();
    
    virtual void update(float t);
public:
    int _projectilesDestroyed;
    
    void addTarget();
    
    void finishShoot();
    void spriteMoveFinished(cocos2d::Object* pSender);
    
    void gameLogic(float dt);
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    cocos2d::Vector<cocos2d::Sprite*> _targets;
    cocos2d::Vector<cocos2d::Sprite*> _projectiles;
    
    cocos2d::Sprite* _player;
    cocos2d::Sprite *_nextProjectile;
};

#endif // __HELLOWORLD_SCENE_H__


