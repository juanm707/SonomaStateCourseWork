
# Ali A. Kooshesh
# CS 470

.SUFFIXES: .o .cpp .x

CFLAGS=-ggdb

OBJECT_FILES=Competition.o Match.o PointScore.o SetScore.o main.o Game.o MatchScore.o Score.o \
	TieBreaker.o GameScore.o Player.o Set.o TieBreakerScore.o 


tennis.x: $(OBJECT_FILES)
	g++ $(CFLAGS) -o tennis.x $(OBJECT_FILES)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

Game.o: Game.cpp Game.hpp Competition.hpp Player.hpp Score.hpp GameScore.hpp PointScore.hpp
Competition.o: Competition.cpp Competition.hpp Player.hpp
Game.o: Game.cpp Game.hpp Competition.hpp Player.hpp Score.hpp GameScore.hpp PointScore.hpp
GameScore.o: GameScore.cpp GameScore.hpp Score.hpp Player.hpp
Match.o: Match.cpp Match.hpp Competition.hpp Player.hpp
MatchScore.o: MatchScore.cpp MatchScore.hpp Score.hpp Player.hpp SetScore.hpp TieBreakerScore.hpp
Player.o: Player.cpp Player.hpp PointScore.hpp Score.hpp
PointScore.o: PointScore.cpp PointScore.hpp Score.hpp Player.hpp
Score.o: Score.cpp Score.hpp
Set.o: Set.cpp Set.hpp Competition.hpp Player.hpp
SetScore.o: SetScore.cpp SetScore.hpp Player.hpp TieBreakerScore.hpp Score.hpp
TieBreaker.o: TieBreaker.cpp TieBreaker.hpp Competition.hpp Player.hpp
TieBreakerScore.o: TieBreakerScore.cpp TieBreakerScore.hpp Score.hpp Player.hpp
main.o: main.cpp Player.hpp Game.hpp Competition.hpp GameScore.hpp Score.hpp

clean:
	rm -fr *.o *~ *.x
