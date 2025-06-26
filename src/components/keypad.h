#ifndef KEYPAD_H
#define KEYPAD_H




#define KEYPAD_4X4_MAX_ROWS 4
#define KEYPAD_4X4_MAX_COLS 4

#define KEYPAD_4X3_MAX_ROWS 4
#define KEYPAD_4X3_MAX_COLS 3


typedef struct
{
    int rowPins[KEYPAD_4X4_MAX_ROWS];
    int colPins[KEYPAD_4X4_MAX_COLS];
}Keypad4x4;

typedef struct
{
    int rowPins[KEYPAD_4X3_MAX_ROWS];
    int colPins[KEYPAD_4X3_MAX_COLS];
}Keypad4x3;

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

void setupKeypad4x4(Keypad4x4 kp);
char KeypadScan4x4(Keypad4x4 kp, char kp_layout[KEYPAD_4X4_MAX_ROWS][KEYPAD_4X4_MAX_COLS]);

void setupKeypad4x3(Keypad4x3 kp);
char KeypadScan4x3(Keypad4x3 kp, char kp_layout[KEYPAD_4X3_MAX_ROWS][KEYPAD_4X3_MAX_COLS]);
#endif