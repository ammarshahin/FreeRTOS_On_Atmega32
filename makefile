CC = gcc
CFLAGS = -I$(IDIR)

IDIR = ./inc
ODIR = ./obj
LDIR = ./lib
SDIR = ./src

LIBS=-lm	

#change here ########
_DEPS = code.h
#####################

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#change here ########
_OBJ = main.o code.o
#####################
 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

######### Rules ############

app: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

git: 
	git add .
	git commit -a -m "updating" 
	git push origin master

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 