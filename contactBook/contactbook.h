#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <QMainWindow>
#include<QVBoxLayout>
#include<QLabel>
#include<QDebug>
#include<QLineEdit>
#include<QPushButton>
#include<QCheckBox>
#include<QSpinBox>
#include <qmessagebox.h>


enum stringType{
    isAlphabetic,
    isNumeric,
    other
};

class Person{
public:
    QString fullname;
    QString address;
    QString ScurityNumber;
    QString Epost;

    QString toLower(QString &ch);
    stringType evaluate(const char &ch);
    stringType inputAnalysis(QString input);
};

class SearchPerson : public QWidget{

     Q_OBJECT
public:
    explicit SearchPerson(QWidget *parent = nullptr): QWidget(parent){
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Search a User"));

        QLineEdit *line = new QLineEdit;
        line->setPlaceholderText("Username");
        layout->addWidget(line);

        QLineEdit *line2 = new QLineEdit;
        line2->setPlaceholderText("Security Number");
        layout->addWidget(line2);

        QPushButton *button = new QPushButton(this);
        button->setText("Submitt");
        button->setObjectName("primary");
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, line, [=](){
            Person NewPerson;
            QString name = line->text();
            QString IdNumber = line2->text();
            bool empty = name.isEmpty();
            bool empty2 = IdNumber.isEmpty();
            if(empty || empty2){
                QMessageBox::information(this, " you have to", "enter a value");
            }else{
                NewPerson.fullname = line->text();
                NewPerson.ScurityNumber = line2->text();
                emit UserCreated(NewPerson);
            }

        });

        this->setStyleSheet(
            "QPushButton#primary {"
            "background-color:#e3f2fd;"
            "color: black }");



        /*setStyleSheet("background-color: #e8f5e9; "
                      "QWidget {font-size: 14px; }"
                      );*/
    }
signals:
     void UserCreated(Person NewPerson);

};



class DeletePerson: public QWidget{
     Q_OBJECT
public:
    explicit DeletePerson(QWidget * parent = nullptr): QWidget(parent){
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Delete user"));

        QLineEdit *username = new QLineEdit;
        username->setPlaceholderText("Username");
        layout->addWidget(username);

        QPushButton *button = new QPushButton(this);
        button->setText("Submitt");
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [=](){
            Person newperson;
            QString name = username->text();
            bool empty = name.isEmpty();
            if(empty){
                QMessageBox::information(this, "", "enter a name to delete");
            }else{
                newperson.fullname = username->text();
                emit userDeleted(newperson);
            }
        });

        button->setObjectName("primaryButton");
        this->setStyleSheet(
            "QPushButton#primaryButton {"
            "   background-color: #e3f2fd;"
            "   color: black;"
            "}"
            );

    }

signals:
    void userDeleted(Person person);
};



class ContactBook : public QMainWindow
{
    Q_OBJECT
public:
    explicit ContactBook(QWidget *parent = nullptr);
    void processDataFromFile();
    void deletedFromFile(Person &person);

private:
    QList<Person>database;


};




class RegistPerson : public QWidget{
    Q_OBJECT
public:
    explicit RegistPerson(QWidget *parent = nullptr): QWidget(parent){

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("User Registration"));

        QLineEdit *username = new QLineEdit;
        username->setPlaceholderText("Username");
        layout->addWidget(username);

        QLineEdit *IdEdit = new QLineEdit;
        IdEdit->setPlaceholderText("IdNumber");
        layout->addWidget(IdEdit);

        QLineEdit *address = new QLineEdit;
        address->setText("address");
        layout->addWidget(address);

        QPushButton *pushButton = new QPushButton;
        pushButton->setText("Save");
        layout->addWidget(pushButton);



        connect(pushButton, &QPushButton::clicked, this, [=](){

            Person NewPerson;

            QString Fname = username->text();
            QString id = IdEdit->text();
            QString adds = address->text();
            bool a = Fname.isEmpty();
            bool b = id.isEmpty();
            bool c = adds.isEmpty();
            if(a || b || c){
                QMessageBox::information(this, "", "please enter fullname && security Number && address");
            }else{


            NewPerson.fullname = NewPerson.toLower(Fname);
            NewPerson.ScurityNumber = NewPerson.toLower(id);
            NewPerson.address = NewPerson.toLower(adds);

            emit UserCreated(NewPerson);

            qDebug() << "helleo: " << username->text()  << "\n your info has been saved:  ";

            username->clear();
            IdEdit->clear();
            }
        });


        pushButton->setObjectName("primaryButton");


        this->setStyleSheet(
            "QPushButton#primaryButton {"
            "   background-color: #e3f2fd;"
            "   color: black;"
            "}"
            );

    };

signals:
    void UserCreated(Person person);

};







#endif // CONTACTBOOK_H
