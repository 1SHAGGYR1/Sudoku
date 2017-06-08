#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sudoku.cpp"
#include <QTimer>
#include "QLabel"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
Sudoku sudoku = Sudoku(0);

QLineEdit *table[9][9];
QLabel *solTable[9][9];

int t[9][9] =
{
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
};

int t2[9][9] =
{
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
};
void MainWindow::colorFill(int i, int j)
{
    if (t[i][j])
        table[i][j]->setStyleSheet("QLineEdit { background-color: rgb(255, 163, 58); font: 15pt Eras Bold ITC;} QLineEdit:focus {border-style: solid; border-width: 4px; border-color: rgb(255, 100, 57);}");
    else
        table[i][j]->setStyleSheet("QLineEdit { background-color: white ; font: 15pt Eras Bold ITC;} QLineEdit:focus {border-style: solid; border-width: 4px; border-color: grey;}");
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->nextDec->setEnabled(false);
    ui->prevDec->setEnabled(false);;
    ui->pbProgress->hide();
    //ui->label->hide();
    ui->centralWidget->setStyleSheet("background-color:white;");

    signalMapper = new QSignalMapper(this);
    //gui решений судоку
    for (int i=0;i<9;i++)
        for (int j =0;j<9;j++) {
            solTable[i][j] = new QLabel("");

            solTable[i][j] ->setMaximumSize(40,40);
            solTable[i][j] ->setMinimumSize(40,40);
            solTable[i][j] ->setAlignment(Qt::AlignCenter);

            if (t[i][j])
                solTable[i][j]->setStyleSheet("QLabel { background-color: rgb(255, 163, 58); font: 15pt Eras Bold ITC; border-style: solid; border-width: 1px; border-color: grey; }");
            else
                solTable[i][j]->setStyleSheet("QLabel { background-color: white ; font: 15pt Eras Bold ITC; border-style: solid; border-width: 1px; border-color: grey;}");

            ui->solutionLayout->addWidget(solTable[i][j],i,j);
        }

    //gui клеток судоку
    for (int i=0;i<9;i++)
        for (int j =0;j<9;j++) {
            table[i][j] = new QLineEdit();

            table[i][j]->setMaximumSize(40,40);
            table[i][j]->setMinimumSize(40,40);
            table[i][j]->setAlignment(Qt::AlignCenter);
            table[i][j]->setValidator(new QRegExpValidator(QRegExp("[1-9]{1}")));

            colorFill ( i, j);

            connect(table[i][j], SIGNAL(textChanged(QString)), signalMapper, SLOT(map()));
            signalMapper->setMapping(table[i][j], QString::number(i*9+j));

            ui->tabLayout->addWidget(table[i][j],i,j);


        }
    //
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(tEdited(const QString &)));

    sudoku.output();

}


void Sudoku::output()
{
    for (int i=0;i<9;i++)
        for (int j =0;j<9;j++) {
            if (sudoku.get_cell(i,j) != 0)
                table[i][j]->setText(QString::number(sudoku.get_cell(i,j)));
            else
                table[i][j]->setText("");
        }

}

void Sudoku::Generate(){

#pragma region rows

    for (int i=0;i<9;i++){
        int rando=rand()%9;
        int number =get_cell(i,rando);
        set_cell(i, rando, 0);
        Set_Empty();
        count=0;
        if (CombinationsTwo(emptyCells)!=1){
            cout<<"wrong! ";
            set_cell(i, rando, number);
            //i--;
        }

        cout<<i<<"r"<<endl;
    }

#pragma endregion

#pragma region columns

    for (int i=0;i<9;i++){
        int rando=rand()%9;
        int number =get_cell(rando, i);
        set_cell(rando, i, 0);
        Set_Empty();
        count=0;
        if (CombinationsTwo(emptyCells)!=1){
            cout<<"wrong! ";
            set_cell(rando, i, number);
            //i--;
        }
        cout<<i<<"c"<<endl;
    }

#pragma endregion

#pragma region square

    for (int i=0; i<9; i++){
        int rando=rand()%9;
        int number=get_cell(i/2+rando/2,i%2+rando%2);
        set_cell(i/2+rando/2,i%2+rando%2,0);
        Set_Empty();
        count=0;
        if (CombinationsTwo(emptyCells)!=1){
            cout<<"wrong! ";
            set_cell(i/2+rando/2,i%2+rando%2, number);
            //i--;
        }
        cout<<i<<"s"<<endl;
    }

#pragma endregion

    cout<<endl;
    //Show();
    cout<<endl;
}

