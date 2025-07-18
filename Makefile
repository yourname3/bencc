SRCS= \
	backend/x86/x86-from.c \
	backend/x86/x86-text.c \
	src/compiler.c \
	src/main.c \
	src/intern.c \
	src/lex.c \
	src/parser.c \
	src/pretty_print.c

bencc: $(SRCS:%=build/%.o)
	gcc $^ -o $@

build/%.o: % | $(addprefix build/,$(dir $(SRCS)))
	gcc -c $< -o $@ -I. -MD -g -Wall -Werror -Wmissing-prototypes -Wno-error=unused-function

%/:
	mkdir -p $@

clean:
	rm -f bencc
	rm -rf build

.PHONY: clean
.PRECIOUS: $(addprefix build/,$(dir $(SRCS)))

-include $(SRCS:%=build/%.d)