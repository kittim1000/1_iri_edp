# include <stdio.h>

extern void read_ig_rz_();
extern void readapf107_();
extern void iri_web_(int *, int [], float *, float *, int *, int *, int *, float *, float *, float *,
    int *, float *, float *, float *, float [][20], float [][100]);

void main() {

  int i, li, numstp, nummax, ind = 1;
  int jm, jf[50], iy, imd, iut, ivar, piktab, jchoice;
  float xlat, xlon, hour, hx, vbeg, vend, vstp, htec_max;
  float outf[1000][20], oar[1000][100];

  read_ig_rz_();
  readapf107_();

  for (i=0; i<100; i++) {
    oar[0][i] = -1.0;
  }

  while (ind) {
    printf("\njmag(=0/1,geog/geom),lati/deg,long/deg\n");
    scanf("%d %f %f", &jm, &xlat, &xlon);

    printf("year(yyyy),mmdd(or -ddd),iut(=0/1,LT/UT),hour\n");
    scanf("%d %d %d %f", &iy, &imd, &iut, &hour);

    printf("height/km\n");
    scanf("%f", &hx);

    printf("begin, end, and stepsize for the selected variable\n");
    scanf("%f %f %f", &vbeg, &vend, &vstp);

    ivar = 1;
    piktab = 0;
    htec_max = 0.0;
    jchoice = 0;

    nummax = 1000;

    for (i=0; i<50; i++) {
      jf[i] = 1;
    }

    if (jchoice == 0) {
      jf[3] = 0; jf[4] = 0; jf[5] = 0; jf[20] = 0; jf[22] = 0;
      jf[25] = 0; jf[27] = 0; jf[28] = 0; jf[29] = 0;
      jf[32] = 0; jf[34] = 0; jf[38] = 0; jf[46] = 0;
    }

    numstp = (int)((vend-vbeg)/vstp) + 1;
    if (numstp > nummax) numstp = nummax;

    iri_web_(&jm, jf, &xlat, &xlon, &iy, &imd, &iut, &hour, &hx, &htec_max,
        &ivar, &vbeg, &vend, &vstp, outf, oar);

    printf("\n");
    for (li=0; li < numstp; li++) {
      i = (int) (outf[li][0]/1.e6 + .5);
      printf("%d\n", i);
    }

    printf("\nEnter 0 to exit or 1 to generate another profile?\n");
    scanf("%d", &ind);
  }
}
