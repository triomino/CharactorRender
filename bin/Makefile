
CFLAGS = -I"../include/"

SRCPATH = ../src/
HEADPATH = ../include/
OBJRASTERIZER = rasterizer.o
test : test.o ${OBJRASTERIZER}
	g++ -o $@ $< ${OBJRASTERIZER} ${CFLAGS}

test.o : ${SRCPATH}test.cc ${HEADPATH}rasterizer.h ${HEADPATH}fragment.h ${HEADPATH}my_math.h ${HEADPATH}vertex.h
	g++ -c -o $@ $< ${CFLAGS}

${OBJRASTERIZER} : ${SRCPATH}rasterizer.cc ${HEADPATH}rasterizer.h ${HEADPATH}fragment.h ${HEADPATH}my_math.h ${HEADPATH}vertex.h
	g++ -c -o $@ $< ${CFLAGS}
    
.PHONY : clean
clean : 
	-rm -r *.o *.exe