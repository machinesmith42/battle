#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <curses.h> 
#include <stdbool.h>
#include<math.h>
#include<string.h>
#include<ctype.h> 
# define XMAX 10
# define YMAX 10
char visibleGrid1[XMAX][YMAX];
char invisibleGrid1[XMAX][YMAX];
char visibleGrid2[XMAX][YMAX];
char invisibleGrid2[XMAX][YMAX];
short int x;
short int y;
short int direction;

int placeShip(int length, char shiptype, char grid[XMAX][YMAX]);
int randnum(int range);
void init(char grid[XMAX][YMAX], char input);
int check(int length, char grid[XMAX][YMAX]);
void print_array(char grid[XMAX][YMAX]);
int shipInit();
void init(char grid[XMAX][YMAX], char input) {
    short int i;
    short int k;
    for (i = 0; i < XMAX; i++) {
        for (k = 0; k < YMAX; k++) {
            grid[i][k] = input;
        }
    }
}
int randnum(int range) {
    int limit;
    short int r;

    limit = RAND_MAX - (RAND_MAX % range);

    while ((r = rand()) >= limit);

    return r % range;
}
int shipInit() {
	char buffer[10];
	printw("Enter x coordinate between 1-10\n");
	do{
		echo();	
		getnstr(buffer,10);
		for(int i = 0; i<strlen(buffer)-1;i++){
			if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||XMAX<atoi(buffer)){
				clear();
				printw("Invalid input.\n Enter x coordinate between 1-10\n");
				refresh();
				buffer[0]='\n';
				buffer[1]='\0';
				i = strlen(buffer)+1;
			}
		}
	}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<0||XMAX<atoi(buffer));
	x =atoi(buffer);
	printw("Enter y coordinate between 1-10\n");
	do{
		echo();	
		getnstr(buffer,10);
		for(int i = 0; i<strlen(buffer)-1;i++){
			if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||YMAX<atoi(buffer)){
				clear();
				refresh();
				printw("Invalid input.\n Enter y coordinate between 1-10\n");
				buffer[0]='\n';
				buffer[1]='\0';
				i = strlen(buffer)+1;
			}
		}
	}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<0||YMAX<atoi(buffer));
	y =atoi(buffer);
	printw("Enter direction, 0 is North, 1 is East, 2 is South, 3 is West,\n 4 is North West, 5 is North East, 6 is South West, 7 is South East \n");
	do{
		echo();	
		getnstr(buffer,10);
		for(int i = 0; i<strlen(buffer)-1;i++){
			if(isdigit(buffer[i])==0||(int)strlen(buffer)>2||buffer[0]=='\n'||atoi(buffer)<0||7<atoi(buffer)){
				printw("Invalid input.\n Enter direction, 0 is North, 1 is East, 2 is South, 3 is West,\n 4 is North West, 5 is North East, 6 is South West, 7 is South East \n");
				buffer[0]='\n';
				buffer[1]='\0';
				i = strlen(buffer)+1;
			}
		}
	}while((int)strlen(buffer)>2||buffer[0]=='\n'||atoi(buffer)<0||7<atoi(buffer));
	direction =atoi(buffer);
	return 0;
}
void print_array(char grid[XMAX][YMAX]) {
    short int i, j;
    /* print each row of the array */
    clear();
	printw("   ");
    for (i = 0; i < XMAX; i++) printw(" %i", i+1);
    printw("\n");
    for (i = 0; i < XMAX; i++) {
        if(i<9){
        	printw("  %i ", i+1);
        }else{
        	printw(" %i ",10);
        }for (j = 0; j < YMAX; j++)
            printw("%c ", grid[i][j]);
        /* must add newline at end */
        printw("\n");
    }
    printw("\n");
	refresh();
}
int placeShip(int length, char shiptype, char grid[XMAX][YMAX]) {
    short int i;
    shipInit();
    check(length, grid);
    for (i = 0; i < length; i++) {
        switch (direction) {
        	case 0:
            	grid[y - i - 1][x - 1] = shiptype;
            	break;
        	case 1:
            	grid[y - 1][x + i - 1] = shiptype;
            	break;
        	case 2:
            	grid[y + i - 1][x - 1] = shiptype;
            	break;
        	case 3:
            	grid[y - 1][x - i - 1] = shiptype;
            	break;
        	case 4:
            	grid[y - i - 1][x - i - 1] = shiptype;
            	break;
        	case 5:
            	grid[y - i - 1][x + i - 1] = shiptype;
            	break;
            case 6:
            	grid[y + i - 1][x - i - 1] = shiptype;
            	break;
            case 7:
            	grid[y + i - 1][x + i - 1] = shiptype;
            	break;
        	default:
            	printw("This is an error.\n");
            	break;
        }
    }
    return 0;
}
int check(int length, char grid[XMAX][YMAX]) {
    short int i;
    noecho();
	for (i = 0; i < length; i++) {
        switch (direction) {
        	case 0:
            	
            	if (grid[y - i - 1][x - 1] != 'x' || y - 1 - i < 0) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
            	    shipInit();
            	    check(length, grid);    
                	return 0;
            	}break;
            case 1:
            	
            	if (grid[y - 1][x + i - 1] != 'x' || x  + i - 1 > XMAX) {
                	clear();
					print_array(grid);
                	printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
                	shipInit();
                	check(length, grid);
                	return 0;
           		}break;
        	case 2:
            	
            	if (grid[y + i - 1][x - 1] != 'x' || y  + i - 1 > YMAX) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
            	    refresh();
					getch();
            	    shipInit();
            	    check(length, grid);	    
            	    return 0;
            	}break;
        	case 3:
            	
            	if (grid[y - 1][x - i - 1] != 'x' || x - i - 1 < 0) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
            	    refresh();
					getch();
            	    shipInit();
            	    check(length, grid);    
                	return 0;
            	}break;
			case 4:
            	
            	if (grid[y - i - 1][x - i - 1] != 'x' || y - 1 - i < 0 || x - i - 1 < 0) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
            	    shipInit();
            	    check(length, grid);    
                	return 0;
            	}break;
			case 5:
            	
            	if (grid[y - i - 1][x + i - 1] != 'x' || y - 1 - i < 0 || x + i - 1 > XMAX) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
            	    shipInit();
            	    check(length, grid);    
                	return 0;
            	}break;
            case 6:
            	
            	if (grid[y + i - 1][x - i - 1] != 'x' || y + 1 - i > YMAX || x - i - 1 < 0) {
            	    clear();
					print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
            	    shipInit();
            	    check(length, grid);
                	return 0;
            	}break;          	
        	case 7:
            	
            	if (grid[y + i - 1][x + i - 1] != 'x' || y + 1 - i > YMAX || x + i - 1 > XMAX) {
            	    print_array(grid);
            	    printw("Error, ship cannot be placed here. Press any key to continue\n");
					refresh();
            	    getch();
					shipInit();
            	    check(length, grid);    
                	return 0;
            	}break;
        	default:
            	clear();
				printw("This is an error. Press any key to continue.\n");
            	shipInit();
            	check(length, grid);
            	return 0;
            	break;
        }
    }return 0;
}
int main() {
	initscr(); 
        char isOkay;
        char buffer[10];
        short int count1;
        short int count2;
		noecho();
        printw(" ______       ___   ______________________     _______    __________    __  __  ______  \n");
        printw("|   _  \\     /   \\ |___    ____    ____   |   |   ____|  /   ____   |  |  ||  ||   _  \\ \n");
        printw("|  |_)  )   /  ^  \\    |  |    |  |    |  |   |  |__    (   (    |  |__|  ||  ||  |_)  )\n");
        printw("|   _  <   /  /_\\  \\   |  |    |  |    |  |   |   __|    \\   \\   |   __   ||  ||   ___/ \n");
        printw("|  |_)  ) /  _____  \\  |  |    |  |    |  |___|  |________)   )  |  |  |  ||  ||  |     \n");
        printw("|______/ /__/     \\__\\ |__|    |__|    |_____________________/   |__|  |__||__||__|     \n");
        printw("\n\n\n\n\n\n\n\n\n");
        printw("Press any key to start.\n");
        getch();
        clear();
        init(visibleGrid1, '-');
        init(visibleGrid2, '-');
        do {
            printw("Player 1\n");
            init(invisibleGrid1, 'x');
			print_array(invisibleGrid1);
            printw("Place Carrier length 5. Press any key to continue.\n");
            getch();
			placeShip(5, 'C', invisibleGrid1);
			print_array(invisibleGrid1);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Battleship length 4. Press any key to continue.\n");
            getch();
			placeShip(4, 'B', invisibleGrid1);
			print_array(invisibleGrid1);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Submarine length 3. Press any key to continue.\n");
            getch();
			placeShip(3, 'S', invisibleGrid1);
			print_array(invisibleGrid1);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Destroyer length 3. Press any key to continue.\n");
            getch();
			placeShip(3, 'D', invisibleGrid1);
			print_array(invisibleGrid1);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Patrol Boat length 2. Press any key to continue.\n");
			getch();
			placeShip(2, 'P', invisibleGrid1);
			print_array(invisibleGrid1);
			refresh();
			
            printw("Is this okay?[Y/N]\n");
            do{	
				echo();
				buffer[0]=getch();

				for(int i = 0; i<strlen(buffer)-1;i++){
					if((buffer[0]!='Y'&&buffer[0]!='N')||(int)strlen(buffer)>2||buffer[0]=='\n'){
						printw("Invalid input. Is this okay?[Y/N]\n");
						buffer[0]='\n';
						buffer[1]='\0';
						i = strlen(buffer)+1;
					}
				}
			}while((buffer[0]!='Y'&&buffer[0]!='N')||(int)strlen(buffer)>2||buffer[0]=='\n');
			isOkay =buffer[0];
		} while (isOkay == 'N');

        do {
			
            printw("Player 2\n");
            init(invisibleGrid2, 'x');
			print_array(invisibleGrid2);
            printw("Place Carrier length 5. Press any key to continue.\n");
            getch();
			placeShip(5, 'C', invisibleGrid2);
			print_array(invisibleGrid2);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Battleship length 4. Press any key to continue.\n");
            getch();
			placeShip(4, 'B', invisibleGrid2);
			print_array(invisibleGrid2);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Submarine length 3. Press any key to continue.\n");
            getch();
			placeShip(3, 'S', invisibleGrid2);
			print_array(invisibleGrid2);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Destroyer length 3. Press any key to continue.\n");
            getch();
			placeShip(3, 'D', invisibleGrid2);
			print_array(invisibleGrid2);
			refresh();
			printw("Press any key to continue\n");
			getch();
            printw("Place Patrol Boat length 2. Press any key to continue.\n");
			getch();
			placeShip(2, 'P', invisibleGrid2);
			print_array(invisibleGrid2);
			refresh();
            
			printw("Is this okay?[Y/N]\n");
			refresh();
            do{	
				echo();
				buffer[0]=getch();
				for(int i = 0; i<strlen(buffer)-1;i++){
					if((buffer[0]!='Y'&&buffer[0]!='N')||(int)strlen(buffer)>2||buffer[0]=='\n'){
						printw("Invalid input. Is this okay?[Y/N]\n");
						refresh();
						buffer[0]='\n';
						buffer[1]='\0';
						i = strlen(buffer)+1;
					}
				}
			}while((buffer[0]!='Y'&&buffer[0]!='N')||(int)strlen(buffer)>2||buffer[0]=='\n');
			isOkay =buffer[0];
		} while (isOkay == 'N');
        short int turn = randnum(2);
        do {
            switch (turn) {
            case 0:
                print_array(visibleGrid1);
                printw("Player 1\n");
				printw("Enter x coordinate between 1-10\n");
				refresh();
				do{
					echo();
					getnstr(buffer,10);
					for(int i = 0; i<strlen(buffer)-1;i++){
						if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer)){
							clear();
							printw("Invalid input. Enter x coordinate between 1-10\n");
							refresh();
							buffer[0]='\n';
							buffer[1]='\0';
							i = strlen(buffer)+1;
						}
					}
				}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer));
				x =atoi(buffer);
				refresh();
				printw("Enter y coordinate between 1-10\n");
				do{
					echo();
					getnstr(buffer,10);
					for(int i = 0; i<strlen(buffer)-1;i++){
						if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer)){
							clear();
							printw("Invalid input. Enter y coordinate between 1-10\n");
							refresh();
							buffer[0]='\n';
							buffer[1]='\0';
							i = strlen(buffer)+1;
						}
					}
				}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer));
				y =atoi(buffer);
                visibleGrid1[y - 1][x - 1] = invisibleGrid1[y - 1][x - 1];
                print_array(visibleGrid1);
                switch (visibleGrid1[y - 1][x - 1]) {
                    case 'x':
                        printw("You missed. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                        break;
                    case 'C':
                        printw("You hit the Carrier. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                        count1++;
                        break;
                    case 'B':
                    	printw("You hit the Battleship. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count1++;
                    	break;
                    case 'S':
                    	printw("You hit the Submarine. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count1++;
                    	break;
                    case 'D':
                    	printw("You hit the Destroyer. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count1++;
                    	break;
                    case 'P':
                    	printw("You hit the Patrol Boat. Press any key to continue.\n");
                    	refresh();
						getch();
						clear();
						count1++;
                    	break;
                    default:
                        printw("This is an error. Press any key to continue.\n");
                        refresh();
						getch();
						clear();
						break;
                    }
                    turn = 1;
				break;
                case 1:
                print_array(visibleGrid1); 
                printw("Player 2\n");
 				printw("Enter x coordinate between 1-10\n");
				refresh();
				do{
					echo();
					getnstr(buffer,10);
					for(int i = 0; i<strlen(buffer)-1;i++){
						if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer)){
							clear();
							printw("Invalid input. Enter x coordinate between 1-10\n");
							refresh();
							buffer[0]='\n';
							buffer[1]='\0';
							i = strlen(buffer)+1;
						}
					}
				}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer));
				x =atoi(buffer);
				refresh();
				printw("Enter y coordinate between 1-10\n");
				do{
					echo();
					getnstr(buffer,10);
					for(int i = 0; i<strlen(buffer)-1;i++){
						if(isdigit(buffer[i])==0||(int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer)){
							clear();
							printw("Invalid input. Enter y coordinate between 1-10\n");
							refresh();
							buffer[0]='\n';
							buffer[1]='\0';
							i = strlen(buffer)+1;
						}
					}
				}while((int)strlen(buffer)>3||buffer[0]=='\n'||atoi(buffer)<=0||10<atoi(buffer));
				y =atoi(buffer);
                visibleGrid2[y - 1][x - 1] = invisibleGrid2[y - 1][x - 1]; 
                print_array(visibleGrid2);
                switch (visibleGrid2[y - 1][x - 1]) {
                    case 'x':
                        printw("You missed. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                        break;
                    case 'C':
                        printw("You hit the Carrier. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                        count2++;
                        break;
                    case 'B':
                    	printw("You hit the Battleship. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count2++;
                    	break;
                    case 'S':
                    	printw("You hit the Submarine. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count2++;
                    	break;
                    case 'D':
                    	printw("You hit the Destroyer. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count2++;
                    	break;
                    case 'P':
                    	printw("You hit the Patrol Boat. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                    	count2++;
                    	break;
                    default:
                        printw("This is an error. Press any key to continue.\n");
						refresh();
						getch();
						clear();
                        break;
                    }turn = 0;
                }break;
	}while (count1 < 17 || count2 < 17);
	switch (turn) {
        case 0:
            printw("Player 1 wins. Press any key to continue.\n");
            print_array(invisibleGrid2);
			getch();
			refresh();
			break;
        case 1:
            printw("Player 2 wins. Press any key to continue.\n");
            print_array(invisibleGrid1);
			getch();
			refresh();
			break;
	}endwin();
	return 0;
}
