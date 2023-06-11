objdir = obj
srcdir = src
sources = $(notdir $(wildcard $(srcdir)/*.c))
objects = $(addsuffix .o, $(notdir $(basename $(sources))))
flags = -g -std=c11 -DDEBUG=0 -TEST=0

all: chess client

chess: $(objects)
	gcc -o chess $(addprefix obj/, $(objects))

client:
	gcc -o client client.c

$(objects): | $(objdir)

$(objects): | $(objdir)
	gcc -c $(flags) $(srcdir)/$(addsuffix .c, $(basename $@)) -o $(objdir)/$@

$(objdir):
	mkdir $(objdir)

clean :
	rm -rf $(objdir) chess client
