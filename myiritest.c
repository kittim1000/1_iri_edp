# include <stdio.h>

extern void read_ig_rz_();
extern void readapf107_();
extern void iri_web_(int *, int [], float *, float *, int *, int *, int *, float *, float *, float *,
    int *, float *, float *, float *, float [][20], float [][100]);

void main() {

  int i, li, numstp, jm, jf[50], iy, imd, iut;
  int nummax = 1000, ind = 1, ivar = 1, piktab = 0, jchoice = 0;

  float xlat, xlon, hour, hx, vbeg, vend, vstp, outf[1000][20], oar[1000][100];
  float htec_max = 0.0;

  for (i=0; i<100; i++) {
    oar[0][i] = -1.0;
  }

  for (i=0; i<50; i++) {
    jf[i] = 1;
  }

  jf[3] = 0; jf[4] = 0; jf[5] = 0; jf[20] = 0; jf[22] = 0;
  jf[25] = 0; jf[27] = 0; jf[28] = 0; jf[29] = 0;
  jf[32] = 0; jf[34] = 0; jf[38] = 0; jf[46] = 0;

  read_ig_rz_();
  readapf107_();

  while (ind) {
    printf("\n>> jmag(=0/1,geog/geom),lati/deg,long/deg\n");
    scanf("%d %f %f", &jm, &xlat, &xlon);

    printf(">> year(yyyy),mmdd(or -ddd),iut(=0/1,LT/UT),hour\n");
    scanf("%d %d %d %f", &iy, &imd, &iut, &hour);

    printf(">> begin, end, and stepsize for the selected variable\n");
    scanf("%f %f %f", &vbeg, &vend, &vstp);
    printf("\n");

    numstp = (int)((vend-vbeg)/vstp) + 1;
    if (numstp > nummax) numstp = nummax;

    iri_web_(&jm, jf, &xlat, &xlon, &iy, &imd, &iut, &hour, &hx, &htec_max,
        &ivar, &vbeg, &vend, &vstp, outf, oar);

    printf("\n>> Altitude (km)\tElectron Density (Ne/cm-3)\n");
    for (li=0; li < numstp; li++) {
      i = (int) (outf[li][0]/1.e6 + .5);
      hx = vbeg + li*vstp;
      printf("%.0f\t%d\n", hx, i);
    }

    printf("\n>> Enter 0 to exit or 1 to generate another profile?\n");
    scanf("%d", &ind);
  }
}
