#include "maze.h"

using namespace std;

maze::maze(string input_path, bool debug) { //constructor for maze
	
    this->in_stream.open(input_path); //open input stream
    this->debug = debug; //set debug mode

    string line; //create a string buffer to store currently processed line

    if (in_stream.is_open()) //are files 
    {
        if(debug){
        cout << "Files opened!" << endl;
        string radek;
        }
        getline(this->in_stream, line); //read next line of input file
        this->xs = stoi(line); //read the x size of the maze

        getline(this->in_stream, line); //read next line of input file
        this->ys = stoi(line); //read the y size of the maze

        this->map = new char[this->xs * this->ys+1]; //allocate memory for the map of the maze

        this->map_out = new char[this->xs * this->ys + 1]; //allocate memory for the outpued map of the maze
        
    }
    else {
        cout << "Files not opened!" << endl;
        throw invalid_argument("File not found");
    }
}

maze::~maze() { //destructor for maze
    this->in_stream.close();
    delete[] map;
    if(this->debug) cout << "map deleted" << endl;
    delete[] map_out;
    if(this->debug) cout << "map_out deleted" << endl;
}

void maze::print(bool exp) { //print maze (exp == 0 => map ; exp == 1 => map_out)
    char* map_to_print = this->map; //sets map_to_print to map
    if (exp) {
        map_to_print = this->map_out; //rewrites map_to_print to map_out if exp == 1
    }
    string to_cout{};
    for (int y = 0; y < this->ys; y++) { //loop through lines
        for (int x = 0; x < this->xs; x++) { //loop through columns
            switch(map_to_print[y * xs + x])
            {
                case m_corr: //if the character is corridor, print ' ' (space)
                    to_cout = " ";
                    break;
                
                case m_wall: //if the character is wall, print +
                    to_cout = "+";
                    break;

                case m_path: //if the character is path, print |
                    to_cout = "\33[1;34m|\33[0m";
                    break;

                case m_start: //if the character is start, print >;
                    to_cout = "\33[1;32m>\33[0m";
                    break;

                case m_end: //if the character is path, print <
                    to_cout = "\33[1;31m<\33[0m";                         
                    break;

                default: //if no special character assigned, print original character
                    to_cout = map_to_print[y * xs + x]; 
            }
            cout << to_cout << to_cout;
        }
        cout << endl;
    }
}

char maze::print_one(int x, int y) { //prints and returns a character that is specified position in map 
    cout << this->map[y * xs + x];
    return this->map[y * xs + x];
}

void maze::print_to_file(string path) { //print contents of map_out to output file
    if(path.empty()){
        path = "output.txt";
    }
    ofstream out_stream{path};
    for (int y = 0; y < this->ys; y++) {
        for (int x = 0; x < this->xs; x++) {
            out_stream << this->map_out[y * this->xs + x]; //write to file
        }
        out_stream << "\n"; //line end
    }
}

