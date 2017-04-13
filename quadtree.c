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
int nodeConvert(int Array[65][65], struct node current, int size)
{
	int mid;
	struct node NE,NW,SE,SW;
	mid=current.size/2;
	//printf("check1\n");
	
	//mid+1
	
	if(current.size == 1)
	{
		current.colour=Array[current.xpos][current.ypos];
		printf("%i",current.colour);
		if(current.xpos==size-1)
		{
			printf("\n");
		}
		return 0;
	}
	
	if(current.size >= 1)
	{   
		current.colour=GRAY;
		current.NE=&NE;
		current.SE=&SE;
		current.NW=&NW;
		current.SW=&NW;
		NE.xpos=current.xpos;
		NE.ypos=current.ypos;
		NE.size=current.size/2;
		NE.parent=&current;
	    nodeConvert(Array, NE,size);
		NW.xpos=(current.xpos+mid);
		NW.ypos=current.ypos;
		NW.size=current.size/2;
		NW.parent=&current;
		nodeConvert(Array, NW,size);
		SE.xpos=current.xpos;
		SE.ypos=(current.ypos+mid);
		SE.size=current.size/2;
		SE.parent=&current;
		nodeConvert(Array, SE,size);
		SW.xpos=(current.xpos+mid);
		SW.ypos=(current.ypos+mid);
		SW.size=current.size/2;
		SW.parent=&current;
		nodeConvert(Array, SW,size);
		
		return 0;
	}
	
	else 
	{
		exit(EXIT_FAILURE); 
	}
	
	
	
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
	printf("\n");
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
	printf("check3\n");
	fscanf(fp,"%i",&size);
	printf("check4\n");
	fscanf(fp,"%i",&numpix);
	//printf("check5\n");
	int inputarray[numpix+1][2];
	//printf("check6\n");
	readfile(fp, numpix, inputarray);
	//printf("check7\n");
	
	//currently writes testarray into tempArray as pixels
	write(tempArray,inputarray, numpix);
	//tests contents of Temparray
	printArray(tempArray, size);
	//converts tempArray into a pointer based node system
	
	//define Layer0
	struct node layer0;
	layer0.xpos=1;
	layer0.ypos=1;
	layer0.colour=2;
	layer0.size=size;
	
	nodeConvert(tempArray, layer0, size);
	fclose(fp);	
}

