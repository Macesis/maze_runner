// maze_runner.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.

#include "maze.h"
#include "empty_path_maze.h"
#include "breadth_first_maze.h"

using namespace std;

const string m_line = "--------------------------------------------------";

/**
 *no runtime UI yet, will be determined later 
*/
int main()
{
    //read from file
    //empty_path_maze* blud = new empty_path_maze("../vstup.txt",false);
    //breadth_first_maze* blud = new breadth_first_maze("../vstup.txt",false);
    //--------------------------------------------------------
    //generate and solve maze
    breadth_first_maze* blud = new breadth_first_maze(100,30,5,5,90,20);
    //empty_path_maze* blud = new empty_path_maze(100,30,4,10,80,20);

    cout << m_line << endl;

    cout << "initiated!" << endl;

    blud->print(0);   //prepared for solving (will be untouched by empty path)
    blud->print(1);

    blud->solve();
    cout << "internal" << endl;
    cout << m_line << endl;
    cout << "for export" << endl;
    
    blud->print(1);
    
    blud->print_to_file();

    delete blud;

    cout << m_line << endl;


    return 0;
}

