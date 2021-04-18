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
    ui->leL1->setText("270");
    ui->leVo->setText("0");

    ui->leRes->setReadOnly(true);
    ui->leC1->setReadOnly(true);
    ui->leC2->setReadOnly(true);
    ui->leL2->setReadOnly(true);

    ui->calc->setFocus();

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
    double l1 = ui->leL1->text().toDouble() * 1e-6;
    double vo = ui->leVo->text().toDouble();

    double res = (std::pow(vcc-vo, 2)/pow)*0.576801*(1.001245-(0.451759/quality)-(0.402444)/std::pow(quality, 2));
    double c1 = (1/(34.2219*freq*res))*(0.99866+(0.91424/quality)-(1.03175/std::pow(quality, 2)))+(0.6/(std::pow(2*M_PI*freq, 2)*l1));
    double c2 = (1/(2*M_PI*freq*res))*(1/(quality-0.104823))*(1.00121+1.01468/(quality-1.7879))-0.2/(std::pow(2*M_PI*freq, 2)*l1);
    double l2 = (quality*res)/(2*M_PI*freq);

    ui->leRes->setText(QString{"%1"}.arg(res, 4 ));
    ui->leC1->setText(QString{"%1"}.arg(c1*1e12, 4 ));
    ui->leC2->setText(QString{"%1"}.arg(c2*1e12, 4 ));
    ui->leL2->setText(QString{"%1"}.arg(l2*1e6, 4 ));

}
