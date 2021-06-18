#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "trackball.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setName(const std::string);
    std::string getName() const;

    void setConstrType(const TrackBall::constructType);
    TrackBall::constructType getConstrType() const;

    void setMfact(const TrackBall::manufacturer);
    TrackBall::manufacturer getMfact() const;

    void setSens(const int);
    int getSens() const;

    void setButtons(const int);
    int getButtons() const;

    void setWireless(const bool);
    bool getWireless() const;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
