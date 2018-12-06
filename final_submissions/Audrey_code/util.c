#include <stdio.h>
#include <math.h>
#include "util.h"

double stdev(double* vals, int len){
  double avg = 0.0;
  for(int i = 0; i < len; i++) {
    avg+= vals[i];
  }
  avg /= len;
  double std = 0;
  for(int i = 0; i < len; i++) {
    double diff = vals[i] - avg;
    std += (diff*diff);
    //printf("%lf ", diff*diff);
  }
  double new_std = sqrt(std/len);
  printf("FUNCTION Avg: %lf Stdev: %lf\n", avg, new_std);
  return new_std;
}

void stdev_and_avg(double* vals, int len, double* avg_to_fill, double* stdev_to_fill){
  double avg = 0.0;
  for(int i = 0; i < len; i++) {
    avg+= vals[i];
  }
  avg /= len;
  double std = 0;
  for(int i = 0; i < len; i++) {
    double diff = vals[i] - avg;
    std += (diff*diff);
    //printf("%lf ", diff*diff);
  }
  double new_std = sqrt(std/len);
  *avg_to_fill = avg;
  *stdev_to_fill = new_std;
}

void strip_outliers(double* vals, int len, double avg, double tolerance) {
  // Copy vals into new_vals, stripping all values that aren't within +-
  // tolerance of avg.
  double max_bound = avg + tolerance;
  double min_bound = avg - tolerance;
  int strip_vals_len = len;
  double strip_avg = -1.0;
  double strip_stdev = -1.0;
  for(int i = 0; i < len; i++) {
    if(vals[i] >= max_bound || vals[i] <= min_bound) {
      strip_vals_len --;
    }
  }
  double strip_vals[strip_vals_len];
  int strip_ctr =0;
  for(int i = 0; i < len; i++) {
    if(vals[i] <= max_bound && vals[i] >= min_bound) {
      strip_vals[strip_ctr] = vals[i];
      strip_ctr++;
    }
  }
  stdev_and_avg(strip_vals, strip_vals_len, &strip_avg, &strip_stdev);
  printf("After removing outliers, avg = %lf and stdev = %lf\n",
         strip_avg, strip_stdev);
}
