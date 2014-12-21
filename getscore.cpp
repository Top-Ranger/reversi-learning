#include "getscore.h"

GetScore::GetScore(QObject *parent) :
    QObject(parent),
    _finished(true),
    _master(),
    _player(0),
    _score(0)
{
    QObject::connect(&_master, SIGNAL(result(int,int)), this, SLOT(result(int,int)));
}

void GetScore::startTest(QString player1, QString player2, int player)
{
    _master.initialise(player1, player2, 0);
    _master.startGame();
    _finished = false;
}

bool GetScore::scoreCalculated()
{
    return _finished;
}

int GetScore::getScore()
{
    return _score;
}

void GetScore::result(int player1, int player2)
{
    _score = 0;
    if(_player == 1)
    {
        _score += player1;
        _score -= player2;
        if(player1>player2)
        {
            _score *= 2;
        }
    }
    else
    {
        _score += player2;
        _score -= player1;
        if(player2>player1)
        {
            _score *= 2;
        }
    }
    _finished = true;
}
