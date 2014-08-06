GCC=gcc
EXEC=music-keyboard
PREFIX=/usr
DEST=$(PREFIX)/bin

$(EXEC):
	$(GCC) -std=c99 -lportmidi -o $(EXEC) src/*.c

install: $(EXEC)
	cp $(EXEC) $(DEST)/$(EXEC)

clean:
	rm -f $(EXEC)

all: install
