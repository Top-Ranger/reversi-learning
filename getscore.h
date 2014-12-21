#ifndef GETSCORE_H
#define GETSCORE_H

#include <QObject>
#include <QString>
#include "reversi/core/gamemaster.h"

class GetScore : public QObject
{
    Q_OBJECT
public:
    explicit GetScore(QObject *parent = 0);
    void startTest(QString player1, QString player2, int player);
    bool scoreCalculated();
    int getScore();

signals:

public slots:
    void result(int player1, int player2);

private:
    bool _finished;
    Gamemaster _master;
    int _player;
    int _score;
};

#endif // GETSCORE_H
