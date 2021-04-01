CC = g++ # Flag for implicit rules
CFLAGS = 
DEPS = baseOps.h allAlgo.h
OBJ = main.o baseOps.o glouton.o dynamique.o approximatif.o dyn.o

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $< 

exec: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ 
	@rm *.o

    
.PHONY: clean

clean:
	@rm -f exec
	@rm -f *.o
