#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = new PlotArea(ui->plotArea);

    ui->boxA->setValue(1.0);
    ui->boxX0->setValue(0.2);
    ui->boxY0->setValue(0.2);

    area->setLabel(ui->mousePos);
    area->setbA(ui->boxA);
    area->setbX0(ui->boxX0);
    area->setbY0(ui->boxY0);

    area->repaint();
    ui->mousePos->raise();
    ui->mousePos->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boxA_valueChanged(double arg1)
{
    area->setA(arg1);
    area->repaint();
}

void MainWindow::on_boxX0_valueChanged(double arg1)
{
    area->setX0(arg1);
    area->repaint();
}

void MainWindow::on_boxY0_valueChanged(double arg1)
{
    area->setY0(arg1);
    area->repaint();
}

void MainWindow::mousePressEvent(QMouseEvent* e)
{
    switch(e->button())
    {
    case Qt::LeftButton:
    {
        area->isRelocating = !area->isRelocating;
        break;
    }
    default:
        QWidget::mousePressEvent(e);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Space:
    {
        area->isRelocating = !area->isRelocating;
        break;
    }
    default:
        QWidget::keyPressEvent(e);
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if(e->angleDelta().y() > 0)
        area->zoomIn();
    else area->zoomOut();
}

