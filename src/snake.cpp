/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: game.cpp
 * Author: ahaoozhang
 * Date: 2019-08-09 21:04:46 (星期五)
 * Describe: 
 *************************************************/
#include "snake.h"

AHAOAHA::Snake::Snake() {}
AHAOAHA::Snake::Snake(unsigned int row, unsigned int col):_bg(row, col) {}
AHAOAHA::Snake::~Snake() {}

bool AHAOAHA::Snake::init() {
    _bg.init(); // background init
    _bg.init_sidebar(); //sidebar init
    _bg.create_food(); 

    //snakebody init
    init_snakebody();

    HIDE_CURSOR();

    return true;
}

bool AHAOAHA::Snake::init_snakebody() {
    //init currst
    srand(time(NULL));
    int st = 0;

    do {
        st = 1 + rand() % 3; //产生0-4的随机数
    } while(st == 0);
    _sn._currst.store(st);

    Pos pos;
    do {
        pos._row = rand() % _bg.get_row();
        pos._col = rand() % _bg.get_col();
    } while(!_bg.pos_ok(pos));
    //init head
    push_snbody(pos);

    //change status
    _st.store(RUN);
    return true;
}

bool AHAOAHA::Snake::push_snbody(const struct Pos& pos) {
    _sn._snbody.push_back(pos);
    _bg.set_snbody(pos);
    return true;
}

bool AHAOAHA::Snake::change_point(int val) {
    _sn._currst.store(val);
    return true;
}

bool AHAOAHA::Snake::exit() {
    GAME_STATUS exp = _st.load();
    _st.store(QUIT);
    SHOW_CURSOR();
    return true;
}

bool AHAOAHA::Snake::move() {
    Pos curr = _sn._snbody.front(); //get head
    Pos next = curr;
    switch(_sn._currst.load()) {
        case Up:
            next._row--;
            break;
        case Down:
            next._row++;
            break;
        case Left:
            next._col--;
            break;
        case Right:
            next._col++;
            break;
        default:
            break;
    }
    if (_bg.is_food(next)) {
        _bg.set_pos(next, SNAKEBODY);
        _sn._snbody.push_front(next);
        _bg.create_food();
    } else if (_bg.is_sidebar(next)) {  //game over
        return false;
    } else {
        _bg.set_pos(next, SNAKEBODY);
        _bg.set_pos(_sn._snbody.back(), EMPTYSPACE);
        _sn._snbody.push_front(next);
        _sn._snbody.pop_back();
    }
    return true;
}

bool AHAOAHA::Snake::GameRun() {
    init();
    while(move() && _bg.echo()) {
        static char command = 'n';
        if(AHAOAHA::Watcher::GetWatcherInst()->wait_command(&command, 100)) {
            if (command == 'q') {
                break;
            }
        } else {
            continue;
        }

        int exp_point = 0;
        switch(command) {
            case 'w':
            case 'W':
                exp_point = AHAOAHA::Snake::Up;
                break;
            case 's':
            case 'S':
                exp_point = AHAOAHA::Snake::Down;
                break;
            case 'a':
            case 'A':
                exp_point = AHAOAHA::Snake::Left;
                break;
            case 'd':
            case 'D':
                exp_point = AHAOAHA::Snake::Right;
                break;
            case 'q':
            case 'Q':
                    _st.store(QUIT);
                break;
            default:
                continue;
        }

        //cas改变状态 no lock
        change_point(exp_point);
    }

    exit();
    return true;
}

