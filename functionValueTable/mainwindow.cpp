#include "mainwindow.h"

#include <QtDebug>
#include <QMenu>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(functionValueTable *a_table, QWidget *parent)
    : QMainWindow(parent), m_table(a_table)
{
    this->setCentralWidget(m_table);

    setSize();

    QMenu *valueMenu = new QMenu("value");
    valueMenu->addAction("input value", this, &MainWindow::changeValues);
    menuBar()->addMenu(valueMenu);
}

void MainWindow::setSize()
{

    quint64 firstColWidth = m_table->columnWidth(0),
            secondColWidth = m_table->columnWidth(1);

    this->setFixedWidth(firstColWidth + secondColWidth + 70);
}

void MainWindow::changeValues()
{
    qreal begin = QInputDialog::getDouble(this, tr("input"), tr("begin: "), 0, -2147483647, 2147483647, 10);
    qreal end = QInputDialog::getDouble(this, tr("input"), tr("end: "), 0, -2147483647, 2147483647, 10);
    qreal step = QInputDialog::getDouble(this, tr("input"), tr("step: "), 0, -2147483647, 2147483647, 10);

    if(begin > end)
    {
        QMessageBox::critical(this, "error", "the begin is greater than end");
        return;
    }

    if(step <= 0)
    {
        QMessageBox::critical(this, "error", "step less than or equal to 0");
        return;
    }

    m_table->setBegin(begin);
    m_table->setEnd(end);
    m_table->setStep(step);

    m_table->fillTable();
    m_table->setSize();

    setSize();
}

