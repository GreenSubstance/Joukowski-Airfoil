#include "PlotArea.h"

PlotArea::PlotArea(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    aSize = parent->size();
    this->resize(aSize);
    isRelocating = 0;

    a = 1; x0 = -0.2; y0 = -0.2;
}

void PlotArea::setA(double A)
{
    a = A;
}

void PlotArea::setX0(double X0)
{
    x0 = X0;
}

void PlotArea::setY0(double Y0)
{
    y0 = Y0;
}


void PlotArea::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    drawAxis(&painter);
    drawJAirfoil(&painter);
}


QPoint PlotArea::PlotToScreen (QPoint plPoint)
{
    QPoint scPoint(plPoint.x() + aSize.width()/2, -plPoint.y() + aSize.height()/2);
    return scPoint;
}

void PlotArea::mouseMoveEvent(QMouseEvent *e)
{
    mousePos = e->pos();
    mouseX = (mousePos.x() - width()/2)/scale;
    mouseY = -(mousePos.y() - height()/2)/scale;
    labelMousePos->setText("x: " + QString::number(mouseX) + "\ny: " + QString::number(mouseY));
    if(isRelocating)
    {
        bX0->setValue(mouseX);
        bY0->setValue(mouseY);
        x0 = mouseX;
        y0 = mouseY;
        repaint();
    }
}

double PlotArea::getMouseX()
{
    return mouseX;
}

double PlotArea::getMouseY()
{
    return mouseY;
}

void PlotArea::zoomIn()
{
    scale *= 1.1;
    repaint();
}

void PlotArea::zoomOut()
{
    scale *= 0.9;
    repaint();
}

void PlotArea::setLabel(QLabel *label)
{
    labelMousePos = label;
}

void PlotArea::setbA(QDoubleSpinBox *box)
{
    bA = box;
}

void PlotArea::setbX0(QDoubleSpinBox *box)
{
    bX0 = box;
}

void PlotArea::setbY0(QDoubleSpinBox *box)
{
    bY0 = box;
}


void PlotArea::drawAxis(QPainter *painter)
{
    double penWidth = 2.;
    double halfDashLen = 10.;

    QPen pen(Qt::white, penWidth, Qt::SolidLine);
    painter->setPen(pen);

    //Border
    painter->drawRect(0, 0, aSize.width(), aSize.height());

    //Axis
    painter->drawLine(width()/2, 0, width()/2, height());
    painter->drawLine(0, height()/2, width(), height()/2);

    //Dashes
    QPen penDashes(Qt::white, penWidth/2, Qt::SolidLine);
    painter->setPen(penDashes);
    for (short int i = -(width()/2)/scale; i < (width()/2)/scale; i++)
    {
        int dashX = i*scale + width()/2;
        int dashY = height()/2 - i*scale;
        painter->drawLine(dashX, height()/2 - halfDashLen, dashX, height()/2 + halfDashLen);
        painter->drawLine(width()/2 - halfDashLen, dashY, width()/2 + halfDashLen, dashY);
    }
}

void PlotArea::drawJAirfoil(QPainter *painter)
{
    QColor grey(105, 105, 105);
    QPen pen(grey, 2, Qt::DashLine);
    painter->setPen(pen);
    int k = scale;

    R = sqrt((abs(x0) + a)*(abs(x0) + a) + y0*y0);
    std::complex<double> c(x0, y0);

    //Center of circ
    QPoint center(x0*k, y0*k);
    QPoint t1(0, y0*k); QPoint t2(x0*k, 0);
    painter->drawLine(PlotToScreen(t1), PlotToScreen(center));
    painter->drawLine(PlotToScreen(t2), PlotToScreen(center));

    //Drawing plot
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    for (double f = 0.; f < 2*M_PI; )
    {
        std::complex<double> z(cos(f), sin(f)); //Circ
        z *= R;
        z += c;
        QPoint cP1(real(z)*k, imag(z)*k);
        std::complex<double> w = z + a*a/z;     //Airfoil
        QPoint aP1(real(w)*k, imag(w)*k);

        f += 0.01;
        z.real(cos(f)); z.imag(sin(f));         //Circ
        z *= R;
        z += c;
        QPoint cP2(real(z)*k, imag(z)*k);
        w = z + a*a/z;                          //Airfoil
        QPoint aP2(real(w)*k, imag(w)*k);

        //Circumference
        pen.setColor(grey);
        painter->setPen(pen);
        painter->drawLine(PlotToScreen(cP1), PlotToScreen(cP2));
        //Airfoil
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawLine(PlotToScreen(aP1), PlotToScreen(aP2));
    }
}


