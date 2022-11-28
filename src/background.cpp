/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: background.cpp
 * Author: ahaoozhang
 * Date: 2019-08-09 20:59:11 (星期五)
 * Describe: 
 *************************************************/
#include "background.h"

AHAOAHA::BackGround::BackGround() {
    int32_t width, height = 0;
    assert(get_terminal_size(width, height));
    _row = width;
    _col = height;
}
AHAOAHA::BackGround::BackGround(unsigned int row, unsigned int col): _row(row), _col(col) {}
AHAOAHA::BackGround::~BackGround() {}

bool AHAOAHA::BackGround::init() {
    for(int row = 0; row < _row; ++row) {
        std::vector<int> tmp_v;
        for(int col = 0; col < _col; ++col) {
            tmp_v.push_back(0);
        }

        _bgv.push_back(tmp_v);
    }

    return true;
}


bool AHAOAHA::BackGround::init_sidebar() {
    for(unsigned int row = 0; row < _row; ++row) {
        _bgv[row][0] = SIDEBAR;
        _bgv[row][_col - 1] = SIDEBAR;
    }

    for(unsigned int col = 0; col < _col; ++col) {
        _bgv[0][col] = SIDEBAR;
        _bgv[_row - 1][col] = SIDEBAR;
    }
    return true;
}

void AHAOAHA::BackGround::create_food() {
    Pos f_pos;
    srand(time(NULL));
    do {
        f_pos._row = rand() % _row;
        f_pos._col = rand() % _col;
    } while(!pos_ok(f_pos) || !pos_empty(f_pos));

    _bgv[f_pos._row][f_pos._col] = FOOD;
}

bool AHAOAHA::BackGround::pos_empty(const Pos& pos) {
    return _bgv[pos._row][pos._col] == EMPTYSPACE;
}

bool AHAOAHA::BackGround::echo() {
    unsigned int row = 0, col = 0;
    //printf("\033[?25h");    //显示光标
    printf("\033[0;0H");    //设置初始打印屏幕光标位置
    //fflush(stdout);

    //printf("_bgv.size(): %d\n", _bgv.size());
    //printf("_bgv[0].size(): %d\n", _bgv[0].size());

    for(row = 0; row < _row; ++row) {
        for(col = 0; col < _col; ++col) {
            switch(_bgv[row][col]) {
                case EMPTYSPACE:
                    printf(" ");
                    break;
                case SIDEBAR:
                    printf("\033[43;43m \033[0m");
                    break;
                case FOOD:
                    printf("\033[41;41m \033[0m");
                    break;
                default:
                    //printf("%d", _bgv[row][col]);
                    printf("\033[47;47m \033[0m");
                    break;
            }
            //printf("%d", _bgv[row][col]); //debug
        }
        printf("\n");
    }

    //fflush(stdout);
    return true;
}

bool AHAOAHA::BackGround::pos_ok(const struct Pos& pos) {
    if (((pos._row < _row) && (pos._row > 0)) && ((pos._col < _col) && (pos._col > 0))) {
        return true;
    }
    return false;
}


bool AHAOAHA::BackGround::set_snbody(const struct Pos& pos) {
    if (!pos_ok(pos)) {
        return false;
    }

    _bgv[pos._row][pos._col] = SNAKEBODY;
    return true;
}

bool AHAOAHA::BackGround::set_pos(const Pos& pos, int val) {
    if (!pos_ok(pos)) {
        return false;
    }

    _bgv[pos._row][pos._col] = val;
    return true;
}

bool AHAOAHA::BackGround::move_snbody(const Pos& insert, const Pos& del) {
    if (!pos_ok(insert)) {
        return false;
    }

    _bgv[insert._row][insert._col] = SNAKEBODY;
    _bgv[del._row][del._col] = EMPTYSPACE;
    return true;
}

bool AHAOAHA::BackGround::is_food(const Pos& pos) {
    return _bgv[pos._row][pos._col] == FOOD;
}

bool AHAOAHA::BackGround::is_sidebar(const Pos& pos) {
    return _bgv[pos._row][pos._col] == SIDEBAR;
}

void AHAOAHA::BackGround::grow_snbody(const Pos& pos) {
    set_snbody(pos);
    create_food();
}
