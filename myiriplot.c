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
    "plot '1' u 2:1 with lines lc 1 lw 3 title '1'\\"
  };

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

  printf("Plotting ...\n");

  FILE * gnuplotpipe = popen ("gnuplot", "w");
  for (i=0; i < 6; i++) fprintf(gnuplotpipe, "%s\n", gnuplotcmd[i]);
  for (i=2; i < j; i++) fprintf(gnuplotpipe, ", '%d' u 2:1 with lines lc %d lw 3 title '%d'\\\n", i, i, i);
  fprintf(gnuplotpipe, "\n");

  pclose (gnuplotpipe);
}
