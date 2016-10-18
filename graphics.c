#include <stdio.h>
#include <stdlib.h>
#include<ncurses.h>
#include"graph.h"
#include<unistd.h>
#define MAX 100000
/*int initColor() {
	if (!has_colors()) {
		return 1;
	} else {
		start_color();
		init_pair(2, 1, 0);
		init_pair(4, 2, 0);
		//init_pair(4, 2, 0);
		init_pair(8, 3, 0);
		init_pair(16, 4, 0);
		init_pair(32, 5, 0);
		init_pair(64, 6, 0);
		init_pair(128, 7, 0);
		init_pair(256, 1, 0);
		init_pair(512, 2, 0);
		init_pair(1024, 3, 0);
		init_pair(2048, 4, 0);
		init_pair(0, 5, 0);
		init_pair(12, 1, 2);
	}
	return 0;
}*/
int initColor() {
	if (!has_colors()) {
		return 1;
	} else {
		start_color();
		init_pair(2, COLOR_WHITE, 1);
		init_pair(4, COLOR_WHITE, 2);
		//init_pair(4, 2, 0);
		init_pair(8, COLOR_WHITE, 3);
		init_pair(16, COLOR_WHITE, 4);
		init_pair(32, COLOR_WHITE, 5);
		init_pair(64, COLOR_WHITE, 6);
		init_pair(128, COLOR_WHITE, 1);
		init_pair(256, COLOR_WHITE, 2);
		init_pair(512, COLOR_WHITE, 3);
		init_pair(1024, COLOR_WHITE, 4);
		init_pair(2048, COLOR_WHITE, 5);
		init_pair(0, 5, 0);
		init_pair(12, COLOR_RED, COLOR_BLACK);
	}
	return 0;
}
int check1(int a[][4]){
	int i, j;
	int flag = 0;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			if(a[i][j] == a[i][j + 1]){
				flag = 1;
				return flag;
			}
		}
		if(flag == 1)	
			return flag;
	} 
	if(flag == 0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < 4; j++){
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
int check2(int a[][4]){
	int i, j;
	int flag = 0;
	for(i = 0;i < 4;i++){
		for(j = 0; j < 4;j++){
			if(a[i][j] == 0){
				flag = 1;
				return flag;
			}
		}
	} 
	return flag;
}
int win(int a[][4]){
	int i, j;
	for(i = 0; i < 4; i++){
                for(j = 0; j < 4; j++){
			if(a[i][j] == 2048){
				return 1;
			}
		}
	}
	return 0;
}
int random_int(int r){
        int n;
        n = rand() % r;
        return n;
}
void display(WINDOW *wn,int a[][4]){

	int x = 10 ;
	for(int i = 0;i < 4; i++){
		int y = 45;
		for(int j = 0;j < 4;j++){
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
			//mvwprintw(wn, x + 5, y + 2,"     ");
			wattroff(wn, COLOR_PAIR(color));
			wattroff(wn, A_BOLD);			
			y = y + 9;
			}
			y = 5;
			x = x + 5;
	}

}
void display_up_sum(int a[][4]){
	int i, j;
	for(j = 0; j < 4; j++){
		for(i = 0; i < 4; i++){
			if(a[i][j] == a[i + 1][j]){
				a[i][j] = a[i + 1][j] + a[i][j];
				a[i + 1][j] = 0;
			}
		}
	}

}
void display_up(int a[][4]){
	int i, j, k;
	for(j = 0; j < 4; j++){
		for(i = 0; i < 4 ; i++){
			if(a[i][j] == 0) {	
				for(k = i + 1;k < 4;k++){
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
void display_down_sum(int a[][4]){
	int i, j;
	for(j = 0; j < 4; j++){
		for(i = 3; i > 0; i--){
			if(a[i][j] == a[i - 1][j]){
				a[i][j] = a[i - 1][j] + a[i][j];
				a[i - 1][j] = 0;
			}
		}	
	}	
}
void display_down(int a[][4]){
	int i, j, k;
	for(j = 0; j < 4; j++){
		for(i = 3; i >=0; i--){
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
void display_right_sum(int a[][4]){
	int i, j;
	for(i = 0;i < 4;i++){
		for(j = 3;j > 0;j--){
                        if(a[i][j] == a[i][j - 1]){
                                a[i][j] = a[i][j - 1] + a[i][j];
                                a[i][j - 1] = 0;
                        }
                }
	}
}
void display_right(int a[][4]){
	int i, j, k;
	for(i = 0;i < 4;i++){
		for(j = 3;j >= 0;j--){
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
void display_left_sum(int a[][4]){
	int i, j;
	for(i = 0; i < 4; i++){
                for(j = 0; j < 3; j++){
                        if(a[i][j] == a[i][j + 1]){
                                a[i][j] = a[i][j + 1] + a[i][j];
                                a[i][j + 1] = 0;
                        }
                }
        }
}
void display_left(int a[][4]){
	int  i, j, k;
	for(i = 0;i < 4;i++){
		for(j = 0;j < 4;j++){
			if(a[i][j] == 0){
                        	for(k = j + 1;k < 4;k++){       	
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
void random_number(int a[][4]){
	int i, j;
	i = random_int(4);
        j = random_int(4);
        if(a[i][j] == 0){
                a[i][j] = (rand() & 3) ? 2 : 4;
        }
	else{
		if(check2(a))
			random_number(a);
	}
}
void play(){
	WINDOW *wn;
	wn = (WINDOW *)malloc(sizeof(WINDOW));
	wn = newwin(800 ,800 , 0, 0);
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	int a[4][4];
	int i, j, flag = 1;
	char ch;
	//int wattron(WINDOW *wn, int *attsr);
	//int wattroff(WINDOW *wn, int *attsr);
	wattron(wn, A_BOLD);
	mvwprintw(wn,2,30,"<< USE A, S, W, D KEYS TO MOVE THE NUMBER DICE LEFT, DOWN, UP, RIGHT >>");
	wattroff(wn, A_BOLD);
	if (initColor()) 
		wgetch(wn);
	//wbkgd(wn, COLOR_PAIR(12));
	//	wgetch(wn);
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			a[i][j] = 0;
		}
	}
	random_number(a);
		display(wn,a);	
	while(1){			
		ch = wgetch(wn);
		//if(ch != '\n'){
		/*for(i = 0; i < 4 ; i++){
	        	for(j = 0;j < 4; j++){
		         	b[i][j] = a[i][j];
		       	}
		}*/
		switch(ch){
			case 'a':case'A':{
				if(flag){					
					display_left(a);
					display_left_sum(a);
					display_left(a);
					random_number(a);
					display(wn,a);
					break;
				}
			}	
			case 's':case'S':{
				if(flag){				        
					display_down(a);
					display_down_sum(a);
				        display_down(a);
					random_number(a);
					display(wn,a);				
					break;
				}
			}
			case 'd':case'D':{
				if(flag){				        
					display_right(a);
				        display_right_sum(a);
					display_right(a);
					random_number(a);
					display(wn,a);				
					break;
				}
			}
			case 'w':case'W':{
				if(flag){
				        display_up(a);
					display_up_sum(a);
				        display_up(a);
					random_number(a);
					display(wn,a);				
					break;
				}
			}
		}
		/*for(i = 0; i < 4 ; i++){
			for(j = 0;j < 4; j++){
		        	if( b[i][j] == a[i][j])
					count++;
				printf("%d",count);
	                }
		}
		if(count == 16)
			flag = 0;
		else
			flag = 1;
		count = 0;*/
		if(!check2(a)){
			if(!check1(a)){
				mvwprintw(wn,40,40,"YOU LOST ");
			}
		}
		if(win(a)){
			mvwprintw(wn,40,40,"YOU WIN");
		}
	}
	wgetch(wn);
	sleep(MAX);
	wrefresh(wn);	
	delwin(wn);
	endwin();

	
}


