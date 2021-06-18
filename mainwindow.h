#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QTranslator>
#include "trackball.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int count = 0;
private slots:
    void on_pushOpen_clicked();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_action_Add_triggered();

    void on_action_Edit_triggered();

    void on_action_Delete_triggered();

    void on_action_About_triggered();

    void on_action_Exit_triggered();

//    void on_actionRus_triggered();

//    void on_actionEng_triggered();

private:
    Ui::MainWindow *ui;

    enum Headers
    {
        name = 0, constr, mfact, sensativity, btns, wireless
    };

    std::string FileName;

    bool Open;

    const int _Amount = 6;

    struct TrackBallSt
    {
        TrackBall Element;

        TrackBallSt *next, *prev;
    }*Last;

    TrackBallSt *TBStr;

    void readFromFile(std::string, TrackBallSt*);
    void newRow(TrackBallSt*, int);
    void reWriteRow(TrackBallSt*, int);
    void deleteRow(int);
    bool fileCheck();

//    QTranslator *translator;

//    void changeTr(QString postfix);
//    void changeEvent(QEvent *event);


};
#endif // MAINWINDOW_H
