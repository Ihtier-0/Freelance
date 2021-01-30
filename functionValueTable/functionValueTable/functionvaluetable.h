#ifndef FUNCTIONVALUETABLE_PRI
#define FUNCTIONVALUETABLE_PRI

#include <QTableWidget>

class functionValueTable : public QTableWidget
{
    Q_OBJECT
public:
    using Function = std::function<bool(const qreal& x, const quint64& num, qreal& result, QString& comment)>;

    functionValueTable(const Function &a_y_x,
                       const qreal& a_begin,
                       const qreal& a_end,
                       const qreal& a_step);
    qreal begin() const;
    void setBegin(const qreal &begin);

    qreal end() const;
    void setEnd(const qreal &end);

    qreal step() const;
    void setStep(const qreal &step);

    void fillTable();
    void setSize();
private:

    Function m_y_x;
    qreal m_begin;
    qreal m_end;
    qreal m_step;
};

#endif // CAMERA_H