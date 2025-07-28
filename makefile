CC = gcc
CFLAGS = -std=c2x -Wall -Werror -Wno-unused-function -I include

SRCDIR = src
BUILDIR = build
BINDIR = bin

TARGET = $(BINDIR)/SRS.exe

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDIR)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Executable file created successfully"

$(BUILDIR)/%.o: $(SRCDIR)/%.c | $(BUILDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDIR) $(BINDIR):
	clear
	mkdir -p $@ data

.PHONY: clean

clean:
	rm -rf $(BUILDIR) $(BINDIR) data
	@echo "Clean successfully"
