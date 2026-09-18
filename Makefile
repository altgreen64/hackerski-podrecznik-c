# Kompiluje każdy rozdział do katalogu build/
# Użycie:
#   make            # zbuduj wszystkie rozdziały
#   make run-01     # zbuduj i uruchom rozdział 01
#   make clean      # posprzątaj

CC      = gcc
CFLAGS  = -Wall -Wextra -O2
BUILD   = build

SOURCES = $(wildcard *.c)
BINARIES = $(patsubst %.c,$(BUILD)/%,$(SOURCES))

all: $(BINARIES)

$(BUILD)/%: %.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

# make run-01, run-02, ... uruchamia pierwszy pasujący rozdział o danym numerze
run-%:
	@bin=$$(ls $(BUILD)/rozdzial$**  $(BUILD)/*$** 2>/dev/null | head -1); \
	if [ -z "$$bin" ]; then $(MAKE) -s all; bin=$$(ls $(BUILD)/rozdzial$** 2>/dev/null | head -1); fi; \
	echo ">>> $$bin"; ./$$bin

clean:
	rm -rf $(BUILD)

.PHONY: all clean
