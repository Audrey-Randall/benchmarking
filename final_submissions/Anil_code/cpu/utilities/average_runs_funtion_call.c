#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Input a file with two numbers in each line separated by a comma.\n");
		exit(0);	
	}

	FILE* fp = fopen (argv[1], "r");
	char buf[10000];
	double col1, col2, total1 = 0, total2 = 0;
	int trials = 0;
	while (fgets(buf, sizeof buf, fp) != NULL) {
		// Get values from each line
		trials++;
		sscanf(buf, "%lf, %lf", &col1, &col2);
		total1 += col1;
		total2 += col2;
	}

	printf("avg mean: %lf, avg std dev: %lf, trials: %d\n", total1/trials, total2/trials, trials);
}
