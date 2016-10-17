OBJDIR = build
targets = timer queue scheduler my_pthread_t
properTargets = $(addsuffix .o, $(addprefix $(OBJDIR)/, $(targets)))

.PHONY: dirs 
dirs: 
	rm -rf $(OBJDIR)
	mkdir $(OBJDIR)
	make all
all: $(targets)
	gcc $(properTargets) demo.c -o $(OBJDIR)/demo
timer:
	gcc -c $@.c -o $(OBJDIR)/$@.o
queue:
	gcc -c $@.c -o $(OBJDIR)/$@.o
scheduler: 
	gcc -c $@.c -o $(OBJDIR)/$@.o
my_pthread_t: 
	gcc -c $@.c -o $(OBJDIR)/$@.o
clean:
	rm -rf $(OBJDIR)