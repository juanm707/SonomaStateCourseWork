CFLAGS= -std=c++11

jsonToHTML.x: main.o Album.o Artist.o Track.o
	g++ $(CFLAGS) -o jsonToHTML.x main.o Album.o Artist.o Track.o

Album.o: Album.hpp Album.cpp
	g++ $(CFLAGS) -c -o Album.o Album.cpp

Artist.o: Artist.hpp Artist.cpp
	g++ $(CFLAGS) -c -o Artist.o Artist.cpp

Track.o: Track.hpp Track.cpp
	g++ $(CFLAGS) -c -o Track.o Track.cpp

main.o: Artist.hpp Album.hpp Track.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o *.x *~ albums.html artists.html tracks.html

run:
	./jsonToHTML.x
