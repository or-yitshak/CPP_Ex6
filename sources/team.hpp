#pragma once
#include <string>
#include <iostream>
using namespace std;

class Team
{
    /**
     * @brief this class represent a basketball team.
     * each team have the following fields in it:
     * name - the name of the team.
     * talent - a real number between 0 and 1 that shows how good is the team.
     * wins - the number of the games they won until this point.
     * points diff - the total points differential
     * longest wins - the longest winning streak 
     * longest losts - the longest losing streak
     * curr wins - the current winning streak
     * curr losts - the current losing streak
     * total points - the number of points they made so far.
     * opp total points - the number of points the opponent made so far.
     * 
     */
private:
    string _name;
    double _talent = 0;
    int _wins = 0;
    int _points_diff = 0;
    int _longest_wins = 0;
    int _longest_losts = 0;
    int _games_played = 0;
    int _curr_wins = 0;
    int _curr_losts = 0;
    int _total_points = 0;
    int _opp_total_points = 0;

    void setTalent(double const &talent);
    void setName(string const &name);

public:
    double &getTalent() { return this->_talent; }
    string &getName() { return this->_name; }
    int &getWins() { return this->_wins; }
    int &getPointsDiff() { return this->_points_diff; }
    int &getLongestWins() { return this->_longest_wins; }
    int &getLongestLosts() { return this->_longest_losts; }
    int &getGamesPlayed() { return this->_games_played; }
    double getAvgPPG() const { return (double)this->_total_points / (double)this->_games_played; }
    double getOppAvgPPG() const { return (double)this->_opp_total_points / (double)this->_games_played; }

    Team(string const &name, double const &talent);
    Team(string const &name);
    Team();
    Team(Team const &other);

    void win();
    void lose();
    void pointsUpdate(int points) { this->_points_diff += points; }
    void gamesPlayedUpdate() { this->_games_played++; }
    void avgPPGUpdate(int points) { this->_total_points += points; }
    void avgOppPPGUpdate(int points) { this->_opp_total_points += points; }
    bool operator==(const Team &other) const { return this->_name == other._name; }
    friend std::ostream &operator<<(std::ostream &out, Team &t);
};