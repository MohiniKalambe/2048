#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include"graph.h"

int main(){
    initscr();
    noecho();
    cbreak();
    play();
}
