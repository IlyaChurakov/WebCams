#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Добавление/Редактирование");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setName(const std::string lName)
{
    ui->Name->setText(QString::fromStdString(lName));
}

std::string Dialog::getName() const
{
    return ui->Name->text().toStdString();
}

void Dialog::setConstrType(const TrackBall::constructType lCT)
{
    if(lCT == 1)
    {
        ui->rdMidlle->setChecked(true);
        ui->rdSide->setChecked(false);
    }
    else if(lCT == 2)
    {
        ui->rdMidlle->setChecked(false);
        ui->rdSide->setChecked(true);
    }
}

TrackBall::constructType Dialog::getConstrType() const
{
    if(ui->rdMidlle->isChecked())
        return TrackBall::midlle_ball;
    else if(ui->rdSide->isChecked())
        return TrackBall::side_ball;
}

void Dialog::setMfact(const TrackBall::manufacturer lMfact)
{
    if(lMfact == 1)
    {
        ui->rdCubase->setChecked(true);
        ui->rdPro->setChecked(false);
        ui->rdLogic->setChecked(false);
        ui->rdStudio->setChecked(false);
    }
    else if(lMfact == 2)
    {
        ui->rdCubase->setChecked(false);
        ui->rdPro->setChecked(true);
        ui->rdLogic->setChecked(false);
        ui->rdStudio->setChecked(false);
    }
    else if(lMfact == 3)
    {
        ui->rdCubase->setChecked(false);
        ui->rdPro->setChecked(false);
        ui->rdLogic->setChecked(true);
        ui->rdStudio->setChecked(false);
    }
    else if(lMfact == 4)
    {
        ui->rdCubase->setChecked(false);
        ui->rdPro->setChecked(false);
        ui->rdLogic->setChecked(false);
        ui->rdStudio->setChecked(true);
    }
}

TrackBall::manufacturer Dialog::getMfact() const
{
    if(ui->rdCubase->isChecked())
        return TrackBall::Cubase;
    else if(ui->rdPro->isChecked())
        return TrackBall::Pro_Tools;
    else if(ui->rdLogic->isChecked())
        return TrackBall::Logic;
    else if(ui->rdStudio->isChecked())
        return TrackBall::Studio_One;
}

void Dialog::setSens(const int lSens)
{
    ui->Sens->setText(QString::number(lSens));
}

int Dialog::getSens() const
{
    return ui->Sens->text().toInt();
}

void Dialog::setButtons(const int lBtns)
{
    ui->btnAm->setText(QString::number(lBtns));
}

int Dialog::getButtons() const
{
    return ui->btnAm->text().toInt();
}

void Dialog::setWireless(const bool lWire)
{
    if(lWire)
    {
        ui->rdYes->setChecked(true);
        ui->rdNo->setChecked(false);
    }
    else
    {
        ui->rdYes->setChecked(false);
        ui->rdNo->setChecked(true);
    }
}

bool Dialog::getWireless() const
{
    if(ui->rdYes->isChecked())
        return 1;
    else if(ui->rdNo->isChecked())
        return 0;
}
