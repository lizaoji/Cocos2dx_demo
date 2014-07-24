//
//  Passenger.h
//  Metro
//
//  Created by li zaoji on 7/23/14.
//
//

#ifndef _PASSENGER_H_
#define _PASSENGER_H_

#include "cocos2d.h"

class Passenger: public cocos2d::Node{
public:
    bool init();
    static Passenger * create(int index, int col);
    void showAt(int col);
    void moveTo(int col);
    void entering(int timeLeft);
    
    //index代表名字序号，用于确定avatar
    int index;
    //col是列号，这里用于计算位置、距离等
    int col;
    float velocity = 0.0;
    float value = 0.0;
    //从玩家开始点击，到目前经过了多少时间
    float costTime = 0.0;
    //该乘客完整上车所需时间
    float needTotalTime = 0.0;
    
    bool isOnEnter = false;
};


#endif