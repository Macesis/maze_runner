// maze_runner.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.

#include "maze.h"
#include "empty_path_maze.h"
#include "breadth_first_maze.h"

using namespace std;

const string m_line = "--------------------------------------------------";

int main()
{
    //empty_path_maze* blud = new empty_path_maze("../vstup.txt",false);
    // breadth_first_maze* blud = new breadth_first_maze("../vstup.txt",false);
    // cout << m_line << endl;

    // cout << "initiated!" << endl;

    // blud->print(0);

    // blud->solve();
    // cout << "internal" << endl;
    // cout << m_line << endl;
    // cout << "for export" << endl;
    // blud->print(1);
    // blud->print_to_file();

    //blud->~maze();
    // delete blud;

    //cout << m_line << endl;

    //breadth_first_maze* gener_maz = new breadth_first_maze(100,100,5,5,90,90);
    empty_path_maze* gener_maz = new empty_path_maze(100,100,5,5,90,90);
    gener_maz->print(1);
    gener_maz->solve();
    cout << m_line << endl;
    gener_maz->print(1);
    return 0;
}

