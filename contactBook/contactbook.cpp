#include "contactbook.h"
#include<QStackedWidget>
#include<QMessageBox>
#include<QFile>
#include <QTextStream>
#include<QBoxLayout>


ContactBook::ContactBook(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget *blankWidget = new QWidget(this);
    QStackedWidget *stack = new QStackedWidget(this);
    RegistPerson *page1 = new RegistPerson(this);
    SearchPerson *page2 = new SearchPerson(this);
    DeletePerson *page3 = new DeletePerson(this);
    stack->addWidget(blankWidget);
    stack->addWidget(page1);
    stack->addWidget(page2);
    stack->addWidget(page3);


    QPushButton *regist = new QPushButton(this);
    regist->setText("Registrering New User");

    QPushButton *search = new QPushButton(this);
    search->setText("Searching an User");

    QPushButton *deleteUser = new QPushButton(this);
    deleteUser->setText("Delete User");

    QPushButton *print = new QPushButton(this);
    print->setText("print all users");

    QPushButton *reset =new QPushButton(this);
    reset->setText("Reset...");


    int standardWidth = 250;
    int standardHeight = 40;
    regist->setFixedSize(standardWidth, standardHeight);
    search->setFixedSize(standardWidth, standardHeight);
    deleteUser->setFixedSize(standardWidth, standardHeight);
    print->setFixedSize(standardWidth, standardHeight);
    reset->setFixedSize(standardWidth, standardHeight);

    connect(regist, &QPushButton::clicked, stack, [=](){
        stack->setCurrentWidget(page1);
    });


    connect(search, &QPushButton::clicked, stack, [=](){
        stack->setCurrentWidget(page2);
    });

    connect(reset, &QPushButton::clicked, stack, [=](){
        stack->setCurrentWidget(blankWidget);
    });

    connect(deleteUser, &QPushButton::clicked,stack, [=](){
        stack->setCurrentWidget(page3);
    } );


    //........... register all users.
    connect(page1, &RegistPerson::UserCreated, this, [=](Person NewPerson){
        database.append(NewPerson);


        QFile file("data.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream out(&file);
            out << "FullName: " << NewPerson.fullname <<"\n";
            out << "Security Number: "<< NewPerson.ScurityNumber <<"\n";
            out << "Address: " <<NewPerson.address << "\n";

            out << "---\n";

            file.close();
            QMessageBox::information(this, "success!", "data sparad till data.txt");

        }else{
            QMessageBox::critical(this, "Error"," kunde inte öppna filen!");
        }
    });

    // ............. print all users.
    connect(print, &QPushButton::clicked, this, [=](){
        // 1. Optional but helpful: Check if the database is empty first
        if (database.isEmpty()) {
            QMessageBox::information(this, "Database", "The contact book is currently empty.");
            return; // Exit the lambda early so we don't run the loop
        }

        // 2. Create an empty string to hold our final message
        QString allContacts = "Registered Users:\n\n";

        // 3. Loop through the list and append data to the string
        for(int i = 0; i < database.count(); ++i) {
            // Using '+=' adds the new text to the end of the existing string.
            // \n creates a line break so each user is on a new line.
            allContacts += "FullName: " + database[i].fullname +
                           " | Address: " + database[i].address +
                           " | Security Number: " + database[i].ScurityNumber + "\n";
        }

        // 4. Finally, display the fully built string in ONE message box
        QMessageBox::information(this, "All Contacts", allContacts);
    });


    // catch a signal from Search class for searching after a user.
    connect(page2, &SearchPerson::UserCreated, this,[=](Person NewPerson){
        QString contactFind;
        bool found = false;
        for (int var = 0; var < database.count(); ++var) {
            if(NewPerson.fullname == database[var].fullname){

                contactFind += "FullName: " + database[var].fullname +
                               " | Address: " + database[var].address +
                               " | Security Number: " + database[var].ScurityNumber + "\n";
                QMessageBox::information(this, " user exist: ",contactFind );
                found = true;
                return;
            }else if(NewPerson.ScurityNumber == database[var].ScurityNumber){
                contactFind += "FullName: " + database[var].fullname +
                               " | Address: " + database[var].address +
                               " | Security Number: " + database[var].ScurityNumber + "\n";
                QMessageBox::information(this, " user exist: ",contactFind );
                found = true;
                return;
            }
        }

        if(!found){

            QMessageBox::information(this, "Not found", "User does not exist");
        }
    });



    // catch a signal från Delete class and delete a contect.
    connect(page3, &DeletePerson::userDeleted, this, [=](Person newperson){
        QString person;
        bool found = false;
        for(int i = 0; i < database.count(); ++i){
            if(newperson.fullname == database[i].fullname){
                database.removeAt(i);
                found = true;
            }
        }



        for(int i = 0; i < database.count(); ++i){
            if(newperson.fullname == database[i].fullname){
                found = false;
                QMessageBox::information(this, "User Found", "User still exist. ");
                return;
            }
        }

        if(!found){
            QMessageBox::information(this, "not Found ", "User does not exist.");
        }

        if(found){
            QString name;
            name += "User: " + newperson.fullname +" has successfully been removed ";
            QMessageBox::information(this, "User:", name);
        }

        deletedFromFile(newperson);

    });


    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(30, 30, 30, 30);

    //layout->setSpacing(30);
    QLabel *label = new QLabel("Welcome to Public Contact Book");
    layout->addWidget(label, 0, Qt::AlignCenter);
    layout->addWidget(regist, 0, Qt::AlignCenter);
    layout->addWidget(search, 0 , Qt::AlignCenter);
    layout->addWidget(deleteUser, 0 , Qt::AlignCenter);
    layout->addWidget(print, 0 , Qt::AlignCenter);
    layout->addWidget(reset, 0 , Qt::AlignCenter);
    layout->addWidget(stack);
    layout->addStretch();



    setCentralWidget(central);
    setWindowTitle("learning exprement of using QStackedWidget");
    processDataFromFile();
}






