#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toggleStateCheck_toggled(bool checked)
{
    ui->LEDWidget1->setState(checked);
}

void MainWindow::on_startButton_clicked()
{
    ui->LEDWidget2->setFlashRate(ui->rateSpinBox->value());
    ui->LEDWidget2->startFlashing();
}

void MainWindow::on_stopButton_clicked()
{
    ui->LEDWidget2->stopFlashing();
}
