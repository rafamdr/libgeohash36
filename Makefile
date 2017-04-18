all: library test

library:
	gcc -std=c99 -c geohash36.c -o geohash36.o
	ar rcs libgeohash36.a geohash36.o
	rm geohash36.o
	
test:
	gcc -std=c99 geohash36_test.c geohash36.c -o geohash36_test
	./geohash36_test
	
clean: 
	rm -rf *.a *.o