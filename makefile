CC=g++

encrypt: encrypt.o
	$(CC) -o $@ $<

encrypt.o: encrypt.cpp
	$(CC) -c $<