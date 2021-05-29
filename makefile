iric: myiritest.c libiri.so
        gcc -o iric myiritest.c ./libiri.so

libiri.so: iritest.for irisub.for irifun.for iritec.for iridreg.for igrf.for cira.for iriflip.for
        f77 --shared -fPIC -o libiri.so iritest.for irisub.for irifun.for iritec.for iridreg.for igrf.for cira.for iriflip.for
        
