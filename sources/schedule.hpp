#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <deque>
#include "team.hpp"
#include "game.hpp"

using namespace std;

class Schedule
{
    /**
     * @brief this class represent a game schedule of a league.
     * there are exactly 20 teams and 38 rounds such that each team plays against
     * each team once at home and once away.
     * each schdule has the following field:
     * curr round - the number of the current round.
     * NUMBER_OF_ROUNDS - number of rounds.
     * NUMBER_OF_TEAMS - number of teams.
     * rounds - a 2D vector that represent the schdule, each vector<Game*> represent one round and in
     * this round each team plays exactly once.
     *
     */
private:
    int _curr_round = 0;
    const int NUMBER_OF_ROUNDS = 38;
    const int NUMBER_OF_TEAMS = 20;
    vector<vector<Game *>> _rounds;

public:
    int &getCurrRoundNumber() { return _curr_round; }
    vector<Game *> &getCurrRound();
    vector<Game *> &getRound(size_t i);
    void updateCurrRound() { this->_curr_round++; }

    Schedule(vector<Team *> &teams);
    void createRound(deque<Team *> &a, deque<Team *> &b, Team *&stay, int round_number);
    friend std::ostream &operator<<(std::ostream &out, Schedule &s);
    ~Schedule();
};