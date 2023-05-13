#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stdexcept>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>

using namespace std;

//constants for maze format

const char m_wall = '1'; //a wall ... duh
const char m_corr = '0'; //explored not part of path
const char m_path = '4'; //explored on path
const char m_start = '2'; //starting point
const char m_end = '3'; //ending point
const char m_reserved = '5'; //is a reserved symbol, it will be used as an unexplored id

const unordered_map<char,string> graphics = {
	{m_wall,"██"},
	{m_corr,"  "},
	{m_path,"\33[1;34m||\33[0m"},
	{m_start,"\33[1;32m>>\33[0m"},
	{m_end,"\33[1;31m<<\33[0m"},
	{m_reserved,"XX"}
};

/**
*Class for solving mazes
*/
class maze
{
private:
	void visit_cell(int x, int y);
protected:
	/**
	*map used for solving
	*/
	//char* map = nullptr; 
	vector<char> map;

	/**
	*map for output
	*/
	//char* map_out = nullptr;
	vector<char> map_out;

	/**
	*xs -> x size; ys -> y size
	*/
	int xs = 0, ys = 0;

	/**
	*stream for reading input file
	*/
	ifstream in_stream;

	/** 
	*stores wether the maze is in debug mode
	*/
	bool debug = false;

public:
	/**
	*load from file constructor for maze
	*@param input_path -> Location of file for input
	*/
	maze(string input_path, bool debug = false); //constructor

	/**
	*generate constructor for maze
	*@param x_size -> x size of maze
	*@param y_size -> y size of maze
	*@param start_x -> x position of starting point
	*@param start_y -> y position of starting point
	*@param end_x -> x position of ending point
	*@param end_y -> y position of ending point
	*/
	maze(int x_size, int y_size, int start_x, int start_y, int end_x, int end_y, bool debug = false); //constructor

	/**
	*copy constructor for maze 
	*/
	maze(const maze& other); //copy constructor

	/**
	*destructor for maze
	*/
	virtual ~maze(); //destructor

	//---------------------------------------------------------------------------
	//utility methods for printing of maze
	/**
	*print the entire maze 
	*\param exp -> 0 prints map ; 1 prints map_out)
	*/
	void print(bool exp) const;

	/**
	*prints a character that is at specified position in map 
	*/
	char print_one(int x, int y) const; 

	//move cursor to a specific pos
	static void gotoxy(int x, int y) {
		printf("\033[%d;%dH", y, 2*x+1);
	}

	/**
	*print contents of map_out to output file
	*/
	void print_to_file(string path = "") const;
};

/*
*Virtualy inheriting interface for maze solvers.
*Has to inherit virtualy so that i don't have to define passing constructors (they would just call the same constructor in maze)
*/
class maze_solver : public virtual maze{
protected:
	bool vis = false; //visualize step by step
public:
	//---------------------------------------------------------------------------
	//these methods are for working with the maze

	/**
	*pre processing for search algorithm
	*automaticaly called by constructor
	*/
	virtual bool maze_fill() = 0;

	/**
	*solves the maze by using an algorithm
	*/
	virtual int solve(bool visualize = false) = 0;

};