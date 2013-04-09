BISON_FILE=bibi.y
LEX_FILE=lex.l
INCLUDE_CAIRO= -I/usr/include/cairo    -I/usr/include/glib-2.0  -I/usr/lib/glib-2.0/include \
	       -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15
LIBS_CAIRO=-lcairo
OUTFILE=Draw
$(OUTFILE): bibi.tab.o lex.yy.o
	gcc $(INCLUDE_CAIRO) $(LIBS_CAIRO) $^ -o $(OUTFILE)
bibi.tab.o: bibi.tab.c
	gcc -c $(INCLUDE_CAIRO) $(LIBS_CAIRO) $< 
lex.yy.o: lex.yy.c
	gcc $< -c
bibi.tab.c: 
	bison -d $(BISON_FILE)
lex.yy.c:
	lex $(LEX_FILE)

lex:
	lex $(LEX_FILE)
bison:
	bison -d $(BISON_FILE)

.PHONY: clean
clean:
	rm -f *.o bibi.tab.c bibi.tab.h lex.yy.c $(OUTFILE) *.pdf *~ *output