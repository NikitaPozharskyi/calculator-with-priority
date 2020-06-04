#include "mainwindow.h"
#include "calculate.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)

{
    setStyleSheet("background-color: #1F1F1F;");
    setWindowTitle("Калькулятор");
    priority ={{"+",1}, {"-",1}, {"*",2}, {"/",2}, {"^",3}, {"√",3}};
//    qDebug()<<priority.keys(1);
    bracketCounter = 0;
    display = new QLineEdit();
    display->setText("0");
    display->setMinimumSize(150,30);
    display->setStyleSheet(QString("QLineEdit{ color:white;"
                                   "font-size:30px;"
                                   "border-style: solid;"
                                   "border-color: #1F1F1F;}"));


    display->setEnabled(false);
//    qDebug()<<priority;

    QChar aButtons[4][3] ={
        {'7','8','9'},
        {'4','5','6'},
        {'1','2','3'},
        {'.','0','='}
                        };
    //Layout setup
    QGridLayout* mainLay = new QGridLayout();
    mainLay->addWidget(display,0,0,1,4);
    mainLay->addWidget(createButton("CE","color:white;"),1,0);
    mainLay->addWidget(createButton("(", "color:white;"),1,1);
    mainLay->addWidget(createButton(")", "color:white;"),1,2);
    mainLay->addWidget(createButton("<-","color:white;"),1,3);
    mainLay->addWidget(createButton("√", "color:white;"),2,0);
    mainLay->addWidget(createButton("^", "color:white;"),2,1);
    mainLay->addWidget(createButton("/", "color:white;"),3,3);
    mainLay->addWidget(createButton("*", "color:white;"),4,3);
    mainLay->addWidget(createButton("-", "color:white;"),5,3);
    mainLay->addWidget(createButton("+", "color:white;"),6,3);
    for(int i =0;i<4;i++)
        for(int j =0;j<3;j++)
            mainLay->addWidget(createButton(aButtons[i][j],"background-color:black;"
                                                           "color:white;"),i+3,j);
     setLayout(mainLay);
}

MainWindow::~MainWindow()
{
}
QPushButton* MainWindow::createButton(const QString &str, const QString& styleSheet){
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40,40);
    pcmd->setStyleSheet(styleSheet);
    connect(pcmd,SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;

}
QPushButton* MainWindow::createButton(const QString &str){
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40,40);
    connect(pcmd,SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}
void MainWindow::slotButtonClicked(){
    QString str = ((QPushButton*) sender()) ->text();

    if(str == "CE"){
        symbolStack.clear();
        numberStack.clear();
        strDisplay="";
        bracketCounter = 0;
        display->setText("0");
        return;
    }
    if(str == "(" || str == ")"){
        strDisplay+=str;
        display->setText(strDisplay);
        bracketCounter++;
    }
    if(str == "+" || str == "-" || str == "*" || str == "/" || str == "^" || str == "√"){
        strDisplay+=str;
        display->setText(strDisplay);
    }
    if(str == "<-"){
        if(strDisplay.isEmpty()) strDisplay="0";
        if(strDisplay != "0"){
        strDisplay.chop(1);
        display->setText(strDisplay);
        } else display->setText(strDisplay);

    }
    if(str.contains(QRegExp("[0-9]"))){
        strDisplay+=str;
       display->setText(strDisplay);
    } else if(str == "."){
        strDisplay += str;
        display->setText(strDisplay);
    }
    if(str == "="){
        calculate(strDisplay);
    }
//    if(str == "^"){
//        strDisplay+=str;
//        display->setText(strDisplay);
//    }
}
void MainWindow::calculate(QString str){
    strDisplay="";
    double result=0;
    if(bracketCounter%2 != 0){
        strDisplay ="ERROR";
        display->setText(strDisplay);
    }
    else{
    for(int i=0;i<str.size();i++){
        QString number;

        //Number setup
        if(str[i].isDigit() || str[i] =='-' && i == 0 || str[i]=='-' && !(str[i-1].isDigit()))
        {
            if(str[i]=='-'){
                number+=str[i];
                i++;
            }
            while(str[i].isDigit() || str[i] == '.'){
            number+=str[i];
            i++;
            }
             numberStack.push(number.toDouble());

        }
        //Symbol setup

        if(str[i] == '+'||str[i] == '-'||
           str[i] == '*'||str[i] == '/'||
           str[i] == '^'||str[i] == "√") {
           if(symbolStack.isEmpty())
            symbolStack.push(str[i]);
            else{
               int presentPrior = searchPrior(symbolStack[symbolStack.size()-1],priority);
               int currentPrior = searchPrior(str[i],priority);

                if(currentPrior > presentPrior){
                    symbolStack.push(str[i]);
                }
                else if (currentPrior<presentPrior && !(numberStack.isEmpty()) || currentPrior == presentPrior && !(numberStack.isEmpty())){
                    QChar ch =symbolStack.pop();
                    numberStack.push(lvl3(ch,numberStack.pop(),numberStack.pop()));
                    symbolStack.push(str[i]);
                }
            }
        }
        else if(str[i] == '('||str[i] == ')'){
            if(str[i] == '('){

            symbolStack.push(str[i]);
            bracketCounter--;
            } else {
                bracketCounter--;
                QChar ch = symbolStack.pop(); // when ')'
                while(ch != '('){
                    double second =numberStack.pop() , first = numberStack.pop();
                     numberStack.push(var(ch, second, first));
                     ch = symbolStack.pop();
                }
//                qDebug()<<symbolStack;
//                qDebug()<<numberStack;

            }
        }

    }


    for(int i =0;i<=symbolStack.size();i++){
        QChar ch =symbolStack.pop();
       numberStack.push_front(lvl4(ch,numberStack.takeFirst(),numberStack.takeFirst()));
    }
//    qDebug()<<symbolStack;
//    qDebug()<<numberStack;
    }

    // result setup
    result = numberStack.pop();
    strDisplay.setNum(result);
    display->setText(strDisplay);
}

