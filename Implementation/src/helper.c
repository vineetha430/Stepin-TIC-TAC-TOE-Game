/*
 * TIC_TAC_TOE
 *
 * 
 * Copyright (C) BytesClub 2017, MIT
 *
 * helper.c
 */

#ifndef __helper_h
#include <helper.h>
#endif

#ifdef __termios_h
struct termios orig_termios;

static void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
#endif

inline void scand(int* a)
{
    register int b = 0, c = get();
    while (b >= '0' && b <= '9') {
        c = (c << 3) + (c << 1) + b - '0', b = get();
    }
    if (b == '\n' || b == EOF) {
        *a = c;
        return;
    }
    while (b ^ '\n' && b ^ EOF) {
        b = get();
    }
}

void greet(void)
{
    CLEAR;
    printf("WELCOME TO GAME OF TIC_TAC_TOE\nCreated by: Bytes Club\n\n");
    printf("Contributers:-\n\n");
    printf("Kolli Vineetha       :- <kollivineetha1828@gmail.com>\n");
    printf("Bandi Veda           :- <vedabandi124@gmail.com>\n");
    printf("Bandi Havish         :- <Bandihavish143@gmail.com>\n");
    printf("Tupakula Bhargavi    :- <bhargavitupakula7@gmail.com>\n");
    printf("Korlepara Pravallika :- <pravallika7707gmail.com>\n");
    printf("\nLoading. Please Wait..."), fflush(stdout);
#ifdef __termios_h
    enableRawMode();
#endif
    SLEEP;
    printf("\rLoading Completed. Press ENTER to continue... "), fflush(stdout);
    scanf("%*[^\n]%*1[\n]");
    get();
#ifdef __termios_h
    disableRawMode();
#endif
}

void init(int n, char* A)
{
    for (int i = 0, l = n * n; i < l && !(A[i] = 0); i++);
}

static char* displayVal(char val) {
    if (val == 'X') {
        return (ANSI_RED "  %c " ANSI_RESET);
    }
    return (ANSI_YELLOW "  %c " ANSI_RESET);
}

void show(int n, char* A)
{
    CLEAR;
    for (int i = !putchar('\n'); i < n; i++) {
        for (int j = 0; (j < n && (!j || printf(ANSI_BLUE "|" ANSI_RESET))) || !putchar('\n'); j++) {
            int pos = i * n + j;
            char val = A[pos];
            if (val) {
                printf(displayVal(val), val);
            } else {
                printf(" %2d ", (pos + 1));
            }
        }
        printf(ANSI_BLUE);
        for (int j = 0; !(i + 1 == n) && (j < n || !putchar('\n')); j++)
            printf("-----");
        printf(ANSI_RESET);
    }
}

int check(int n, char* A)
{
    int row, col, flag = 0;
    // Row-wise checking
    for (row = 0; row < n; row++) {
        for (col = 1; col < n || !(flag = 1); col++) {
            if (!A[row * n + col] || A[row * n + col] != A[row * n + col - 1]) {
                break;
            }
        }
        if (flag) {
            return A[row * n + col - 1] == 'X' ? 1 : 2;
        }
    }
    // Column-wise checking
    for (col = 0; col < n; col++) {
        for (row = 1; row < n || !(flag = 1); row++) {
            if (!A[row * n + col] || A[row * n + col] != A[(row - 1) * n + col]) {
                break;
            }
        }
        if (flag) {
            return A[(row - 1) * n + col] == 'X' ? 1 : 2;
        }
    }
    // Upper diagonal checking
    for (row = col = 1; row < n || !(flag = 1); row++, col++) {
        if (!A[row * n + col] || A[row * n + col] != A[(row - 1) * n + col - 1]) {
            break;
        }
    }
    if (flag) {
        return A[0] == 'X' ? 1 : 2;
    }
    // Lower diagonal checking
    for (row = 1, col = n - 1; col > 0 || !(flag = 1); row++, col--) {
        if (!A[row * n + col - 1] || A[row * n + col - 1] != A[(row - 1) * n + col]) {
            break;
        }
    }
    if (flag) {
        return A[n - 1] == 'X' ? 1 : 2;
    }
    // Checking for empty position
    for (row = col = 0; col < n || (col = 0, ++row) < n || !(flag = 1); col++) {
        if (A[row * n + col] == '\0') {
            break;
        }
    }
    // Match Tied
    if (flag) {
        return -1;
    }
    // Match is on
    return 0;
}