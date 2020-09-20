#include "logindialog.h"
#include <QGridLayout>


loginDialog::loginDialog(QWidget *parent)
         : QDialog(parent)
    {
        nameLabel = new QLabel("用户名");
        passwordLabel = new QLabel("密码");
        nameEdit = new QLineEdit;
        passwordEdit = new QLineEdit;
        loginButton = new QPushButton("登录");
        registButton = new QPushButton("注册");

        QGridLayout *gridLayout = new QGridLayout;
        gridLayout->addWidget(nameLabel,0,0);
        gridLayout->addWidget(nameEdit,0,1);
        gridLayout->addWidget(passwordLabel,1,0);
        gridLayout->addWidget(passwordEdit,1,1);
        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(loginButton);
        hLayout->addWidget(registButton);
        QVBoxLayout *vLayout = new QVBoxLayout;
        vLayout->addLayout(gridLayout);
        vLayout->addLayout(hLayout);

        setLayout(vLayout);

}

loginDialog::~loginDialog()
{

}
