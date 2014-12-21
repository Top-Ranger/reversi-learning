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

#include <QDebug>
#include <QList>
#include <QTime>
#include <QString>
#include <QtAlgorithms>
#include "getscore.h"
#include "gene.h"

// Parameters of learning
int rounds = 40;
int population = 20;
int children = 20;
int mutationRate = 0.1;
int redoTests = 3;

struct TestScenario {
    QString player1;
    QString player2;
    int player;
};

QList<TestScenario> getScenarios();

int main(int argc, char *argv[])
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QList<Gene> currentPopulation;
    QList<TestScenario> scenatios = getScenarios();
    GetScore calc;

    for(int i = 0; i < population; ++i)
    {
        currentPopulation.append(Gene(mutationRate));
    }

    for(int round = 1; round <= rounds; ++round)
    {
        qDebug() << "Current round: " << round;

        QList<Gene> newPopulation = currentPopulation;
        for(int i = 0; i < children; ++i)
        {
            Gene children = currentPopulation[qrand()%population];
            children.mutate();
            newPopulation.append(children);
        }

        for(int testnr=0; testnr < population+children; ++testnr)
        {
            qDebug() << "\tGene " << testnr;
            int score = 0;
            newPopulation[testnr].saveFiles();
            for(int test = 0; test < scenatios.size(); ++test)
            {
                calc.startTest(scenatios[test].player1, scenatios[test].player2,scenatios[test].player);
                while(calc.scoreCalculated()) {qDebug() << "Waiting";}
                score += calc.getScore();
            }
            newPopulation[testnr].saveScore(score);
        }

        currentPopulation.clear();
        qSort(newPopulation);
        for(int i = 0; i < population; ++i)
        {
            currentPopulation.append(newPopulation[i]);
        }

        qDebug() << "++++++++++\nBest score: " << currentPopulation[0].getScore() << "\n++++++++++\n";
    }

    currentPopulation[0].saveFiles();
    qDebug() << "Finished";
}

QList<TestScenario> getScenarios()
{
    QList<TestScenario> scenarios;

    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Greedy AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Greedy AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Tree AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Tree AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Balanced AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Balanced AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Static Rule AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Static Rule AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Adaptive Tree AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Adaptive Tree AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Control AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Control AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }


    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player1 = "Assembly AI";
        test.player2 = "Neural Network AI";
        test.player = 2;
        scenarios.append(test);
    }
    for(int i=0; i<redoTests; ++i)
    {
        TestScenario test;
        test.player2 = "Assembly AI";
        test.player1 = "Neural Network AI";
        test.player = 1;
        scenarios.append(test);
    }

    return scenarios;
}
