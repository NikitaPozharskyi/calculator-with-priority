#ifndef CALCULATE_H
#define CALCULATE_H
#include <QWidget>
#include <QMap>
#include <math.h>

double lvl4(QChar & ch, double second, double first);
double lvl3(QChar & ch, double second, double first);
int searchPrior(QChar ch, QMap<QString,int> priority);
double var(QChar ch, double second, double first);
double getNumber(int& k, QString expr);
//QChar getOperation(int& k, QString first, QString second);

#endif // CALCULATE_H
