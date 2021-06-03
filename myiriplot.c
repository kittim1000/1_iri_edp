#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[])
{
  int i, j;

  char *gnuplotcmd[] = {
    "set terminal png",
    "set output 'EDP.png'",
    "set xrange [0:600000]",
    "set xlabel 'Electron Density Ne/cm-3'",
    "set ylabel 'Altitude (km)'",
  };
  char gnuplotcmd2[500] = "plot '1' using 2:1 with lines lc 1 lw 3";

  char str[50], nums[2];
  FILE *fp, *fp2;

  printf("Computing ...\n");
  sprintf(str, "./iric < %s | grep -v -e '[eo]' > gnuplot.dat", argv[1]);
  system(str);

  fp = fopen("gnuplot.dat", "r");

  i = 0; // Is the input line empty?
  j = 1;

  while ( fgets (str, 50, fp) != NULL) {
    if (i == 0 && strlen(str) > 1) {
      sprintf(nums, "%d", j++);
      fp2 = fopen(nums, "w");
      i = 1;
    }

    if (strlen(str) > 1) fprintf(fp2, "%s", str);

    if (i == 1 && strlen(str) == 1) {
      fclose (fp2);
      i = 0;
    }
  }
  fclose (fp);

  for (i=2; i < j; i++) {
    sprintf(str, ", '%d' using 2:1 with lines lc %d lw 3", i, i);
    strcat(gnuplotcmd2, str);
  }

  printf("Plotting ...\n");

  FILE * gnuplotpipe = popen ("gnuplot", "w");
  for (i=0; i < 5; i++) fprintf(gnuplotpipe, "%s \n", gnuplotcmd[i]);
  fprintf(gnuplotpipe, "%s \n", gnuplotcmd2);

  pclose (gnuplotpipe);
}
