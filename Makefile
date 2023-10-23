.PHONY = all clean

SRC := kblight.c
BIN := kblight

PREFIX := /usr/local

all: kblight

kblight: kblight.o
	@echo "Checking.."
	${CC} -lm $< -o $@

kblight.o: kblight.c
	@echo "Creating object.."
	${CC} -c $<

clean:
	@echo "Cleaning up..."
	rm -rvf kblight.o kblight

install: ${BIN}
	install -Dm744 -t $(DESTDIR)$(PREFIX)/bin ${BIN}

uninstall:
	rm -vf $(DESTDIR)$(PREFIX)/bin/${BIN}
