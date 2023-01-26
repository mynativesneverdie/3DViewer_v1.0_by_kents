CC = gcc -g
QMAKE_PATH = /home/obrol/Qt/6.3.2/gcc_64/bin/qmake
LIN_FLAGS = -lpthread -pthread -lrt -lm -lsubunit
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs --coverage
LCHECK = -lcheck
ifeq ($(shell uname), Linux)
LCHECK += $(LIN_FLAGS)
endif

SOURCES_TEST:= $(wildcard parser/*.c)

OBJ_GCOV_DIR := obj_gcov
OBJECTS_GCOV := $(addprefix obj_gcov/,$(SOURCES_TEST:.c=.o))

all: install

install:
	sh build/script1.sh $(QMAKE_PATH)

uninstall:
	rm -rf viewer.app

clean:
	make clean_tests
	rm -rf viewer* build/.*q* \
	build/*.o build/*.h \
	build/*.cpp build/Makefile \
	build/viewer.app build/.tmp \
	rm -rf *.gz build/*bak

dist:
	sh build/script2.sh

create_dir:
	@mkdir -p $(OBJ_GCOV_DIR)

test: parser/test/tests.c $(OBJECTS_GCOV)
	$(CC) $< $(OBJ_GCOV_DIR)/*.o -o $@ $(LCHECK) $(LDFLAGS) $(GCOVFLAGS)
	./$@
	@rm -f *tests*

$(OBJ_GCOV_DIR)/%.o: %.c create_dir
	@$(CC) $(GCOVFLAGS) -c $< -o obj_gcov/$(subst /,_,$@)

clean_tests: 
	rm -rf obj_gcov
	rm -rf test *gcda *gcno
	rm -rf out


.PHONY: all install uninstall clean dvi dist gcov_report clean_tests
