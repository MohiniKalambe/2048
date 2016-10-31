#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "graph.h"
#include <unistd.h>
#define MAX 100000

int initColor() {
	if (!has_colors()) {
		return 1;
	} else {
		start_color();
		init_pair(0, 5, 0);
		init_pair(2, COLOR_WHITE, 1);
		init_pair(4, COLOR_WHITE, 2);
		init_pair(8, COLOR_WHITE, 3);
		init_pair(16, COLOR_WHITE, 165);
		init_pair(32, COLOR_WHITE, 20);
		init_pair(64, COLOR_WHITE, 6);
		init_pair(128, COLOR_WHITE, 40);
		init_pair(256, COLOR_WHITE, 2);
		init_pair(512, COLOR_WHITE, 125);
		init_pair(1024, COLOR_WHITE, 4);
		init_pair(2048, COLOR_WHITE, 5);
		init_pair(4096, COLOR_WHITE, 1);
		init_pair(8192, COLOR_WHITE, 2);
		init_pair(1024, COLOR_WHITE, 4);
		init_pair(2048, COLOR_WHITE, 5);
		init_pair(12, COLOR_YELLOW, COLOR_BLACK);
		init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	}
	return 0;
}
int check1(int* a[],int n){
	int i, j;
	int flag = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n - 1; j++){
			if(a[i][j] == a[i][j + 1]){
				flag = 1;
				return flag;
			}
		}
		if(flag == 1)	
			return flag;
	} 
	if(flag == 0){
		for(i = 0;i < n - 1; i++){
			for(j = 0; j < n; j++){
				if(a[i][j] == a[i + 1][j]){
					flag = 1;
					return flag;
				}
			}
			if(flag == 1)
				return flag;
		}
	}
	return flag;
}
int check2(int* a[],int n){
	int i, j;
	int flag = 0;
	for(i = 0;i < n;i++){
		for(j = 0; j < n;j++){
			if(a[i][j] == 0){
				flag = 1;
				return flag;
			}
		}
	} 
	return flag;
}
int win(int* a[],int n){
	int i, j;
	for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
			if(a[i][j] == 126 && n == 3)
				return 1;
			else if(a[i][j] == 2048 && n == 4)
				return 1;
			else if(a[i][j] == 4096 && n == 5)
				return 1;
			else if(a[i][j] == 4096 && n == 6)
				return 1;
			else if(a[i][j] == 8192 && n == 7)
				return 1;
			else if(a[i][j] == 16384 && n == 8)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}
