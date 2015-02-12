/*
  Copyright (C) 2014 Marcus Soll
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
    _score = 0;
    _player = player;
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
        if(player1>player2)
        {
            _score = 1;
        }
    }
    else
    {
        if(player2>player1)
        {
            _score = 1;
        }
    }
    _finished = true;
}
