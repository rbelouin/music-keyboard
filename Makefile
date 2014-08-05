GCC=gcc
FRAMEWORKS=-framework CoreServices -framework CoreMIDI
EXEC=music-keyboard
INSTALL_DIR=/usr/bin

$(EXEC):
	$(GCC) $(FRAMEWORKS) -o $(EXEC) src/*.c

install: $(EXEC)
	cp $(EXEC) $(INSTALL_DIR)/$(EXEC)

all: install
