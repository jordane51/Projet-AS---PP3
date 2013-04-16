BISON_FILE=draw.y
LEX_FILE=draw.l
INCLUDE_CAIRO= -I/usr/include/cairo    -I/usr/include/glib-2.0  -I/usr/lib/glib-2.0/include \
	       -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15
INCLUDE_GENERATOR= generator.c generator.h
LIBS_CAIRO=-lcairo
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
	rm -f *.o draw.tab.c draw.tab.h lex.yy.c $(OUTFILE) *.pdf *~ *output