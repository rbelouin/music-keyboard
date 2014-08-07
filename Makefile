GCC=gcc
EXEC=music-keyboard
DESTDIR?=/
PREFIX=/usr

$(EXEC):
	$(GCC) -std=c99 -lportmidi -o $(EXEC) src/*.c

install: $(EXEC)
	cp $(EXEC) $(DESTDIR)/$(PREFIX)/bin/$(EXEC)

clean:
	rm -f $(EXEC)

all: install
