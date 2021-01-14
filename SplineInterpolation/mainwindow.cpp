#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Viewport *viewport, QWidget *parent)
    : QMainWindow(parent), m_viewport(viewport)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);

    setCentralWidget(m_viewport);

    this->setFocusPolicy(Qt::NoFocus);
    m_viewport->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
//    delete ui;
}