int random_int(int r){
        int n;
        n = rand() % r;
        return n;
}
void display(WINDOW *wn,int *a[],int n){
	int x = 7;	
	if(n == 3)	
		x = 12;
	else if(n == 4)	
		x = 10;
	else if(n == 7 || n == 8)
		x = 2;
	for(int i = 0;i < n; i++){
		int y = 40;
		if(n == 3 || n == 4 || n == 5)
			y = 50;
		for(int j = 0;j < n;j++){
			int color = a[i][j];
			mvwprintw(wn, x + 1, y + 2,"_____");
			wattron(wn, COLOR_PAIR(color));
			wattron(wn, A_BOLD);	
			mvwprintw(wn, x + 2, y + 1,"*     *");
			if(a[i][j]/10 == 0)
			mvwprintw(wn, x + 3, y,"|   %d   |",a[i][j]);
			else if(a[i][j]/100 == 0)
			mvwprintw(wn, x + 3, y,"|  %d   |",a[i][j]);
			else if(a[i][j]/1000 == 0)
			mvwprintw(wn, x + 3, y,"|  %d  |",a[i][j]);
			else if(a[i][j]/10000 == 0)
			mvwprintw(wn, x + 3, y,"| %d  |",a[i][j]);		
			mvwprintw(wn, x + 4, y + 1,"*_____*");
			wattroff(wn, COLOR_PAIR(color));
			wattroff(wn, A_BOLD);			
			y = y + 9;
			}
			y = 5;
			x = x + 5;
	}

}
void display_up_sum(int* a[],int n, int *score){
	int i, j;
	for(j = 0; j < n; j++){
		for(i = 0; i < n - 1; i++){
			if(a[i][j] == a[i + 1][j]){
				a[i][j] = a[i + 1][j] + a[i][j];
				a[i + 1][j] = 0;
				*score = *score + a[i][j];
			}
		}
	}

}
void display_up(int* a[],int n){
	int i, j, k;
	for(j = 0; j < n; j++){
		for(i = 0; i < n ; i++){
			if(a[i][j] == 0) {	
				for(k = i + 1;k < n;k++){
					if(a[k][j]){
						a[i][j] = a[k][j];
                                		a[k][j] = 0;
						break;
					}
                        	}
			}	
		}
	}
}
void display_down_sum(int* a[],int n, int *score){
	int i, j;
	for(j = 0; j < n; j++){
		for(i = n - 1; i > 0; i--){
			if(a[i][j] == a[i - 1][j]){
				a[i][j] = a[i - 1][j] + a[i][j];
				a[i - 1][j] = 0;
				*score = *score + a[i][j];
			}
		}	
	}	
}
void display_down(int* a[],int n){
	int i, j, k;
	for(j = 0; j < n; j++){
		for(i = n - 1; i >=0; i--){
			if(a[i][j] == 0){
				for(k = i - 1; k >= 0; k--){
                                	if(a[k][j]){
						a[i][j] = a[k][j];
                                		a[k][j] = 0;
                       			break;
					}
				}
			}
		}	
	}
}
void display_right_sum(int* a[],int n, int *score){
	int i, j;
	for(i = 0;i < n;i++){
		for(j = n - 1;j > 0;j--){
                        if(a[i][j] == a[i][j - 1]){
                                a[i][j] = a[i][j - 1] + a[i][j];
                                a[i][j - 1] = 0;
				*score = *score + a[i][j];
                        }
                }
	}
}
void display_right(int* a[],int n){
	int i, j, k;
	for(i = 0;i < n;i++){
		for(j = n - 1;j >= 0;j--){
			if(a[i][j] == 0){
				for(k = j - 1;k >= 0;k--){
                                	if(a[i][k]){
						a[i][j] = a[i][k];
                                		a[i][k] = 0;
						break;
					}
				}
                        }

		}
	}
}
void display_left_sum(int* a[],int n, int *score){
	int i, j;
	for(i = 0; i < n; i++){
                for(j = 0; j < n - 1; j++){
                        if(a[i][j] == a[i][j + 1]){
                                a[i][j] = a[i][j + 1] + a[i][j];
                                a[i][j + 1] = 0;
				*score = *score + a[i][j];
                        }
                }
        }
}
void display_left(int* a[],int n){
	int  i, j, k;
	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			if(a[i][j] == 0){
                        	for(k = j + 1;k < n;k++){       	
					if(a[i][k]){
						a[i][j] = a[i][k];
                                		a[i][k] = 0;
						break;
                        		}
				}
			}
		}
	}
}
void random_number(int* a[],int n){
	int i, j;
	i = random_int(n);
        j = random_int(n);
        if(a[i][j] == 0){
                a[i][j] = (rand() & 3) ? 2 : 4;
        }
	else{
		if(check2(a, n))
			random_number(a, n);
	}
}
void arrow_right(WINDOW *wn){
	int x = 15, y = 120;
	wattron(wn, COLOR_PAIR(32));
	mvwprintw(wn, x + 1, y,"   ");
	mvwprintw(wn, x + 2, y + 2,"   ");
	mvwprintw(wn, x + 3, y + 4,"   ");
	mvwprintw(wn, x + 4, y + 6,"   ");
	mvwprintw(wn, x + 5, y + 8,"   ");
	mvwprintw(wn, x + 6, y + 6,"   ");
	mvwprintw(wn, x + 7, y + 4,"   ");
	mvwprintw(wn, x + 8, y + 2,"   ");
	mvwprintw(wn, x + 9, y ,"   ");
	wattroff(wn, COLOR_PAIR(32));
}
void arrow_left(WINDOW *wn){
	int x = 15, y = 10;
	wattron(wn, COLOR_PAIR(32));
	mvwprintw(wn, x + 1, y + 8,"   ");
	mvwprintw(wn, x + 2, y + 6,"   ");
	mvwprintw(wn, x + 3, y + 4,"   ");
	mvwprintw(wn, x + 4, y + 2,"   ");
	mvwprintw(wn, x + 5, y ,"   ");
	mvwprintw(wn, x + 6, y + 2,"   ");
	mvwprintw(wn, x + 7, y + 4,"   ");
	mvwprintw(wn, x + 8, y + 6,"   ");
	mvwprintw(wn, x + 9, y + 8,"   ");
	wattroff(wn, COLOR_PAIR(32));
}
void win1(WINDOW *wn){
	wclear(wn);
	int x = 15, y = 30;
	wattron(wn, COLOR_PAIR(32));
	mvwprintw(wn, x + 1, y,"11      11    88     11    11   	11    11  11  11    11");
	mvwprintw(wn, x + 2, y,"  11  11    88  88   11    11   	11    11  11  111   11");
	mvwprintw(wn, x + 3, y,"    11     88    88  11    11   	11 11 11  11  11 11 11");
	mvwprintw(wn, x + 4, y,"    11      88  88   11    11   	111  111  11  11   111");
	mvwprintw(wn, x + 5, y,"    11        88       1111     	11    11  11  11    11");
	wattroff(wn, COLOR_PAIR(32));
	wattron(wn, COLOR_PAIR(4));
	mvwprintw(wn,25,50,"DO YOU WANT TO PLAY AGAIN? (Y/N)");
	wattroff(wn, COLOR_PAIR(4));
}
void lost1(WINDOW *wn){
	wclear(wn);
	int x = 15, y = 30;
	wattron(wn, COLOR_PAIR(32)); 
	mvwprintw(wn, x + 1, y,"11        11    888     11      11       11        888         1111  11111111");
	mvwprintw(wn, x + 2, y,"  11    11    88   88   11      11       11      88   88     111        11   ");
	mvwprintw(wn, x + 3, y,"    1111     88     88  11      11       11     88     88   111         11   ");
	mvwprintw(wn, x + 4, y,"     11      88     88  11      11       11     88     88      111      11   ");   
	mvwprintw(wn, x + 5, y,"     11       88   88    11    11        11      88   88        111     11   ");
	mvwprintw(wn, x + 6, y,"     11         888        1111          1111111   888      11111       11   ");
	wattroff(wn, COLOR_PAIR(32));
	wattron(wn, COLOR_PAIR(4));
	mvwprintw(wn,25,50,"DO YOU WANT TO PLAY AGAIN? (Y/N)");
	wattroff(wn, COLOR_PAIR(4));
}
void front_page(WINDOW *wn){
	int x = 15 , y = 40 , r = 64, t = 15;
	wattron(wn, COLOR_PAIR(4));
	wattron(wn, A_BOLD);
	for(y = 40; y < 64; y++){
		wclear(wn);
		wattron(wn, COLOR_PAIR(4));
		wattron(wn, A_BOLD);
		mvwprintw(wn, x + 1, y,"2222       ");
		mvwprintw(wn, x + 2, y,"   2222    ");
		mvwprintw(wn, x + 3, y,"     2222  ");
		mvwprintw(wn, x + 4, y,"     2222  ");
		mvwprintw(wn, x + 5, y,"   2222    ");
		mvwprintw(wn, x + 6, y,"2222       ");
		mvwprintw(wn, x + 7, y,"22222222222");
		mvwprintw(wn, t + 1, r,"2222       ");
		mvwprintw(wn, t + 2, r,"   2222    ");
		mvwprintw(wn, t + 3, r,"     2222  ");
		mvwprintw(wn, t + 4, r,"     2222  ");
		mvwprintw(wn, t + 5, r,"   2222    ");
		mvwprintw(wn, t + 6, r,"2222       ");
		mvwprintw(wn, t + 7, r,"22222222222");
		usleep(20000);
		wrefresh(wn);
	}
	usleep(30000);
	wclear(wn);
	y = 40;
	mvwprintw(wn, x + 1, y + 24,"     444   ");
	mvwprintw(wn, x + 2, y + 24,"   44 44   ");
	mvwprintw(wn, x + 3, y + 24,"  44  44   ");
	mvwprintw(wn, x + 4, y + 24," 44   44   ");
	mvwprintw(wn, x + 5, y + 24,"44444444444");
	mvwprintw(wn, x + 6, y + 24,"      44   ");
	mvwprintw(wn, x + 7, y + 24,"      44   ");
	wrefresh(wn);
	usleep(1000000);
	wclear(wn);
	y = 40;
	wattroff(wn, COLOR_PAIR(4));
	wattron(wn, COLOR_PAIR(2));
	mvwprintw(wn, x + 1, y + 1,"2222        ");
	mvwprintw(wn, x + 2, y + 1,"   2222     ");
	mvwprintw(wn, x + 3, y + 1,"     2222   ");
	mvwprintw(wn, x + 4, y + 1,"     2222   ");
	mvwprintw(wn, x + 5, y + 1,"   2222     ");
	mvwprintw(wn, x + 6, y + 1,"2222        ");
	mvwprintw(wn, x + 7, y + 1,"22222222222 ");
	wattroff(wn, COLOR_PAIR(2));	
	wattron(wn, COLOR_PAIR(64));
	mvwprintw(wn, x + 1, y + 13,"   000000   ");
	mvwprintw(wn, x + 2, y + 13," 000    000 ");
	mvwprintw(wn, x + 3, y + 13," 000    000 ");
	mvwprintw(wn, x + 4, y + 13," 000    000 ");
	mvwprintw(wn, x + 5, y + 13," 000    000 ");
	mvwprintw(wn, x + 6, y + 13," 000    000 ");
	mvwprintw(wn, x + 7, y + 13,"   000000   ");
	wattroff(wn, COLOR_PAIR(64));
	wattroff(wn, A_BOLD);	
	wattron(wn, COLOR_PAIR(16));
	mvwprintw(wn, x + 1, y + 24,"      444   ");
	mvwprintw(wn, x + 2, y + 24,"    44 44   ");
	mvwprintw(wn, x + 3, y + 24,"   44  44   ");
	mvwprintw(wn, x + 4, y + 24,"  44   44   ");
	mvwprintw(wn, x + 5, y + 24," 44444444444");
	mvwprintw(wn, x + 6, y + 24,"       44   ");
	mvwprintw(wn, x + 7, y + 24,"       44   ");
	wattroff(wn, COLOR_PAIR(16));
	wattron(wn, COLOR_PAIR(8));	
	mvwprintw(wn, x + 1, y + 35,"    8888    ");
	mvwprintw(wn, x + 2, y + 35," 888    888 ");
	mvwprintw(wn, x + 3, y + 35," 888    888 ");
	mvwprintw(wn, x + 4, y + 35,"    8888    ");
	mvwprintw(wn, x + 5, y + 35," 888    888 ");
	mvwprintw(wn, x + 6, y + 35," 888    888 ");
	mvwprintw(wn, x + 7, y + 35,"    8888    ");
	wattroff(wn, COLOR_PAIR(8));
	wattroff(wn, A_BOLD);
	wattron(wn, COLOR_PAIR(32));
	wattron(wn, A_BOLD);
	mvwprintw(wn, 30, 55, "PRESS ANY KEY TO START");
	wattroff(wn, A_BOLD);
	wattroff(wn, COLOR_PAIR(32));	
	wgetch(wn);
	wclear(wn);	
}
int start(WINDOW *wn){

	int i, j, *b[3], *a[4], *c[5], ch = -1, *d[6], *e[7], *f[8];
	a :	
	for(int i = 0;i < 3;i++)
                b[i] = (int*)malloc(3 * sizeof(int));
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			b[i][j] = 0;
		}
	}
	b[0][0] = 2; b[1][0] = 8;
	b[1][1] = 2; b[2][1] = 4;
	b[2][2] = 2; b[2][0] = 32;
	display(wn, b, 3);
	wattron(wn, COLOR_PAIR(32));
	wattron(wn, A_BOLD);
	mvwprintw(wn, 8, 57, "**  TINY  **");
	wattroff(wn, A_BOLD);
	wattroff(wn, COLOR_PAIR(32));
	arrow_right(wn);
	v :
	while((ch = wgetch(wn)) != KEY_RIGHT){
		if('\n' == ch)
			return 3;		
		goto v;
	}
	wclear(wn);
	if(KEY_RIGHT == ch) {
		b :		
		for(int i = 0;i < 4;i++)
		        a[i] = (int*)malloc(4 * sizeof(int));
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				a[i][j] = 0;
			}
		}
		a[0][0] = 16; a[1][1] = 2;
		a[0][1] = 8; a[1][2] = 2;
		a[0][2] = 4; a[2][0] = 8;
		a[0][3] = 4; a[2][1] = 16;
		a[1][0] = 32; a[3][0] = 4;
		display(wn, a, 4);
		wattron(wn, COLOR_PAIR(32));
		wattron(wn, A_BOLD);
		mvwprintw(wn, 6, 60, "**  CLASSIC  **");
		wattroff(wn, A_BOLD);
		wattroff(wn, COLOR_PAIR(32));	
	}
	arrow_right(wn);
	arrow_left(wn);
	v1 :
	ch = wgetch(wn);
	while(ch != KEY_RIGHT && ch != KEY_LEFT){
		if('\n' == ch)
			return 4;
		goto v1;
	}
	wclear(wn);
	if(KEY_LEFT == ch)
		goto a; 
	if(KEY_RIGHT == ch) {
		c:		
		for(int i = 0;i < 5;i++)
		        c[i] = (int*)malloc(5 * sizeof(int));
		for(i = 0; i < 5; i++){
			for(j = 0; j < 5; j++){
				c[i][j] = 0;
			}
		}
		c[0][0] = 64; c[1][1] = 2;
		c[0][1] = 8; c[1][2] = 2;
		c[0][2] = 4; c[2][0] = 8;
		c[0][3] = 4; c[2][1] = 16;
		c[1][0] = 32; c[4][0] = 4;
		c[2][2] = 4; c[3][0] = 64;
		c[3][3] = 4; c[3][1] = 16;
		c[3][0] = 32; c[1][3] = 4;	
		display(wn, c, 5);
		wattron(wn, COLOR_PAIR(32));
		wattron(wn, A_BOLD);
		mvwprintw(wn, 4, 67, "**  BIG  **");
		wattroff(wn, A_BOLD);
		wattroff(wn, COLOR_PAIR(32));	
	}
	arrow_right(wn);
	arrow_left(wn);
	v2 :
	ch = wgetch(wn);
	while(ch != KEY_RIGHT && ch != KEY_LEFT){
		if('\n' == ch)
			return 5;
		goto v2;
	}
	wclear(wn);
	if(KEY_LEFT == ch)
		goto b;
	if(KEY_RIGHT == ch) {		
			d:	
		for(int i = 0;i < 6;i++)
		        d[i] = (int*)malloc(6 * sizeof(int));
		for(i = 0; i < 6; i++){
			for(j = 0; j < 6; j++){
				d[i][j] = 0;
			}
		}
		d[0][0] = 64; d[1][1] = 2;
		d[0][1] = 8; d[1][2] = 2;
		d[0][2] = 4; d[2][0] = 8;
		d[0][3] = 4; d[2][1] = 16;
		d[1][0] = 32; d[4][0] = 4;
		d[2][2] = 4; d[3][0] = 64;
		d[3][3] = 4; d[3][1] = 16;
		d[5][0] = 32; d[1][3] = 4;
		d[5][2] = 4; d[5][5] = 64;
		d[5][3] = 4; d[4][4] = 16;
		d[3][5] = 32; d[4][3] = 4;	
		display(wn, d, 6);
		wattron(wn, COLOR_PAIR(32));
		wattron(wn, A_BOLD);
		mvwprintw(wn, 4, 60, "**  BIGGER  **");
		wattroff(wn, A_BOLD);
		wattroff(wn, COLOR_PAIR(32));	
	}
	arrow_right(wn);
	arrow_left(wn);
	v3 :
	ch = wgetch(wn);
	while(ch != KEY_RIGHT && ch != KEY_LEFT){
		if('\n' == ch)
			return 6;	
		goto v3;
	}
	wclear(wn);
		if(KEY_LEFT == ch)
		goto c;	
	if(KEY_RIGHT == ch) {
		e:		
		for(int i = 0;i < 7;i++)
		        e[i] = (int*)malloc(7 * sizeof(int));
		for(i = 0; i < 7; i++){
			for(j = 0; j < 7; j++){
				e[i][j] = 0;
			}
		}
		e[0][0] = 64; e[1][1] = 2;
		e[0][1] = 8; e[1][2] = 2;
		e[0][2] = 4; e[2][0] = 8;
		e[0][3] = 4; e[2][1] = 16;
		e[1][0] = 32; e[4][0] = 4;
		e[2][2] = 4; e[3][0] = 64;
		e[3][3] = 4; e[3][1] = 16;
		e[5][0] = 32; e[1][3] = 4;
		e[5][3] = 4; e[2][5] = 16;
		e[4][1] = 128; e[4][2] = 4;
		e[5][2] = 4; e[5][5] = 64;
		e[3][5] = 4; e[4][4] = 16;
		e[3][4] = 32; e[5][6] = 256;
		e[6][0] = 32; e[1][3] = 4;
		e[6][3] = 4; e[6][5] = 16;
		e[5][1] = 128; e[2][6] = 4;
		e[6][2] = 4; e[6][6] = 256;
		e[3][6] = 4; e[4][6] = 16;
		e[3][5] = 32; e[1][6] = 1024;	
		display(wn, e, 7);
		wattron(wn, COLOR_PAIR(32));
		wattron(wn, A_BOLD);
		mvwprintw(wn, 0, 66, "**  HUGE  **");
		wattroff(wn, A_BOLD);
		wattroff(wn, COLOR_PAIR(32));	
	}
	arrow_right(wn);
	arrow_left(wn);
	v4 :
	ch = wgetch(wn);
	while(ch != KEY_RIGHT && ch != KEY_LEFT){
		if('\n' == ch)
			return 7;
		goto v4;
	}
	wclear(wn);
	if(KEY_LEFT == ch)
		goto d;	
	if(KEY_RIGHT == ch) {		
		for(int i = 0;i < 8;i++)
		        f[i] = (int*)malloc(8 * sizeof(int));
		for(i = 0; i < 8; i++){
			for(j = 0; j < 8; j++){
				f[i][j] = 0;
			}
		}
		c[0][0] = 64; f[1][1] = 2;
		f[0][1] = 8; f[1][2] = 2;
		f[0][2] = 4; f[2][0] = 8;
		f[0][3] = 4; f[2][1] = 16;
		f[1][0] = 32; f[4][0] = 4;
		f[2][2] = 4; f[3][0] = 64;
		f[3][3] = 4; f[3][1] = 16;
		f[3][0] = 32; f[1][3] = 4;
		f[5][0] = 32; f[1][3] = 4;
		f[5][3] = 4; f[2][5] = 16;
		f[4][1] = 128; f[4][2] = 4;
		f[5][2] = 4; f[5][5] = 64;
		f[3][5] = 4; f[4][4] = 16;
		f[3][4] = 32; f[1][5] = 4;
		f[6][0] = 32; f[1][3] = 4;
		f[6][3] = 4; f[6][5] = 16;
		f[5][1] = 128; f[2][6] = 4;
		f[6][2] = 4; f[6][6] = 256;
		f[3][6] = 4; f[4][6] = 16;
		f[3][5] = 32; f[1][6] = 4;
		f[7][1] = 128; f[2][7] = 2;
		f[7][2] = 2; f[6][7] = 256;
		f[7][6] = 2; f[4][7] = 16;
		f[7][5] = 32; f[1][7] = 2;	
		display(wn, f, 8);
		wattron(wn, COLOR_PAIR(32));
		wattron(wn, A_BOLD);
		mvwprintw(wn, 0, 70, "**  GIANT  **");
		wattroff(wn, A_BOLD);
		wattroff(wn, COLOR_PAIR(32));
	}
	arrow_left(wn);
	v5 :
	while((ch = wgetch(wn)) != KEY_LEFT){
		if('\n' == ch)
			return 8;
		goto v5;
	}
	wclear(wn);
	if(KEY_LEFT == ch)
		goto e;	
	return 0;

}
void play(){
	WINDOW *wn;
	wn = (WINDOW *)malloc(sizeof(WINDOW));
	wn = newwin(800 ,800 , 0, 0);
	keypad(wn, TRUE);
	curs_set(FALSE);
	if (initColor()) 
		wgetch(wn);
	front_page(wn);	
	int n = start(wn);
	int *a[n], score = 0;
	for(int i = 0;i < n;i++)
                a[i] = (int*)malloc(n*sizeof(int));
	int i, j;
	int ch;
	wattron(wn, COLOR_PAIR(13));
	wattron(wn, A_BOLD);	
	mvwprintw(wn,1,50,"<< USE KEYS TO MOVE THE NUMBER DICE>>");
	mvwprintw(wn,2,40,"<< USE BACKSPACE TO START THE GAME AGAIN AND ESCAPE TO EXIT THE GAME>>");
	
	mvwprintw(wn,6,120,"SCORE : %d",score);
	wattroff(wn, A_BOLD);
	wattroff(wn, COLOR_PAIR(13));
	wbkgd(wn, COLOR_PAIR(12));
	wrefresh(wn);	
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			a[i][j] = 0;
		}
	}
	random_number(a,n);
		display(wn,a,n);
	while(1){			
		ch = wgetch(wn);
		if(ch == KEY_BACKSPACE){
			play();
		}
		switch(ch){
			case 27:{
				wrefresh(wn);
				delwin(wn);
				endwin();
				exit(1);
				break;
			}
			case KEY_LEFT:{					
				display_left(a,n);
				display_left_sum(a, n, &score);
				display_left(a,n);
				random_number(a,n);
				display(wn,a,n);
				wattron(wn, A_BOLD);
				wattron(wn, COLOR_PAIR(13));
				mvwprintw(wn,6,120,"SCORE : %d",score);
				wattroff(wn, COLOR_PAIR(13));
				wattroff(wn, A_BOLD);
				break;
			}	
			case KEY_DOWN:{
				display_down(a,n);
				display_down_sum(a, n, &score);
			        display_down(a, n);
				random_number(a, n);
				display(wn,a, n);	
				wattron(wn, A_BOLD);
				wattron(wn, COLOR_PAIR(13));
				mvwprintw(wn,6,120,"SCORE : %d",score);
				wattroff(wn, COLOR_PAIR(13));	
				wattroff(wn, A_BOLD);			
				break;
			}
			case KEY_RIGHT:{
				display_right(a, n);
			        display_right_sum(a, n, &score);
				display_right(a, n);
				random_number(a, n);
				display(wn,a, n);	
				wattron(wn, A_BOLD);
				wattron(wn, COLOR_PAIR(13));
				mvwprintw(wn,6,120,"SCORE : %d",score);
				wattroff(wn, COLOR_PAIR(13));
				wattroff(wn, A_BOLD);		
				break;	
			}
			case KEY_UP:{
			        display_up(a, n);
				display_up_sum(a, n, &score);
			        display_up(a, n);
				random_number(a, n);
				display(wn,a, n);	
				wattron(wn, A_BOLD);
				wattron(wn, COLOR_PAIR(13));
				mvwprintw(wn,6,120,"SCORE : %d",score);
				wattroff(wn, COLOR_PAIR(13));
				wattroff(wn, A_BOLD);		
				break;
			}
		}
		char ch1 = '\0';
		if(!check2(a, n)){
			if(!check1(a, n)){
				lost1(wn);
				while((ch1 = wgetch(wn))){
					 if(ch1 == 'N'|| ch1 == 'n'){
						wrefresh(wn);
						delwin(wn);
						endwin();
						exit(1);
						return ;
					}
					else if(ch1 == 'Y' || ch1 == 'y')
						play();
				}				
			}
		}
		if(win(a, n)){
			win1(wn);
			while((ch1 = wgetch(wn))){
				if(ch1 == 'Y' || ch1 == 'y')
					play();
				else if(ch1 == 'N' || ch1 == 'n'){
					wrefresh(wn);
					delwin(wn);
					endwin();
					exit(1);
					return ;
				}
			}						
		}
	
	}
	wgetch(wn);
	sleep(MAX);
	wrefresh(wn);	
	delwin(wn);
	endwin();
}


