#include "widget.h"
#include "ui_widget.h"


int Widget::random(){
    srand(static_cast<unsigned int>(time(nullptr)));

    secretNumber = rand() % 10 + 1;
    qDebug() << "secret number generated" << QString::number(secretNumber);
    return secretNumber;
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    random();
    ui->StartOverButton->setDisabled(true);

    ui->messageLabel->setText("");


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_guessButton_clicked()
{
    guessNumber = ui->NumberSpinBox->value();
    qDebug() << "the guess number is  : " << QString::number(guessNumber);

    if(guessNumber == secretNumber){
        ui->messageLabel->setText("congratulations, number is :" + QString::number(secretNumber)) ;

        ui->guessButton->setDisabled(true);
        ui->StartOverButton->setDisabled(false);
    }else{
        if(secretNumber < guessNumber){
            ui->messageLabel->setText("Number is lower then that");
        }
        if(secretNumber > guessNumber){
            ui->messageLabel->setText("Number is higher then that");
        }
    }
}


void Widget::on_StartOverButton_clicked()
{
    ui->StartOverButton->setDisabled(true);
    ui->guessButton->setDisabled(false);
    ui->NumberSpinBox->setValue(1);
    ui->messageLabel->setText("");
}

