#include <stdio.h>

#include "../src/watch_keyboard.h"


int main() {
    static char command = 'r';
    int count = 0;
    while (true) {
        if(AHAOAHA::Watcher::GetWatcherInst()->wait_command(&command, 100)) {
            if (command == 'q') {
                break;
            }
            printf("get command not exit!\n");
        } else {
            printf("press 'q' quit!\n");
        }
    }
    return 0;
}