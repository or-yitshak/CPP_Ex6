#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include "game.hpp"

using namespace std;

int &Game::getHomeScore()
{
    if (!this->_start)
    {
        throw invalid_argument("the game hasnt started yet!");
    }
    return this->_home_score;
}
int &Game::getAwayScore()
{
    if (!this->_start)
    {
        throw invalid_argument("the game hasnt started yet!");
    }
    return this->_away_score;
}
Team *&Game::getWinner()
{
    if (!this->_start)
    {
        throw invalid_argument("the game hasnt started yet!");
    }
    return this->_winner;
}
Team *&Game::getLoser()
{
    if (!this->_start)
    {
        throw invalid_argument("the game hasnt started yet!");
    }
    return this->_loser;
}

Game::Game(Team &home, Team &away)
{
    if (home == away)
    {
        throw invalid_argument("a team cannot play against it self");
    }
    this->_home = &home;
    this->_away = &away;
}
void Game::play()
{
    if (this->_start)
    {
        throw invalid_argument("this game is alredy over!");
    }
    random_device rd{};
    mt19937 gen{rd()};
    double const mean_home = 77.5;
    double const stv_home = 5.625;
    double const mean_away = 75.0;
    double const stv_away = 6.25;

    normal_distribution<double> away_distribution(mean_away, stv_away);
    normal_distribution<double> home_distribution(mean_home, stv_home);
    int const pts_mul = 10;
    while (this->_away_score < 50 || this->_away_score > 100)
    {
        this->_away_score = (int)round(away_distribution(gen));
        this->_away_score += (int)round(_away->getTalent() * pts_mul);
    }
    while (this->_home_score < 55 || this->_home_score > 100)
    {
        this->_home_score = (int)round(home_distribution(gen));
        this->_home_score += (int)round(_home->getTalent() * pts_mul);
    }
   
    if (_home_score >= _away_score)
    {
        this->_winner = this->_home;
        this->_loser = this->_away;
    }
    else
    {
        this->_winner = this->_away;
        this->_loser = this->_home;
    }
    int points_diff = abs(_home_score - _away_score);
    this->_winner->win();
    this->_loser->lose();
    this->_winner->pointsUpdate(points_diff);
    this->_loser->pointsUpdate(-points_diff);
    this->getHomeTeam()->avgPPGUpdate(_home_score);
    this->getAwayTeam()->avgPPGUpdate(_away_score);
    this->getHomeTeam()->avgOppPPGUpdate(_away_score);
    this->getAwayTeam()->avgOppPPGUpdate(_home_score);
    this->_start = true;
}

ostream &operator<<(ostream &out, Game &g)
{
    out << g.getHomeTeam()->getName() << " VS " << g.getAwayTeam()->getName() << endl;
    out << "Score:" << endl;
    out << g.getHomeTeam()->getName() << "\t" << g.getHomeScore() << endl;
    out << g.getAwayTeam()->getName() << "\t" << g.getAwayScore() << endl;
    out << "The Winner Is " << g.getWinner()->getName() << endl;
    return out;
}