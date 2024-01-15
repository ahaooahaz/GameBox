#include <string.h>
#include <cmdline/cmdline.h>

#include "2048.h"
#include "snake.h"
#include "version.h"

enum
{
    GAME_UNKNOWN,
    GAME_2048,
    GAME_Snake,
};

int game_2048(int argc, char *argv[])
{
    Game_2048 g;
    g.Init(4, 4);
    g.Game();
    return 0;
}

void usage()
{
    
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
    cmdline::parser a;
    a.add("version", '\0', "show version");
    a.add<std::string>("run", 'r', "game name. [2048|snake]", false, "2048", cmdline::oneof<std::string>("2048", "snake"));
    a.parse_check(argc, argv);

    if (a.exist("version")) 
    {
        version();
        return 0;
    }

    auto run = GAME_UNKNOWN;
    if (a.get<std::string>("run") == "2048")
    {
        run = GAME_2048;
    } else if (a.get<std::string>("run") == "snake") {
        run = GAME_Snake;
    } else {
        a.usage();
        return 1;
    }

    switch (run)
    {
    case GAME_2048:
        return game_2048(argc, argv);
    case GAME_Snake:
        return game_snake(argc, argv);
    }

    return 0;
}
