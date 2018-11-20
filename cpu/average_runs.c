#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double stdev(double* vals, int len){
	  double avg = 0.0;
	  for(int i = 0; i < len; i++) {
			avg += vals[i];
	  }
	  avg /= len;
	  double std = 0;
	  for(int i = 0; i < len; i++) {
			double diff = vals[i] - avg;
			std += (diff*diff);
	  }
	  double new_std = sqrt(std/len);

		printf("Mean: %lf, Std dev: %lf, trials: %d\n", avg, new_std, len);
	  return new_std;
}


int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Input a file with one number in each line.\n");
		exit(0);	
	}

	char buf[10000];
	double runs[1000000];

	FILE* fp = fopen (argv[1], "r");
	double col1;
	int trials = 0;
	printf("here");

	while (fgets(buf, sizeof buf, fp) != NULL) {
		// Get values from each line
		sscanf(buf, "%lf", &col1);
		runs[trials] = col1;
		trials++;
	}

	stdev(runs, trials);
}
