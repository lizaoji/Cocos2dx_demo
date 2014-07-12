//
//  MenuScene.cpp
//  demo
//
//  Created by li zaoji on 7/10/14.
//
//

#include "MenuScene.h"

Scene * MenuScene::createScene(){
    Scene * menuS = MenuScene::create();
    return menuS;
}

bool MenuScene::init(){
    
    //准备后续代码所需变量
    Size winSize = Director::getInstance()->getVisibleSize();
    Point winOrigin = Director::getInstance()->getVisibleOrigin();
    
    //构建菜单背景层，因为元素只有一个，直接用Sprite处理
    auto menuBgSprY = Sprite::create("bg.png");
    menuBgSprY->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(menuBgSprY);
    
    ///////////////////////
    //构建菜单UI层
    //
    auto menuUILayer = Layer::create();
    menuUILayer->setTag(this->menuUILayerTag);
    
    //游戏标题,以后可用LabelAtlas来做有材质的标题
    LabelTTF * gameTitleLabel = LabelTTF::create("Monster Hunter 6", "Menlo-bold", 45);
    gameTitleLabel->setPosition(winSize.width / 2 + winOrigin.x, winSize.height * 3 / 4 + winOrigin.y);
    menuUILayer->addChild(gameTitleLabel);
    
    //登陆相关:输入账号、密码、登陆按钮
    //账号Box
    EditBox * usernameBox = EditBox::create(SizeFromString("{300.0, 50.0}"), Scale9Sprite::create("inputBox.png"));
    usernameBox->setPlaceHolder("输入用户名");
    usernameBox->setFontColor(Color3B::BLACK);
    auto usernameSize = usernameBox->getContentSize();
    usernameBox->setPosition(Vec2(winSize.width / 2 + winOrigin.x, winSize.height * 3 / 4 - 100 + winOrigin.y ));
    usernameBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    usernameBox->setTag(this->usernameBoxTag);
    
    //密码Box
    EditBox * pwdBox = EditBox::create(SizeFromString("{300.0, 50.0}"), Scale9Sprite::create("inputBox.png"));
    pwdBox->setPlaceHolder("输入密码");
    pwdBox->setFontColor(Color3B::BLACK);
    pwdBox->setInputFlag(EditBox::InputFlag::PASSWORD);
    pwdBox->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4 - 200));
    pwdBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    pwdBox->setTag(this->pwdBoxTag);

    //登陆Button
    ControlButton * loginButton = ControlButton::create(LabelTTF::create("登陆", "Menlo-bold", 30),Scale9Sprite::create("loginButton.png"));
    loginButton->setPosition(winSize.width / 2, winSize.height * 3 / 4 - 300);
    loginButton->setPreferredSize(SizeFromString("{200, 40}"));
    //添加点击事件
    loginButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::loginButtonTouchBegin), Control::EventType::TOUCH_DOWN);
    loginButton->setTag(this->loginButtonTag);
    
    //登陆Box的delegate
    LoginBoxDeligate * boxDelegate = new LoginBoxDeligate();
    usernameBox->setDelegate(boxDelegate);
    pwdBox->setDelegate(boxDelegate);
    
    //添加Node
    menuUILayer->addChild(usernameBox);
    menuUILayer->addChild(pwdBox);
    menuUILayer->addChild(loginButton);
    
    //添加总UI图层
    this->addChild(menuUILayer,4);
    ///////////////////////
    
    //创建socket
    BSDSocket * menuSocket = new BSDSocket("192.168.0.120", 6666);
    menuSocket->setTag(this->socketTag);
    this->addChild(menuSocket);
    
    //结束
    return true;
}

void MenuScene::loginButtonTouchBegin(Ref * obj, Control::EventType type){
    BSDSocket * socket = (BSDSocket *)this->getChildByTag(this->socketTag);
    if(socket->connectSocket() != 0){
        return ;
    }
    else{
        auto usernameBox = (EditBox * )this->getChildByTag(this->menuUILayerTag)->getChildByTag(this->usernameBoxTag);
        auto pwdBox = (EditBox * )this->getChildByTag(this->menuUILayerTag)->getChildByTag(this->pwdBoxTag);
        string sendMsg = "username: " + string(usernameBox->getText()) + ", pwd: " + string(pwdBox->getText()) + '\0';
        const char * str = sendMsg.c_str();
        socket->sendDataToServer(str, sendMsg.length(), 0);
    }
}

