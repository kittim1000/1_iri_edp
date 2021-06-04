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
    "plot 'gnuplot.dat' u 2:1 every :::0::0 with lines lc 0 lw 3 title '0'\\"
  };
  char str[100];

  sprintf(str, "./iric < %s | grep -v -e '[eo]' | tr '\\n' 'Z' | sed -r 's/ZZ+/ZZ/g' | sed 's/Z/\\n/g' > gnuplot.dat", argv[1]);
  system(str);

  FILE * fp = fopen(argv[1], "r");

  j = 0;
  while ( fgets (str, 100, fp) != NULL)
    if (strlen(str) > 1) j++;

  FILE * gnuplotpipe = popen ("gnuplot", "w");
  for (i=0; i < 6; i++) fprintf(gnuplotpipe, "%s\n", gnuplotcmd[i]);
  for (i=1; i < j; i++) fprintf(gnuplotpipe, ", 'gnuplot.dat' u 2:1 every :::%d::%d with lines lc %d lw 3 title '%d'\\\n", i, i, i, i);
  fprintf(gnuplotpipe, "\n");

  fclose (fp);
  pclose (gnuplotpipe);
}
