#include<iostream>	// For input, output & system commands
#include<vector>	// For infinite collection container
#include<windows.h>	// For Sleep function for delay
#include<conio.h>	// For _kbhit() and _getch for getting keybord input
using namespace std;

struct Segment{	// Representing a point on a plane
	int x, y;	// Contains X and Y cordinated
};

class Game{		// Mian game-class
	public:
		const static int vert=10, hori=50;	// Verticle and horizontal lengths in characters
		char grid[vert][hori];				// 2-D plane for game area
		vector<Segment> snake;				// Collection of points of snake
		Segment point;						// Snake food (a point)
		char direction;						// Where snake is going ('t', 'b', 'l' and 'r')
		bool end;							// Game start/end Status (false/true)

		Game(){						// Constructor
			end = false;			// Setting game-end to false
			Segment head, tail;		// Head and tails points of snake initialy
			tail.x = 5;				// Verticle position of tail to 5
			tail.y = 1;				// Horizontal position of tail to 1
			head.x = 5;				// Verticle position of head to 5
			head.y = 2;				// Horizontal position of head to 2
			snake.push_back(tail);	// Add tail to snake vector (infinte collection)
			snake.push_back(head);	// Then Head (order is tail to head in vector)
			direction = 'l';		// By default direction will be "left"

			this->setSpacesInGrid();	// Setting each character of 2D game area to spaces
			this->setSnakeInGrid();		// Setting snake points '*' in 2D game area
			this->printGame();			// Printing out the 2D game area on screen
		}	// Constructor end

		void setSpacesInGrid(){				// Function for setting spaces in grid
			for(int i=0; i<vert; i++){		// Loop for verticle axis
				for(int j=0; j<hori; j++){	// Loop for horizontal axis
					grid[i][j] = ' ';		// Setting space in each segment
				}
			}
		}	// end function

		void setSnakeInGrid(){				// Function for setting the snake segments in 2D game area
			for(Segment seg : snake){		// Loop for iterating the snake points as "seg"
				grid[seg.x][seg.y] = '*';	// Setting '*' in 2D grid according to "seg" coordinates
			}
		}	// end function

		void printGame(){	// Function for printing game's 2D game area
			Sleep(1);		// Pausing the program for 1 milisecond for stability
			system("cls");	// Clearing the screen *NOTE:* Only works in Windows
			cout << "\n ";	// Printing 2D game area top border
			for(int i=0; i<hori; i++)cout <<'=';	// Using '=' for top border
			cout << '\n';
			for(int i=0; i<vert; i++){		// Loop for verticle axis
				cout << 'I';				// Using 'I' for left border
				for(int j=0; j<hori; j++){	// Loop for horizontal axis
					cout << grid[i][j];		// printing grid
				}
				cout << "I\n";	// Using 'I' for right border
			}
			cout << ' ';		// Printing 2D game area bottom border
			for(int i=0; i<hori; i++)cout <<'=';	// Using '=' for bottom border
		}	// end function

