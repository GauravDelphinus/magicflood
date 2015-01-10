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

	char dummygrid[150];
	int strIndex = 0;
	int xpos = -1;
	int ypos = -1;
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
				xpos = j;
				ypos = k;
			}
	
		}
	}
	dummygrid[strIndex] = '\0';
	
	char output [10000];
	sprintf(output, "\"%d#%d#%d#%s\"", xpos, ypos, i-1, dummygrid);
	if (xpos == -1 || ypos == -1)
	{
		printf("\n error in string");
	}
	else
	{
		printf("\n dummygrid = %s", output);
	}
	printf("\n END OF SCRIPT\n");
	return 0;
}
