
#ifndef ADDSUPPLIERDIALOG_H
#define ADDSUPPLIERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class addSupplierDialog : public QDialog
{
    Q_OBJECT

public:
    addSupplierDialog(QWidget *parent = nullptr);
    ~addSupplierDialog();

    QLineEdit *nameEdit;
    QComboBox *addrEdit;
    QComboBox *categoryEdit;
    QLineEdit *contactEdit;
    QLineEdit *teleEdit;
    QPushButton *addButton;
};

#endif
