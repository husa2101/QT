#include "contactbook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QPushButton {"
        "   background-color: #333333;"
        "   color: white;"
        "}"
        "QPushButton:hover {"     /* You can even style hover states! */
        "   background-color: #555555;"
        "}"
        "QLabel {"
        "   border: 1px solid gray;"
        "   border-radius: 3px;"
        "}"
        );


    ContactBook w;
    w.resize(500, 400);
    w.setWindowTitle(" Welcome to ContactBook");
    w.show();

    return a.exec();
}
