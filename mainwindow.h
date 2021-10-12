#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlotArea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_boxA_valueChanged(double arg1);
    void on_boxX0_valueChanged(double arg1);
    void on_boxY0_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    PlotArea* area;
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent * e);

};
#endif // MAINWINDOW_H
