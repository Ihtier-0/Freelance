#include "mainwindow.h"

MainWindow::MainWindow(airportTable *a_table, QWidget *parent)
    : QMainWindow(parent), m_table(a_table)
{
    this->setCentralWidget(m_table);
}

MainWindow::~MainWindow()
{
}

