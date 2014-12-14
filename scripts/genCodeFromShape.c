#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//printf("Hello World, %s - %s\n", argv[0], argv[1]);

	FILE * fp;
	char str[20][20];
	char out[200][200];

	fp = fopen (argv[1], "r");

	int i = 0;
	int shapewidth = 0, shapeheight = 0;
	int miny = 20, maxy = 0, minx = 20, maxx = 0;
	while(! feof(fp))
	{
		fscanf(fp, "%s", str[i]);
/*
		char *ptr = NULL;
		if ((ptr = strchr(str[i],'*')) != NULL)
		{
			if (i < miny)
			{
				miny = i;
			}
			if (i > maxy)
			{
				maxy = i;
			}

			int firstx = ptr - str[i];
			char *rptr = strrchr(str[i],'*');
			int lastx = rptr - str[i];
			if (lastx - firstx < minx)
			{
				minx = lastx - firstx;
			}
			if (lastx - firstx > maxx)
			{
				maxx = lastx - firstx;
			}
		}
*/

		i++;
	}
	fclose(fp);


	int outindex = 0;
	for (int j = 0; j < i; j++)
	{
		int length = strlen(str[j]);
		for (int k = 0; k < length; k++)
		{
			if (str[j][k] == '*')
			{
				if (k < minx)
					minx = k;
				if (k > maxx)
					maxx = k;
				if (j < miny)
					miny = j;
				if (j > maxy)
					maxy = j;
				sprintf(out[outindex++], "grid[yoffset + %d][xoffset + %d] = GRID_OBSTACLE;\n", k, j);
			}
		}
	}

	shapewidth = maxx - minx + 1;
	shapeheight = maxy - miny + 1;

	printf("shapeWidth = %d;\n", shapewidth);
	printf("shapeHeight = %d;\n", shapeheight);
	printf("if (useRandom)\n");
	printf("{\n");
	printf("\txoffset = random() %% (gridSize - shapeWidth + 1);\n");
	printf("\tyoffset = random() %% (gridSize - shapeHeight + 1);\n");
	printf("}\n");
	printf("else\n");
	printf("{\n");
	printf("\txoffset = yoffset = 1;\n");
	printf("}\n");

	for (int j = 0; j < outindex; j++)
		printf("%s", out[j]);
	printf("break;\n");

	return 0;
}
