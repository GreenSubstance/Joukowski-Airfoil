#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QtMath>
#include <complex.h>
#include <math.h>
#include <QMouseEvent>
#include <QLabel>
#include <QDoubleSpinBox>

class PlotArea : public QWidget
{
public:
    explicit PlotArea(QWidget *parent = 0);
    virtual ~PlotArea() {};
    void setA(double A);
    void setX0(double X0);
    void setY0(double Y0);
    void setLabel(QLabel* label);
    void setbA(QDoubleSpinBox* box);
    void setbX0(QDoubleSpinBox* box);
    void setbY0(QDoubleSpinBox* box);
    double getMouseX();
    double getMouseY();
    bool isRelocating;
    void zoomIn();
    void zoomOut();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void drawAxis(QPainter *painter);
    void drawJTransformation(QPainter *painter);
    void drawJAirfoil(QPainter *painter);

    inline QPoint PlotToScreen (QPoint plPoint);

private:
    QLabel* labelMousePos;
    QDoubleSpinBox* bA;
    QDoubleSpinBox* bX0;
    QDoubleSpinBox* bY0;

    double scale = 111.;
    QSize aSize;

    QPoint mousePos;
    double mouseX;
    double mouseY;

    double a;
    double R;
    double x0;
    double y0;

    //double R, a;
    //double beta;
};

#endif // PLOTAREA_H
