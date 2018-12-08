sims2unpack: sims2unpack.c sims2unpack.h
	gcc -o sims2unpack sims2unpack.c -Wall

clean:
	rm sims2unpack
