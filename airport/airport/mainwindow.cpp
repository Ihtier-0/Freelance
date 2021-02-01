#include "mainwindow.h"

#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(airportTable *a_table, QWidget *parent)
    : QMainWindow(parent), m_table(a_table)
{
    this->setCentralWidget(m_table);

    QMenu *fileMenu = new QMenu("File");
    fileMenu->addAction("Open file", this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction("Save table", this, &MainWindow::saveTable, QKeySequence::Save);
    menuBar()->addMenu(fileMenu);

    QMenu *tableMenu = new QMenu("Table");
    tableMenu->addAction("add flight", this, &MainWindow::add);
    tableMenu->addAction("flights to the entered destination with free seats", this, &MainWindow::flightsToTheEnteredDestinationWithFreeSeats);
    tableMenu->addAction("delete all records with specific flight numbers", this, &MainWindow::deleteAllRecordsWithSpecificFlightNumbers);
    tableMenu->addAction("update the number of free seats in the cabin in the specified flight number", this,
                         &MainWindow::updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber);
    menuBar()->addMenu(tableMenu);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "");

    if (fileName.isEmpty())
    {
        return;
    }

    m_table->openFile(fileName);

    this->update();
}

void MainWindow::saveTable()
{
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Open file", "", "");

    if (fileName.isEmpty())
    {
        return;
    }

    m_table->save(fileName);
}

void MainWindow::add()
{
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    qint64 flightNumber = QInputDialog::getInt(this, tr("Input flight number"), tr("flight number:"));

    if(flightNumber <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("flight number <= 0!"));
        return;
    }

    QString destination = QInputDialog::getText(this, tr("Input destination"), tr("destination:"));

    if(destination.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("destination is empty!"));
        return;
    }
    ///
    qint64 d, mon, y, h, min;

    d = QInputDialog::getInt(this, tr("Input departure date day:"), tr("departure date day:"));

    if(d < 0 || d > 31)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure day!"));
        return;
    }

    mon = QInputDialog::getInt(this, tr("Input departure date month:"), tr("departure date month:"));

    if(mon <= 0 || mon > 12)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure month!"));
        return;
    }

    y = QInputDialog::getInt(this, tr("Input departure date year:"), tr("departure date year:"));

    if(y < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure year!"));
        return;
    }


    h = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date hour:"));

    if(h < 0 || h > 23)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure hour!"));
        return;
    }

    min = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date hour:"));

    if(h < 0 || h > 59)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure minut!"));
        return;
    }

    QDateTime departureTime(QDate(y, mon, d), QTime(h, min));

    if(!departureTime.isValid())
    {
        QMessageBox::warning(this, tr("Error"),tr("departure DateTime invalid!"));
        return;
    }
    //
    d = QInputDialog::getInt(this, tr("Input arrival date day:"), tr("arrival date day:"));

    if(d < 0 || d > 31)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong arrival day!"));
        return;
    }

    mon = QInputDialog::getInt(this, tr("Input arrival date month:"), tr("arrival date month:"));

    if(mon <= 0 || mon > 12)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong arrival month!"));
        return;
    }

    y = QInputDialog::getInt(this, tr("Input arrival date year:"), tr("arrival date year:"));

    if(y < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong arrival year!"));
        return;
    }


    h = QInputDialog::getInt(this, tr("Input arrival date hour:"), tr("arrival date hour:"));

    if(h < 0 || h > 23)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong arrival hour!"));
        return;
    }

    min = QInputDialog::getInt(this, tr("Input arrival date hour:"), tr("arrival date hour:"));

    if(h < 0 || h > 59)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong arrival minut!"));
        return;
    }

    QDateTime arrivalTime(QDate(y, mon, d), QTime(h, min));
    if(!arrivalTime.isValid())
    {
        QMessageBox::warning(this, tr("Error"),tr("arrival DateTime invalid!"));
        return;
    }

    if(arrivalTime < departureTime)
    {
        QMessageBox::warning(this, tr("Error"),tr("arrivalDateTime < departureDateTime!"));
        return;
    }

    qint64 numberFreeSeatsInCabin = QInputDialog::getInt(this, tr("Input number free seats in cabin"),
                                                         tr("number free seats in cabin:"));
    if(numberFreeSeatsInCabin < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("number free seats in cabin < 0!"));
        return;
    }

    m_table->add(Flight(flightNumber, destination, departureTime, arrivalTime, numberFreeSeatsInCabin));
}

void MainWindow::flightsToTheEnteredDestinationWithFreeSeats()
{
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    QString destination = QInputDialog::getText(this, tr("Input destination"), tr("destination:"));

    if(destination.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("destination is empty!"));
        return;
    }

    m_table->eraseIf([&](const Flight& x) -> bool
    {
        return !(x.destination() == destination && x.numberFreeSeatsInCabin() > 0);
    });
}

void MainWindow::deleteAllRecordsWithSpecificFlightNumbers()
{
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    int FlightNumbers = QInputDialog::getInt(this, tr("Input Flight Numbers"), tr("Flight Numbers:"));

    if(FlightNumbers <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("FlightNumbers <= 0!"));
        return;
    }

    m_table->eraseIf([&](const Flight& x) -> bool
    {
        return x.flightNumber() == FlightNumbers;
    });
}

void MainWindow::updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber()
{
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    quint64 FlightNumbers = QInputDialog::getInt(this, tr("Input Flight Numbers"), tr("Flight Numbers:"));

    if(FlightNumbers <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("FlightNumbers <= 0!"));
        return;
    }

    quint64 newNumberOfFreeSeatsInTheCabin = QInputDialog::getInt(this, tr("Input new Number Of Free Seats In The Cabin"),
                                                              tr("new Number Of Free Seats In The Cabin:"));
    if(newNumberOfFreeSeatsInTheCabin < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("new Number Of Free Seats In The Cabin < 0!"));
        return;
    }

    m_table->updateNumberFreeSeatsInCabin(FlightNumbers, newNumberOfFreeSeatsInTheCabin);
}
