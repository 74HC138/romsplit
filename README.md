## What is romsplit

romsplit is a simple file splitter that splits binary files into a low byte and a high byte file. One can tell it to handle the binary file as big or little endian to minimize confusion.

## How to use it

romsplit needs at least one argument: `-i` or `--input`. Follow this argument with the path to the file you want split.
The default output file names are `high.bin` and `low.bin` but you can change the names with the `-o` or `--output` argument.

You can change the endianness of the input file with the `-be` or `--bigEndian` and `-le` or `--littleEndian` argument. The endianness defines if the first byte of the input file is the high or low byte. For example the x86 architecture is little endian and the 68K architecture is big endian so the bytes are "swapped" in relation to one another. Having the low and high bytes swapped could lead to some "strange" behaviour and headscratching on the coders side (speaking from experience).

All of the above things are also statet in the help section that can be accessed with the `-h` or `--help` argument.

## Building

To compile romsplit you need a C++ compiler like g++ and the standart librarys. No further dependecies needed. The code just uses the standart c and c++ libraries thus it should compile on windows and macos as well tho i havent tested this.

### Getting the files

```sh
git clone https://github.com/74HC138/romsplit.git
```

### Compiling

```sh
cd romsplit
make
```

### Installing

```sh
sudo make install
```

This only works under linux as the finished executable is copied to `/usr/bin/`

## License

This tool is licensed under GPL3.

I give no warranty what so ever, ie. if your computer catches fire or the Makefile eats your harddrive thats on you.
