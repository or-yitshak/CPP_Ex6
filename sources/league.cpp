#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include "team.hpp"
#include "game.hpp"
#include "league.hpp"

using namespace std;

League::League()
{
    for (string const &name : this->_optional_names)
    {
        Team *new_team = new Team(name);
        this->_teams.push_back(new_team);
    }
    this->_secd = new Schedule(this->_teams);
}
League::League(vector<Team *> const &teams)
{
    unordered_set<string> names_set;
    for (size_t i = 0; i < teams.size(); i++)
    {
        Team *ptr_team = new Team(*teams.at(i));
        if ((names_set.find(ptr_team->getName()) == names_set.end()) && (this->_teams.size() < NUMBER_OF_TEAMS))
        {
            names_set.insert(ptr_team->getName());
            this->_teams.push_back(ptr_team);
        }
    }
    if (this->_teams.size() >= NUMBER_OF_TEAMS)
    {
        return;
    }
    size_t i = 0;
    while (this->_teams.size() < NUMBER_OF_TEAMS)
    {
        string curr_name = this->_optional_names[i];
        if (names_set.find(curr_name) == names_set.end())
        {
            names_set.insert(curr_name);
            Team *ptr_team = new Team(curr_name);
            this->_teams.push_back(ptr_team);
        }
        i++;
    }
    this->_secd = new Schedule(this->_teams);
}

League::~League()
{
    for (size_t i = 0; i < this->_teams.size(); i++)
    {
        delete this->_teams.at(i);
    }
    delete this->_secd;
}

void League::playRound()
{
    if (this->_over)
    {
        throw invalid_argument("The league is over!");
    }
    vector<Game *> round = this->_secd->getCurrRound();
    for (Game *curr_game : round)
    {
        curr_game->play();
    }
    this->_secd->updateCurrRound();
    this->_sorted = false;
    if (this->_secd->getCurrRoundNumber() == NUMBER_OF_ROUNDS)
    {
        this->_over = true;
    }
}

void League::playAllRounds()
{
    if (this->_over)
    {
        throw invalid_argument("The league is over!");
    }
    for (size_t i = (size_t)this->_secd->getCurrRoundNumber(); i < NUMBER_OF_ROUNDS; i++)
    {
        playRound();
    }
}

bool compare(Team *t1, Team *t2)
{
    if (t1->getWins() != t2->getWins())
    {
        return t1->getWins() > t2->getWins();
    }
    return t1->getPointsDiff() > t2->getPointsDiff();
}

void League::mysort()
{
    sort(_teams.begin(), _teams.end(), compare);
    this->_sorted = true;
}

void League::showTop(int size)
{
    if (size > NUMBER_OF_TEAMS || size < 1)
    {
        throw invalid_argument("i should be between 1 and 20");
    }
    if (!this->_sorted)
    {
        this->mysort();
    }
    cout << "the top " << size << " teams are:" << endl;
    for (size_t i = 0; i < size; i++)
    {
        cout << "No." << i + 1 << "\t" << this->_teams.at(i)->getName() << endl;
    }
    cout << endl;
}
void League::showLongestWins()
{
    int _max = 0;
    string name;
    for (size_t i = 0; i < _teams.size(); i++)
    {
        if (this->_teams.at(i)->getLongestWins() >= _max)
        {
            _max = this->_teams.at(i)->getLongestWins();
            name = this->_teams.at(i)->getName();
        }
    }
    cout << name << " won " << _max << " games in a row!" << endl;
}
void League::showLongestLosts()
{
    int _max = 0;
    string name;
    for (size_t i = 0; i < _teams.size(); i++)
    {
        if (this->_teams.at(i)->getLongestLosts() >= _max)
        {
            _max = this->_teams.at(i)->getLongestLosts();
            name = this->_teams.at(i)->getName();
        }
    }
    cout << name << " lost " << _max << " games in a row!" << endl;
}
void League::countPositivePts()
{
    int counter = 0;
    for (size_t i = 0; i < _teams.size(); i++)
    {
        if (this->_teams.at(i)->getPointsDiff() > 0)
        {
            counter++;
        }
    }
    cout << counter << " teams have positive points diffrential games in a row!" << endl;
}

ostream &operator<<(ostream &out, League &le)
{
    if (!le._sorted)
    {
        le.mysort();
    }
    cout << "No."
         << "\t";
    out << "Name"
        << "\t";
    out << "Talent"
        << "\t";
    out << "Win"
        << "\t";
    out << "Pts"
        << "\t";
    out << "L_WIN"
        << "\t";
    out << "L_LOSE"
        << "\t";
    out << "PPG"
        << "\t";
    out << "OPPG"
        << "\t";
    out << "GP"
        << "\t";
    out << endl;
    int i = 1;
    for (Team *ptr_team : le._teams)
    {
        out << i << "\t" << *ptr_team;
        i++;
    }
    return out;
}
