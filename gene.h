#ifndef GENE_H
#define GENE_H

#include <QList>

class Gene
{
public:
    Gene(float mutationRate);
    void mutate();
    void saveScore(int score);
    void saveFiles();
    bool operator<(const Gene &other) const;
    int getScore();

private:
    QList<float> _inputToHidden;
    QList<float> _hiddenToOutput;
    float _mutationRate;
    int _score;

    static const int _sizeHidden = 64;
};

#endif // GENE_H
