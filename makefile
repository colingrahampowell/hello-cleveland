##########################################################
## File: makefile
## Description: Makefile for "Hello, Cleveland!" game.
## “Robust Makefile” provided with course material. 
##########################################################

#set compiler, flags
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall

####################
### USER SECTION ###
####################

#source files:
SRC1 = powell_final.cpp
SRC2 = Item.cpp
SRC3 = Hero.cpp
SRC4 = Room.cpp
SRC5 = GreenRoom.cpp
SRC6 = JanRoom.cpp
SRC7 = LoadingDock.cpp
SRC8 = BoilerRoom.cpp
SRC9 = DressingRoom.cpp
SRC10 = FlySpace.cpp
SRC11 = ControlRoom.cpp
SRC12 = Catwalk.cpp
SRC13 = Lift.cpp
SRC14 = HeroTest.cpp

SRCS_ALL = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7} ${SRC8} ${SRC9} ${SRC10} ${SRC11} ${SRC12} ${SRC13} ${SRC14}
SRCS_BASE = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7} ${SRC8} ${SRC9} ${SRC10} ${SRC11} ${SRC12} ${SRC13}
SRCS_TEST1 = ${SRC2} ${SRC3} ${SRC14}

#header files:
HEADER1 = Item.hpp
HEADER2 = Hero.hpp
HEADER3 = Room.hpp
HEADER4 = GreenRoom.hpp
HEADER5 = JanRoom.hpp
HEADER6 = LoadingDock.hpp
HEADER7 = BoilerRoom.hpp 
HEADER8 = DressingRoom.hpp
HEADER9 = FlySpace.hpp
HEADER10 = ControlRoom.hpp
HEADER11 = Catwalk.hpp
HEADER12 = Lift.hpp

HEADERS = ${HEADER1} ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5} ${HEADER6} ${HEADER7} ${HEADER8} ${HEADER9} ${HEADER10} ${HEADER11} ${HEADER12} 

#executable files
PROG1 = hello_cleveland 
PROGS = ${PROG1} 

#####################
### BUILD SECTION ###
#####################

all: 
	${CXX} ${CXXFLAGS} ${SRCS_BASE} -o ${PROG1}


#removes all executable files, debug folders
clean:
	rm -rf -v *~ ${PROGS} *.dSYM 
