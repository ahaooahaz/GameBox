#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <vector>
#include <stdint.h>

int game_2048();

class Game_2048
{
public:
    Game_2048() {}
    ~Game_2048() {}

    bool Init(uint32_t row, uint32_t col);
    void Echo();  //打印函数
    int Game();   //游戏主体函数
    int IsDown(); //判断游戏是否失败
    int IsFull();
    void Seed();    //播撒种子
    void MoveMap(); //移动游戏元素
    void MovePointW();
    void MovePointS();
    void MovePointA();
    void MovePointD();
    void CountFuncW();
    void CountFuncA();
    void CountFuncS();
    void CountFuncD();
    void IsSeedW();
    void IsSeedS();
    void IsSeedA();
    void IsSeedD();
    void Proc();

private:
    int Flag_Seed;
    uint32_t _col;
    uint32_t _row;
    std::vector<std::vector<int>> _map;
};
