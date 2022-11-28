#include "common.h"

bool get_terminal_size(int32_t& width, int32_t& height) {
    //screen init
    struct winsize w;
    try{
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    }catch(...){
        return false;
    }
    width = w.ws_row - 2;
    height = w.ws_col - 0;
    return true;
}