UNAME = $(shell uname)
BISON_FILE=draw.y
LEX_FILE=draw.l
ifeq ($(UNAME), Linux)
	INCLUDE_CAIRO= -I/usr/include/cairo    -I/usr/include/glib-2.0  -I/usr/lib/glib-2.0/include \
	       -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15
endif
ifeq ($(UNAME), Darwin)
	INCLUDE_CAIRO= -L/usr/X11/lib -L/opt/X11/include/cairo/
endif

INCLUDE_GENERATOR= generator.c generator.h list.c list.h stack_list.c stack.h
LIBS_CAIRO=-lcairo -lm
OUTFILE=Draw
CFLAGS=-D_GNU_SOURCE
$(OUTFILE): draw.tab.o lex.yy.o
	gcc  $(CFLAGS) $(INCLUDE_CAIRO) $(INCLUDE_GENERATOR) $(LIBS_CAIRO) $^ -o $(OUTFILE)
draw.tab.o: draw.tab.c
	gcc -c $(INCLUDE_CAIRO) $(LIBS_CAIRO)  $< 
lex.yy.o: lex.yy.c
	gcc $< -c
draw.tab.c: 
	bison -d $(BISON_FILE)
lex.yy.c:
	lex $(LEX_FILE)

lex:
	lex $(LEX_FILE)
bison:
	bison -d $(BISON_FILE)

.PHONY: clean
clean:
	rm -f *.o draw.tab.c draw.tab.h lex.yy.c $(OUTFILE) *.pdf *~ *output *out
exe:
ifeq ($(UNAME), Darwin)
	gcc draw.gen.c `pkg-config --cflags --libs cairo` -o ex1.out
else
	gcc draw.gen.c `pkg-config --cflags --libs cairo` -o ex1.out
endif