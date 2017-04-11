#include <stdio.h>
#include <stdlib.h>

//testing parameters
#define TESTSIZE 8
#define TESTNUMPIX 15

#define GRAY 2
#define WHITE 0
#define BLACK 1






struct node
{
	struct node *parent;
	struct node *NE;
	struct node *NW;
	struct node *SE;
	struct node *SW;
	int colour;
	int xpos;
	int ypos;
	int size;
};
void nodeConvert(int Array[65][65])
{
	
}
void initialize(int array[65][65])
	{
		for (int i=0;i<64;i++)
		{
			for (int j=0;j<64;j++)
			{
				array[i][j]=0;
			}
		}
	}
void write(int Array[65][65], int inputarray[][2], int numpix)
{	

	int x, y, i;
	//writes coordinates of inputarray into Array as pixels
	for(i = 1;i<=numpix;i++)
	{
		x = inputarray[i][0];
		y = inputarray[i][1];
		
		Array[x][y]=1;
	}
	
}

void printArray(int Array[65][65],int size)
{
	int i, j;
	//prints contents of Array
	for(i = 0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%i", Array[j][i]);
		}
		printf("\n");
	}
}

void readfile(FILE *fp, int numpix, int inputarray[][2])
{
	int i;
	for(i=1;i<=numpix;i++)
	{
		fscanf(fp,"%i %i",&inputarray[i][0],&inputarray[i][1]);
	}
	
}
	
int main(int argc, char *argv[])
{
	int tempArray[65][65]={0};
	initialize(tempArray);
	FILE *fp;
	//printf("check1\n");
	int i, size, numpix, x, y;
	//printf("check2\n");
	fp = fopen(argv[1], "r");
	//printf("check3\n");
	fscanf(fp,"%i",&size);
	//printf("check4\n");
	fscanf(fp,"%i",&numpix);
	//printf("check5\n");
	int inputarray[numpix+1][2];
	//printf("check6\n");

	/*for(i=1;i<=numpix;i++)
	{
		printf("count1 %i\n", i);
		fscanf(fp,"%i %i",&x,&y);
		inputarray[i][0]=x;
		printf("count2 %i\n", i);
		inputarray[i][1]=y;
		printf("count3 %i\n", i);
		
	}*/
	
	readfile(fp, numpix, inputarray);
	
	//printf("check7\n");
	/*temporary coordinates for testing
	int testarray[TESTNUMPIX+1][2];
	size = TESTSIZE;
	numpix = TESTNUMPIX;
	testarray[1][0] = 4;testarray[1][1] = 1;
	testarray[2][0] = 5;testarray[2][1] = 1;
	testarray[3][0] = 2;testarray[3][1] = 2;
	testarray[4][0] = 3;testarray[4][1] = 2;
	testarray[5][0] = 4;testarray[5][1] = 2;
	testarray[6][0] = 5;testarray[6][1] = 2;
	testarray[7][0] = 2;testarray[7][1] = 3;
	testarray[8][0] = 3;testarray[8][1] = 3;
	testarray[9][0] = 4;testarray[9][1] = 3;
	testarray[10][0] = 5;testarray[10][1] = 3;
	testarray[11][0] = 4;testarray[11][1] = 4;
	testarray[12][0] = 5;testarray[12][1] = 4;
	testarray[13][0] = 6;testarray[13][1] = 4;
	testarray[14][0] = 4;testarray[14][1] = 5;
	testarray[15][0] = 5;testarray[15][1] = 5;
	
	write(tempArray,testarray,numpix);
	
	*/
	
	//currently writes testarray into tempArray as pixels
	write(tempArray,inputarray, numpix);
	//tests contents of Temparray
	printArray(tempArray, size);
	//converts tempArray into a pointer based node system
	nodeConvert(tempArray);
	
	fclose(fp);	
}

