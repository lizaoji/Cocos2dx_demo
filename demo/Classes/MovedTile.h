//
//  MovedTiled.h
//  demo
//
//  Created by li zaoji on 7/12/14.
//
//

#include "cocos2d.h"
#include "Game1Define.h"

USING_NS_CC;

class MovedTile: public Node{
private:
    Color4B movedTileColor;
    Color3B movedTileNumColor;
    LayerColor * movedTileColorLayer;
    Label * movedTileNumLabel;

public:
    int mRow;
    int mCol;
    int mNumber;
    void showAt(int r, int c);
    void moveTo(int r, int c);
    void update();
    
    CREATE_FUNC(MovedTile);
    bool init();
};