//
//  MenuScene.h
//  demo
//
//  Created by li zaoji on 7/10/14.
//
//

#include "cocos2d.h"
#include "cocos-ext.h"
#include "socket.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

//登陆场景
class MenuScene: public Scene{
public:
    bool init();
    static Scene * createScene();
    CREATE_FUNC(MenuScene);
    void loginButtonTouchBegin(Ref * obj, Control::EventType type);
private:
    enum MenuSceneTag{
        menuUILayerTag = 4,
        usernameBoxTag = 1,
        pwdBoxTag = 2,
        loginButtonTag = 3,
        socketTag = 5
    };
};

//登陆box的分发器
class LoginBoxDeligate: public EditBoxDelegate {
public:
    void editBoxEditingDidBegin(EditBox* editBox) {
        //editBox->setPosition(Vec2(320,0));
    }
    void editBoxEditingDidEnd(EditBox* editBox) {}
    void editBoxTextChanged(EditBox* editBox, const std::string& text) {}
    void editBoxReturn(EditBox* editBox){
        //editBox->setPosition(
    }
};
