TEST_SRC_DIR := ./parser/test/
SRC_DIR := ./parser

# chage the qmake path
QMAKE_PATH = /home/obrol/Qt/6.3.2/gcc_64/bin/qmake

LIB_SRC = $(shell find $(SRC_DIR) -maxdepth 1 -name 's21*.c')
LIB_OBJ := $(LIB_SRC:.c=.o)

TEST_SRC = $(shell find $(TEST_SRC_DIR) -maxdepth 1 -name 's21*.c')
TEST_OBJ := $(TEST_SRC:.c=.o)

OS := $(shell uname -s)

CFLAGS := -c
GCOV_CFLAGS := -fprofile-arcs -ftest-coverage -fPIC
LFLAGS := -lcheck -lpthread -lrt -lm -lsubunit # <--- unix

GCOV_LFLAGS := --coverage

TEST_CFLAGS += $(GCOV_CFLAGS)
TEST_CFLAGS += $(CFLAGS)

TEST_LFLAGS += $(GCOV_LFLAGS)
TEST_LFLAGS += $(LFLAGS)

LIB_CFLAGS += $(CFLAGS)

LIB_LFLAGS += $(LFLAGS)

CC := gcc
COV := gcovr

all: install

install:
	sh build/install.sh $(QMAKE_PATH)

uninstall:
	rm -rf viewer

clean:
	rm -rf build/.*q* \
	rm -rf ./**/*.o build/*.h \
	rm -rf ./**/*.gcno \
	rm -rf ./**/*.gcda \
	rm -rf ./**/test/*.o \
	rm -rf build/*.cpp build/Makefile \
	rm -rf build/.tmp build/s21_3dviewer_test \
	rm -rf *.gz build/*bak \
	rm -rf 3DViewer.tar.gz \
	rm -rf html_report

dist:
	-@mkdir 3DViewer_dist
	-cp -r ./build ./3DViewer_dist/
	-cp -r ./core ./3DViewer_dist/
	-cp -r ./parser ./3DViewer_dist
	-cp -r ./gif ./3DViewer_dist
	-cp -r ./objects ./3DViewer_dist
	-cp -r ./qtgifimage ./3DViewer_dist
	-cp -r ./screens ./3DViewer_dist
	
	-cp ./readme.html ./3DViewer_dist
	-cp ./Makefile ./3DViewer_dist
	-cp ./config.cfg ./3DViewer_dist

	tar -czf 3DViewer.tar.gz 3DViewer_dist/
	rm -rf ./3DViewer_dist

dvi:
ifeq ($(OS), Linux)
	firefox readme.html
else
	open readme.html
endif

tests: $(TEST_OBJ) $(LIB_OBJ)
	-@mkdir ./build
	$(CC) $(TEST_OBJ) $(LIB_OBJ) $(TEST_LFLAGS) -o ./build/s21_3dviewer_test
	./build/s21_3dviewer_test

$(LIB_OBJ): %.o: %.c
	$(CC) $(TEST_CFLAGS) -g $< -o $@

$(TEST_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -g $< -o $@

gcov_report:
	-@mkdir ./html_report
	$(COV) . --html --html-details -o ./html_report/coverage_report.html

.PHONY: all install uninstall clean dvi dist gcov_report clean_tests
