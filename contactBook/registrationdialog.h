#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QObject>

class registrationDialog : public QObject
{
    Q_OBJECT
public:
    explicit registrationDialog(QObject *parent = nullptr);

signals:
};

#endif // REGISTRATIONDIALOG_H
