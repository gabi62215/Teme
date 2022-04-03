#include <iostream>
#include <cstring>
#include <cstdint>
#include <csignal>
#include "definitions.h"
#include "variables.h"
#include "functions.h"

using namespace std;

/*
    Main functions, also serves as a parser for the commands
    given by xboard to this engine
*/
int main() {
    char stdLine[256], command[256];
    printf("\n");
    init_board();
    int move;
    signal(SIGINT, SIG_IGN);

    for (;;) {
        fflush(stdout);
        if (side == engine_side) {
            generate_move();
            char *engine_move = get_move();
            if (engine_move == nullptr)
                printf("resign\n");
            printf("move %s\n", engine_move);
            side = !side;
            printTable();
            continue;
        }
        if (!fgets(stdLine, 256, stdin)) {
            continue;
        }
        if (stdLine[0] == '\n') {
            continue;
        }

        sscanf(stdLine, "%s", command);

        if (!strcmp(command, "quit")) {
            break;
        } else if (!strcmp(command, "xboard")) {
            continue;
        } else if (!strcmp(command, "go")) {
            engine_side = side;
            continue;
        } else if (!strcmp(command, "random")) {
            continue;
        } else if (!strcmp(command, "new")) {
            init_board();
            continue;
        } else if (!strcmp(command, "force")) {
            engine_side = EMPTY;
            continue;
        } else if (!strcmp(command, "resign")) {
            printf("resign\n");
            continue;
        }

        move = registerMove(stdLine);
        if (move == -1) {
            continue;
        } else {
            side = !side;
            printTable();
            continue;
        }
    }
    return 0;
}
