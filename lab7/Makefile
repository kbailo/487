CC = g++
CFLAGS = -g -Wall -Wno-deprecated
MKDEP=makedepend -Y
OS := $(shell uname)
ifeq ($(OS), Darwin)
  LIBS = -framework OpenGL -framework GLUT -lm -lc
else ifeq ($(OS), Linux)
  LIBS = -lGL -lGLU -lGLEW -lglut -lm
#  CFLAGS = -g -Wall -Wno-deprecated -I./GLEW/include
#  GLEW = ./GLEW/src/glew.o
else
  CC = x86_64-w64-mingw32-g++
  LIBS = -lglew32 -lglut32 -lglu32 -lopengl32
endif

HDRS = scene.h xvec.h
SRCS = 
HDRS_SLN = 
SRCS_SLN = raytrace.cpp scene.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS)) $(patsubst %.cpp,%.o,$(SRCS_SLN))

raytrace: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean: 
	-rm -f -r $(OBJS) *.o *~ *core* raytrace

depend: $(SRCS) $(SRCS_SLN) $(HDRS) $(HDRS_SLN) Makefile
	$(MKDEP) $(CFLAGS) $(SRCS) $(SRCS_SLN) $(HDRS) $(HDRS_SLN) >& /dev/null

# DO NOT DELETE

raytrace.o: scene.h xvec.h
scene.o: xvec.h scene.h
scene.o: xvec.h
