#include "empty_path_maze.h"

empty_path_maze::empty_path_maze(string input_path, bool debug) : maze(input_path, debug ){
    //fill maze from file
    if(!maze_fill()){
        cout << "Fill failed!" << endl;
        throw runtime_error("Fill failed!");
    }
}

empty_path_maze::empty_path_maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug) : maze(x_size, y_size, start_x, start_y, end_x, end_y, debug)
{
    for(int i = 0; i < this->xs * this->ys; i++){
        if (this->map[i] == m_corr) this->map[i] = m_path; //set corridor to path, solving algorithm should replace all wrong paths
        this->map_out[i] = this->map[i]; //copy map to map_out
    }
}

bool empty_path_maze::maze_fill() { //filling maze from file for use of empty path algorithm
    if(!this->in_stream.is_open()) return false; //end if no in_stream
	string line; //create a string buffer to store currently processed line
	for (int y = 0; y < this->ys; y++) { //loop through lines of file
		getline(in_stream, line); //read next line of input file
        for (int x = 0; x < this->xs; x++) { //loop through characters of line
            if (line[x] == m_corr) line[x] = m_path; //set corridor to path, solving algorithm should replace all wrong paths
            this->map[y * this->xs + x] = line[x];
            //this->map.push_back(line[x]);
            this->map_out[y * this->xs + x] = line[x];
            //this->map_out.push_back(line[x]);
            //cout << radek[x];
        }
        //cout << endl;
	}
    this->map[this->xs * this->ys] = '\0';
    //this->map.push_back('\0');
    
    this->map_out[this->xs * this->ys] = '\0';
    //this->map_out.push_back('\0');
    return true;
}

int empty_path_maze::solve() { //brute force call of blind path detection for every point inside the maze
    for (int y = 1; y < this->ys; y++) {
        for (int x = 1; x < this->xs-1; x++) {
            //cout << this->map_out[y * xs + x];
            proximity(x, y);
        }
    }
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
