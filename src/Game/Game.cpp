#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

// Player class implementation
Player::Player(int startingChips) : chips(startingChips), hasFolded(false) {}

void Player::receiveCard(const Card& card) {
    hand.cards.push_back(card);
}

void Player::resetHand() {
    hand.cards.clear();
    hasFolded = false;
}

// Deck class implementation
Deck::Deck() {
    const std::vector<Rank> ranks = {Rank::TWO, Rank::THREE, Rank::FOUR, Rank::FIVE, Rank::SIX, Rank::SEVEN, Rank::EIGHT, Rank::NINE, Rank::TEN, Rank::JACK, Rank::QUEEN, Rank::KING, Rank::ACE};
    const std::vector<Suit> suits = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES};

    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            cards.push_back({rank, suit});
        }
    }
    std::srand(unsigned(std::time(0)));
}

void Deck::shuffle() {
    std::random_shuffle(cards.begin(), cards.end());
}

Card Deck::dealCard() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

// Game class implementation
Game::Game(int startingChips) : player1(startingChips), player2(startingChips), pot(0) {}

void Game::playRound() {
    setupRound();
    dealHands();
    printGameState(true); // Print hands at the beginning of the round
    bettingRound(PlayerAction::CHECK, PlayerAction::CHECK);

    if (!player1.hasFolded && !player2.hasFolded) {
        dealFlop();
        printGameState();
        bettingRound(PlayerAction::CALL, PlayerAction::RAISE);
    }

    if (!player1.hasFolded && !player2.hasFolded) {
        dealTurn();
        printGameState();
        bettingRound(PlayerAction::RAISE, PlayerAction::RAISE);
    }

    if (!player1.hasFolded && !player2.hasFolded) {
        dealRiver();
        printGameState();
        bettingRound(PlayerAction::FOLD, PlayerAction::RAISE, true);
    }

    if (!player1.hasFolded && !player2.hasFolded) {
        determineWinner();
    }
}

void Game::setupRound() {
    player1.resetHand();
    player2.resetHand();
    communityCards.clear();
    pot = 0;
    deck.shuffle();
}

void Game::dealHands() {
    for (int i = 0; i < 2; ++i) {
        player1.receiveCard(deck.dealCard());
        player2.receiveCard(deck.dealCard());
    }
}

void Game::dealFlop() {
    for (int i = 0; i < 3; ++i) {
        communityCards.push_back(deck.dealCard());
    }
}

void Game::dealTurn() {
    communityCards.push_back(deck.dealCard());
}

void Game::dealRiver() {
    communityCards.push_back(deck.dealCard());
}

BettingState transition(BettingState currentState, PlayerAction action1, PlayerAction action2) {
    std::cout << "Current state: " << static_cast<int>(currentState) << ", Player 1 action: " << static_cast<int>(action1) << ", Player 2 action: " << static_cast<int>(action2) << std::endl;

    switch (currentState) {
        case BettingState::INITIAL:
            if (action1 == PlayerAction::CHECK) {
                return BettingState::PLAYER_2_ACTS_AFTER_CHECK;
            } else if (action1 == PlayerAction::CALL) {
                return BettingState::PLAYER_2_ACTS_AFTER_SMALL_BET;
            } else if (action1 == PlayerAction::RAISE) {
                return BettingState::PLAYER_2_ACTS_AFTER_LARGE_BET;
            }
            break;
        case BettingState::PLAYER_2_ACTS_AFTER_CHECK:
            if (action2 == PlayerAction::CHECK) {
                return BettingState::ROUND_END;
            } else if (action2 == PlayerAction::CALL || action2 == PlayerAction::RAISE) {
                return BettingState::PLAYER_1_ACTS_AFTER_PLAYER_2_BET;
            }
            break; 
        case BettingState::PLAYER_2_ACTS_AFTER_SMALL_BET:
            if (action2 == PlayerAction::CHECK) {
                return BettingState::PLAYER_2_ACTS_AFTER_SMALL_BET;
            } else if (action2 == PlayerAction::CALL) {
                return BettingState::ROUND_END;
            } else if (action2 == PlayerAction::RAISE) {
                return BettingState::PLAYER_1_ACTS_AFTER_PLAYER_2_BET;
            } else if (action2 == PlayerAction::FOLD) {
                return BettingState::ROUND_END;
            }
            break;
        case BettingState::PLAYER_2_ACTS_AFTER_LARGE_BET:
            if (action2 == PlayerAction::CHECK) {
                return BettingState::PLAYER_2_ACTS_AFTER_LARGE_BET;
            } else if (action2 == PlayerAction::CALL) {
                return BettingState::PLAYER_2_ACTS_AFTER_LARGE_BET;
            } else if (action2 == PlayerAction::RAISE) {
                return BettingState::ROUND_END;
            } else if (action2 == PlayerAction::FOLD) {
                return BettingState::ROUND_END;
            }
            break;
        case BettingState::PLAYER_1_ACTS_AFTER_PLAYER_2_BET:
            if (action1 == PlayerAction::CALL) {
                return BettingState::ROUND_END;
            } else if (action1 == PlayerAction::FOLD) {
                return BettingState::ROUND_END;
            }
            break;
        default:
            std::cerr << "Unhandled state-action combination!" << std::endl;
            return BettingState::ROUND_END;
    }
    std::cerr << "Unhandled state-action combination!" << std::endl;
    return BettingState::ROUND_END;
}

