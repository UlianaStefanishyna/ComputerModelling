#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu.h"
#include "lifo.h"
#include "rr.h"
#include "sf.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_butStart_clicked(){

    int countOfTasks = ui->spBoxCount->value();
    double lambda = ui->dSpBoxLambda->value();
    double mu = ui->dSpBoxMu->value();

    if(lambda > mu)
        QMessageBox::warning(this,"Attention","Інтенсивність вхідного потоку більша ніж вихідного !!!");

    LIFO *lifo = new LIFO(lambda,mu,countOfTasks);
    RR *rr = new RR(lambda,mu,countOfTasks);
    SF *sf = new SF(lambda,mu,countOfTasks);

    rr->setGoodTau(mu);
    rr->start();
    lifo->start();
    sf->start();

    ui->coeffPower->setText(QString::number((lambda/mu)*100));

    ui->tAver_LIFO->setText(QString::number(lifo->getMx()));
    ui->tAver_RR->setText(QString::number(rr->getMx()));
    ui->tAver_SF->setText(QString::number(sf->getMx()));

    ui->Dx_LIFO->setText(QString::number(lifo->getDx()));
    ui->Dx_RR->setText(QString::number(rr->getDx()));
    ui->Dx_SF->setText(QString::number(sf->getDx()));

    ui->tReact_LIFO->setText(QString::number(lifo->timeReaction()));
    ui->tReact_RR->setText(QString::number(rr->react));
    ui->tReact_SF->setText(QString::number(sf->timeReaction()));

    ui->countComplTask_LIFO->setText(QString::number(lifo->coefDone()));
    ui->countComplTask_RR->setText(QString::number(rr->coefDone()));
    ui->countComplTask_SF->setText(QString::number(sf->coefDone()));

    delete lifo;
    delete rr;
    delete sf;
}
