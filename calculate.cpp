#include "calculate.h"

double getNumber(int& k, QString expr){
    QString temp;
    if(expr[k]=='-'){
        temp+=expr[k];
        k++;
    }
    while(expr[k].isDigit() || expr[k] == '.'){
    temp+=expr[k];
    k++;
    }
    return temp.toDouble();
}

int searchPrior(QChar ch,QMap<QString,int> priority){
    QList<QString> keys = priority.keys();
    int currentPrior;
    for(int i=0;i<keys.size();i++){
       if(ch == keys[i])currentPrior = priority.value(keys[i]);
    }
 return currentPrior;
}
double lvl3(QChar & ch, double second, double first){
    if(ch == '^' || ch == "√"){
        if(ch == '^')
        return(var('*', second, second));

        if(ch =="√")
            return(sqrt(second));

    }else
    return(var(ch, second, first));
}
double lvl4(QChar & ch, double second, double first){
    return(var(ch, second, first));
}

double var(QChar ch, double second, double first){
    if(ch == '+')return(second + first);
    if(ch == '-')return(second - first);
    if(ch == '*')return(second * first);
    if(ch == '/')return(second / first);
}
