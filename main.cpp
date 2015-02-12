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
#include "omp.h"

// Parameters of learning
int rounds = 1000000;
int population = 20;
int children = 100;
int mutationRate = 0.05;
int redoTests = 16;

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

    qDebug() << "Initializing";
    for(int i = 1; i <= population; ++i)
    {
        qDebug() << "\tGene " << i;
        Gene g(mutationRate);
        int score = 0;
        g.saveFiles();
#pragma omp parallel for schedule(dynamic) reduction(+:score)
        for(int test = 0; test < scenatios.size(); ++test)
        {
            GetScore calc;
            calc.startTest(scenatios[test].player1, scenatios[test].player2,scenatios[test].player);
            while(calc.scoreCalculated()) {qDebug() << "Waiting";}
            score += calc.getScore();
        }
        g.saveScore(score);
        currentPopulation.append(g);

    }


    for(int round = 1; round <= rounds; ++round)
    {
        qDebug() << "Current round: " << round;

        QList<Gene> newPopulation = currentPopulation;
        for(int i = 1; i <= children; ++i)
        {
            qDebug() << "\tGene " << i;
            Gene children = currentPopulation[qrand()%population];
            children.mutate();

            int score = 0;
            children.saveFiles();
#pragma omp parallel for schedule(dynamic) reduction(+:score)
            for(int test = 0; test < scenatios.size(); ++test)
            {
                GetScore calc;
                calc.startTest(scenatios[test].player1, scenatios[test].player2,scenatios[test].player);
                while(calc.scoreCalculated()) {qDebug() << "Waiting";}
                score += calc.getScore();
            }
            children.saveScore(score);


            newPopulation.append(children);
        }


        while(newPopulation.size() > population && newPopulation.size() >= 2)
        {
            Gene g1 = newPopulation.takeAt(qrand()%newPopulation.size());
            Gene g2 = newPopulation.takeAt(qrand()%newPopulation.size());

            if(g1.getScore() > g2.getScore())
            {
                newPopulation.append(g1);
            }
            else
            {
                newPopulation.append(g2);
            }
        }

        qSort(newPopulation);
        currentPopulation = newPopulation;

        qDebug() << "++++++++++\nBest score: " << currentPopulation[0].getScore() << "\n++++++++++\n";
        currentPopulation[0].saveFiles("./inputToHidden1.endOfRound.txt", "./hidden1ToHidden2.endOfRound.txt", "./hidden2ToOutput.endOfRound.txt");
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
