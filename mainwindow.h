#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLCDNumber>
#include "calculate.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* createButton(const QString &str);
    QPushButton* createButton(const QString &str, const QString& styleSheet);
    void calculate(QString str);

public slots:
    void slotButtonClicked();

private:
    QLineEdit* display;
    QStack<QChar>symbolStack;
    QStack<double> numberStack;
    QString strDisplay;
    int bracketCounter;
    QMap<QString,int> priority;


};
#endif // MAINWINDOW_H
