all: parabola users

LDFLAGS=-l sqlite3
CPPFLAGS = -Wall

parabola: parabola.cpp
users: users.cpp

