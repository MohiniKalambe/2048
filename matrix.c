#include<stdio.h>
#include <stdlib.h>

int check1(int a[][4]){
	int i, j;
	int flag = 0;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 3; j++){
			if(a[i][j] == a[i][j + 1]){
				flag = 1;
				break;
			}
		}
		if(flag == 1)	
			break;
	} 
	if(flag == 0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < 4; j++){
				if(a[i][j] == a[i + 1][j]){
					flag = 1;
					break;
				}
			}
			if(flag == 1)
				break;
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
				break;
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
void display(int a[][4]){
	int  i, j;
	for(i = 0; i < 4; i++) {
                for(j = 0; j < 4; j++) {
                	printf("%d     ", a[i][j]);
                }
                printf("\n");
        }
	printf("\n");
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
                a[i][j] = (rand() & 3) ? 2 : 4 ;
		return;
        }
	else{
		random_number(a);
	}

}
int main(){
	int a[4][4], b[4][4];
	int i, j, count = 0, s;
	char ch;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++) {
			a[i][j] = 0;
		}
		
	}
	random_number(a);
		display(a);	
	while(1){
		int b[4][4];
        	for(i = 0; i < 4 ; i++){
                	for(j = 0;j < 4; j++){
                        	b[i][j] = a[i][j];
                	}
        	}	
		scanf("%c", &ch);
		switch(ch){
			case 'a':{
				display_left(a);
				display_left_sum(a);
				display_left(a);
				random_number(a);
				display(a);
				break;
			}	
			case 's':{
		                display_down(a);
				display_down_sum(a);
		                display_down(a);
				random_number(a);
				display(a);				
				break;
		        }
		        case 'd':{
		                display_right(a);
		                display_right_sum(a);
				display_right(a);
				random_number(a);
				display(a);				
				break;
		        }
			case 'w':{
		                display_up(a);
				display_up_sum(a);
		                display_up(a);
				random_number(a);
				display(a);				
				break;
		        }
		}
		
		for(i = 0; i < 4 ; i++){
                	for(j = 0;j < 4; j++){
                               if( b[i][j] == a[i][j])
					count++;
                        }
                }
		if(!check2(a)){
			if(!check1(a)){
				printf("YOU LOST");
			}
		}
		if(win(a)){
			printf("YOU WIN");
		}
	}
		

	
}


