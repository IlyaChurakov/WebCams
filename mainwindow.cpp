#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QEvent>

#include "qfiledialog.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <QtGui>
#include <fstream>
#include <string>
#include <iostream>
#include "dialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList Headers;
    Headers << "Название" << "Тип конструции" << "Производитель" << "Чувстивтельность" << "Количество\nкнопок" << "Беспроводное\nподключение";
    setWindowTitle("Trackball");
    ui->tableWidget->setColumnCount(_Amount);
    ui->tableWidget->setHorizontalHeaderLabels(Headers);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushOpen_clicked()
{
    QFile in;
    do{
        QString FN = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.db *.txt");
        if(FN=="") return;
        in.setFileName(FN);
        FileName = FN.toStdString();

        if(!fileCheck()){
            QMessageBox MSGBox;
            MSGBox.setWindowTitle("Ошибка");
            MSGBox.setText("Выбранный вами файл не соответствует требуемому формату!");
            MSGBox.setInformativeText("Ок - открыть другой файл\nCancel - отменить открытие файла");
            MSGBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            MSGBox.setIcon(QMessageBox::Information);
            MSGBox.setDefaultButton(QMessageBox::Ok);
            int res = MSGBox.exec();
            if (res == QMessageBox::Cancel)
                return;
        }
    }while(!fileCheck());

    Last = 0;
    TBStr = 0;

    in.open(QFile::ReadOnly);
    char a [1024];

    while(!in.atEnd()){
        in.readLine(a, sizeof(a));
        std::string str(a);

        if(str.empty())continue;

        TrackBallSt* NewSt = new TrackBallSt;

        readFromFile(str,NewSt);

        if(!TBStr){
            Last = NewSt;
            TBStr = NewSt;
            NewSt->prev = 0;
            NewSt->next = 0;
        }else {
            Last->next = NewSt;
            NewSt->prev= Last;
            NewSt->next = 0;
            Last = NewSt;
        }
        count++;
    }
    in.close();

//    CreateHeader();

    TrackBallSt* St = TBStr;
    int i=0;
    for(St=TBStr; St!=0; St=St->next, i++){
       newRow(St,i);
    }

    ui->menu_2->setEnabled(true);
    ui->action_Add->setEnabled(true);
    ui->action_Delete->setEnabled(true);
    ui->action_Edit->setEnabled(true);
    ui->action_Save->setEnabled(true);
    ui->action_Open->setEnabled(false);
    ui->pushOpen->setEnabled(false);
}

void MainWindow::readFromFile(string str, MainWindow::TrackBallSt *New)
{
    string arr[_Amount];
    int index[_Amount+1];

    index[0]=-1;
    int j = 1;
    for(int i=0; i < (int)str.length();i++)
    {
        if(str[i] == ';')
        {
            index[j]=i;
            j++;
        }
    }

    for(int i=0;i<_Amount;i++)
    {
        arr[i] = str.substr(index[i]+1, index[i+1]-index[i]-1);
    }

    New->Element.setTrackballName(arr[0]);
    switch (stoi(arr[1]))
    {
    case 1: New->Element.setConstructType(TrackBall::midlle_ball);
        break;
    case 2: New->Element.setConstructType(TrackBall::side_ball);
        break;
    }
    switch (stoi(arr[2]))
    {
    case 1: New->Element.setmfact(TrackBall::Cubase);
        break;
    case 2: New->Element.setmfact(TrackBall::Pro_Tools);
        break;
    case 3: New->Element.setmfact(TrackBall::Logic);
        break;
    case 4: New->Element.setmfact(TrackBall::Studio_One);
        break;
    }
    New->Element.setSensitivity(stoi(arr[3]));
    New->Element.setWireless(stoi(arr[4]));
    New->Element.setButtons(stoi(arr[5]));
}

