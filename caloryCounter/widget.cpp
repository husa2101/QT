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
    m_level = ui->comboBox->currentText();


    // combobox alowe you to chose various option road angel
    ui->comboBox->addItem("CB 0%");
    ui->comboBox->addItem("CB -5%");
    ui->comboBox->addItem("CB -3%");
    ui->comboBox->addItem("CB +4%");
    ui->comboBox->addItem("CB +2%");

    /*QString name[] = {"0%","-5%","+4%","+2%","-1%"};

    for(int i = 0; i <= 4; ++i){
        ui->comboBox->addItem("CB " + name[i]);
    }*/

    // connect the ui component to respective slots
    connect(ui->SpeedSpinBox_2, &QDoubleSpinBox::valueChanged,
            this, &Widget::speed_changed);
    connect(ui->TimeSpinBox, &QDoubleSpinBox::valueChanged,
            this, &Widget::time_changed);
    connect(ui->WeightSpinBox_3, &QDoubleSpinBox::valueChanged,
            this, &Widget::weight_changed);
    connect(ui->comboBox, &QComboBox::currentTextChanged,
            this, &Widget::level_changed);


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
    //auto pos = ui->comboBox->currentText();
    if(m_level == "CB 0%"){

        m_calory_count = ((0.0215*(m_speed * m_speed * m_speed)) - (0.1765 *(m_speed * m_speed))
                          + (0.8710 * m_speed) + 1.4577) * m_person.weight() * m_time;
    }else if(m_level == "CB -5%"){
        m_calory_count = ((0.0221 *(m_speed * m_speed * m_speed)) - (0.1349 *(m_speed * m_speed))
                         + (0.8025 * m_speed) + 2.1000) * m_person.weight() * m_time;
    }else if(m_level == "CB -3%"){
        m_calory_count = ((0.0237 *(m_speed * m_speed * m_speed)) - (0.2000 *(m_speed * m_speed))
                          + (0.8217 * m_speed) + 1.3605) * m_person.weight() * m_time;
    }else if(m_level == "CB +4%"){
        m_calory_count = ((0.0208 *(m_speed * m_speed * m_speed)) - (0.1277 *(m_speed * m_speed))
                          + (0.7539 * m_speed) + 2.0400) * m_person.weight() * m_time;
    }else{
        m_calory_count = ((0.0184 *(m_speed * m_speed * m_speed)) - (0.1134 *(m_speed * m_speed))
                          + (0.6566 * m_speed) + 1.9200) * m_person.weight() * m_time;
    }

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

void Widget::level_changed(QString level)
{
    m_level = level;
    calculate_calories();
}