		void move(){						// Function for making a move of snake
			int len = snake.size();			// Getting the number of segments in snake
			Segment temp = snake[len-1];	// Temporary segment for the head of snake
			switch (this->direction)		// Condition according to direction
			{
			case 'l':					// If direction is "left"
				if(temp.y < hori-1){	// If head is not overflowing from 2D game area
					temp.y += 1;		// Increasing the distance from right
				}else{					// If snake is going out of 2D game area
					temp.y = 0;			// Returning snake from right side
				}
				break;
			case 'r':					// If direction is "right"
				if(temp.y > 0){			// If head is not overflowing from 2D game area
					temp.y -= 1;		// Decrease the distance from right
				}else{					// If snake is going out of 2D game area
					temp.y = hori -1;	// Returning snake from left side
				}
				break;
			case 't':					// If direction is "top"
				if(temp.x > 0){			// If head is not overflowing from 2D game area
					temp.x -= 1;		// Decrease the distance from top
				}else{					// If head is going out of 2D game area
					temp.x = vert-1;	// Returning snake from bottom
				}
				break;
			case 'b':					// If direction is "bottom"
				if(temp.x < vert-1){	// If head is not overflowing from 2D game area
					temp.x += 1;		// Increasing distance from top
				}else{					// If head is going out of 2D game area
					temp.x = 0;			// Returning snake from top
				}
				break;
			}
			if(grid[temp.x][temp.y] == 'O'){		// If snake head is going over 'O' (Point/Food)
				snake.push_back(temp);				// Increase the length of snake
			}else if(grid[temp.x][temp.y] == '*'){	// If snake bits itself
				end = true;							// Turn game-end flag to true
			}else{								// Other wise
				Segment temp2;					// 2nd temporary segment for current position
				for(int i=len-1; i>=0; i--){	// Iterating snake segments
					temp2 = snake[i];			// Setting current position to "temp2"
					snake[i].x = temp.x;		// Setting X coordinate of snake's segment to "temp" (new position)
					snake[i].y = temp.y;		// Setting Y coordinate of snake's segment to "temp" (new position)
					temp = temp2;				// Moving temp to temp2 position
					if(i!=0)temp2 = snake[i-1];	// Moving temp2 to previous snake's segment if segment(s) remaining
				}
			}
		}	// end position

		void pointNewLocation(){		// Setting a new location for Point/Food
			int x,y;					// X and Y coordinates
			do{							// Loop for selecting right coordinates
				x = rand() % vert;		// Getting random X coordinate
				y = rand() % hori;		// Getting random Y coordinate
			}while(grid[x][y]!=' ');	// Check if X and Y coordinates are valid
			point.x = x;				// Setting X coordinate of point
			point.y = y;				// Settign Y coordinate of point
		}	// end function

		void setPoint(){	// Function for setting 'O' at point's location in 2D game area
			if(
				point.x == snake[snake.size()-1].x &&	// If X coordinate matches to snake's head and
				point.y == snake[snake.size()-1].y){	// If Y coordinate matches to snake's head
				pointNewLocation();						// Setting a new location for point
			}
			grid[point.x][point.y] = 'O';				// Placing 'O' on grid
		}
};

int main(){
	Game game;					// Initialzing game object
	game.point.x = game.vert-2;	// Setting X coordinator of point
	game.point.y = 2;			// Setting Y coordinator of point

	char c;					// Character for keybord input
	while(!game.end){		// Repeat while game is not end
		Sleep(100);			// Giving delay of 0.1 second (Used for changing speed)
		if(_kbhit()){		// If keyboard key is press
			c = _getch();	// Get character of pressed key
			switch (c){		// Condition according to character of pressed key
			case 'w':		// If small w or
			case 'W':		// If capital W
				if(game.direction!='b') game.direction='t';	// Direction to "top" if not "bottom"
				break;
			case 'a':		// If small a or
			case 'A':		// If capital A
				if(game.direction!='l') game.direction='r';	// Direction to "right" if not "left"
				break;
			case 's':		// If small s or
			case 'S':		// If capital S
				if(game.direction!='t') game.direction='b';	// Direction to "bottom" if not "top"
				break;
			case 'd':		// If small d or
			case 'D':		// If capital D
				if(game.direction!='r')game.direction='l';	// Direction to "left" if not "right"
				break;
			}
		}
		game.move();			// Making snake move
		game.setSpacesInGrid();	// Setting spaces in 2D game area
		game.setSnakeInGrid();	// Seting snake segments in 2D game area
		game.setPoint();		// Setting point segment in 2D game area
		game.printGame();		// Printing 2D game area
	}	// Loop end (when game ends)

	cout << "\nGame over . . . \n";	// Display game is ended
	Sleep(1500);					// Delay for 1.5 seconds
	system("pause");				// For "press any key to exit"
	
	return 0;
}