void MainWindow::newRow(MainWindow::TrackBallSt * St, int i)
{
    const char* strConstr[]={"Undefined", "Midlle Ball", "Side Ball"};
    const char* strMfact[]={"Undefined", "Cubase", "Pro Tools", "Logic", "Studio One"};

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

    QTableWidgetItem *NewEl[_Amount];

    NewEl[0] = new QTableWidgetItem(QString::fromStdString(St->Element.getTrackballName()));
    NewEl[1] = new QTableWidgetItem(strConstr[St->Element.getConstructType()]);
    NewEl[2] = new QTableWidgetItem(strMfact[St->Element.getmfact()]);
    NewEl[3] = new QTableWidgetItem(QString::number(St->Element.getSensitivity()));
    NewEl[4] = new QTableWidgetItem(QString::number(St->Element.getButtons()));

    if(St->Element.getWireless())
        NewEl[5] = new QTableWidgetItem(QString::fromStdString("Есть"));
    else
        NewEl[5] = new QTableWidgetItem(QString::fromStdString("Нет"));


    ui->tableWidget->setItem(i, name, NewEl[0]);
    ui->tableWidget->setItem(i, constr, NewEl[1]);
    ui->tableWidget->setItem(i, mfact, NewEl[2]);
    ui->tableWidget->setItem(i, sensativity, NewEl[3]);
    ui->tableWidget->setItem(i, btns, NewEl[4]);
    ui->tableWidget->setItem(i, wireless, NewEl[5]);
}

void MainWindow::reWriteRow(MainWindow::TrackBallSt *St, int i)
{
    const char* strConstr[]={"Undefined", "Midlle Ball", "Side Ball"};
    const char* strMfact[]={"Undefined", "Cubase", "Pro Tools", "Logic", "Studio One"};

    QTableWidgetItem *NewEl[_Amount];

    NewEl[0] = new QTableWidgetItem(QString::fromStdString(St->Element.getTrackballName()));
    NewEl[1] = new QTableWidgetItem(strConstr[St->Element.getConstructType()]);
    NewEl[2] = new QTableWidgetItem(strMfact[St->Element.getmfact()]);
    NewEl[3] = new QTableWidgetItem(QString::number(St->Element.getSensitivity()));
    NewEl[4] = new QTableWidgetItem(QString::number(St->Element.getButtons()));

    if(St->Element.getWireless())
        NewEl[5] = new QTableWidgetItem(QString::fromStdString("Есть"));
    else
        NewEl[5] = new QTableWidgetItem(QString::fromStdString("Нет"));


    ui->tableWidget->setItem(i, name, NewEl[0]);
    ui->tableWidget->setItem(i, constr, NewEl[1]);
    ui->tableWidget->setItem(i, mfact, NewEl[2]);
    ui->tableWidget->setItem(i, sensativity, NewEl[3]);
    ui->tableWidget->setItem(i, btns, NewEl[4]);
    ui->tableWidget->setItem(i, wireless, NewEl[5]);
}

void MainWindow::deleteRow(int i)
{
    ui->tableWidget->removeRow(i);
}

bool MainWindow::fileCheck()
{
    QString  FN = QString::fromStdString(FileName);
    QFile in(FN);
    FileName = FN.toStdString();

    in.open(QFile::ReadOnly);
    char a [1024];
    TrackBallSt* New = new TrackBallSt;

    while(!in.atEnd()){
        in.readLine(a, sizeof(a));
        std::string str(a);

        if(str.empty())continue;

        try{
            readFromFile(str,New);
        }
        catch(...){
            in.close();
            return (false);
        }
    }
    in.close();
    return (true);
}

//void MainWindow::changeTr(QString postfix)
//{
//    QApplication::removeTranslator(translator);
//    translator = new QTranslator(this);

//    translator->load(QApplication::applicationName() + "_" + postfix);

//    QApplication::installTranslator(translator);
//}

//void MainWindow::changeEvent(QEvent *event)
//{
//    if(event->type() == QEvent::LanguageChange)
//    {
//        setWindowTitle(tr("TrackBall"));
//        ui->action_About->setText(tr("О программе"));
//    }
//    else
//    {
//        QMainWindow::changeEvent(event);
//    }
//}

