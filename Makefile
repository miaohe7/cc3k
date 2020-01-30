CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = cc3k
OBJECTS = main.o enemy.o helpers.o pc.o FloorTile.o Level.o Object.o  Coordinates.o potionTypes.o Stairs.o stats.o subject.o TextDisplay.o treasureTypes.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}i
