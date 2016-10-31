#include<ncurses.h>
void diplay(WINDOW *wn,int* a[],int n);
int check1(int* a[],int n);
int check2(int* a[],int n);
int win(int* a[],int n);
int random_int(int r);
void display_up_sum(int* a[],int n, int *score);
void display_down_sum(int* a[],int n, int *score);
void display_left_sum(int* a[],int n, int *score);
void display_right_sum(int* a[],int n, int *score);
void display_up(int* a[],int n);
void display_down(int* a[],int n);
void display_left(int* a[],int n);
void display_right(int* a[],int n);
void random_number(int* a[],int n);
void play();
int start(WINDOW *wn);
