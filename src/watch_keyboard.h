#ifndef __WATCH_KEYBOARD_H__
#define __WATCH_KEYBOARD_H__

#include <wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <assert.h>

#include "common.h"


namespace AHAOAHA {

class Watcher {
    public:
        static Watcher* GetWatcherInst() {
            return &_Inst;
        }

        bool wait_command(char *ch, int waittime);

    private:
        Watcher();
        ~Watcher();

        static void disable_terminal_return();
        static void restore_terminal_settings();

        static Watcher _Inst;

        int _epfd;
        epoll_event wev, rev[1];
        static struct termios _old_terminal;
};


}

#endif