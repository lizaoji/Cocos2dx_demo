#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "socket.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Demo : public cocos2d::LayerColor,public EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Demo);
    
    void editBoxEditingDidBegin(EditBox * editBox);
    void editBoxEditingDidEnd(EditBox * editBox);
    void editBoxTextChanged(EditBox * editBox, const std::string& text);
    void editBoxReturn(EditBox * editBox);
};

#endif // __DEMO_SCENE_H__
