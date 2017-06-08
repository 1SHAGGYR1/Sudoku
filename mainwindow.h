#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
using namespace  std;
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSignalMapper *signalMapper;

public slots:

private slots:
    void tEdited(const QString & cell);
    void colorFill(int i, int j);
    void on_generate_clicked();
    bool on_checkCells_clicked();
    void on_clearField_clicked();
    void on_decisions_clicked();
    void on_pushButton_clicked();
    void on_prevDec_clicked();
    void on_nextDec_clicked();
};

#endif // MAINWINDOW_H
