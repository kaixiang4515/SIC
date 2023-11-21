main: main.cpp ds.cpp ds.h
	g++ -std=c++17 -Wall -Wextra -o main main.cpp ds.cpp
test: test.cpp ds.cpp ds.h
	g++ -std=c++17 -Wall -Wextra -o test test.cpp ds.cpp