#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_person.set_Weigth(ui->WeightSpinBox_3->value());
    m_time = ui->TimeSpinBox->value();
    m_speed = ui->SpeedSpinBox_2->value();

    // connect the ui component to respective slots
    connect(ui->SpeedSpinBox_2, &QDoubleSpinBox::valueChanged,
            this, &Widget::speed_changed);
    connect(ui->TimeSpinBox, &QDoubleSpinBox::valueChanged,
            this, &Widget::time_changed);
    connect(ui->WeightSpinBox_3, &QDoubleSpinBox::valueChanged,
            this, &Widget::weight_changed);



    connect(this, &Widget::calory_count_changed, [=](){
        ui->caloryCount->setText(QString::number(m_calory_count));
    });

    calculate_calories();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculate_calories()
{
    m_calory_count = ((0.0215*(m_speed * m_speed * m_speed)) - (0.1765 *(m_speed * m_speed))
                      + (0.8710 * m_speed) + 1.4577) * m_person.weight() * m_time;

    emit calory_count_changed();
}

void Widget::weight_changed(double weight)
{
    m_person.set_Weigth(weight);
    calculate_calories();

}

void Widget::time_changed(double time)
{
    m_time = time;
    calculate_calories();
}

void Widget::speed_changed(double speed)
{
    m_speed = speed;
    calculate_calories();
}
