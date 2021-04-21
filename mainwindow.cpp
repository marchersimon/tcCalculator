#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLocale::setDefault(QLocale("en_US"));

    ui->leFreq->setValidator(new QDoubleValidator(this));

    connect(ui->leFreq, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->leVcc, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->lePow, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->leQuality, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->leL1, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->leVo, SIGNAL(returnPressed()), ui->calc, SLOT(click()));
    connect(ui->calc, SIGNAL(returnPressed()), ui->calc, SLOT(click()));

    ui->leFreq->setText("4");
    ui->leVcc->setText("50");
    ui->lePow->setText("50");
    ui->leQuality->setText("4");
    ui->leVo->setText("0");

    ui->leRes->setReadOnly(true);
    ui->leC1->setReadOnly(true);
    ui->leC2->setReadOnly(true);
    ui->leL2->setReadOnly(true);

    ui->calc->setFocus();

    ui->leN->setText("10");
    ui->leRadius->setText("40");
    ui->leHeight->setText("17.32");
    ui->leWidth->setText("30");
    ui->leAngle->setText("30");

    ui->leL1_p->setReadOnly(true);
    ui->leL2_p->setReadOnly(true);
    ui->leL_p->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calc_clicked()
{
    double freq = ui->leFreq->text().toDouble() * 1e6;
    double vcc = ui->leVcc->text().toDouble();
    double pow = ui->lePow->text().toDouble();
    double quality = ui->leQuality->text().toDouble();
    double vo = ui->leVo->text().toDouble();

    double res = (std::pow(vcc-vo, 2)/pow)*0.576801*(1.001245-(0.451759/quality)-(0.402444)/std::pow(quality, 2));
    double l1 = 2*(std::pow(M_PI, 2)/4 + 1) * res / freq;
    double c1 = (1/(34.2219*freq*res))*(0.99866+(0.91424/quality)-(1.03175/std::pow(quality, 2)))+(0.6/(std::pow(2*M_PI*freq, 2)*l1));
    double c2 = (1/(2*M_PI*freq*res))*(1/(quality-0.104823))*(1.00121+1.01468/(quality-1.7879))-0.2/(std::pow(2*M_PI*freq, 2)*l1);
    double l2 = (quality*res)/(2*M_PI*freq);

    ui->leL1->setText(QString{"%1"}.arg(l1*1e6, 4));
    ui->leRes->setText(QString{"%1"}.arg(res, 4 ));
    ui->leC1->setText(QString{"%1"}.arg(c1*1e12, 4 ));
    ui->leC2->setText(QString{"%1"}.arg(c2*1e12, 4 ));
    ui->leL2->setText(QString{"%1"}.arg(l2*1e6, 4 ));

}

void MainWindow::on_calc_2_clicked()
{
    double numTurns = ui->leN->text().toDouble();
    double radius = ui->leRadius->text().toDouble();
    double height = ui->leHeight->text().toDouble();
    double width = ui->leWidth->text().toDouble();
    double angle = ui->leAngle->text().toDouble();

    double l1 = std::pow(numTurns*radius, 2)/(25.4*(9*radius + 10*height));
    double l2 = std::pow(numTurns*radius, 2)/(25.4*(8*radius + 11*width));
    double l = std::sqrt(std::pow(l1*std::sin(angle*M_PI/180),2) + std::pow(l2*std::cos(angle*M_PI/180),2));

    ui->leL1_p->setText(QString{"%1"}.arg(l1, 4));
    ui->leL2_p->setText(QString{"%1"}.arg(l2, 4));
    ui->leL_p->setText(QString{"%1"}.arg(l, 4));



}
