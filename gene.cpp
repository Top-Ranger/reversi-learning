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

#include "gene.h"
#include <QTime>
#include <cstdlib>
#include <QFile>
#include <QTextStream>

namespace {
float getRandomFloat()
{
    return static_cast<float> (qrand()) / (static_cast<float> (RAND_MAX/2.0)) - 1.0;
}

float getRandomChancet()
{
    return static_cast<float> (qrand()) / (static_cast<float> (RAND_MAX));
}
}

Gene::Gene(float mutationRate):
    _inputToHidden1(),
    _hidden1ToHidden2(),
    _hidden2ToOutput(),
    _mutationRate(mutationRate),
    _score(0)
{
    for(int i = 0; i < 129*_sizeHidden; ++i)
    {
        _inputToHidden1.append(getRandomFloat());
    }
    for(int i = 0; i < _sizeHidden*(_sizeHidden+1); ++i)
    {
        _hidden1ToHidden2.append(getRandomFloat());
    }
    for(int i = 0; i < 64*(_sizeHidden+1); ++i)
    {
        _hidden2ToOutput.append(getRandomFloat());
    }
}

void Gene::mutate()
{
    for(int i = 0; i < 129*_sizeHidden; ++i)
    {
        if(getRandomChancet() < _mutationRate)
        {
            _inputToHidden1[i] = getRandomFloat();
        }
    }
    for(int i = 0; i < _sizeHidden*(_sizeHidden+1); ++i)
    {
        if(getRandomChancet() < _mutationRate)
        {
            _hidden1ToHidden2[i] = getRandomFloat();
        }
    }
    for(int i = 0; i < 64*(_sizeHidden+1); ++i)
    {
        if(getRandomChancet() < _mutationRate)
        {
            _hidden2ToOutput[i] = getRandomFloat();
        }
    }
}


void Gene::saveScore(int score)
{
    _score = score;
}

void Gene::saveFiles(QString inputToHiddenPath, QString hiddenToHiddenPath, QString hiddenToOutputPath)
{
    QFile ith1(inputToHiddenPath);
    ith1.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream ith1Stream(&ith1);
    for(int i = 0; i < _sizeHidden*129; ++i)
    {
        ith1Stream << _inputToHidden1[i];
        ith1Stream << " ";
    }
    ith1.close();

    QFile h1th2(hiddenToHiddenPath);
    h1th2.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream h1th2Stream(&h1th2);
    for(int i = 0; i < _sizeHidden*_sizeHidden; ++i)
    {
        h1th2Stream << _hidden1ToHidden2[i];
        h1th2Stream << " ";
    }
    h1th2.close();

    QFile hto(hiddenToOutputPath);
    hto.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream htoStream(&hto);
    for(int i = 0; i < _sizeHidden*64; ++i)
    {
        htoStream << _hidden2ToOutput[i];
        htoStream << " ";
    }
    hto.close();
}

bool Gene::operator<(const Gene &other) const
{
    return _score > other._score;
}

int Gene::getScore()
{
    return _score;
}
