
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "addsupplierdialog.h"

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

    QLabel *nameLabel;
    QLabel *passwordLabel;
    QLineEdit *nameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registButton;
};

#endif
