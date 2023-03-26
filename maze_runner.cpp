// maze_runner.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.

#include "maze.h"
#include "empty_path_maze.h"
#include "breadth_first_maze.h"

using namespace std;

const string m_line = "--------------------------------------------------";

int main()
{
    empty_path_maze* blud = new empty_path_maze("../vstup.txt",false);
    //breadth_first_maze* blud = new breadth_first_maze("../vstup.txt",false);
    cout << m_line << endl;

    cout << "initiated!" << endl;

    blud->print(0);

    blud->solve();
    cout << "internal" << endl;
    cout << m_line << endl;
    cout << "for export" << endl;
    blud->print(1);
    blud->print_to_file();
    //blud->print();

    // }
    // if (blud->maze_fill()) {
    //     cout << "initiated!" << endl;
    //     blud->print(0);
    //     blud->solve();
    //     blud->stamp();
    //     cout << "-------------------------\n";
    //     //blud->print(0);
    //     blud->print(1);
    //     blud->print_to_file();
    // }
    //system("pause");
    //blud->~maze();
    delete blud;
    return 0;
}

