#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// border char
#define BORDER_CHAR ACS_DIAMOND


int player_score = 0;
int currentDirection = 4;	// initial direction
bool isGameOverFlag = false;
time_t trophyStartTime;             // Time when the trophy was placed
int trophyDuration;                 // Random duration for trophy expiration


struct snake_body {
	int x;
	int y;
        char value;
};

// snake struct made out of body structs
struct user_snake {
	int size;
	struct snake_body segments[256];
};

struct user_snake snake;
struct snake_body trophy;

void updateBoard();
void initBoard();
void startGame();
void movePlayer();
void draw_border();
void show_score();
void placeTrophy();
void drawTrophy();
void checkTrophyCollision();
void updateTrophyState();
bool game_over();
void display_score();

int main() {
	// written by: Michael Balachandar and Gavin Bryson
	// entry point of game and starts game loop
	initscr();                     //initialize curses lib
	startGame();                   // start game loop
	endwin();                      // end curses
	return 0;
}

void moveSnake() {
	// written by: Michael Balachandar and Gavin Bryson
	int deltaX = 0;        // change in x
	int deltaY = 0;        // change in y

	//direction of movement
	switch (currentDirection) {
		case 1: deltaX = -1; break; // up
		case 2: deltaX = 1; break;  // down
		case 3: deltaY = -1; break; // left
		case 4: deltaY = 1; break;  // right
	}

	//move snake body
	for (int i = snake.size - 1; i > 0; i--) {
		snake.segments[i] = snake.segments[i - 1];
	}
	//move snake head
	snake.segments[0].x += deltaX;
	snake.segments[0].y += deltaY;

	if (snake.segments[0].x < 0) snake.segments[0].x = LINES - 1;
	if (snake.segments[0].x >= LINES) snake.segments[0].x = 0;
	if (snake.segments[0].y < 0) snake.segments[0].y = COLS - 1;
	if (snake.segments[0].y >= COLS) snake.segments[0].y = 0;
        if (snake.segments[0].x == trophy.x && snake.segments[0].y == trophy.y) {
        player_score += trophy.value - '0'; // Convert the char value to its numeric value
        snake.size += trophy.value - '0';    // Grow the snake
        placeTrophy();       // Place a new trophy
        /*displayScore();     // Update the score display*/
    }

	updateBoard();              // update board with new snake position
}

void startGame() {
    // written by: Gavin Bryson
    // starts game and clears screen
    // initalizes screen settings and snake, controls snake position

    int game_speed = 12;        // sets game speed

    clear();                    // clear screen
    curs_set(0);                // hide cursor
    noecho();                   // disable echo
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);       // allow arrow keys

    draw_border();         // draw border
    snake.size = 5;             // starting size
    snake.segments[0].x = 10;   // initialize snake head position
    snake.segments[0].y = 10;

    //initialize snake body
    for (int i = 0; i < snake.size; i++) {
        snake.segments[i].x = 10;
        snake.segments[i].y = 10 - i;
    }

    updateBoard();               // draw game board
    placeTrophy();

    // game loop
    while (!game_over()) {
        int ch = getch();                                                           // user input
        switch (ch) {
            case 'q': isGameOverFlag = true; break;                                 // quit
            case KEY_UP: if (currentDirection != 2) currentDirection = 1; break;    // change direction
            case KEY_DOWN: if (currentDirection != 1) currentDirection = 2; break;
            case KEY_LEFT: if (currentDirection != 4) currentDirection = 3; break;
            case KEY_RIGHT: if (currentDirection != 3) currentDirection = 4; break;
        }

        moveSnake();
        usleep(1000000/game_speed);
    }

    keypad(stdscr, FALSE);
    currentDirection = 0;
    sleep(1);
}

void draw_border() {
    // written by: Michael Balachandar
    // redraws border for when screen refreshes

    int colCursor = 1;
    int lineCursor = 0;
    while (colCursor < COLS || lineCursor < LINES) {
        if (colCursor < COLS && lineCursor < LINES) {
            if (colCursor % 2 == 0) {
                mvaddch(0, colCursor, BORDER_CHAR);                      // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), BORDER_CHAR); // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                              // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), ' ');         // bottom border print in reverse
            }

            mvaddch(lineCursor, 0, BORDER_CHAR);                         // left border print
            mvaddch(LINES - lineCursor, COLS - 1 , BORDER_CHAR);         // left border print in reverse
        }

        // continue printing left and right border if top and bottom borders are done printing
        else if (lineCursor < LINES - 1) {
            mvaddch(lineCursor, 0, BORDER_CHAR);
            mvaddch(LINES - lineCursor, COLS, BORDER_CHAR);
        }

        // finish printing top and bottom border if left and right borders are done printing
        else{
            if (colCursor % 2 == 0) {
                mvaddch(0, colCursor, BORDER_CHAR);                     // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), BORDER_CHAR);  // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                             // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), ' ');          // bottom border print in reverse
            }
        }
        colCursor++;
        lineCursor++;
    }
}

