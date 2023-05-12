// maze_runner.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.

#include "maze.h"
#include "empty_path_maze.h"
#include "breadth_first_maze.h"

#include <limits>
#include <iostream>

using namespace std;

const string m_line = "--------------------------------------------------";

void test(){
    //read from file
    breadth_first_maze* blud = new breadth_first_maze("../vstup.txt",false);
    //empty_path_maze* blud = new empty_path_maze("../vstup.txt",false);
    //--------------------------------------------------------
    //generate and solve maze
    //breadth_first_maze* blud = new breadth_first_maze(100,30,5,5,90,20);
    //empty_path_maze* blud = new empty_path_maze(100,30,4,10,80,20);

    cout << m_line << endl;

    cout << "initiated!" << endl;

    system("clear");

    //blud->print(0);   //prepared for solving (will be untouched by empty path)
    blud->print(1);

    //cout << "\033[2;5H";
    //cout << "ahoj";

    int solved = blud->solve();

    cout << "solved: " << solved << endl;
    cout << "internal" << endl;
    cout << m_line << endl;
    cout << "for export" << endl;

    blud->print(1);
    
    blud->print_to_file();

    delete blud;

    cout << m_line << endl;
}


enum class State{
    main_menu, //no maze
    path_load,
    generate,
    solve_menu,
    exit
};

using namespace std;

bool check_num(){
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return false;
    } 
    return true;
}

/**
 *runtime UI WIP
*/
int main()
{
    State current_state = State::main_menu;

    string pth;

    while (current_state != State::exit) {
        switch (current_state) {
            case State::main_menu:
                cout << "Main menu:" << endl;
                cout << "1. Load" << endl;
                cout << "2. Generate" << endl;
                cout << "3. Exit" <<endl;
                int mm_input;
                cin >> mm_input;
                
                if(!check_num()) break;



                switch (mm_input){
                    case 1:
                        cout << "Path to load: " << endl;                        
                        cin >> pth;
                        break;
                    case 2:
                        cout << "Input size X: " << endl;
                        break;
                    case 3:
                        current_state = State::exit;
                        break;
                }
                break;

            default:
                break;
        }
    }
    test();

    return 0;
}

