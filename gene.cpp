#include "gene.h"
#include <QTime>
#include <cstdlib>
#include <QFile>
#include <QTextStream>

namespace {
float getRandomFloat()
{
    return static_cast<float> (qrand()) / (static_cast<float> (RAND_MAX/2));
}

float getRandomChancet()
{
    return static_cast<float> (qrand()) / (static_cast<float> (RAND_MAX));
}
}

Gene::Gene(float mutationRate):
    _inputToHidden(),
    _hiddenToOutput(),
    _mutationRate(mutationRate),
    _score(0)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 128*_sizeHidden; ++i)
    {
        _inputToHidden.append(getRandomFloat());
    }
    for(int i = 0; i < 64*_sizeHidden; ++i)
    {
        _hiddenToOutput.append(getRandomFloat());
    }
}

void Gene::mutate()
{
    for(int i = 0; i < 128*_sizeHidden; ++i)
    {
        if(getRandomChancet() < _mutationRate)
        {
            _inputToHidden[i] = getRandomFloat();
        }
    }
    for(int i = 0; i < 64*_sizeHidden; ++i)
    {
        if(getRandomChancet() < _mutationRate)
        {
            _hiddenToOutput[i] = getRandomFloat();
        }
    }
}


void Gene::saveScore(int score)
{
    _score = score;
}

void Gene::saveFiles()
{
    QFile ith("./inputToHidden.txt");
    ith.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream ithStream(&ith);
    for(int i = 0; i < _sizeHidden*128; ++i)
    {
        ithStream << _inputToHidden[i];
        ithStream << " ";
    }
    ith.close();

    QFile hto("./hiddenToOutput.txt");
    hto.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream htoStream(&hto);
    for(int i = 0; i < _sizeHidden*64; ++i)
    {
        htoStream << _hiddenToOutput[i];
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
