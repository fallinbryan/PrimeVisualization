#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

//bool isPrime(int n) {
//    if(n==1) return false;
//    if(n==2) return true;
//    for(int i = 2; i < n; i++) {
//        int result = n%i;
//        //qDebug() << i << "%" << n << "=" << result;
//        if(n % i == 0) return false;
//    }
//    return true;
//}

bool isPrime(unsigned int n)
{
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0) return false;

    const unsigned int iMax = (int)sqrt(n) + 1;
    unsigned int i;
    for (i = 3; i <= iMax; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new myTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;

}



myWidget::myWidget(QWidget* parent)
{
    this->setParent(parent);
    offset.rx() = offset.ry() = 0;
}

void myWidget::setXOffset(int n)
{
    offset.rx() = n;
}

void myWidget::incrementX(int n)
{
    offset.rx() += n;
}


void myWidget::paintEvent(QPaintEvent *)
{
    QPixmap map(this->geometry().right(),this->geometry().bottom());
    unsigned int grayscale = 0x000000;
    unsigned int redscale = 0xff0000;
    QPainter paint(&map);
    QBrush brush(paint.brush());
    QPen red_pen(paint.pen());
    QPen green_pen(paint.pen());
    QPen grayScale_pen(paint.pen());
    red_pen.setColor(QColor(redscale));
    green_pen.setColor(Qt::green);
    grayScale_pen.setColor(QColor(grayscale));

    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    //paint.drawRect(this->geometry());
    brush.setColor(Qt::black);
    paint.setBrush(brush);

    for(int x = 1 + offset.x(); x < this->geometry().right()+ offset.x(); x++) {


        if (isPrime(x) ) {
             grayscale = 0x000000;
            //grayscale = 0xbfb137;
            paint.setPen(grayscale);
            paint.drawLine(x- offset.x(),0/*this->geometry().bottom()/2*/,x- offset.x(),this->geometry().bottom());
            //grayscale = 0x000000;
        }else {
            //grayscale += 0x111111;
            grayscale += 0x000011;
            //qDebug() << grayscale;
            paint.setPen(grayscale);
            paint.drawLine(x- offset.x(),0/*this->geometry().bottom()/2*/,x- offset.x(),this->geometry().bottom());
        }
    }
//    for(int y = 1; y < this->geometry().bottom(); y++) {
//        for(int x = 1+ offset.x(); x < this->geometry().right()+ offset.x(); x++) {

//            if( x % y == 0 ) {
//                // qDebug() << "found Prime " << x << y;
//                redscale = 0xff0000;
//                red_pen.setColor(QColor(redscale));
//                paint.setPen(red_pen);
//                paint.drawPoint(x- offset.x(),y);
//            } else {
////                redscale -= (x%y) * 0x010000;
////                //redscale += (x%y) * 0x100001;
////                red_pen.setColor(QColor(redscale));
////                paint.setPen(red_pen);
////                paint.drawPoint(x- offset.x(),y);
//            }


//        }
//    }

    paint.end();
    paint.begin(this);
    paint.drawPixmap(this->geometry(),map);
    paint.end();
}

void MainWindow::on_horizontalScrollBar_sliderMoved(int position)
{
    ui->drawOnMe->setXOffset(position);
    ui->drawOnMe->update();
}

void MainWindow::on_actionPlay_triggered()
{
    timer->start();

}

myTimer::myTimer(MainWindow *mw)
{
    app_ = mw;
}

void myTimer::timerEvent(QTimerEvent *e)
{
    app_->ui->drawOnMe->incrementX(20);
    app_->ui->drawOnMe->update();
}

void MainWindow::on_actionStop_triggered()
{
    timer->stop();
}
