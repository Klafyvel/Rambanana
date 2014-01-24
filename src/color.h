#ifndef H_COLOR
#define H_COLOR

#include <stdio.h>
#if defined __linux__
#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)
#endif
#if defined _WIN32
#define clrscr() 1;
#define couleur(param) 1;
#endif
#endif
