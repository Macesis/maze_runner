# maze_runner
Maze runner project for cpp_programming 1  
runtime console UI  
# loading maze from file
maze file format:  
```
<width>
<height>
<row1>
<row2>
...
<rowN>
```
where each row is a string of numbers: 0 - wall, 1 - path, 2 - start, 3 - end (can be changed in maze.h)  
# generating maze
maze is generated using a recursive depth first tunneling algorithm with these parameters:   
```
size_x - maze width
size_y - maze height
start_x - start point x coordinate
start_y - start point y coordinate
end_x - end point x coordinate
end_y - end point y coordinate
``` 
# solving maze
maze can be solved by breadth first search or by empty path algorithm  
# solving maze visualy
maze can be solved visualy by breadth first search or by empty path algorithm (beware of large mazes)  
# Included classes:
__maze__ - basic maze class that can import maze from file or generate maze (start and end points need to be set manually)  
__maze_solver__ - an interface for implementing the solver algorithms  
__empty_path_maze__ - a maze solver class that uses an empty path algorithm (something similar to post order traversal)  
__breadth_first_maze__ - a maze solver class that uses a Breadth-first search algorithm (something similar to post order traversal)
