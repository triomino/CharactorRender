
CFLAGS = -I"../include/"

SRCPATH = ../src/
HEADPATH = ../include/
OBJS = rasterizer.o vertex_shader.o
test : test.o ${OBJS}
	g++ -o $@ $< ${OBJS} ${CFLAGS}

test.o : ${SRCPATH}test.cc ${HEADPATH}rasterizer.h ${HEADPATH}fragment.h ${HEADPATH}my_math.h ${HEADPATH}vertex.h ${HEADPATH}vertex_shader.h
	g++ -c -o $@ $< ${CFLAGS}

rasterizer.o : ${SRCPATH}rasterizer.cc ${HEADPATH}rasterizer.h ${HEADPATH}fragment.h ${HEADPATH}my_math.h ${HEADPATH}vertex.h
	g++ -c -o $@ $< ${CFLAGS}
	
vertex_shader.o : ${SRCPATH}vertex_shader.cc ${HEADPATH}rasterizer.h ${HEADPATH}fragment.h ${HEADPATH}my_math.h ${HEADPATH}vertex.h ${HEADPATH}vertex_shader.h
	g++ -c -o $@ $< ${CFLAGS}
	
.PHONY : clean
clean : 
	-rm -r *.o *.exe