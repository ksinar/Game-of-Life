#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 20
#define COLUMNS 40
#define MAXSIZE 150

/*
 * code by Kaan Sinar
 * Conway's Game of Life
 * Usage: ./cgol seed (ticks)
 */


/* function to remove the spaces from a string */
int removeSpaces(char * input){
    int len = strlen(input);
	char sub[MAXSIZE];
	int i;
	int replace = 0;
	int spacesRemoved = 0;
	for(i = 0; i < len; i++){
		sub[i] = input[i];
	}

	for(i = 0; i < len; i++){
		if(sub[i] != ' '){
			input[replace] = sub[i];
			replace++;
		}else{
			spacesRemoved++;
		}
	}


	input[replace] = '\0';


return 0;

}


int main(int argc, char *argv[]){

    int i = 0;
    int j = 0;

    int repeat = 0;

    char start[200];

    int ticks;

    int tickCount = 0;

    char cont[200];

    FILE *seed;
    char buffer[MAXSIZE];
    if((argc != 2) && (argc != 3)){
        printf("Usage: ./cgol seed (ticks)\n");
        exit(1);
    }

    if (argc == 3){
        ticks = atoi(argv[2]);
    }else{
        ticks = 50;
    }

    char read[ROWS][COLUMNS];

    /* reading the seed into an array */

    if ( (seed = fopen(argv[1], "r")) != NULL ) {

        j = 0;

        while ( fgets(buffer, MAXSIZE, seed) != NULL ) {
            removeSpaces(buffer);

            for(i = 0; i < COLUMNS; i++){
            
                read[j][i] = buffer[i];
                
            }
            j++;
            
        }

    }

    for(i = 0; i < 20; i++){
        for(j = 0; j < 40; j++){
            
                if(read[i][j] == '1'){
                    read[i][j] = 'x';
                }else if(read[i][j] == '0'){
                    read[i][j] = ' ';
                }
            
        }
    }

    char grid1[22][43];
    char grid2[22][43];
/* addition of the border */
    for(i = 1; i < 21; i++){

        grid1[i][0] = '|';
        grid1[i][41] = '|';

        grid2[i][0] = '|';
        grid2[i][41] = '|';

    }

    for(j = 0; j < 42; j++){

        grid1[0][j] = '-';
        grid1[21][j] = '-';

        grid2[0][j] = '-';
        grid2[21][j] = '-';

    }

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            grid1[i + 1][j + 1] = ' ';
            grid2[i + 1][j + 1] = ' ';
        }
    }
    
/* reading in the seed into the grid */
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLUMNS; j++){
            grid1[i + 1][j + 1] = read[i][j];
        }
    }

    int neighbors[20][40];

    int x;

int restart;
int askStart = 0;
while (askStart == 0){

    for(i = 0; i < 22; i++){ 
        for(j = 0; j < 42; j++){
            printf("%c", grid1[i][j]);
        }
        printf("\n");
    }

/* asks if you want to start, terminates if 'n' is pressed and starts if 'y' is pressed.
asks again if neither are pressed */

    printf("Start? (y or n):");
    fgets(start,200,stdin);
	sscanf(start, "%*c");

if(start[1] == '\n'){

    if(((start[0]) == 'y') || ((start[0]) == 'Y')){
        system("clear");
        restart = 0;
        askStart = 1;
    }else if(((start[0]) == 'n') || ((start[0]) == 'N')){
        restart = 1;
        askStart = 1;
        break;
    }else{
        system("clear");
        askStart = 0;
    }
}else{
    system("clear");
    askStart = 0;
}
}

while(restart == 0){

    for(x = 0; x < ticks; x++){

    repeat = 0;
/* clearing neighbors array before each iteration */
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            neighbors[i][j] = 0;
        }
    }
/* putting the number of live neighbors each cell has in an array */
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            if((grid1[i][j]) == 'x'){
                neighbors[i][j]++;
            }
            
            if((grid1[i][j + 1]) == 'x'){
                neighbors[i][j]++;
            }

            if((grid1[i][j + 2]) == 'x'){
                neighbors[i][j]++;
            }

            if((grid1[i + 1][j]) == 'x'){
                neighbors[i][j]++;
            }
            
            if((grid1[i + 1][j + 2]) == 'x'){
                neighbors[i][j]++;
            }

            if((grid1[i + 2][j]) == 'x'){
                neighbors[i][j]++;
            }

            if((grid1[i + 2][j + 1]) == 'x'){
                neighbors[i][j]++;
            }

            if((grid1[i + 2][j + 2]) == 'x'){
                neighbors[i][j]++;
            }
        }
    }

/* setting next generation in real time */
    
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            if(((neighbors[i][j]) < 2) && ((grid1[i + 1][j + 1]) == 'x')){
                grid2[i + 1][j + 1] = ' ';
            }

            if((((neighbors[i][j]) == 2) || (neighbors[i][j] == 3)) && ((grid1[i + 1][j + 1]) == 'x')){
                grid2[i + 1][j + 1] = 'x';
            }

            if(((neighbors[i][j]) > 3) && ((grid1[i + 1][j + 1]) == 'x')){
                grid2[i + 1][j + 1] = ' ';
            }

            if(((neighbors[i][j]) == 3) && ((grid1[i + 1][j + 1]) == ' ')){
                grid2[i + 1][j + 1] = 'x';
            }
        }
    }

    for(i = 0; i < ROWS; i++){ 
        for(j = 0; j < COLUMNS; j++){
            if((grid1[i + 1][j + 1]) == (grid2[i + 1][j + 1])){
                repeat++;
            }
        }
    }

    if(repeat == 800){
        printf("No change.\n");
        return 0;
    }

    for(i = 0; i < 22; i++){ 
        for(j = 0; j < 42; j++){
            printf("%c", grid2[i][j]);
        }
        if(i != 21){
            printf("\n");
        }
    }

    printf("%d\n", tickCount);

    tickCount++;


    for(i = 0; i < ROWS; i++){ 
        for(j = 0; j < COLUMNS; j++){
            

            grid1[i + 1][j + 1] = grid2[i + 1][j + 1];
        }
    }

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            grid2[i + 1][j + 1] = ' ';
        }
    }

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            neighbors[i][j] = 0;
        }
    }

    system("sleep 0.25");
    system("clear");
    
    }
    
    int rep = 0;
/* asks if you want to continue after the set amount of ticks */
    while(rep == 0){

    printf("Continue? (y or n):");
    fgets(cont,100,stdin);
	sscanf(cont, "%*c");

    if(cont[1] == '\n'){

        if(((cont[0]) == 'y') || ((cont[0]) == 'Y')){
            break;
            rep = 1;
        }else if(((cont[0]) == 'n') || ((cont[0]) == 'N')){
            rep = 1;
            restart = 1;
        }else{
            printf("Enter y or n.\n");
            continue;
    }
    }else{
        printf("Enter y or n.\n");
        continue;
    }
    }
}
return(0);
}
