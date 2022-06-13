/**
 * AUTHORS: or yitshak
 *
 * Date: 2022-03
 */

#include "doctest.h"
#include "league.hpp"
#include "team.hpp"
#include "game.hpp"
#include "schedule.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

TEST_CASE("All tests")
{
    Team t1("A", 0.5);
    Team t2("B");
    Team t3;
    Team t4(t1);
    Team t5("C", 0.3);

    CHECK_EQ(t1.getName(), "A");
    CHECK_EQ(t1.getTalent(), 0.5);
    CHECK_EQ(t2.getName(), "B");
    CHECK_EQ(t3.getName(), "a");
    CHECK_EQ(t3.getTalent(), 0);
    CHECK_EQ(t1.getGamesPlayed(), 0);
    CHECK_EQ(t1.getLongestLosts(), 0);
    CHECK_EQ(t1.getLongestWins(), 0);
    CHECK_EQ(t1.getWins(), 0);
    CHECK_EQ(t1.getPointsDiff(), 0);
    CHECK_EQ(t4.getName(), "A");
    CHECK_EQ(t4.getTalent(), 0.5);

    CHECK_THROWS(Team("0"));
    CHECK_THROWS(Team("! me"));
    CHECK_THROWS(Team("   "));

    CHECK_NOTHROW(t5.win());
    CHECK_EQ(t5.getWins(), 1);
    CHECK_EQ(t5.getGamesPlayed(), 1);
    CHECK_EQ(t5.getLongestWins(), 1);
    CHECK_NOTHROW(t5.lose());
    CHECK_EQ(t5.getGamesPlayed() - t5.getWins(), 1);
    CHECK_EQ(t5.getGamesPlayed(), 2);
    CHECK_EQ(t5.getLongestWins(), 1);
    CHECK_EQ(t5.getLongestLosts(), 1);

    Game g(t1, t2);
    CHECK_EQ(*(g.getHomeTeam()), t1);
    CHECK_EQ(*(g.getAwayTeam()), t2);
    CHECK_THROWS(g.getHomeScore());
    CHECK_THROWS(g.getAwayScore());
    CHECK_THROWS(g.getLoser());
    CHECK_THROWS(g.getWinner());
    CHECK_NOTHROW(g.play());
    CHECK_NOTHROW(g.getHomeScore());
    CHECK_NOTHROW(g.getAwayScore());
    CHECK_NOTHROW(g.getLoser());
    CHECK_NOTHROW(g.getWinner());
    CHECK(g.getLoser() != g.getWinner());
    CHECK_THROWS(Game g(t1, t1));

    League l1;
    l1.playAllRounds();
    int sum = 0;
    vector<Team *> teams1 = l1.get_teams();
    for (size_t i = 0; i < teams1.size(); i++)
    {
        Team *t = teams1.at(i);
        sum += t->getPointsDiff();
        
    }
    CHECK_EQ(sum, 0);

    vector<Team *> vec;
    Team *ptr1 = &t1;
    Team *ptr2 = &t2;
    vec.push_back(ptr1);
    vec.push_back(ptr2);
    League l2(vec);
    CHECK_NOTHROW(l2.playRound());
    CHECK_NOTHROW(l2.playRound());
    CHECK_NOTHROW(l2.playAllRounds());

    League l3;
    l3.playAllRounds();
    Schedule *s = l3.getSchedule();
    for (size_t i = 0; i < 38; i++)
    {
        for (size_t j = 0; j < s->getRound(j).size(); j++)
        {
            CHECK(l3.getSchedule()->getRound(i).at(j)->getHomeScore()<=100);
            CHECK(l3.getSchedule()->getRound(i).at(j)->getHomeScore()>=55);
            CHECK(l3.getSchedule()->getRound(i).at(j)->getAwayScore()<=100);
            CHECK(l3.getSchedule()->getRound(i).at(j)->getAwayScore()>=50);
        }
    }
    CHECK_THROWS(l3.playRound());
    CHECK_THROWS(l3.playAllRounds());
}