void Game::bettingRound(PlayerAction action1, PlayerAction action2, bool isFinalRound) {
    const int smallBet = 20;
    const int largeBet = 100;
    const int maxIterations = 10; // Prevent infinite loops during testing

    BettingState currentState = BettingState::INITIAL;
    int iterationCount = 0;

    while (currentState != BettingState::ROUND_END && iterationCount < maxIterations) {
        currentState = transition(currentState, action1, action2);
        iterationCount++;

        // Perform actions based on the state
        switch (currentState) {
            case BettingState::PLAYER_2_ACTS_AFTER_SMALL_BET:
                // Player 2 acts after Player 1's small bet
                if (action2 == PlayerAction::RAISE) {
                    player2.chips -= largeBet;
                    pot += largeBet;
                    action1 = PlayerAction::CALL; // Force Player 1 to act after a raise
                } else if (action2 == PlayerAction::CALL) {
                    player2.chips -= smallBet;
                    pot += smallBet;
                } else if (action2 == PlayerAction::CHECK) {
                    // No change in chips
                } else if (action2 == PlayerAction::FOLD) {
                    player2.hasFolded = true;
                    currentState = BettingState::ROUND_END;
                }
                break;
            case BettingState::PLAYER_2_ACTS_AFTER_LARGE_BET:
                // Player 2 acts after Player 1's large bet
                if (action2 == PlayerAction::CALL) {
                    player2.chips -= largeBet;
                    pot += largeBet;
                } else if (action2 == PlayerAction::FOLD) {
                    player2.hasFolded = true;
                    currentState = BettingState::ROUND_END;
                }
                break;
            case BettingState::PLAYER_1_ACTS_AFTER_PLAYER_2_BET:
                // Player 1 acts after Player 2's bet
                if (action1 == PlayerAction::CALL) {
                    player1.chips -= largeBet;
                    pot += largeBet;
                } else if (action1 == PlayerAction::FOLD) {
                    player1.hasFolded = true;
                    currentState = BettingState::ROUND_END;
                }
                break;
            case BettingState::ROUND_END:
                // Round ends, no action needed
                break;
            default:
                std::cerr << "Unhandled state-action combination!" << std::endl;
                currentState = BettingState::ROUND_END;
                break;
        }
    }

    if (iterationCount >= maxIterations) {
        std::cerr << "Betting round exceeded maximum iterations. Potential infinite loop detected." << std::endl;
    }
}

void Game::determineWinner() {
    if (player1.hasFolded) {
        std::cout << "Player 2 wins the pot of " << pot << " chips!\n";
        player2.chips += pot;
        return;
    } else if (player2.hasFolded) {
        std::cout << "Player 1 wins the pot of " << pot << " chips!\n";
        player1.chips += pot;
        return;
    }

    std::vector<std::string> allCards1;
    for (const auto& card : player1.hand.cards) {
        allCards1.push_back(card.toString());
    }
    for (const auto& card : communityCards) {
        allCards1.push_back(card.toString());
    }

    std::vector<std::string> allCards2;
    for (const auto& card : player2.hand.cards) {
        allCards2.push_back(card.toString());
    }
    for (const auto& card : communityCards) {
        allCards2.push_back(card.toString());
    }

    HandResult result1 = evalHand(allCards1);
    HandResult result2 = evalHand(allCards2);

    std::cout << "\nFinal Community cards: ";
    for (const auto& card : communityCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;

    if (result1.value > result2.value) {
        std::cout << "Player 1 wins the pot of " << pot << " chips!\n";
        player1.chips += pot;
    } else if (result2.value > result1.value) {
        std::cout << "Player 2 wins the pot of " << pot << " chips!\n";
        player2.chips += pot;
    } else {
        std::cout << "It's a tie! The pot is split.\n";
        player1.chips += pot / 2;
        player2.chips += pot / 2;
    }
}

void Game::printGameState(bool showHands) {
    if (showHands) {
        std::cout << "\nPlayer 1's hand: " << player1.hand.toString() << std::endl;
        std::cout << "Player 2's hand: " << player2.hand.toString() << std::endl;
    }

    std::cout << "Community cards: ";
    for (const auto& card : communityCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;

    std::cout << "Pot size: " << pot << " chips\n";
}

std::vector<std::string> Game::getCurrentGameState() const {
    std::vector<std::string> state;
    for (const auto& card : player1.hand.cards) {
        state.push_back(card.toString());
    }
    for (const auto& card : player2.hand.cards) {
        state.push_back(card.toString());
    }
    for (const auto& card : communityCards) {
        state.push_back(card.toString());
    }
    return state;
}

void Game::handleAction(PlayerAction action1, PlayerAction action2) {
    bettingRound(action1, action2);
}

void Game::resetGameState() {
    setupRound();
}

int Game::getPot() const {
    return pot;
}