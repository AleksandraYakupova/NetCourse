#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void generatePackage();
    unsigned int parseIPAddresses();

private:
    QLineEdit *lEditSourceIPAddr;
    QLineEdit *lEditDestIPAddr;
     //Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
