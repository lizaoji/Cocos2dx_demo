#include "demo.h"

Scene* Demo::createScene()
{
    auto scene = Scene::create();
    auto layer = Demo::create();
    scene->addChild(layer);
    return scene;
}


bool Demo::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Demo::initWithColor(Color4B::Color4B(0,0,0,255), visibleSize.width, visibleSize.height);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Scale9Sprite * scale9SprY = Scale9Sprite::create("input.png");
    EditBox * box = EditBox::create(SizeFromString("{300.0, 30.0}"), scale9SprY);
    box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    box->setDelegate(this);
    box->setFontColor(ccc3(255, 0, 0));
    this->addChild(box);
    return true;
}

void Demo::editBoxEditingDidBegin(EditBox *editBox)
{
    editBox->setText("");
}
void Demo::editBoxEditingDidEnd(EditBox *editBox)
{
}
void Demo::editBoxReturn(EditBox *editBox)
{
    log(editBox->getText());
}
void Demo::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
}

void Demo::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
