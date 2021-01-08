#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Viewport/viewport.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Viewport *viewport, QWidget *parent = nullptr);
    ~MainWindow();

private:
//    Ui::MainWindow *ui;
    Viewport *m_viewport;
};
#endif // MAINWINDOW_H
