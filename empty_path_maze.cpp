#include "empty_path_maze.h"

empty_path_maze::empty_path_maze(string input_path, bool debug) : maze(input_path, debug ){
    //fill maze from file
    maze_fill();
}

empty_path_maze::empty_path_maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug) : maze(x_size, y_size, start_x, start_y, end_x, end_y, debug)
{
    maze_fill();
}

empty_path_maze::empty_path_maze(const maze &other) : maze(other)
{
    maze_fill();
}

bool empty_path_maze::maze_fill(){
    for(int i = 0; i < this->xs * this->ys; i++){
        if (this->map[i] == m_corr) this->map[i] = m_path; //set corridor to path, solving algorithm should replace all wrong paths
        this->map_out[i] = this->map[i]; //copy map to map_out
    }
    return true;
}

int empty_path_maze::solve(bool visualize) { //brute force call of blind path detection for every point inside the maze
    if(visualize){
        this->vis = true;
        system("clear");
        this->print(1);
    }
    for (int y = 1; y < this->ys; y++) {
        for (int x = 1; x < this->xs-1; x++) {
            //cout << this->map_out[y * xs + x];
            if(proximity(x, y) != 0) x++; //if proximity returns 0, the point is not a blind end, so we can skip the next point
        }
    }

    if(this->vis){
        gotoxy(0,this->ys+1);
    }
    this->vis = false;
    return 0;
}

int empty_path_maze::proximity(int x, int y) { //detects wether the point is blind and recursively destructs such a path 
    //Problems:
    // leaves entire chambers as paths
    // loops inside the maze will remain marked as path (even when inaccessible from neither start nor finish)
    char& current = this->map_out[y * xs + x];
    if (current != m_wall && current != m_start && current != m_end) {

        // this->print(1); //visualization output for testing
        // system("clear"); //clear screen
        if(this->vis){
            gotoxy(x,y+1);
            cout << flush;
            usleep(10000);
        }  

        //get values of cells around current cell (neighbours)
        char above = this->map_out[(y - 1) * xs + x];
        char left = this->map_out[y * xs + x - 1];
        char right = this->map_out[y * xs + x + 1];
        char below = this->map_out[(y + 1) * xs + x];

        int walls = 0;
        if (above == m_wall || above == m_corr) { //is wall above?
            walls++;
        }

        if (left == m_wall || left == m_corr) { //is wall left?        
            walls++;
        }
        if (right == m_wall || right == m_corr) { //is wall right?        
            walls++;
        }

        if (below == m_wall || below == m_corr) { //is wall below?  
            walls++;
        }

        //visualization output for testing below
        if(debug){ 
            cout << endl << "up" << above << endl;
            cout << left << "<<";
            cout << current;
            cout << ">>" << right << endl;
            cout << "down" << below;
            cout << endl << "walls: " << walls;
        }
        if (walls > 2) { //more than 2 walls
            if(this->vis){
                cout << graphics.at(m_corr) << flush;
            }  
            //cout << "blind" << endl;
            current = m_corr; //set to corridor (blind cannot be blind)
            if (above == m_path) { //is path above?
                proximity(x, y - 1); //recursive call for cell that is above
                return 2;
            }

            if (left == m_path) { //is path left?
                proximity(x - 1, y); //recursive call for cell that is left
                return 1;
            }
            if (right == m_path) { //is path right?
                proximity(x + 1, y); //recursive call for cell that is right
                return 3;
            }

            if (below == m_path) { //is path below?
                proximity(x, y + 1); //recursive call for cell that is below
                return 4;
            }
        }
        else {
            return 0;
        }
    }
    return 0;
}
