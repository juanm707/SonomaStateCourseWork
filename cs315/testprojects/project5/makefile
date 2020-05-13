CFLAGS= -std=c++11

jsonToHTML.x: main.o Album.o Artist.o Track.o Artists.o AlbumImage.o AlbumImages.o Albums.o ArtistImage.o ArtistImages.o JSONArray.o JSONDataItem.o JSONDataObject.o Tracks.o
	g++ $(CFLAGS) -o jsonToHTML.x main.o Album.o Artist.o Track.o Artists.o AlbumImage.o AlbumImages.o Albums.o ArtistImage.o ArtistImages.o JSONArray.o JSONDataItem.o JSONDataObject.o Tracks.o

Album.o: Album.hpp Album.cpp JSONDataObject.hpp Tracks.hpp AlbumImage.hpp
	g++ $(CFLAGS) -c -o Album.o Album.cpp

AlbumImage.o: AlbumImage.hpp AlbumImage.cpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o AlbumImage.o AlbumImage.cpp

AlbumImages.o: AlbumImages.hpp AlbumImages.cpp JSONArray.hpp AlbumImage.hpp
	g++ $(CFLAGS) -c -o AlbumImages.o AlbumImages.cpp

Albums.o: Albums.hpp Albums.cpp Album.hpp AlbumImages.hpp JSONArray.hpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o Albums.o Albums.cpp

Artist.o: Artist.hpp Artist.cpp Albums.hpp JSONDataObject.hpp ArtistImage.hpp
	g++ $(CFLAGS) -c -o Artist.o Artist.cpp

ArtistImage.o: ArtistImage.hpp ArtistImage.cpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o ArtistImage.o ArtistImage.cpp

ArtistImages.o: ArtistImages.hpp ArtistImages.cpp JSONArray.hpp ArtistImage.hpp
	g++ $(CFLAGS) -c -o ArtistImages.o ArtistImages.cpp

Artists.o: Artists.hpp Artists.cpp JSONArray.hpp Artist.hpp JSONDataObject.hpp Albums.hpp ArtistImages.hpp
	g++ $(CFLAGS) -c -o Artists.o Artists.cpp

JSONArray.o: JSONArray.hpp JSONArray.cpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o JSONArray.o JSONArray.cpp

JSONDataItem.o: JSONDataItem.hpp JSONDataItem.cpp
	g++ $(CFLAGS) -c -o JSONDataItem.o JSONDataItem.cpp

JSONDataObject.o: JSONDataObject.hpp JSONDataObject.cpp JSONDataItem.hpp
	g++ $(CFLAGS) -c -o JSONDataObject.o JSONDataObject.cpp

Track.o: Track.hpp Track.cpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o Track.o Track.cpp

Tracks.o: Tracks.hpp Tracks.cpp JSONArray.hpp Track.hpp JSONDataObject.hpp
	g++ $(CFLAGS) -c -o Tracks.o Tracks.cpp

main.o: Artists.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o *.x *~ artists.html

run:
	./jsonToHTML.x
