#include "../include/game.h"

bombe_t* bombe_init() {

    bombe_t* sBombe = NULL;
    sBombe = malloc(sizeof(bombe_t));

    sBombe->bombePositionRect.x = 0;
    sBombe->bombePositionRect.y = 0;
    sBombe->bombePositionRect.w = 32;
    sBombe->bombePositionRect.h = 32;

    return sBombe;
}