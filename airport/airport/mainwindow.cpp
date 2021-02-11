#include "mainwindow.h"

#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(airportTable *a_table, QWidget *parent)
    : QMainWindow(parent), m_table(a_table)
{
    // сделать таблицу центральным виджетом
    this->setCentralWidget(m_table);

    // меню работы с файлами
    QMenu *fileMenu = new QMenu("File");
    // добавление действий
    fileMenu->addAction("Open file", this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction("Save table", this, &MainWindow::saveTable, QKeySequence::Save);
    // добавление действий в менюбар
    menuBar()->addMenu(fileMenu);

    // меню работы с таблицей
    QMenu *tableMenu = new QMenu("Table");
    // добавление действий
    tableMenu->addAction("add flight", this, &MainWindow::add);
    tableMenu->addAction("clear filters", this, &MainWindow::clearFilters);
    tableMenu->addAction("flights to the entered destination with free seats", this, &MainWindow::flightsToTheEnteredDestinationWithFreeSeats);
    tableMenu->addAction("delete all records with specific flight numbers", this, &MainWindow::deleteAllRecordsWithSpecificFlightNumbers);
    tableMenu->addAction("update the number of free seats in the cabin in the specified flight number", this,
                         &MainWindow::updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber);
    // добавление действий в менюбар
    menuBar()->addMenu(tableMenu);
}

void MainWindow::openFile()
{
    // получаем имя файла с помощью окна выбора файла для открытия
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "");

    // если название пустое(было нажато cancel) выходим из функции
    if (fileName.isEmpty())
    {
        return;
    }

    // открываем файл в таблице, все данные будут сразу показаны
    m_table->openFile(fileName);
}

void MainWindow::saveTable()
{
    // если файл не открыт, нечего сохранять
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    // получаем имя файла с помощью окна выбора файла для сохранения
    QString fileName = QFileDialog::getSaveFileName(this, "Open file", "", "");

    // если название пустое(было нажато cancel) выходим из функции
    if (fileName.isEmpty())
    {
        return;
    }

    // сохранение
    m_table->save(fileName);
}

void MainWindow::add()
{
    // если файл не открыт, некуда добавлять
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    // вводим номер рейса
    qint64 flightNumber = QInputDialog::getInt(this, tr("Input flight number"), tr("flight number:"));

    // если номер рейса < 0 ошибка
    if(flightNumber <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("flight number <= 0!"));
        return;
    }

    // вводим пункт назначения
    QString destination = QInputDialog::getText(this, tr("Input destination"), tr("destination:"));

    // если пункт назначения пустой ошибка
    if(destination.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("destination is empty!"));
        return;
    }

    // день, месяц, год, час, минуты
    qint64 d, mon, y, h, min;

    // вводим день
    d = QInputDialog::getInt(this, tr("Input departure date day:"), tr("departure date day:"));

    // если день больше чем возможно у месяца ошибка
    if(d < 0 || d > 31)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure day!"));
        return;
    }

    // вводим месяц
    mon = QInputDialog::getInt(this, tr("Input departure date month:"), tr("departure date month:"));

    // если месяц больше чем возможный ошибка
    if(mon <= 0 || mon > 12)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure month!"));
        return;
    }

    // вводим год
    y = QInputDialog::getInt(this, tr("Input departure date year:"), tr("departure date year:"));

    // год не может быть меньше 0
    if(y < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure year!"));
        return;
    }

    // вводим час
    h = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date hour:"));

    // проверка что час не выходит за границу
    if(h < 0 || h > 23)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure hour!"));
        return;
    }

    // вводим минуты
    min = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date minut:"));

    // проверка что минуты не выходят за границу
    if(min < 0 || min > 59)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure minut!"));
        return;
    }

    // врямя вылета
    QDateTime departureTime(QDate(y, mon, d), QTime(h, min));

    // если время вылета не валидное, ошибка
    if(!departureTime.isValid())
    {
        QMessageBox::warning(this, tr("Error"),tr("departure DateTime invalid!"));
        return;
    }

    // вводим день
    d = QInputDialog::getInt(this, tr("Input departure date day:"), tr("departure date day:"));

    // если день больше чем возможно у месяца ошибка
    if(d < 0 || d > 31)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure day!"));
        return;
    }

    // вводим месяц
    mon = QInputDialog::getInt(this, tr("Input departure date month:"), tr("departure date month:"));

    // если месяц больше чем возможный ошибка
    if(mon <= 0 || mon > 12)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure month!"));
        return;
    }

    // вводим год
    y = QInputDialog::getInt(this, tr("Input departure date year:"), tr("departure date year:"));

    // год не может быть меньше 0
    if(y < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure year!"));
        return;
    }

    // вводим час
    h = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date hour:"));

    // проверка что час не выходит за границу
    if(h < 0 || h > 23)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure hour!"));
        return;
    }

    // вводим минуты
    min = QInputDialog::getInt(this, tr("Input departure date hour:"), tr("departure date hour:"));

    // проверка что минуты не выходят за границу
    if(min < 0 || min > 59)
    {
        QMessageBox::warning(this, tr("Error"),tr("wrong departure minut!"));
        return;
    }

    // время прибытия
    QDateTime arrivalTime(QDate(y, mon, d), QTime(h, min));
    // если время прибытия не валидное, ошибка
    if(!arrivalTime.isValid())
    {
        QMessageBox::warning(this, tr("Error"),tr("arrival DateTime invalid!"));
        return;
    }

    // если прибытие меньше вылета, ошибка, самолёты не путешествуют во времени
    if(arrivalTime < departureTime)
    {
        QMessageBox::warning(this, tr("Error"),tr("arrivalDateTime < departureDateTime!"));
        return;
    }

    // количество свободных мест в салоне
    qint64 numberFreeSeatsInCabin = QInputDialog::getInt(this, tr("Input number free seats in cabin"),
                                                         tr("number free seats in cabin:"));
    // количество свободных мест в салоне не может быть меньше 0
    if(numberFreeSeatsInCabin < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("number free seats in cabin < 0!"));
        return;
    }


    m_table->add(Flight(flightNumber, destination, departureTime, arrivalTime, numberFreeSeatsInCabin));
}

