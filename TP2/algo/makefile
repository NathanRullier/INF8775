CC = g++ # Flag for implicit rules
CFLAGS= 
DEPS = baseOps.h allAlgo.h
OBJ = main.o baseOps.o glouton.o dynamique.o approximatif.o

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@rm *.o

    
.PHONY: clean

clean:
	@rm -f exec
	@rm -f *.o
