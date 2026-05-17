#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Person.h"
#include <QDoubleSpinBox>
#include <QComboBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    private slots:
    void calculate_calories();
        void weight_changed(double weight);
    void time_changed(double time);
        void speed_changed(double speed);
    void level_changed(QString level);
signals:
        void calory_count_changed();
private:
    Ui::Widget *ui;
    double m_calory_count;
    double m_time;
    double m_speed;
    QString  m_level;
    Person m_person;

};
#endif // WIDGET_H