void MainWindow::on_action_Open_triggered()
{
    on_pushOpen_clicked();
}

void MainWindow::on_action_Save_triggered()
{
    fstream out(FileName, ios_base::out);
    TrackBallSt* Curr;
    for(Curr = TBStr; Curr != 0; Curr = Curr->next)
    {
        out << Curr->Element.getTrackballName() << ";"
            << Curr->Element.getConstructType() << ";"
            << Curr->Element.getmfact() << ";"
            << Curr->Element.getSensitivity() << ";"
            << Curr->Element.getButtons() << ";"
            << Curr->Element.getWireless() << ";"
            << endl;
    }
    out.close();
}

void MainWindow::on_action_Add_triggered()
{
    Dialog D;
    D.exec();
    if(D.result() == Dialog::Rejected)
        return;

    TrackBallSt* NewElem = new TrackBallSt;
    NewElem->Element.setTrackballName(D.getName());
    NewElem->Element.setConstructType(D.getConstrType());
    NewElem->Element.setmfact(D.getMfact());
    NewElem->Element.setSensitivity(D.getSens());
    NewElem->Element.setButtons(D.getButtons());
    NewElem->Element.setWireless(D.getWireless());


    if(!TBStr)
    {
        Last = NewElem;
        TBStr = NewElem;
        NewElem->next = 0;
        NewElem->prev = 0;
    }
    else
    {
        Last->next = NewElem;
        NewElem->prev = Last;
        NewElem->next = 0;
        Last = NewElem;
    }
    count++;

    newRow(NewElem,ui->tableWidget->rowCount());
}

void MainWindow::on_action_Edit_triggered()
{
    Dialog D;
    bool check;
    int j;
    int numOfEl = QInputDialog::getInt(this, QString::fromUtf8("Редактирование"), QString::fromStdString("Выберите строку:"), 1, 1, _Amount, 1, &check) - 1;

    if(!check)
        return;

    TrackBallSt* N= TBStr;
    for(j = 0; j < numOfEl; j++)
        N= N->next;

    D.setName(N->Element.getTrackballName());
    D.setConstrType(N->Element.getConstructType());
    D.setMfact(N->Element.getmfact());
    D.setSens(N->Element.getSensitivity());
    D.setButtons(N->Element.getButtons());
    D.setWireless(N->Element.getWireless());

    D.exec();

    N->Element.setTrackballName(D.getName());
    N->Element.setConstructType(D.getConstrType());
    N->Element.setmfact(D.getMfact());
    N->Element.setSensitivity(D.getSens());
    N->Element.setButtons(D.getButtons());
    N->Element.setWireless(D.getWireless());

    reWriteRow(N, numOfEl);
}

void MainWindow::on_action_Delete_triggered()
{
    bool check;
    int j;
    int numOfEl = QInputDialog::getInt(this, QString::fromUtf8("Удаление"), QString::fromStdString("Выберите строку:"), 1, 1, _Amount, 1, &check) - 1;

    if(!check)
        return;
    TrackBallSt* N = TBStr;

    for(j=0;j<numOfEl;j++)
        N=N->next;

    if(N->next)
        N->next->prev = N->prev;
    else
        Last = N->prev;

    if(N->prev)
        N->prev->next = N->next;
    else
        TBStr = N->next;


    N->~TrackBallSt();
    count--;

    deleteRow(numOfEl);
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox MSGBox;
    MSGBox.setWindowTitle("О программе");
    MSGBox.setText("Илья Чураков ЭУИС 2-4");
    MSGBox.setStandardButtons(QMessageBox::Ok );
    MSGBox.setIcon(QMessageBox::Information);
    MSGBox.setDefaultButton(QMessageBox::Ok);
    int res = MSGBox.exec();
    if (res == QMessageBox::Ok)
        return;
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

//void MainWindow::on_actionRus_triggered()
//{
//    changeTr("ru");
//}

//void MainWindow::on_actionEng_triggered()
//{
//    changeTr("ru");
//}