void MainWindow::flightsToTheEnteredDestinationWithFreeSeats()
{
    // если файл не открыт, нечего фильтровать
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    // получаем пункт назначения
    QString destination = QInputDialog::getText(this, tr("Input destination"), tr("destination:"));

    // если пункт назначения пуст, ошибка
    if(destination.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("destination is empty!"));
        return;
    }

    // удаляем все записи у которых пунст назначения не равен введенному
    // и количество свободных мест > 0
    m_table->eraseIf([&](const Flight& x) -> bool
    {
        return !(x.destination() == destination && x.numberFreeSeatsInCabin() > 0);
    });
}

void MainWindow::deleteAllRecordsWithSpecificFlightNumbers()
{
    // если файл не открыт, нечего удалять
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    // получить номер рейса
    qint64 FlightNumbers = QInputDialog::getInt(this, tr("Input Flight Numbers"), tr("Flight Numbers:"));

    // если номер рейса меньше 0, ошибка
    if(FlightNumbers <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("FlightNumbers <= 0!"));
        return;
    }

    // удалеть записи с введенным номером рейса
    m_table->eraseIf([&](const Flight& x) -> bool
    {
        return x.flightNumber() == FlightNumbers;
    });
}

void MainWindow::updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber()
{
    // если файл не открыт, нечего обновлять
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    // получить номер рейса
    qint64 FlightNumbers = QInputDialog::getInt(this, tr("Input Flight Numbers"), tr("Flight Numbers:"));

    // если номер рейса меньше 0, ошибка
    if(FlightNumbers <= 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("FlightNumbers <= 0!"));
        return;
    }

    // новое количесто свободных мест
    qint64 newNumberOfFreeSeatsInTheCabin = QInputDialog::getInt(this, tr("Input new Number Of Free Seats In The Cabin"),
                                                              tr("new Number Of Free Seats In The Cabin:"));
    // если колчество мест < 0 такого не может быть
    if(newNumberOfFreeSeatsInTheCabin < 0)
    {
        QMessageBox::warning(this, tr("Error"),tr("new Number Of Free Seats In The Cabin < 0!"));
        return;
    }

    // обновляем
    m_table->updateNumberFreeSeatsInCabin(FlightNumbers, newNumberOfFreeSeatsInTheCabin);
}

void MainWindow::clearFilters()
{
    // если файл не открыт, нечего обновлять
    if(m_table->getDBFileAddress().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),tr("file not created!"));
        return;
    }

    m_table->update();
}
