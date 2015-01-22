#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	//printf("Hello World, %s - %s\n", argv[0], argv[1]);

	FILE * fp;
	char str[20][20];

	fp = fopen (argv[1], "r");
	int i = 0;
	while(! feof(fp))
	{
		fscanf(fp, "%s", str[i]);
		i++;
	}
	fclose(fp);

	char dummygrid[1500];
	int strIndex = 0;
	int startposCount = 0;
	int a = 0;
	//Assuming there will be maximum 10 start points in a game
	int startposArr[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	//int xpos = -1;
	//int ypos = -1;
	for (int j = 0; j < i; j++)
	{
		int length = strlen(str[j]);
		for (int k = 0; k < length; k++)
		{

			if (str[j][k] == '*')
			{	
				dummygrid[strIndex++] = '0';
				//insert 0 to tht position
			}
			else if (str[j][k] == '-')
			{
				//insert random number
				int num = (rand() % 6 ) + 1;
				dummygrid[strIndex++] = num + '0';
			}
			else if (str[j][k] == '$')
			{ 
				//insert $
				int num = (rand() % 6 ) + 1;
				dummygrid[strIndex++] = num + '0';
				startposArr[a++] = j;
				startposArr[a++] = k;
				startposCount++; 
				//xpos = j;
				//ypos = k;
			}
	
		}
	}
	dummygrid[strIndex] = '\0';
	
	char output [10000];
	sprintf(output, "\"%d#", startposCount);
	printf("%s", output);
	for (int i = 0; i < a; i++)
	{
		sprintf(output, "%d#", startposArr[i]);
		printf("%s", output);
	}
	sprintf(output, "%d#%s\"", i-1, dummygrid);
	printf("%s,\n", output);
	//if (xpos == -1 || ypos == -1)
	//{
	//	printf("\n error in string");
	//}
	//else
	//{
	//	printf("%s,\n", output);
	//}
	return 0;
}
