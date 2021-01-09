#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "functionValueTable/functionvaluetable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(functionValueTable *a_table, QWidget *parent = nullptr);
private:
    void setSize();

    functionValueTable *m_table;
protected slots:
    void changeValues();
};
#endif // MAINWINDOW_H
