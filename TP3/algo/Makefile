CC = g++ # Flag for implicit rules
CFLAGS = 
DEPS = baseOps.h allAlgo.h
OBJ = main.o baseOps.o base.o totalProfits.o dynamic.o

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $< 

exec: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ 

    
.PHONY: clean

clean:
	@rm -f exec
	@rm -f *.o