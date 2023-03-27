#include "maze.h"

using namespace std;

maze::maze(string input_path, bool debug) : debug(debug) { //constructor for maze
	
    this->in_stream.open(input_path); //open input stream

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

maze::maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug) : xs(x_size), ys(y_size), debug(debug) {
    start_x--;
    start_y--;
    end_x--;
    end_y--;

    if(start_x >= xs || start_x < 0 || start_y >= ys || start_y < 0 ||          //out of bounds 
    (start_x == 0 && start_y == 0) || (start_x == xs-1 && start_y == 0) ||      //upper corners
    (start_x == 0 && start_y == ys-1) || (start_x == xs-1 && start_y == ys-1)   //lower corners
    ){
        cout << "Start out of bounds!" << endl;
        throw invalid_argument("Start out of bounds");
    }
    if(end_x >= xs || end_x < 0 || end_y >= ys || end_y < 0 ||                  //out of bounds 
    (end_x == 0 && end_y == 0) || (end_x == xs-1 && end_y == 0) ||              //upper corners
    (end_x == 0 && end_y == ys-1) || (end_x == xs-1 && end_y == ys-1)           //lower corners
    ){
        cout << "End out of bounds!" << endl;
        throw invalid_argument("End out of bounds");
    }
    int actual_size = this->xs * this->ys + 1;
    this->map = new char[actual_size]; //allocate memory for the map of the maze
    this->map_out = new char[actual_size]; //allocate memory for the outpued map of the maze

    this->map[actual_size-1] = '\0';
    this->map_out[actual_size-1] = '\0';

    for(int i = 0; i < actual_size; i++){
        this->map[i] = m_wall;
    }

    //todo generate maze

    //place start
    this->map[start_x+start_y*xs] = m_start;
    this->map[end_x+end_y*xs] = m_end;
    //place end
}

maze::~maze() { //destructor for maze
    this->in_stream.close();
    delete[] map;
    if(this->debug) cout << "map deleted" << endl;
    delete[] map_out;
    if(this->debug) cout << "map_out deleted" << endl;
}

void maze::print(bool exp) const { //print maze (exp == 0 => map ; exp == 1 => map_out)
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
                    to_cout = "\33[1;34m";
                    to_cout += "|";
                    to_cout += "\33[0m";
                    break;

                case m_start: //if the character is start, print >;
                    to_cout = "\33[1;32m";
                    to_cout += ">";
                    to_cout += "\33[0m";
                    break;

                case m_end: //if the character is path, print <
                    to_cout = "\33[1;31m";
                    to_cout += "<";
                    to_cout += "\33[0m";                         
                    break;

                default: //if no special character assigned, print original character
                    to_cout = map_to_print[y * xs + x]; 
            }
            cout << to_cout << to_cout;
        }
        cout << endl;
    }
}

char maze::print_one(int x, int y) const{ //prints and returns a character that is specified position in map 
    cout << this->map[y * xs + x];
    return this->map[y * xs + x];
}

void maze::print_to_file(string path) const{ //print contents of map_out to output file
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

