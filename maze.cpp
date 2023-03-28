#include "maze.h"

using namespace std;

void maze::visit_cell(int x, int y)
{
    //get direct neighbors
    char above = this->map[(y - 1) * xs + x];
    char left = this->map[y * xs + x - 1];
    char right = this->map[y * xs + x + 1];
    char below = this->map[(y + 1) * xs + x];

    //get diagonal neighbors
    char upleft = this->map[(y - 1) * xs + x - 1];
    char upright = this->map[(y - 1) * xs + x + 1];
    char downleft = this->map[(y + 1) * xs + x - 1];
    char downright = this->map[(y + 1) * xs + x + 1];

    //check if there is more than one coridor (and remember the direction)
    int coridors = 0;
    int direction = 0;
    if (above == m_corr) { //is coridor above?
        coridors++;
        direction = 1;
    }

    if (left == m_corr) { //is coridor left?        
        coridors++;
        direction = 2;
    }
    if (right == m_corr) { //is coridor right?        
        coridors++;
        direction = 3;
    }

    if (below == m_corr) { //is coridor below?  
        coridors++;
        direction = 4;
    }

    //visualization output for testing below
    if(debug){
        cout << "coridors: " << coridors << endl;
        cout << "direction: " << direction << endl;
        cout << "X: " << x << " Y: " << y << endl;
    }
    if(coridors>1) return;

    vector<pair<int,int>> candidates;
    switch(direction)
    {
        case 1:
            //check if there is a coridor in the diagonal
            if(downleft == m_corr || downright == m_corr) return;
            //go left, right and down
            candidates.push_back({x - 1, y});
            candidates.push_back({x + 1, y});
            candidates.push_back({x, y + 1});
            break;

        case 2:
            //check if there is a coridor in the diagonal
            if(upright == m_corr || downright == m_corr) return;
            //go up, right and down
            candidates.push_back({x, y - 1});
            candidates.push_back({x + 1, y});
            candidates.push_back({x, y + 1});
            break;
        case 3:
            //check if there is a coridor in the diagonal
            if(upleft == m_corr || downleft == m_corr) return;
            //go up, left and down
            candidates.push_back({x, y - 1});
            candidates.push_back({x - 1, y});
            candidates.push_back({x, y + 1});
            break;
        case 4:
            //check if there is a coridor in the diagonal
            if(upleft == m_corr || upright == m_corr) return;
            //go up, left and right
            candidates.push_back({x, y - 1});
            candidates.push_back({x - 1, y});
            candidates.push_back({x + 1, y});
            break;
        default:
            //go in all directions
            candidates.push_back({x, y - 1});
            candidates.push_back({x - 1, y});
            candidates.push_back({x + 1, y});
            candidates.push_back({x, y + 1});
            break;
    }   
    //set the cell to coridor (all conditions are met)
    this->map[y * xs + x] = m_corr;

    //shuffle the candidates and visit them
    random_shuffle(candidates.begin(), candidates.end());
    for(auto candidate : candidates)
    {
        //check if the candidate is out of bounds
        if(candidate.first <= 0 || candidate.first >= xs-1 || candidate.second <= 0 || candidate.second >= ys-1) continue;
        visit_cell(candidate.first, candidate.second);
    }
}

maze::maze(string input_path, bool debug) : debug(debug)
{ // constructor for maze

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
    srand(time(NULL));
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

    //generate maze (start at start)
    //visit_cell(start_x, start_y);

    //generate maze (start at end)
    visit_cell(end_x, end_y);

    //place start
    this->map[start_y*xs+start_x] = m_start;
    //place end
    this->map[end_y*xs+end_x] = m_end;

    for(int i = 0; i < actual_size; i++){
        this->map_out[i] = this->map[i];
    }

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
                    to_cout = "X";
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

