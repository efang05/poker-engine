#ifndef STRATEGY_H
#define STRATEGY_H

#include "Player.h"
#include "Game.h"

enum Action {
    FOLD,
    CALL,
    RAISE,
    CHECK
};

class Strategy {
public:
    Action decideAction(const Player& player, const Game& game);
};

#endif
