#include "breadth_first_maze.h"

breadth_first_maze::breadth_first_maze(string input_path, bool debug) : maze(input_path, debug ){
    //fill maze from file
    if(!maze_fill()){
        cout << "Fill failed!" << endl;
        throw runtime_error("Fill failed!");
    }
}
breadth_first_maze::breadth_first_maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug) : maze(x_size, y_size, start_x, start_y, end_x, end_y, debug) {
    //fill maze randomly
    for(int i = 0; i < this->xs * this->ys; i++){
        
    }
}

breadth_first_maze::~breadth_first_maze()
{
    while(!this->joints.empty()){
        delete this->joints.back();
        this->joints.pop_back();
    }
    //this->joints.~vector(); //this does not work for some reason
    if(this->debug) cout << "joints vector deleted" << endl;

    clear_queue(this->joint_buffer);
    if(this->debug) cout << "joint buffer deleted" << endl;
};

bool breadth_first_maze::maze_fill() { //filling maze for use of Breadth-first search algorithm
    if(!this->in_stream.is_open()) return false; //end if no in_stream
    string line; //create a string buffer to store currently processed line
    for (int y = 0; y < this->ys; y++) { //loop through lines of file
        getline(in_stream, line); //read next line of input file
        for (int x = 0; x < this->xs; x++) { //loop through characters of line
            this->map_out[y * this->xs + x] = line[x]; //put original character into map_out
            if (line[x] == m_corr) line[x] = m_reserved; //set empty corridor to reserved (unexplored)
            if (line[x] == m_start) { //if start create a starting joint
                joint* discover = new joint(nullptr, y * xs + x); //create a joint with nullptr origin
                this->joints.push_back(discover); //store joint
            }
            this->map[y * this->xs + x] = line[x]; //put character into map (corridor has been replaced by reserved)
            if(debug) cout << line[x];
        }
        if(debug) cout << endl;
    }
    this->map[this->xs * this->ys] = '\0'; //end the map with a \0 end symbol
    this->map_out[this->xs * this->ys] = '\0';//end the map_out with a \0 end symbol
    return true;
}

int breadth_first_maze::solve() { //solves the maze by using a Breadth-first search algorithm
    joint_buffer.push(joints[0]); //put start in buffer
    while (!this->joint_buffer.empty()) { //loop while buffer isn't empty
        joint* orig = joint_buffer.front(); //get joint at the front of the queue
        joint_buffer.pop(); //move queue
        int y = (orig->getpos()+1) % this->xs; //calculate y position
        int x = orig->getpos() - y * this->xs; //calculate x position

        if (this->map[y * xs + x] != m_corr) {
            char above = this->map[(y - 1) * xs + x];
            char left = this->map[y * xs + x - 1];
            char right = this->map[y * xs + x + 1];
            char below = this->map[(y + 1) * xs + x];

            if (above == m_end || left == m_end || right == m_end || below == m_end) { //proper end
                clear_queue(joint_buffer); //clear buffer
                this->found_path = true; //set found_path to true (indicates that the maze solution has been found)
                joints.push_back(new joint(orig, y * xs + x)); //push back the last joint so that stamp can just start from the last joint
                this->stamp();
                return 0;
            }
            if(this->map[y * xs + x] == m_reserved) this->map[y * xs + x] = m_corr; //change reserved (unexplored) to corridor (explored)
            
            if (above == m_reserved) { //is reserved OR end above?
                joint* discover = new joint(orig, (y - 1) * xs + x); //create a new joint
                this->joints.push_back(discover); //save the joint
                joint_buffer.push(discover); //push joint into buffer
            }
            
            if (left == m_reserved) { //is reserved OR end left?        
                joint* discover = new joint(orig, y * xs + x - 1);
                this->joints.push_back(discover);
                joint_buffer.push(discover);
            }
            
            if (right == m_reserved) { //is reserved OR end right?        
                joint* discover = new joint(orig, y * xs + x + 1);
                this->joints.push_back(discover);
                joint_buffer.push(discover);
            }

            if (below == m_reserved) { //is reserved OR end below?  
                joint* discover = new joint(orig, (y + 1) * xs + x);
                this->joints.push_back(discover);
                joint_buffer.push(discover);
            }

            //visualization output for testing below
            // 
            if(debug){
                cout << endl << "   " << this->map[(y - 1) * xs + x] << endl;
                cout << this->map[y * xs + x - 1] << "<<" << this->map[y * xs + x];
                cout << ">>" << this->map[y * xs + x + 1] << endl;
                cout << "   " << this->map[(y + 1) * xs + x];
                cout << endl << "-------------------";
            }
        }
    }
    return 1;
}

int breadth_first_maze::stamp() { //intiates stamping the solution into map_out
    if (this->found_path) { //check if there is a solution to stamp
        internal_stamp(joints.back()); //begin stamping
        return 0;
    }
    return 1;
}

int breadth_first_maze::internal_stamp(joint* joint) {
    if (joint == nullptr || joint->getorig() == nullptr) { //end stamping
        return 1;
    }
    else {
        this->map_out[joint->getpos()] = m_path; //stamp m_path constant to a point in map_out
        internal_stamp(joint->getorig()); //recursive call
    }
    return 0;
}

void breadth_first_maze::clear_queue(queue<joint*>& q) //clearing queue by swaping with empty one
{
    //code taken from https://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently
    queue<joint*> empty;
    swap(q, empty);
}