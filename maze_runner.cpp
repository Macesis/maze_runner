// maze_runner.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.

#include "maze.h"
#include "empty_path_maze.h"
#include "breadth_first_maze.h"

#include <limits>
#include <iostream>
#include <chrono>

using namespace std;

const string m_line = "--------------------------------------------------";

void test(){
    //read from file
    //breadth_first_maze* blud = new breadth_first_maze("../vstup.txt",false);
    //empty_path_maze* blud = new empty_path_maze("../vstup.txt",false);
    //--------------------------------------------------------
    //generate and solve maze
    //breadth_first_maze* blud = new breadth_first_maze(100,30,5,5,90,20);
    empty_path_maze* blud = new empty_path_maze(100,30,4,10,80,20);

    cout << m_line << endl;

    cout << "initiated!" << endl;

    //system("clear");

    //blud->print(0);   //prepared for solving (will be untouched by empty path)
    blud->print(1);

    //cout << "\033[2;5H";
    //cout << "ahoj";

    int solved = blud->solve(1);

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

int get_num(string prompt = ""){
    int num;
    while(true){
        cout << prompt;
        cin >> num;
        if(!check_num()) continue;
        break;
    }
    return num;
}

int get_num(int min, int max, string prompt = ""){
    int num;
    while(true){
        cout << prompt;
        cin >> num;
        if(!check_num()) continue;
        if(num < min || num > max){
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
            continue;
        }
        break;
    }
    return num;
}


/**
 *runtime UI WIP
 *beware of small windows size when solving visualy
*/
void menu()
{
    State current_state = State::main_menu;

    int mm_input;

    string pth;
    string prompt;

    maze* blud = nullptr;
    breadth_first_maze* bf_blud = nullptr;
    empty_path_maze* ep_blud = nullptr;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    while (current_state != State::exit) {
        switch (current_state) {
            case State::main_menu:
                cout << "Main menu:" << endl;
                cout << "1. Load" << endl;
                cout << "2. Generate" << endl;
                cout << "3. Exit" <<endl;
                cin >> mm_input;
                
                if(!check_num()) break;

                switch (mm_input){
                    case 1:
                        cout << "Path to load: " << endl;                        
                        cin >> pth;
                        try{
                            blud = new maze(pth);
                        } catch (const std::exception& e) {
                            system("clear");
                            cout << "Path to load: " << pth << endl;
                            cout << "\033[31mError: " << e.what() << "\033[0m" << endl;
                            break;
                        }
                        system("clear");
                        blud->print(0);
                        current_state = State::solve_menu;
                        break;
                    case 2:
                        prompt = "Input size X: ";
                        int x_size;
                        x_size = get_num(5,1000, prompt);

                        prompt = "Input size Y: ";
                        int y_size;
                        y_size = get_num(5,1000, prompt);


                        prompt = "Input start X (1 - " + to_string(x_size) + "): ";
                        int start_x;
                        start_x = get_num(1,x_size, prompt);

                        prompt = "Input start Y (1 - " + to_string(y_size) + "): ";
                        int start_y;
                        start_y = get_num(1,y_size, prompt);


                        prompt = "Input end X (1 - " + to_string(x_size) + "): ";//TODO: check if end is not in start (or vice versa)
                        int end_x;
                        end_x = get_num(1,x_size, prompt);
                        
                        prompt = "Input end Y (1 - " + to_string(y_size) + "): ";
                        int end_y;
                        end_y = get_num(1,y_size, prompt);
                        try{
                            blud = new maze(x_size,y_size,start_x,start_y,end_x,end_y);
                        }
                        catch (const std::exception& e) {
                            system("clear");
                            cout << "\033[31mError: " << e.what() << "\033[0m" << endl;
                            break;
                        }
                        system("clear");
                        blud->print(0);
                        current_state = State::solve_menu;
                        break;
                    case 3:
                        current_state = State::exit;
                        break;
                }
                break;
            case State::solve_menu:
                cout << "Solve menu:" << endl;
                cout << "1. View" << endl;
                cout << "2. Solve breadth-first" << endl;
                cout << "3. Solve breadth-first visualy" <<endl;
                cout << "4. Solve empty-path" << endl;
                cout << "5. Solve empty-path visualy" <<endl;
                cout << "6. Back" << endl;
                cin >> mm_input;
                
                if(!check_num()) break;

                switch(mm_input){
                    case 1:
                        system("clear");
                        blud->print(1);
                        break;
                    case 2:
                        bf_blud = new breadth_first_maze(*blud);
                        system("clear");
                        start = std::chrono::steady_clock::now();
                        bf_blud->solve(false);
                        end = std::chrono::steady_clock::now();
                        bf_blud->print(1);
                        cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " µs" << endl;
                        bf_blud->~breadth_first_maze();
                        break;
                    case 3:
                        bf_blud = new breadth_first_maze(*blud);
                        start = std::chrono::steady_clock::now();
                        bf_blud->solve(true);
                        end = std::chrono::steady_clock::now();
                        system("clear");
                        maze::gotoxy(0,0);
                        bf_blud->print(1);
                        cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << " ms" << endl;
                        bf_blud->~breadth_first_maze();
                        break;
                    case 4:
                        ep_blud = new empty_path_maze(*blud);
                        system("clear");
                        start = std::chrono::steady_clock::now();
                        ep_blud->solve(false);
                        end = std::chrono::steady_clock::now();
                        ep_blud->print(1);
                        cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " µs" << endl;
                        ep_blud->~empty_path_maze();
                        break;
                    case 5:
                        ep_blud = new empty_path_maze(*blud);
                        start = std::chrono::steady_clock::now();
                        ep_blud->solve(true);
                        end = std::chrono::steady_clock::now();
                        system("clear");
                        maze::gotoxy(0,0);
                        ep_blud->print(1);
                        cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << " ms" << endl;
                        ep_blud->~empty_path_maze();
                        break;
                    case 6:
                        system("clear");
                        current_state = State::main_menu;
                        break;
                }
                break;
            default:
                break;
        }
    }

    //test();

    return;
}


int main(int argc, char const *argv[])
{
    menu();

    return 0;
}