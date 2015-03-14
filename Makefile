include config.mk

EXE = cboy
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: options cboy

options:
	@echo $(EXE) build options:
	@echo "CC      = $(CC)"
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

$(OBJ): config.h config.mk

.o:
	@echo LD $@
	@$(LD) -o $@ $< $(LDFLAGS)

.c.o:
	@echo CC $<
	@$(CC) -c -o $@ $< $(CFLAGS)

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

cboy: $(OBJ)
	@echo CC -o $@
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)

run: all
	./$(EXE)

clean:
	@echo cleaning
	@rm -f $(OBJ) $(EXE)

dist: clean
	@echo creating dist tarball
	@mkdir -p $(EXE)-$(VERSION)
	@cp -R Makefile config.mk src/ data/ misc/ \
		$(EXE).1 $(EXE)-$(VERSION)
	@tar -cf $(EXE)-$(VERSION).tar $(EXE)-$(VERSION)
	@gzip $(EXE)-$(VERSION).tar
	@rm -rf $(EXE)-$(VERSION)

install: all
	@echo installing executable file to $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(EXE) $(DESTDIR)$(PREFIX)/bin
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/$(EXE)

uninstall:
	@echo removing executable file from $(DESTDIR)$(PREFIX)/bin
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(EXE)

.PHONY: all options run clean install uninstall
