//
//  Globel.h
//  Metro
//
//  Created by li zaoji on 7/23/14.
//
//

#ifndef _GLOBEL_H_
#define _GLOBEL_H_

#define WIN_SIZE_WIDTH 960
#define WIN_SIZE_HEIGHT 640

#define PADDING 5

#define PASSENGER_WIDTH 150
#define PASSENGER_HEIGHT 200

#define STATUS_WIDTH 100
#define STATUS_HEIGHT 30

#define PASSENGER_NUM 5
#define UNIT_DIS 2
#define UNIT_VELOCITY 1
#define UNIT_VALUE 5
#define UNIT_TIME 0.1
#define LEVELUP_TIME_ADD 5
#define LEVELUP_MINVALUE_ADD 10
#define CHARACTOR_NUM 15 //nameIndex跟该参数有关

#define STATION_WIDTH (PASSENGER_WIDTH + PADDING) * PASSENGER_NUM + PADDING
#define STATION_HEIGHT (2 * PADDING + PASSENGER_HEIGHT + STATUS_HEIGHT)

#define STATION_COLOR Color4B(206, 193, 165, 255)
#define TIMER_LAYER_COLOR Color4B(34, 34, 34, 255)
#define SHOWBOARD_TIME_LAYER_COLOR Color4B(237, 229, 218, 255)
#define SHOWBOARD_LVL_LAYER_COLOR Color4B(235,226,200,255)
#define SHOWBOARD_FONT_COLOR Color4B(118, 111, 101, 255)
#define SHOWBOARD_MIN_SCORE_LAYER_COLOR Color4B(237, 127, 98, 255)
#define SHOWBOARD_CURRENT_SCORE_LAYER_COLOR Color4B(235, 180, 123, 255)


enum nameIndex{
    CONAN = 0, //4,4
    BOY = 1,  //2,3
    GRANDMA = 2, //1,5
    GREENGIANT = 3, //1,1
    HINADA = 4, //5,1
    MFC = 5, //2,5
    MOMO = 6, //4,3
    NARUTO = 7, //5,5
    OUTMAN = 8, //5,4
    SAW = 9, //1,3
    SNAKEWOMAN = 10, //2,2
    YIN = 11, //2,3
    YINGMU = 12, //4,2
    LIN =13, //3,4
    JINZHENGEN = 14
};

//乘客序号

#endif