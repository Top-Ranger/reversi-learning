#include <QCoreApplication>
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
