#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>



namespace Ui {
class MainWindow;

}
class myWidget;
class myTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class myTimer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalScrollBar_sliderMoved(int position);

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
    myTimer* timer;



};

class myWidget : public QWidget {
public:
    myWidget(QWidget* parent);
    void setXOffset(int n);
    void incrementX(int n);
protected:
    void paintEvent(QPaintEvent*);
private:
    QPoint offset;
};

class myTimer : public QTimer {
public:
    myTimer(MainWindow* mw);
protected:
    void timerEvent(QTimerEvent* e);
private:
    MainWindow* app_;
};

#endif // MAINWINDOW_H
