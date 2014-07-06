#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
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

void HelloWorld::onEnter()
{
	LayerColor::onEnter();
    
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

    listener->onTouchBegan = [=](cocos2d::Touch* touch,cocos2d::Event* event)
    {
        return true;
    };
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::update(float t)
{
	Vector<Sprite*> targetsToDelete;
	Vector<Sprite*> projectilesToDelete;
    
	for (int i = 0; i < _projectiles.size(); i++)
	{
		auto projectile = _projectiles.at(i);
		auto projectileRect = Rect(
                                   projectile->getPositionX() - projectile->getContentSize().width / 2,
                                   projectile->getPositionY() - projectile->getContentSize().height / 2,
                                   projectile->getContentSize().width,
                                   projectile->getContentSize().height );
        
		for (int j = 0; j < _targets.size(); j++)
		{
			auto target = _targets.at(j);
			auto targetRect = Rect(
                                   target->getPositionX() - target->getContentSize().width / 2,
                                   target->getPositionY() - target->getContentSize().height / 2,
                                   target->getContentSize().width,
                                   target->getContentSize().height);
            
			if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete.pushBack(target);
			}
		}
        
		//C++11 的 range-based for循环
		for (Sprite* target : targetsToDelete)
		{
			_targets.eraseObject(target);
			this->removeChild(target);
            
            _projectilesDestroyed++;
            if (_projectilesDestroyed >3) {
                auto gameOverScene = GameOverScene::create();
                gameOverScene->getLayer()->getLabel()->setString("You Win!");
                Director::getInstance()->replaceScene(gameOverScene);
            }
		}
        
		if (targetsToDelete.size() >0)
		{
			projectilesToDelete.pushBack(projectile);
		}
		targetsToDelete.clear();
	}
	
	for (const auto& p : projectilesToDelete)
	{
		_projectiles.eraseObject(p);
		this->removeChild(p);
		//p->removeFromParentAndCleanup(true);
	}
	projectilesToDelete.clear();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //创建精灵
    _player = Sprite::create("Player2.png");
	_player->setPosition(Point(_player->getContentSize().width/2, visibleSize.height / 2));
	this->addChild(_player);
    
    //更新函数
    this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0f);
    this->scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.caf");
    
    _nextProjectile = NULL;
    
    return true;
}

void HelloWorld::gameLogic(float dt)
{
	addTarget();
}

void HelloWorld::addTarget()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    
	auto target = Sprite::create("Target.png", Rect(0, 0, 27, 40));
    
    // Determine where to spawn the target along the Y axis
	int minY = target->getContentSize().height / 2;
	int maxY = visibleSize.height - target->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (CCRANDOM_0_1() * rangeY) + minY;
	target->setPosition(Point(visibleSize.width + target->getContentSize().width / 2, actualY));
	this->addChild(target,0);
    
    target->setTag(1);
    _targets.pushBack(target);
    
    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated above
	int minDuration = 2.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (CCRANDOM_0_1() * rangeDuration) + minDuration;
    
    
    // Determine speed of the target
	auto actionMove = MoveTo::create(actualDuration, Point(-target->getContentSize().width, actualY));
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    
	target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    if (NULL != _nextProjectile) return;
    
    // Choose touch to work with
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto touchPoint = touch->getLocation();
    
    // Set up initial location of projectile
	_nextProjectile = Sprite::create("Projectile2.png");
	_nextProjectile->setPosition(Point(20, visibleSize.height / 2));
    
	// Determine offset of location to projectile
	int offX = touchPoint.x - _nextProjectile->getPosition().x;
	int offY = touchPoint.y - _nextProjectile->getPosition().y;
    
	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;
    
    // Play a sound!
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.caf");
    
    // set tag
    _nextProjectile->setTag(2);
    
	// Determine where we wish to shoot the projectile to
	int realX = visibleSize.width + (_nextProjectile->getContentSize().width / 2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + _nextProjectile->getPosition().y;
	auto realDest = Point(realX, realY);
    
	// Determine the length of how far we're shooting
	int offRealX = realX - _nextProjectile->getPosition().x;
	int offRealY = realY - _nextProjectile->getPosition().y;
	float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
	float velocity = 960 / 1; // 960pixels/1sec
	float realMoveDuration = length / velocity;
    
    // Determine angle to face
    float angleRadians = atanf((float)offRealY / (float)offRealX);
    float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
    float cocosAngle =-1* angleDegrees;
    float rotateSpeed =0.5/ M_PI; // Would take 0.5 seconds to rotate 0.5 radians, or half a circle
    float rotateDuration = fabs(angleRadians * rotateSpeed);
    _player->runAction(Sequence::create(
                                        RotateTo::create(rotateDuration, cocosAngle),
                                        CallFuncN::create(CC_CALLBACK_0(HelloWorld::finishShoot, this)),
                                        NULL));
    
	// Move projectile to actual endpoint
	_nextProjectile->runAction(
                          Sequence::create(MoveTo::create(realMoveDuration, realDest),
                                           CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this)),
                                           NULL));
}
                       
void HelloWorld::finishShoot()
{
    // Ok to add now - we've finished rotation!
    this->addChild(_nextProjectile);
    // Add to projectiles vector
    _projectiles.pushBack(_nextProjectile);
    
    _nextProjectile = NULL;
}

void HelloWorld::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
    
    if (sprite->getTag() == 1) { // target
		_targets.eraseObject(sprite);
        
        auto gameOverScene = GameOverScene::create();
        gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
        Director::getInstance()->replaceScene(gameOverScene);
	} else if(sprite->getTag() == 2) { // projectile
		_projectiles.eraseObject(sprite);
	}
    
    this->removeChild(sprite);
    

}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
