
/*****************************************************************************
 * Copyright (C) MOHINI NILKANTH KALAMBE mohini_kalambe@yahoo.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/*					2048				*/
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include"graph.h"
#include<string.h>
int main(int argc, char *argv[]){
        FILE *f1;
        char a;
        int b;
	if(argc == 2){
        	b = strcmp(argv[1],"-h");
        	if(b == 0){
        		f1 = fopen("use.txt","r");
              		if(f1){
                		while (fscanf(f1, "%c", &a)!=EOF)
                        		printf("%c",a);
                        		fclose(f1);
                	}
       		}
	}
	else{
		initscr();
		noecho();
        	cbreak();
        	play();
		endwin();
	}
	return 0;
}
