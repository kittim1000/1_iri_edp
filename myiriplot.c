#include <stdio.h>
#include <stdlib.h>

void main()
{
  int i, jm, iy, imd, iut;
  float xlat, xlon, hour, vbeg, vend, vstp;

  char * gnuplotcmd[] = {
    "set terminal png",
    "set output 'EDP.png'",
    "set xrange [0:600000]",
    "set xlabel 'Electron Density Ne/cm-3'",
    "set ylabel 'Altitude (km)'",
    "set key off",
    "plot 'gnuplottmp.txt' using 2:1 with lines lc 3 lw 3",
  };

  printf("\n>> jmag(=0/1,geog/geom),lati/deg,long/deg\n");
  scanf("%d %f %f", &jm, &xlat, &xlon);

  printf(">> year(yyyy),mmdd(or -ddd),iut(=0/1,LT/UT),hour\n");
  scanf("%d %d %d %f", &iy, &imd, &iut, &hour);

  printf(">> begin, end, and stepsize for the selected variable\n");
  scanf("%f %f %f", &vbeg, &vend, &vstp);

  printf("Plotting ...\n");

  FILE * fp = fopen("gnuplottmp", "w");
  fprintf(fp, "%d %.2f %.2f\n%d %04d %d %.2f\n%.2f %.2f %.2f\n0\n", jm, xlat, xlon, iy, imd, iut, hour, vbeg, vend, vstp); // Print input file for ./iric
  fclose (fp);

  system("./iric < gnuplottmp | grep -v -e '[eo]' > gnuplottmp.txt"); // Run ./iric

  FILE * gnuplotpipe = popen ("gnuplot", "w");
  for (i=0; i<7; i++) fprintf(gnuplotpipe, "%s \n", gnuplotcmd[i]); // Run gnuplot
  pclose (gnuplotpipe);
}
