#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <deque>
#include "team.hpp"
#include "game.hpp"
#include "schedule.hpp"

using namespace std;

Schedule::Schedule(vector<Team *> &teams)
{
    this->_rounds.resize((size_t)NUMBER_OF_ROUNDS);
    Team *stay = teams.at(0);
    deque<Team *> a;
    deque<Team *> b;
    for (size_t i = 1; i < teams.size(); i++)
    {
        Team *curr_team = teams.at(i);
        if (i < NUMBER_OF_TEAMS / 2)
        {
            a.push_back(curr_team);
        }
        else
        {
            b.push_back(curr_team);
        }
    }

    for (size_t i = 0; i < teams.size() - 1; i++)
    {
        createRound(a, b, stay, i);
        Team *team1 = a.front();
        Team *team2 = b.back();
        a.pop_front();
        b.pop_back();
        a.push_back(team2);
        b.push_front(team1);
    }
}
Schedule::~Schedule()
{
    for (size_t i = 0; i < this->_rounds.size(); i++)
    {
        vector<Game *> round = this->_rounds.at(i);
        for (size_t j = 0; j < round.size(); j++)
        {
            delete round.at(j);
        }
    }
}

void Schedule::createRound(deque<Team *> &a, deque<Team *> &b, Team *&stay, int round_number)
{
    for (size_t i = 0; i < NUMBER_OF_TEAMS / 2; i++)
    {
        Team *team1 = nullptr;
        if (i == 0)
        {
            team1 = stay;
        }
        else
        {
            team1 = a.front();
            a.pop_front();
        }
        Team *team2 = b.front();
        b.pop_front();
        Game *first_game = new Game(*team1, *team2);
        Game *second_game = new Game(*team2, *team1);
        this->_rounds.at((size_t)round_number).push_back(first_game);
        this->_rounds.at((size_t)(round_number + NUMBER_OF_TEAMS - 1)).push_back(second_game);
        if (i != 0)
        {
            a.push_back(team1);
        }
        b.push_back(team2);
    }
}
vector<Game *> &Schedule::getCurrRound() 
{ 
    if (this->_curr_round == NUMBER_OF_ROUNDS){
        throw invalid_argument("the league is over there are no more rounds!");
    }
    return _rounds.at((size_t)_curr_round); 
}

vector<Game *> &Schedule::getRound(size_t i)
{ 
    if (i >= NUMBER_OF_ROUNDS || i<0){
        throw invalid_argument("round number is out of range!");
    }
    return _rounds.at(i); 
}

ostream &operator<<(ostream &out, Schedule &s)
{
    for (size_t i = 0; i < s._rounds.size(); i++)
    {
        out << "Round No." << i + 1 << ":" << endl;
        vector<Game *> curr_round = s._rounds.at(i);
        for (size_t j = 0; j < curr_round.size(); j++)
        {
            Game *curr_game = curr_round.at(j);
            out << curr_game->getHomeTeam()->getName() << " VS " << curr_game->getAwayTeam()->getName() << endl;
        }
    }
    return out;
}
