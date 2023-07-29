CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror=vla -MMD -I blocks -I factory
EXEC = biquadris
OBJECTS = queue.o blocks/block.o blocks/LBlock.o blocks/JBlock.o blocks/SBlock.o blocks/ZBlock.o blocks/TBlock.o blocks/OBlock.o blocks/IBlock.o factory/level0Factory.o factory/level1Factory.o board.o player.o window.o game.o main.o 
DEPENDS = ${OBJECTS:.o=.d}

# Platform specific libraries and flags
MACOS_LIBS = -framework OpenGL -lSDL2
MACOS_FLAGS = -I /opt/homebrew/opt/SDL2/include -L /opt/homebrew/opt/SDL2/lib
LINUX_LIBS = -lSDL2 -lGL
ENDLIBS :=
ifeq ($(shell uname), Darwin)
	ENDLIBS += ${MACOS_LIBS}
	CXXFLAGS += ${MACOS_FLAGS}
else
	ENDLIBS += ${LINUX_LIBS}
endif

${EXEC}: ${OBJECTS}
	@echo $(OSFLAG)
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${ENDLIBS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} 2> /dev/null | true