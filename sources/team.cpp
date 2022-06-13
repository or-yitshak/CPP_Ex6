#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include "team.hpp"

using namespace std;

void checkName(string const &name)
{
    if (name.empty())
    {
        throw invalid_argument("name cant be between empty");
    }
    int spaces = 0;
    for (size_t i = 0; i < name.size(); i++)
    {
        if ((name.at(i) < 'A' || name.at(i) > 'Z') && (name.at(i) < 'a' || name.at(i) > 'z'))
        {
            if (name.at(i) != ' ')
            {
                throw invalid_argument("string contains unprintable chars");
            }
            spaces++;
        }
    }
    if (spaces == name.size())
    {
        throw invalid_argument("just spaces");
    }
}

void Team::setTalent(double const &talent)
{
    if (talent > 1 || talent < 0)
    {
        throw invalid_argument("talent should be between 0 and 1");
    }
    this->_talent = talent;
}
void Team::setName(string const &name)
{
    checkName(name);
    this->_name = name;
}

Team::Team(string const &name, double const &talent)
{
    setName(name);
    setTalent(talent);
}
Team::Team(string const &name)
{
    random_device rd;
    mt19937 e2(rd());
    uniform_real_distribution<double> dist(0, 1);
    double talent = dist(e2);
    setName(name);
    setTalent(talent);
}
Team::Team()
{
    this->_name = "a";
    this->_talent = 0;
}

Team::Team(Team const &other)
{
    this->_name = other._name;
    this->_talent = other._talent;
    this->_wins = 0;
    this->_points_diff = 0;
    this->_longest_wins = 0;
    this->_longest_losts = 0;
    this->_games_played = 0;
    this->_curr_wins = 0;
    this->_curr_losts = 0;
}

void Team::win()
{
    this->_wins++;
    this->_curr_wins++;
    if (this->_curr_wins > this->_longest_wins)
    {
        this->_longest_wins = this->_curr_wins;
    }
    this->_curr_losts = 0;
    this->gamesPlayedUpdate();
}
void Team::lose()
{
    this->_curr_losts++;
    if (this->_curr_losts > this->_longest_losts)
    {
        this->_longest_losts = this->_curr_losts;
    }
    this->_curr_wins = 0;
    this->gamesPlayedUpdate();
}

ostream &operator<<(ostream &out, Team &t)
{
    out << t.getName() << "\t";
    out << std::fixed << std::setprecision(2) << t.getTalent() << "\t";
    out << t.getWins() << "\t";
    out << t.getPointsDiff() << "\t";
    out << t.getLongestWins() << "\t";
    out << t.getLongestLosts() << "\t";
    out << t.getAvgPPG() << "\t";
    out << t.getOppAvgPPG() << "\t";
    out << t.getGamesPlayed() << "\t";
    out << endl;
    return out;
}
