#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Viewport/viewport.h"
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Viewport *a_viewport, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Viewport* m_viewport;
    QTimer* m_timer;

};
#endif // MAINWINDOW_H