//.....read registerd data fron a txt file and putt them into the database.
void ContactBook::processDataFromFile(){

    QFile DataFile("data.txt");

    if(DataFile.open(QIODevice::ReadOnly | QIODevice::Text)){
         QTextStream in(&DataFile);
        Person CurrentPerson;
        while(!in.atEnd()){
            QString line = in.readLine();

            if(line.startsWith("FullName: ")){
                CurrentPerson.fullname = line.mid(9).trimmed();
            }else if(line.startsWith("Security Number: ")){
                CurrentPerson.ScurityNumber = line.mid(16).trimmed();
            }else if(line.startsWith("Address: ")){
                CurrentPerson.address = line.mid(8).trimmed();
            }else if(line.startsWith("---")){
                database.append(CurrentPerson);
                CurrentPerson = Person();
            }

            DataFile.close();
        }

        // Optional: Let yourself know it worked!
        qDebug() << "Successfully loaded" << database.count() << "people from file.";      

    }else{
        QMessageBox::warning(this, "Error", "Could not open data.txt for reading!");
    }
    }

#include <QFile>
#include <QTextStream>
#include <QStringList>

void ContactBook::deletedFromFile(Person &person) {
    QStringList lines;

    // STEP 1: Open in ReadOnly mode to read all content into memory
    QFile readFile("data.txt");
    if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&readFile);
        while (!in.atEnd()) {
            QString line = in.readLine();


            // Only keep the line if it is NOT the item we want to delete
            if (line.contains(person.fullname)) {
                in.readLine();
                in.readLine();
                in.readLine();
            }else{
                lines.append(line);
            }
        }
        readFile.close(); // Close the file after reading
    }

    // STEP 2: Open in WriteOnly + Truncate mode to wipe the file and write the kept lines
    QFile writeFile("data.txt");
    if (writeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&writeFile);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        writeFile.close();
    }
}




QString Person::toLower(QString &s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](QChar c){ return c.toLower();}
                   );
    return s;
}


