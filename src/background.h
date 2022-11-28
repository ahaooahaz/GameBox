/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: background.h
 * Author: ahaoozhang
 * Date: 2019-08-09 20:59:00 (星期五)
 * Describe: 
 *************************************************/

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include <vector>
#include <iostream>
#include "common.h"
#include <assert.h>

namespace AHAOAHA { //

    class BackGround {
        private:
        public:
            BackGround();
            BackGround(unsigned int row, unsigned int col);
            ~BackGround();

            bool init();
            bool init_sidebar();
            void create_food();
            bool echo();
            bool set_snbody(const struct Pos& pos);
            unsigned int get_row() const { return _row; }
            unsigned int get_col() const { return _col; }

            bool pos_ok(const struct Pos& pos);
            bool is_food(const Pos& pos);
            bool pos_empty(const Pos& pos);
            bool is_sidebar(const Pos& pos);
            bool move_snbody(const Pos& insert, const Pos& del);
            void grow_snbody(const Pos& pos);
            bool set_pos(const Pos& pos, int val);
        private:
            unsigned int _row;
            unsigned int _col;
            std::vector<std::vector<int>> _bgv;
    };
}

#endif // background.h
