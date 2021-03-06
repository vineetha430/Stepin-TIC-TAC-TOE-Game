/*
 * TIC_TAC_TOE
 *
 *
 * Copyright (C) BytesClub 2017, MIT
 *
 * helper.h
 */

#define _XOPEN_SOURCE 500

#ifndef __helper_h
#define __helper_h

#ifndef __color_h
#include <color.h>
#endif
#ifndef __stdbool_h
#include <stdbool.h>
#endif
#ifndef __stdio_h
#include <stdio.h>
#endif
#ifndef __stdlib_h
#include <stdlib.h>
#endif
#ifndef __time_h
#include <time.h>
#endif
#if defined(_WIN32) || defined(__WIN32__)
#ifndef __windows_h
#include <windows.h>
#define SLEEP Sleep(5000)
#define CLEAR system("clear")
#endif
#else
#ifndef __termios_h
#include <termios.h>
#endif
#ifndef __unistd_h
#include <unistd.h>
#define SLEEP sleep(5)
#define CLEAR system("clear")	//tput reset
#endif
#endif

/*
 * Minimum and Maximum Dimension
 */
#define DIM_MIN 3
#define DIM_MAX 9
#ifdef getchar_unlocked
#define get getchar_unlocked
#else
#define get getchar
#endif

/*
 * Takes an integer from stdin
 */
void scand(int*);

/*
 * Initialization of the Board
 */
void init(int, char*);

/*
 * Prints a Welcome Message
 */
void greet(void);

/*
 * Loads the Modified Board
 */
void show(int, char*);

/*
 * Checks if a user wins
 * Returns 1 if X wins
 * Returns 2 if O wins
 * Returns -1 if draw
 * Returns 0 otherwise
 */
int check(int, char*);

/*
 * Updates Board State into Cache
 */
void newState(int, const char*);

/*
 * Log the States and Result
 */
void setResult(int, int);

/*
 * Returns a move according to board
 */
int moveAI(int, const char*);

#endif
