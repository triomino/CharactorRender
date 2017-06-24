HEADPATH = ../include/

test : test.cc ${HEADPATH}rasterizer.h rasterizer.cc
	cd ../bin && make test
	cp ../bin/test.exe ../src/test.exe

.PHONY : clean
clean : 
	-rm -r *.o *.exe
	cd ../bin && make clean