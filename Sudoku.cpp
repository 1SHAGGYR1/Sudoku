#include "ui_mainwindow.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <QMessageBox>
using namespace std;

struct cell{
    int x,y,number;
    cell(int _x, int _y, int _number){
        this->x=_x;
        this->y=_y;
        this->number=_number;
    }

};

struct emptyCell {
    int x, y;
    vector<int> numbers;
    emptyCell () {
        x = 0; y = 0;
        numbers.clear ();
    }

    emptyCell (int x, int y, vector<int> input) {
        this->x = x;
        this->y = y;
        numbers = input;
    }
};

class Sudoku {

private:
    short field[9][9] =
    {
        { 1,2,3,4,5,6,7,8,9 },
        { 4,5,6,7,8,9,1,2,3 },
        { 7,8,9,1,2,3,4,5,6 },
        { 2,3,4,5,6,7,8,9,1 },
        { 5,6,7,8,9,1,2,3,4 },
        { 8,9,1,2,3,4,5,6,7 },
        { 3,4,5,6,7,8,9,1,2 },
        { 6,7,8,9,1,2,3,4,5 },
        { 9,1,2,3,4,5,6,7,8 }
    };

public:
    vector < vector <short>> solutions;

    ofstream fout;

    Sudoku (int user)
    {
        srand(time(0));
        switch (user)
        {
            case 0:
                clear ();
            break;

            case 1:
            {
                clear ();
                set_cell (1, 3, 6);
                set_cell (2, 1, 7);
                set_cell (2, 4, 9);
                set_cell (2, 6, 2);
                set_cell (3, 1, 5);
                set_cell (3, 5, 7);
                set_cell (4, 4, 4);
                set_cell (4, 5, 5);
                set_cell (4, 6, 7);
                set_cell (5, 3, 1);
                set_cell (5, 7, 3);
                set_cell (6, 2, 1);
                set_cell (6, 7, 6);
                set_cell (6, 8, 8);
                set_cell (7, 2, 8);
                set_cell (7, 3, 5);
                set_cell (7, 7, 1);
                set_cell (8, 1, 9);
                set_cell (8, 6, 4);
            }
            break;
            case 2:
            {
                mix ();
                for (int i = 0;i<3;i++)
                    for (int j = 0;j<9;j++)
                        set_cell (i, j, 0);
            }
            break;
            default:
            {
                fill ();
            }
            break;
        }
        Set_Empty ();
        fout.open ("log.txt");
    }

    void clear () {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                field[i][j] = 0;
    }

    void fill () {
        for (int i = 0; i < 9; i++)
            field[0][i] = i + 1;
        for (int i = 0; i < 9; i++)
            field[1][i] = (i + 3) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[2][i] = (i + 6) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[3][i] = (i + 1) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[4][i] = (i + 4) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[5][i] = (i + 7) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[6][i] = (i + 2) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[7][i] = (i + 5) % 9 + 1;
        for (int i = 0; i < 9; i++)
            field[8][i] = (i + 8) % 9 + 1;
    }

    void set_cell (int x, int y, int value) {
        field[x][y] = value;
    }

    int get_cell (int x, int y) {
        return field[x][y];
    }

    bool check (int x, int y, int value) {
        if (value == 0)
            return true;
        for (int i = 0; i < 9; i++) {
            if (i != y)
                if (get_cell (x, i) == value)
                    return false;
        }

        for (int i = 0; i < 9; i++) {
            if (i != x)
                if (get_cell (i, y) == value)
                    return false;
        }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                if ((x / 3 * 3 + i != x) || (y / 3 * 3 + j != y))
                    if ((get_cell (x / 3 * 3 + i, y / 3 * 3 + j) == value))
                        return false;
            }

