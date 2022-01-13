COMPILER = g++
SOURCE_PATH = source/
BUILD_PATH = build/

all:
	test ! -d $(BUILD_PATH) || rm $(BUILD_PATH) -r
	mkdir $(BUILD_PATH)
	$(COMPILER) $(SOURCE_PATH)*.cpp -o $(BUILD_PATH)out.a
	cp $(BUILD_PATH)out.a romsplit

clean:
	if test -d $(BUILD_PATH); then rm $(BUILD_PATH) -r; fi

install: all
	cp romsplit /usr/bin/