void MainWindow::tEdited(const QString & cell)
{
    int k = cell.toInt(), i = k/9, j = k-k/9*9;

    if (!sudoku.check(i,j,table[i][j]->text().toInt()))
    {
        // table[i][j]->setStyleSheet("QLineEdit { background-color: red; font: 15pt Eras Bold ITC;}");
    }
    else
    {   //table[i][j]->setStyleSheet("QLineEdit { background-color: green; font: 15pt Eras Bold ITC;}");
        sudoku.set_cell(i,j, table[i][j]->text().toInt());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generate_clicked()
{

    ui->pbProgress->show();
    int pbvalue = 0;

    ui->pbProgress->setValue(pbvalue);
    for (int i =0; i<4;i++){
        cout<<i<<" step! ###############################"<<endl;
        sudoku.Generate();
        pbvalue+=25;
        ui->pbProgress->setValue(pbvalue);
    }
    sudoku.output();

    ui->pbProgress->hide();
    QMessageBox::information(this, "Сгенерировано", "готово", QMessageBox::Ok);

}

bool MainWindow::on_checkCells_clicked()
{
    bool L = true;
    for (int i = 0;i<9;i++)
        for (int j= 0;j<9;j++)
            if (!sudoku.check(i,j,table[i][j]->text().toInt()))
            {
                // table[i][j]->setStyleSheet("QLineEdit { background-color: red; font: 15pt Eras Bold ITC;} QLineEdit:focus {border-style: outset; border-width: 4px; border-color: rgb(0, 0, 0);}");
                L = false;
                sudoku.set_cell(i,j, table[i][j]->text().toInt());
            }
            else
                sudoku.set_cell(i,j, table[i][j]->text().toInt());


    if (L)
    {

        QMessageBox::information(this, "Проверка ячеек", "В этом судоку ошибок нет!" , QMessageBox::Ok);
        return true;
    }
    else
    {
        QMessageBox::information(this, "Проверка ячеек", "В этом судоку была обнаружена ошибка!" , QMessageBox::Ok);
        return false;
    }
}

void MainWindow::on_clearField_clicked()
{
    sudoku.clear();
    sudoku.output();
}

int solShown = 0, maxSolShown =0;

void MainWindow::on_decisions_clicked()
{
    sudoku.Set_Empty ();

    if (on_checkCells_clicked())
    {
        sudoku.solutions.clear();
        QString result = QString::number(sudoku.Combinations (sudoku.emptyCells));
        solShown = 0;
        maxSolShown = result.toInt();
        ui->label->show();
        ui->label->setText("РЕШЕНИЕ " + QString::number(solShown+1) + " ИЗ " + QString::number(maxSolShown));
        ui->prevDec->setEnabled(false);
        if (result.toInt() <= 1)
            ui->nextDec->setEnabled(false);
        else
            ui->nextDec->setEnabled(true);

        for (int i=0;i<9;i++)
            for (int j =0;j<9;j++)
                    solTable[i][j]->setText(QString::number(sudoku.solutions[solShown][i*9+j]));

        QMessageBox::information(this, "Количество решений", result , QMessageBox::Ok);
    }

}

void MainWindow::on_pushButton_clicked()
{
    sudoku.fill();
    sudoku.mix();
    sudoku.output();
}

void MainWindow::on_prevDec_clicked()
{
    solShown--;
    if (solShown == 0)
        ui->prevDec->setEnabled(false);
    if (solShown != maxSolShown)
        ui->nextDec->setEnabled(true);
    ui->label->setText("РЕШЕНИЕ " + QString::number(solShown+1) + " ИЗ " + QString::number(maxSolShown));
    for (int i=0;i<9;i++)
        for (int j =0;j<9;j++)
                solTable[i][j]->setText(QString::number(sudoku.solutions[solShown][i*9+j]));

}

void MainWindow::on_nextDec_clicked()
{
    solShown++;
    if (solShown == maxSolShown-1)
        ui->nextDec->setEnabled(false);
    if (solShown != 0)
        ui->prevDec->setEnabled(true);
    ui->label->setText("РЕШЕНИЕ " + QString::number(solShown+1) + " ИЗ " + QString::number(maxSolShown));

    for (int i=0;i<9;i++)
        for (int j =0;j<9;j++)
                solTable[i][j]->setText(table[i][j]->text());


}
