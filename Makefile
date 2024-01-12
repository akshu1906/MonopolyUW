CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD 
OBJECTS =  academic.o boardsquare.o collectosap.o controller.o coopfee.o game.o goosenesting.o gototims.o gym.o needleshall.o nonownable.o ownable.o player.o residence.o slc.o timsline.o tuition.o view.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

# TO UPDATE
