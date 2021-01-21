#include "mainwindow.h"

MainWindow::MainWindow(Viewport *a_viewport, QWidget *parent)
    : QMainWindow(parent), m_viewport(a_viewport)
{
    setCentralWidget(m_viewport);

    this->setFocusPolicy(Qt::NoFocus);
    m_viewport->setFocusPolicy(Qt::StrongFocus);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, m_viewport, &Viewport::animate);
    m_timer->start(500);
}

MainWindow::~MainWindow()
{
}

