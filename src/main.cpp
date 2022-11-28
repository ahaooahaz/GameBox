#include <string.h>

#include "2048.h"
#include "snake.h"
#include "version.h"

enum
{
    GAME_2048,
    GAME_Snake,
};

int game_2048()
{
    Game_2048 g;
    g.Init(4, 4);
    g.Game();
    return 0;
}

void usage()
{
    printf("./snake [version]\n");
}

int game_snake(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (strstr(argv[1], "version"))
        {
            version();
        }
        else
        {
            usage();
            exit(1);
        }
        return 0;
    }
    AHAOAHA::Snake sn;
    sn.GameRun();
    return 0;
}

int main(int argc, char *argv[])
{
    int game = GAME_2048;
    if (argc >= 2)
    {
        game = GAME_Snake;
    }

    switch (game)
    {
    case GAME_2048:
        return game_2048();
    case GAME_Snake:
        return game_snake(argc, argv);
    }

    return 0;
}
