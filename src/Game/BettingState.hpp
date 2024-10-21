#ifndef BETTINGSTATE_HPP
#define BETTINGSTATE_HPP

#include "Action.hpp"

enum class BettingState {
    INITIAL,
    PLAYER_2_ACTS_AFTER_CHECK,
    PLAYER_2_ACTS_AFTER_SMALL_BET,
    PLAYER_2_ACTS_AFTER_LARGE_BET,
    PLAYER_1_ACTS_AFTER_PLAYER_2_BET,
    ROUND_END
};

BettingState transition(BettingState currentState, PlayerAction action1, PlayerAction action2);

#endif