CC = gcc
CFLAGS = -W -Wall
EXEC = DFA_DES
SRCDIR  = src
HEADDIR = head
OBJDIR  = bin


all: $(EXEC)
	
run: $(EXEC)
	./$(EXEC)


$(EXEC): $(OBJDIR)/DES_main.o $(OBJDIR)/DES_algo.o $(OBJDIR)/DES_permutation.o $(OBJDIR)/DES_K16.o $(OBJDIR)/DES_K.o
	$(CC) $^ -o $@


$(OBJDIR)/DES_main.o: $(HEADDIR)/DES_algo.h $(HEADDIR)/DES_K16.h $(HEADDIR)/DES_K.h
$(OBJDIR)/DES_algo.o: $(HEADDIR)/DES_permutation.h 
$(OBJDIR)/DES_K16.o: $(HEADDIR)/DES_permutation.h  
$(OBJDIR)/DES_K.o: $(HEADDIR)/DES_permutation.h  $(HEADDIR)/DES_algo.h


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)


.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf $(OBJDIR)

mrproper: clean
	rm -rf $(EXEC)