void updateBoard() {
    // written by: Gavin Bryson
    // updates screen by erasing and refreshing with new snake position
    // redraws border and adjusts the snake's head based on direction snake is facing

    char head;
    erase();                    // erase game window for rendering of the snake's position

    switch (currentDirection) { // decides the head char based on direction
        case 1: head = '^'; 
            break;
        case 2: head = 'v';
            break;
        case 3: head = '<';
            break;
        case 4: head = '>';
            break;
    }

    draw_border();                               // redraw border
    for (int i = 0; i < snake.size; i++) { 
        if (i == 0) {
            mvaddch(snake.segments[i].x, snake.segments[i].y, head);      // pick head segment
        }
        else {
            mvaddch(snake.segments[i].x, snake.segments[i].y, '@'); // body segment
        }
    }
    drawTrophy();
    display_score();
    checkTrophyCollision();
    updateTrophyState();
    refresh();                      // refresh screen with new snake position
}

void placeTrophy() {
    // written by: Michael Balachandar
    // generates trophy position and value
    bool validPosition = false;

    while (!validPosition) {
        // Generate random position within the screen, inside the border
        int x = rand() % (LINES - 2) + 1; // rows between 1 and LINES-2
        int y = rand() % (COLS - 2) + 1; // columns between 1 and COLS-2

        // generate a random digit between 1 and 9 for the trophy
        char trophyValue = '1' + (rand() % 9); // random digit as a character

        // check if the trophy's position overlaps with the snake
        validPosition = true;
        for (int i = 0; i < snake.size; i++) {
            if (snake.segments[i].x == x && snake.segments[i].y == y) {
                validPosition = false; // overlaps with snake find new one
                break;
            }
        }

        // If valid position is found, place the trophy
        if (validPosition) {
            trophy.x = x;
            trophy.y = y;
            trophy.value = trophyValue; // assign the trophy value
            mvaddch(trophy.x, trophy.y, trophy.value); // display trophy
            refresh();

            // expiration timer
            trophyStartTime = time(NULL);          // current time
            trophyDuration = 1 + rand() % 9;       // random duration (1-9 seconds)
        }
    }
}

void drawTrophy() {
    // written by: Michael Balachandar
    // redraw trophy for screen refresh
    mvaddch(trophy.x, trophy.y, trophy.value); // Use the trophy's value
}

void checkTrophyCollision() {
    // written by: Gavin Bryson
    // Check if the snake's head overlaps with the trophy's position
    if (snake.segments[0].x == trophy.x && snake.segments[0].y == trophy.y) {
        // Convert trophy value (char) to integer and add to playerScore
        player_score += trophy.value - '0'; // Convert char ('1'-'9') to int (1-9)

        // Place a new trophy at a valid position
        placeTrophy();
    }
}

void updateTrophyState() {
    // written by: Gavin Bryson
    // Check if the trophy has expired
    if (time(NULL) - trophyStartTime >= trophyDuration) {
        // Trophy has expired, place a new one
        placeTrophy();
    }
}

void display_score() {
    // written by: Michael Balachandar
    // display the player score in the center of the top border
    int centerX = COLS / 2;     // calculate the horizontal center of the screen
    char scoreText[50];

    // format the score text
    snprintf(scoreText, sizeof(scoreText), " Score: %d ", player_score);

    // clear the area where the score is displayed
    mvprintw(0, centerX - strlen(scoreText) / 2, "              "); 

    // display the score centered at the top border
    attron(COLOR_PAIR(5)); // green and white for score
    mvprintw(0, centerX - strlen(scoreText) / 2, "%s", scoreText); // print the score
}

bool game_over() {
    // written by: Gavin Bryson
    // checks if the snake hits its self and ends game
    int headX = snake.segments[0].x;
    int headY = snake.segments[0].y;

    //check if head collides with body
    for (int i = 1; i < snake.size; i++) {
        if (snake.segments[i].x == headX && snake.segments[i].y == headY) {
            return true;    //game over
        }
    }
    // check if snake goes outside boundry
    if (headX <= 0 || headX >= LINES - 1 || headY <= 0 || headY >= COLS - 1) {
        return true;  // game over
    }
    // reach max score
    if (snake.size >= ((LINES*2) + (COLS*2)) / 2) {
        return true;
    }
    return false;
}
