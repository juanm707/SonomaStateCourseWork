
# Ali A. Kooshesh
# CS 470

.SUFFIXES: .o .cpp .x

CFLAGS=-ggdb

OBJECT_FILES=tennis.o

tennis.x: $(OBJECT_FILES)
	g++ $(CFLAGS) -o tennis.x $(OBJECT_FILES)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

tennis.o: tennis.cpp
	g++ $(CFLAGS) -c tennis.cpp -o tennis.o

clean:
	rm -fr *.o *~ *.x
