#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    void set_Weigth(double weight);
    double weight()const { return m_weight;};

private:
    double m_weight = 0.0;

    signals:
             void weightChanged();
};

#endif // PERSON_H
