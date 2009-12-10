
all: myst

%.yy.c: %.l
	flex -o$@ $^

%: %.yy.c
	g++ -o $@ $^

clean:
	rm -f myst
