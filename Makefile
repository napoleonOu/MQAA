PROGRAM		=MQAA-Sever
CXX		= g++
CFLAGS		= -std=c++11 -g
#source file
EVENT2_DIR	=/home/napoleon/Desktop/GCC_4_7_0/git/Libevent/include/event2
MAIN_DIR	=/home/napoleon/Desktop/GCC_4_7_0/git/Libevent/include
BUILD_DIR	=/home/napoleon/Desktop/GCC_4_7_0/git/Libevent/build/include

PROTOBUF_DIR	=/home/napoleon/Desktop/GCC_4_7_0/git/protobuf/src/google/protobuf


EVENT_LIB	=/home/napoleon/Desktop/GCC_4_7_0/git/Libevent/build/lib/libevent.a /home/napoleon/Desktop/GCC_4_7_0/git/Libevent/build/lib/libevent_core.a /home/napoleon/Desktop/GCC_4_7_0/git/Libevent/build/lib/libevent_extra.a /usr/local/lib/libprotobuf.so.10 

BASE_DIR	=./src
SRC		=src/date.cpp src/loop.cpp src/tcpClient.cpp src/tcpServer.cpp src/tcpServerDispatcher.cpp src/tcpSession.cpp src/tcpSocket.cpp src/timer.cpp Server-Main.cpp ./MQAA/tcpMQAA.cpp ./MQAA/MQAA.pb.cpp


BASE_INC	=./include
INC		=$(BASE_INC)

OBJ		=$(SRC:.cpp=.o)

$(PROGRAM):$(OBJ)
	$(CXX) $(CFLAGS) -o $(PROGRAM) $(OBJ) $(EVENT_LIB) -lpthread -lefence
%.o:%.cpp
	$(CXX) $(CFLAGS) -I$(EVENT2_DIR) -I$(MAIN_DIR) -I$(BUILD_DIR) -I$(INC) -I./example/ -c $< -o $@ #$(CXX) $(CFLAGS) -I$(BASE_DIR) -c $< -o $@
clean:
	rm -rf ./src/*.o ./MQAA/*.o *.o
