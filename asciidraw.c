//Barry Chen, Department of Computer Science, McGill ID: 260952566 

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){

	int exit = -1; // a flag to determine when to terminate the program
	int flag = -1; // a flag that determining whether GRID command has been entered
	char cha = '*';
	char garbage[1000];
	int row, col;
	char grid[1000][1000];
	while (exit != 0){
		// reading from the input and store them.
		char input[30], command[30];
		fgets(input,30,stdin);
		sscanf(input,"%s",command);
		//printf("contents of input: %sand command: %s\n", input, command);

		if (strcmp(command,"END") == 0){
			exit = 0;

	    }else if (strcmp(command,"CHAR") == 0){
			sscanf(input,"%s %c", garbage, &cha);
			//printf("the draw character changes to %c\n", cha);

		}else if (strcmp(command,"GRID") != 0 && flag != 0){ // stop user entering other commands before enter GRID command
			puts("Only CHAR command is allowed before the grid size is set.");

		}else if (strcmp(command,"GRID") == 0 && flag != 0){ // first time user enter GRID command
			sscanf(input,"%s %d %d", garbage, &col, &row);
			//printf("row: %d, column: %d\n", row, col);
			for (int i = 0; i < row; i++){    // initializing an empty canvas with correct size
				for (int j = 0; j < col; j++){
					grid[i][j] = ' ';
				}
			}
			flag = 0;
		
		}else if (strcmp(command,"GRID") == 0 && flag == 0){ // stop user entering GRID command again
			printf("GRID was already set to %d,%d.\n", col, row);

		}else if (strcmp(command,"DISPLAY") == 0){
			// display the contents of the canvas
			for (int i = 0; i < (row+1); i++){
				int rindex = (row-i-1)%10; 
				if (i == row){
					printf(" ");
				}else{
					printf("%d", rindex);
				}
				for (int j = 0; j < col; j++){
					if (i == row){
						int cindex = j % 10;
						printf("%d", cindex);
					}else{
						printf("%c", grid[i][j]);
					}	
				}
				printf("\n");
			}

		}else if (strcmp(command,"RECTANGLE") == 0){
        	int x1, y1, x2, y2;
			sscanf(input,"%s %d,%d %d,%d", garbage,&x1,&y1,&x2,&y2);
			//printf("(x1,y1): (%d,%d) and (x2,y2): (%d,%d)\n", x1,y1,x2,y2);
			for(int i = x1; i <= x2; i++){ // draw the horizontal lines
				if (i <= col ){ 
					grid[row-y1-1][i] = cha;
					grid[row-y2-1][i] = cha;
				}else break; // truncate line
			}
			for (int j = row-y1-1; j <= row-y2-1; j++){ // draw the vertical lines
				if ( j >= 0 ) {
					grid[j][x1] = cha;
					grid[j][x2] = cha;
				}else continue; // truncate line
			}

		}else if (strcmp(command,"LINE") == 0){
        	int x1, y1, x2, y2;
			int mark = 0;   // a flag that marks whether its a line with positive slope or negatve slopw
			sscanf(input,"%s %d,%d %d,%d", garbage,&x1,&y1,&x2,&y2);
			if (x1 >= x2 && y1 >= y2){    // line with postive slope
				int tempx1 = x1;
				int tempy1 = y1;
				x1 = x2;
				x2 = tempx1;
				y1 = y2;
				y2 = tempy1;
			}
			if ((x1 <= x2 && y1 >= y2) || (x1 >= x2 && y1 <= y2)){ // line with negative slope
				mark = -1;
				if (x1 > x2 && y1 < y2){
					int temp1 = x1;
					int temp2 = y2;
					x1 = x2;
					x2 = temp1;
					y2 = y1;
					y1 = temp2;
				}
			}
			//printf("x1 is %d, y1 is %d, x2 is %d, y2 is %d\n", x1,y1,x2,y2);
			if (x2 - x1 == 0){     // vertical line
				for (int i = row-y2-1; i<= row-y1-1; i++){
					if (i < 0 ){
						continue;  // truncate line
					}else if ( i > row){
						break;
					}else grid [i][x1] = cha;
				}
			}else{     // diagonal line or horizontal line
				int yprevious = y1; // !! recording previous y position
				float slope =(double)(y2-y1)/(double)(x2-x1);
				float intercept = y1 - slope * x1;
			   	//printf("the equation of the line is y = %fx + (%f)\n", slope, intercept);
				for (int j = x1; j <= x2; j++){ // drawing from left to right 
					
					float yvalue = slope * j + intercept;
					int rdvalue = roundf(yvalue);    // next rounded y position
					//printf("rounded y value is %d\n", rdvalue);
					//printf("ycurrent is %d\n",yprevious);
					if (j >= col){
						break;
					}
					grid[row-yprevious-1][j] = cha;
					if (mark != -1){	
						for (int i = yprevious; i <= rdvalue; i++){ // drawing from bottom to top (positive slope)
							grid[row-i-1][j] = cha;
						}
						yprevious = rdvalue;
					}else{
						for (int i = yprevious; i >= rdvalue; i--){ // drawing from top to bottom (negative slope)
							grid[row-i-1][j] = cha;
						}
						yprevious = rdvalue;
					}
				}
				grid[row-y2-1][x2] = cha;
			}

		}else if (strcmp(command,"CIRCLE") == 0){
			int x_center, y_center, radious, xnext, ynext;
			sscanf(input,"%s %d,%d %d", garbage,&x_center,&y_center,&radious);
			//printf("the x center is %d, the y center is %d, and the radious is %d\n", x_center,y_center,radious);
			int xcurrent = x_center;
			int ycurrent = y_center + radious;
			int xend = x_center + radious;
			grid[row-ycurrent-1][xcurrent] = cha; 
			grid[row-y_center+ycurrent-y_center-1][xcurrent] = cha;
			while(xcurrent != xend || ycurrent != y_center){ // stop entil the character is drawed at position (y,x+r)
				double diff = 100000;
				double a = xcurrent+1-x_center;
				double b = ycurrent-y_center;
				double a2 = pow(a,2);   // find a^2
				double b2 = pow(b,2);   // fine b^2
				double r = sqrt(a2+b2); // find the distance between center and character by pythagorean theorem

				// find the r that is closet to the radious
				if(fabs(r-radious) < diff){ 
					diff = fabs(r-radious);
					//printf("1 the difference is %f\n", diff);
					xnext = xcurrent + 1;
					ynext = ycurrent;
				}
				a = xcurrent-x_center;
				b = ycurrent-1-y_center;
				a2 = pow(a,2);
				b2 = pow(b,2);
				r = sqrt(a2+b2); 
				if (fabs(r-radious) < diff){
					diff = fabs(r-radious);
					//printf("2 the difference is %f\n", diff);
					xnext = xcurrent;
					ynext = ycurrent-1;
				}
				a = xcurrent+1-x_center;
				b = ycurrent-1-y_center;
				a2 = pow(a,2);
				b2 = pow(b,2);
				r = sqrt(a2+b2); 
				if (fabs(r-radious) < diff){
					diff = fabs(r-radious);
					//printf("3 the difference is %f\n", diff);
					xnext = xcurrent+1;
					ynext = ycurrent-1;
				}
				//printf("final the difference is %f\n", diff);
				grid[row-ynext-1][xnext] = cha;
				grid[row-ynext-1][x_center-xnext+x_center] = cha;
				grid[row-y_center+ynext-y_center-1][xnext] = cha;
				grid[row-y_center+ynext-y_center-1][x_center-xnext+x_center] = cha;
				xcurrent = xnext;  // upadate the current posttion of the character to the next postion
				ycurrent = ynext;
				//printf("xcurrent is %d, ycurrent is %d\n",xcurrent,ycurrent);
			}

		}else{
			printf("Error did not understand %s", input);
		}
	}
	
	return 0;

}

