#include <iostream>
#include "team.hpp"
#include "game.hpp"
#include "league.hpp"
#include "schedule.hpp"

using namespace std;

int main()
{
    League l;
    l.playRound();
    cout << "Table after 1 round:" << endl;
    cout << l;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    l.playAllRounds();
    cout << "Table after all rounds:" << endl;
    cout << l;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    l.showTop(5);
    l.showLongestLosts();
    l.showLongestWins();
    cout << "game eaxample:" << endl;
    cout << *(l.getSchedule()->getRound(13).at(0));
    // cout<< "full schedule:"<<endl;
    // cout<<*(l.getSchedule());

    return 0;
}