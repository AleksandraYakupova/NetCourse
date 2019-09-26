#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QDialogButtonBox>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent);
private:
    QLineEdit *nameFld;//поле для имени участника чата
};

#endif // LOGINDIALOG_H
