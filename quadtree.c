#include <stdio.h>
#include <stdlib.h>

#define GRAY 2
#define WHITE 0
#define BLACK 1
#define TRUE 1
#define FALSE 0

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

void printArray(int Array[65][65],int size, int xpos, int ypos)
{
	int i, j;
	//prints contents of Array
	for(i = 0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%i", Array[j+xpos][i+ypos]);
		}
		printf("\n");
	}
	printf("\n");
}
//Copies data values from node into printingarray
int ArrayfromNode(int printingarray[65][65], struct node current)
{
	
	static int count=0;
	printf("count = %i\n", count);
	printf("check1");
	if((current.colour == WHITE)||(current.colour==BLACK))
	{
		int i, j;
		count++;
		for(i=0;i<current.size;i++)
		{
			for (j=0;j<current.size; j++)
			{
				printingarray[current.xpos+i][current.ypos+j]=current.colour;
			}
		}
		
		
		return 0;
	}
	
	if(current.colour == GRAY)
	{   
		printf("check1-1");
		
	    ArrayfromNode(printingarray, *current.NE);
		printf("check2-2");
		ArrayfromNode(printingarray, *current.NW);
		
		ArrayfromNode(printingarray, *current.SE);
		
		ArrayfromNode(printingarray, *current.SW);
		
		return 0;
	}
	
	else 
	{
		exit(EXIT_FAILURE); 
	}
	
}

int detectColour(struct node current, int Array[65][65])
{
	int i,j,count1=0, count0=0,this=0;
	//printf("detecting colour\n");
	//printArray(Array, current.size, current.xpos, current.ypos);
	//printf("current.xpos is %i\n", current.xpos);
	//printf("current.ypos is %i\n", current.ypos);
	for(i = 0;i<current.size;i++)
	{
		for(j=0;j<current.size;j++)
		{
			if(Array[j+current.xpos][i+current.ypos]==1)
			{
				//printf("(Array[%i][%i] is 1\n",j+current.xpos, i+current.ypos);
				count1++;
			}
			else if(Array[j+current.xpos][i+current.ypos]==0)
			{
				//printf("(Array[%i][%i] is 0\n",j+current.xpos, i+current.ypos);
				count0++;
			}
			else 
			{
				printf("exit FAILURE");
				exit(EXIT_FAILURE); 
			}
			
		}
	}
	
	//printf("current.size is %i\n", current.size);
	//printf("count1, count0 is %i, %i\n", count1, count0);
	if(count0==(current.size*current.size))
	{
		//printf("returning WHITE\n");
		return WHITE;
	}
	
	else if(count1==(current.size*current.size))
	{
		//printf("returning BLACK\n");
		return BLACK;
	}
	else
	{
		//printf("returning GRAY\n");
		return GRAY;
	}
}

int NodefromArray(int Array[65][65], struct node current, int size)
{
	int mid;
	struct node NE,NW,SE,SW;
	//static int layer = -1;
	//layer++;
	//printf("current layer is %i\n\n", layer);
	mid=current.size/2;
	
	current.colour=detectColour(current, Array);
	

	if (current.colour==WHITE||current.colour==BLACK)
	{
		//printf("current.colour=%i\n\n", current.colour);
		current.NE=NULL;
		current.SE=NULL;
		current.NW=NULL;
		current.SW=NULL;
		return 0;
	}
	else if(current.colour == GRAY)
	{   
		//printf("current.colour=GRAY\n\n");
		current.NE=&NE;
		current.SE=&SE;
		current.NW=&NW;
		current.SW=&NW;
		
		NE.xpos=current.xpos;
		NE.ypos=current.ypos;
		NE.size=mid;
		NE.parent=&current;
		
		//printf("NodefromArrayNE\n");

	    NodefromArray(Array, NE,size);
		//layer--;
		NW.xpos=(current.xpos+mid);
		//printf("NW.xpos=%i\n", NW.xpos);
		NW.ypos=current.ypos;
		//printf("NW.ypos=%i\n", NW.ypos);
		NW.size=mid;
		//printf("NW.size=%i\n", NW.size);
		NW.parent=&current;
		
		//printf("NodefromArrayNW\n");

		NodefromArray(Array, NW,size);
		//layer--;
		
		SE.xpos=current.xpos;
		SE.ypos=(current.ypos+mid);
		SE.size=mid;
		SE.parent=&current;
		

		NodefromArray(Array, SE,size);
		//layer--;
		
		SW.xpos=(current.xpos+mid);
		SW.ypos=(current.ypos+mid);
		SW.size=mid;
		SW.parent=&current;
		
		//printf("NodefromArraySW\n");

		NodefromArray(Array, SW,size);
		
		//printf("Returned@layer %i\n", layer);
		//layer--;
		return 0;
	}
	
	else 
	{
		printf("exit FAILURE, current.colour is %i\n", current.colour);
		exit(EXIT_FAILURE); 
	}
}





void readWritefile(FILE *fp, int numpix, int array[65][65])
{
	int x, y ,i;
	//writes coordinates of input file into array as pixels
	for(i=0;i<numpix;i++)
	{
		fscanf(fp,"%i %i", &x, &y);
		array[x][y]=1;
	}
}
	
int main(int argc, char *argv[])
{
	int tempArray[65][65];
	int printingarray[65][65];
	initialize(tempArray);
	initialize(printingarray);
	
	if (argc != 2)
	{
		fprintf(stderr,"Incorrect number of arguments. Correct number is 1\n");
		exit(EXIT_FAILURE);
	}
	
	FILE *fp;
	//printf("check1\n");
	int i, size, numpix, x, y;
	//printf("check2\n");
	fp = fopen(argv[1], "r");
	//printf("check3\n");
	
	fscanf(fp,"%i",&size);
	printf("Size is %i\n", size);
	
	fscanf(fp,"%i",&numpix);
	printf("Number of Pixels is %i\n", numpix);

	//printf("check6\n");
	
	//Reads coordinates and writes into tempArray as pixels
	readWritefile(fp, numpix, tempArray);
	//printf("check7\n");
	
	//tests contents of Temparray
	printArray(tempArray, size, 0, 0);
	
	//converts tempArray into a pointer based node system
	//createNode(NULL, );
	//defines parent
	struct node parent;
	parent.parent=NULL;
	parent.xpos=0;
	parent.ypos=0;
	parent.colour=GRAY;
	parent.size=size;
	
	NodefromArray(tempArray, parent, size);
	printf("NodefromArray complete\n\n");
	
	ArrayfromNode(printingarray,parent);
	printArray(printingarray, size, 0, 0);
	
	fclose(fp);	
}