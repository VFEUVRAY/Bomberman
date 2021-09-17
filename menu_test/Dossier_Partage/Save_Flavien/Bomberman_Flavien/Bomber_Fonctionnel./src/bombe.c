#include "../include/game.h"

//void bombe_init(bombe_t *sBombe) {
bombe_t* bombe_init() {

    bombe_t* sBombe = NULL;
    sBombe = malloc(sizeof(bombe_t));

    //sBombe->bombeTexture = NULL;

    sBombe->bombePositionRect.x = 130;
    sBombe->bombePositionRect.y = 130;
    sBombe->bombePositionRect.w = 30;
    sBombe->bombePositionRect.h = 30;

    return sBombe;
}