#include "functionvaluetable.h"

#include <QSizePolicy>

functionValueTable::functionValueTable(const Function &a_y_x,
                                       const qreal& a_begin,
                                       const qreal& a_end,
                                       const qreal& a_step)
    : m_y_x(a_y_x), m_begin(a_begin), m_end(a_end), m_step(a_step)
{
    this->setColumnCount(2);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    fillTable();
    setSize();
}

void functionValueTable::fillTable()
{
    this->setRowCount(qAbs(m_begin - m_end) / m_step + 1);

    this->setHorizontalHeaderLabels(QStringList() << "x" << "f(x)");

    int rowSize = this->rowCount();

    int i = 0;
    qreal result;
    QString comment;

    for(; i < rowSize; ++i)
    {
        this->setItem(i, 0, new QTableWidgetItem(QString::number(m_begin + m_step * i)));

        if(m_y_x(m_begin + m_step * i, i + 1, result, comment))
        {
            this->setItem(i, 1, new QTableWidgetItem(QString::number(result)));
        }
        else
        {
            this->setItem(i, 1, new QTableWidgetItem(comment));
        }
    }

    if(m_end != (m_begin + m_step * (i - 1)))
    {
        this->insertRow(i);

        this->setItem(i, 0, new QTableWidgetItem(QString::number(m_end)));

        if(m_y_x(m_end, i + 1, result, comment))
        {
            this->setItem(i, 1, new QTableWidgetItem(QString::number(result)));
        }
        else
        {
            this->setItem(i, 1, new QTableWidgetItem(comment));
        }
    }
}

void functionValueTable::setSize()
{
    this->resizeColumnsToContents();
    this->resizeRowsToContents();

    this->setColumnWidth(0, this->columnWidth(0) * 2);
    this->setColumnWidth(1, this->columnWidth(1) * 2);
}

qreal functionValueTable::step() const
{
    return m_step;
}

void functionValueTable::setStep(const qreal &step)
{
    m_step = step;
}

qreal functionValueTable::end() const
{
    return m_end;
}

void functionValueTable::setEnd(const qreal &end)
{
    m_end = end;
}

qreal functionValueTable::begin() const
{
    return m_begin;
}

void functionValueTable::setBegin(const qreal &begin)
{
    m_begin = begin;
}