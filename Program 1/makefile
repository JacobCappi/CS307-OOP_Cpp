# This is an extremely simple version of a make file
# for a C++ project that you wish to compile on linux
#
# Usage:
#    make             will build all of the code in your program
#    make clean       will clean up the compiled code if applicable
#   
#######################################################
# list each file here.  

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

# I am using the ansi standard C++11. You can change this if your
# environment uses a different version

CFLAGS = -std=c++11

#the following line should be removed or altered if using external
#libraries (such as files,etc)

# NOTE the leading indentation MUST be a tab character not spaces!
# In the below commands

main: $(SOURCES)
	g++ $(CFLAGS) $? $(LDFLAGS) -o $@ 

clean:
	rm main

tar:
	tar -cvf testprogram.tar $(SOURCES) $(HEADERS)
