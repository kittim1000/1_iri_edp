# Ionospheric Electron Density Profile

`myiritest.c` is a C-interface for the Ionospheric model found in the International Reference Ionosphere (IRI, http://irimodel.org/). 
IRI provides a suite of Fortran codes and data sets to model the ionospheric properties such as electron density/temperature, ion composition and temperature for the given time, location and a host of other variables. 
`myiritest.c` is intended as a minimal interface for the IRI model on which extensions may be built up for further applications. 
It provides the Electron Density Profile (EDP) for the Altitude range, date/time and location supplied by the user.

## Method

`iritest.for` in the IRI model provides a user-interface for which many variables and options are available for garnering ionospheric information. 
We built a simpler rendering of it in `myiritest.c` so that only those variables necessary for standard input and Altitude-EDP output may be retained. 
Considerations for C-Fortran interface such as Data-types, Passing-by-reference, Array settings etc. were maintained.

Specifically, the following variables are fixed in `myiritest.c`, although they are chosen by the users in the IRI model:

```
jf[50], ivar = 1, piktab = 0, jchoice = 0, htec_max = 0.0
// hx value is not relevant for altitude-dependent EDP
```

Makefile was written so that a shared object may be built out of IRI Fortran codes, which is incorporated in the `myiritest.c` compilation.

## Usage

Download and extract the codes and data set:

```
wget http://irimodel.org/IRI-2016/00_iri.tar 
tar -xvf 00_iri.tar
wget http://irimodel.org/COMMON_FILES/00_ccir-ursi.tar
tar -xvf 00_ccir-ursi.tar

wget https://chain-new.chain-project.net/echaim_downloads/apf107.dat
wget https://chain-new.chain-project.net/echaim_downloads/ig_rz.dat
```

Place `makefile` and `myiritest.c` in the same directory.

Compile and run ./iric

```
make
./iric
```

Specify the geographic or geomagnetic latitude and longtitude in degrees in [-90.:90] and [-180.:180.] respectively
(Negative numbers for Southern or Western hemisphere; Longitude range in [0.:360.] also works).

Input year/date after 1958, indicate universal or local time, and hour in [0.:24.].

Set the desired altitude range and stepsize between 60 and 2000 km.

```
>> jmag(=0/1,geog/geom),lati/deg,long/deg
0 37.8 -75.4
>> year(yyyy),mmdd(or -ddd),iut(=0/1,LT/UT),hour
2021 0303 1 11.
>> begin, end, and stepsize for the selected variable
60. 1000. 10.
```

The following will be shown for the initial running:

```
*** IRI parameters are being calculated ***
Ne: NeQuick for Topside
Ne, foF2: URSI model is used.
Ne: B0,B1-ABT-2009
Ne, foF1: probability function used.
Ne, D: IRI1990
Ion Com.: RBV-10 & TBT-15
Te: TBT-2012 model
Auroral boundary model off
Ne, foE: storm model off
```

And then the EDP is printed as follows:

```
>> Altitude (km)        Electron Density (Ne/cm-3)
60      0
70      15
80      308
90      1881
100     6323
  … etc

>> Enter 0 to exit or 1 to generate another profile?
```

A Gnuplot for the following iputs is shown above as `EDP.png`:
```
time of interest: Mar 3 2021 UT 11:00:00 and Mar 4, 2021 UT 23:00:00 
location of interest: Lat 37.8N and Lon 75.4W 
```

`myiriplot.c` is an example of C code running `myiritest.c` and incorporating gnuplot for EDP visualization.

## Discussion

This exercise provides a valuable example of scientific computation involving C-Fortran interface and shared library. 
Study of IRI codes and data provides an excellent opportunity to learn the ionosphere physics and the methods currently utilized by scientists,
as well as gain insights on the importance of the higher realm for modern life and applications. 
This exercise may serve as a basis from which more sophisticated tools can be built for more flexible and extensive utilization of IRI model that meets the need of users.
