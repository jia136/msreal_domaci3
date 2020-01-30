sources=$(wildcard *.c)
objs=$(sources:.c=.o)

all: kol3 
kol3: $(objs)
	@echo "Building output binary.."
	$(CC) -o $@ $(objs) -lm
%.o: %.c
	@echo "Compiling sources.."
	$(CC) -c $(sources)
clean:
	@rm -f kol3 *.o *.d*
	@echo "Clean done.."

-include $(sources:.c=.d)

