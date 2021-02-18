proj5.x : proj5.o passserver.o
	g++ -std=c++11 proj5.o passserver.o -lcrypt -o proj5.x

proj5.o: proj5.cpp passserver.h
	g++ -std=c++11 -c proj5.cpp

passserver.o: passserver.cpp passserver.h
	g++ -std=c++11 -c passserver.cpp

clean:
	rm -f *.o proj5.x

# Hello Mr/Ms. grader, I have done the extra credit and
# the makefile for it is commented out below. Please
# just uncomment it out and comment out the one above or
# you can just add an 's' in front of everywhere you see proj5 

#sproj5.x : sproj5.o passserver.o
#	g++ -std=c++11 sproj5.o passserver.o -lcrypt -o sproj5.x

#sproj5.o: sproj5.cpp passserver.h
#	g++ -std=c++11 -c sproj5.cpp

#passserver.o: passserver.cpp passserver.h
#	g++ -std=c++11 -c passserver.cpp

#clean:
#	rm -f *.o sproj5.x
