server:main.o Ring.o
	g++ -g -o ../bin/server main.o Ring.o -L/usr/lib64/mysql -luuid -lpthread -lmysqlclient 
Ring.o:Ring.cpp Ring.h
	g++ -g -c -o Ring.o Ring.cpp -I../include -I/mnt/server/mysql/include
main.o:main.cpp Ring.h
	g++ -g -c -o main.o main.cpp -I../include -I/mnt/server/mysql/include
clean:
	rm *.o ../bin/server

