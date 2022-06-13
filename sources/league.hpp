#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include "team.hpp"
#include "game.hpp"
#include "schedule.hpp"

using namespace std;

class League
{
    /**
     * @brief this class represent a basketball league. in each league there are exactly 20 teams and 38
     * rounds such that each team plays against each team once at home and once away.
     * after each round we can print the league table that shows the following statistics:
     * No. - the place in the table.
     * Name - the name of the team.
     * Talent - the talent of the team.
     * Win - the number of games they won so far.
     * Pts - points differential.
     * L_WIN - longest winning streak.
     * L_LOSE - longest losing streak.
     * PPG - avereage points per game.
     * OPPG - avereage opponent points per game.
     * GP - games played.
     * 
     * each league have the following fields:
     * optional names - in case that the user dosent gave enogh names (20) we will use this names.
     * teams - a vector that contains pointers to all the teams in this league.
     * secd - the game schedule of this league.
     * NUMBER_OF_ROUNDS - number of rounds.
     * NUMBER_OF_TEAMS - number of teams.
     * sorted - says if the table is sorted right now.
     * over - says if the league over yet.
     * 
     * 
     */
private:
    vector<string> _optional_names{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T"};
    vector<Team *> _teams;
    Schedule *_secd;
    const int NUMBER_OF_ROUNDS = 38;
    const int NUMBER_OF_TEAMS = 20;
    bool _sorted = true;
    bool _over = false;
    void mysort();

public:
    vector<Team *> get_teams() { return this->_teams; }
    Schedule *&getSchedule() { return this->_secd; }
    League();
    League(vector<Team *> const &teams);
    ~League();
    friend std::ostream &operator<<(std::ostream &out, League &le);
    void playRound();
    void playAllRounds();

    void showTop(int size);
    void showLongestWins();
    void showLongestLosts();
    void countPositivePts();
};