        return true;
    }

    void trans () {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < i; j++) {
                int save = field[i][j];
                field[i][j] = field[j][i];
                field[j][i] = save;
            }
    }

    void swap_rows () {
        int row_num1, row_num2, k;
        k = rand () % 3 * 3;
        do {
            row_num1 = rand () % 3 + k;
            row_num2 = rand () % 3 + k;

        }
        while (row_num1 == row_num2);
        for (int i = 0; i < 9; i++) {
            int save = field[row_num1][i];
            field[row_num1][i] = field[row_num2][i];
            field[row_num2][i] = save;
        }
    }

    void swap_columns () {
        int col_num1, col_num2, k;
        k = rand () % 3 * 3;
        do {
            col_num1 = rand () % 3 + k;
            col_num2 = rand () % 3 + k;
        }
        while (col_num1 == col_num2);
        for (int i = 0; i < 9; i++) {
            int save = field[i][col_num1];
            field[i][col_num1] = field[i][col_num2];
            field[i][col_num2] = save;
        }
    }

    void swap_big_rows () {
        int group_num1, group_num2;
        do {
            group_num1 = rand () % 3;
            group_num2 = rand () % 3;
        }
        while (group_num1 == group_num2);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 9; j++) {
                int save = field[group_num1 * 3 + i][j];
                field[group_num1 * 3 + i][j] = field[group_num2 * 3 + i][j];
                field[group_num2 * 3 + i][j] = save;
            }
    }

    void swap_big_columns () {
        int group_num1, group_num2;
        do {
            group_num1 = rand () % 3;
            group_num2 = rand () % 3;
        }
        while (group_num1 == group_num2);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 9; j++) {
                int save = field[j][group_num1 * 3 + i];
                field[j][group_num1 * 3 + i] = field[j][group_num2 * 3 + i];
                field[j][group_num2 * 3 + i] = save;
            }
    }

    void mix () {
        int mix_num;
        mix_num = rand () % 100 + 20;
        for (int i = 0; i < mix_num; i++) {
            int chose = rand () % 5 + 1;
            switch (chose) {
                case 1: trans ();
                break;
                case 2: swap_rows ();
                break;
                case 3: swap_columns ();
                break;
                case 4: swap_big_columns ();
                break;
                case 5: swap_big_rows ();
                break;

            }
        }
    }
    vector<emptyCell>  emptyCells;

    //Initialize empty Cells
    void Set_Empty () {
        emptyCells.clear ();
        emptyCells.reserve (32);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (field[i][j] == 0) {
                    emptyCell empt (i, j, Numbers (i, j));
                    emptyCells.push_back (empt);
                }
            }
        }
        if (emptyCells.size ()>0)
            SortEmptyCells ();
    }

    //Returns able numbers for x,y cell
    vector<int> Numbers (int x, int y) {
        vector<int> buffer;
        buffer.reserve (9);
        for (int i = 1; i < 10; i++) {
            if (check (x, y, i))
                buffer.push_back (i);
        }
        return buffer;
    }

    //Sort empty sells
    void SortEmptyCells () {
        for (int i = 0; i < emptyCells.size () - 1; i++) {
            for (int j = i + 1; j < emptyCells.size (); j++) {
                if (emptyCells[i].numbers.size () > emptyCells[j].numbers.size ()) {
                    emptyCell buffer = emptyCells[i];
                    emptyCells[i] = emptyCells[j];
                    emptyCells[j] = buffer;
                }
            }
        }
    }

    int count = -1;

    int CombinationsTwo (vector<emptyCell> cells) {
        if (cells.size () == 0) {
            if (count <1)
                count++;
            else
                return -1;
            //if (count % 100 == 0)
            //	cout << endl;
            //cout << "+";
            //Show ();
            return 1;
        }
        else {
            int buf = 0;
            for each (int number in cells[0].numbers) {
                if (check (cells[0].x, cells[0].y, number)) {
                    vector<emptyCell> buffer;
                    buffer = cells;
                    set_cell (cells[0].x, cells[0].y, number);
                    Set_Empty ();
                    buffer.erase (buffer.begin ());
                    //Show();
                    //Print();
                    buf += CombinationsTwo (buffer);
                    set_cell (cells[0].x, cells[0].y, 0);
                }
                else
                    continue;
            }

            return buf;
        }
    }

    void Sol ()
    {
        vector <short> temp (81);

            for (int i = 0;i < 9;i++)
                for (int j = 0;j < 9;j++)
                    temp[i * 9 + j]=field[i][j];

        solutions.push_back (temp);
    }


    //Count amount of all combinations
    int Combinations (vector<emptyCell> cells) {
        if (cells.size () == 0) {
            count++;
            Show ();
            Sol();
            return 1;
        }
        else {
            int buf = 0;
            for each (int number in cells[0].numbers) {
                if (check (cells[0].x, cells[0].y, number)) {
                    vector<emptyCell> buffer;
                    buffer = cells;
                    set_cell (cells[0].x, cells[0].y, number);
                    Set_Empty ();
                    buffer.erase (buffer.begin ());
                    buf += Combinations (buffer);
                    set_cell (cells[0].x, cells[0].y, 0);
                }
                else
                    continue;
            }

            return buf;
        }
    }

    void Generate();

    //Print sudoku
    void Show () {
        cout << "-----------" << endl;
        for (int i = 0; i<9; i++) {
            for (int j = 0; j < 9; j++) {
                if  (field[i][j]==0)
                    cout<<"_";
                else
                    cout << field[i][j];

            }
            cout << "\n";
        }
    }

    void Print () {
        for each (emptyCell item in emptyCells) {
            cout << item.x << " " << item.y << ") ";
            for each (int it in item.numbers) {
                cout << it << ",";
            }
            cout << endl;
        }
    }

    void output();

};


