#include "watch_keyboard.h"

namespace AHAOAHA {

Watcher Watcher::_Inst;
struct termios Watcher::_old_terminal;

//restore terminal settings
void Watcher::restore_terminal_settings() {
    tcsetattr(0, TCSANOW, &_old_terminal); 
}

//make terminal read 1 char at a time
void Watcher::disable_terminal_return() {
    struct termios newt;
    
    //save terminal settings
    tcgetattr(0, &_old_terminal); 
    //init new settings
    newt = _old_terminal;  
    //change settings
    newt.c_lflag &= ~(ICANON | ECHO);
    //apply settings
    tcsetattr(0, TCSANOW, &newt);
    
    //make sure settings will be restored when program ends
    atexit(restore_terminal_settings);
}

Watcher::Watcher() {
    _epfd = epoll_create(1);

    assert(_epfd > 0);

    wev.data.fd = STDIN_FILENO;
    wev.events = EPOLLIN | EPOLLET;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, STDIN_FILENO, &wev);
    disable_terminal_return();
}

Watcher::~Watcher() {
    restore_terminal_settings();
}

bool Watcher::wait_command(char *command, int waittime) {
    auto ret = epoll_wait(_epfd, rev, 1, waittime);
    if (ret <= 0) {
        return false;
    }

    for (int i = 0; i < ret; i++) {
        if (rev[i].data.fd == STDIN_FILENO) {
            read(STDIN_FILENO, command, sizeof(char));
            return true;
        }
    }

    return false;
}



}