#ifndef KEYPAD_H
#define KEYPAD_H




#define MAX_ROWS 8
#define MAX_COLS 8


typedef struct
{
    int rowPins[MAX_ROWS];
    int colPins[MAX_COLS];
}Keypad;

static char keypad4x4_layout[4][4] =
{
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
};

static char keypad4x3_layout[4][3] =
{
    { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' },
    { '*', '0', '#' }
};

void setupKeypad(int cols, int rows, Keypad kp);
char KeypadScan(Keypad kp, char kp_layout[MAX_ROWS][MAX_COLS]);
#endif