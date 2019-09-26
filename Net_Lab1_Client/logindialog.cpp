#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
{
    nameFld = new QLineEdit();

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                 Qt::Horizontal, this);


}
