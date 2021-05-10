#include <iostream>
#include <stdio.h>
#include <cstring>

std::string inputFileName;
std::string outputFileOddName;
std::string outputFileEvenName;
FILE* inputFile;
FILE* outputFileOdd;
FILE* outputFileEven;

bool littleEndian = false;
bool noWarn = false;

int main(int argc, char** argv) {
	if(argc <= 1) {
		std::cout << "no arguments given\n";
		std::cout << "to get a list of arguments use -h or --help\n";
		return 1;
	}

	outputFileOddName = "low.bin";
	outputFileEvenName = "high.bin";
	int argPos = 1;
	while(42) {
		if (strcmp(argv[argPos], "-h") == 0 || strcmp(argv[argPos], "--help") == 0) {
			std::cout << "available commands:\n";
			std::cout << "-h  | --help			display this help\n";
			std::cout << "-o  | --output [high] [low]	specify output file for high and low byte (if not specified high.bin and low.bin will be used)\n";
			std::cout << "-i  | --input [file]		specify input file\n";
			std::cout << "-be | --bigEndian			select big endian mode (first byte in file is high byte)\n";
			std::cout << "-le | --littleEndian		select little endian mode (first byte in file is low byte)\n";
			std::cout << "					default for endianes is big endian\n";
			std::cout << "-nw | --noWarn			no warning about odd file length will be issued\n";
			std::cout << "if multiple instances of commands are issued the last instance is valid\n";
			return 0;
		}
		if (strcmp(argv[argPos], "-o") == 0 || strcmp(argv[argPos], "--output") == 0) {
			argPos++;
			outputFileEvenName = argv[argPos];
			argPos++;
			outputFileOddName = argv[argPos];
			argPos++;
			if (argPos >= argc) break;
		}
		if (strcmp(argv[argPos], "-i") == 0 || strcmp(argv[argPos], "--input") == 0) {
			argPos++;
			inputFileName = argv[argPos];
			argPos++;
			if (argPos >= argc) break;
		}
		if (strcmp(argv[argPos], "-be") == 0 || strcmp(argv[argPos], "--bigEndian") == 0) {
			argPos++;
			littleEndian = false;
			if (argPos >= argc) break;
		}
		if (strcmp(argv[argPos], "-le") == 0 || strcmp(argv[argPos], "--littleEndian") == 0) {
			argPos++;
			littleEndian = true;
			if (argPos >= argc) break;
		}
		if (strcmp(argv[argPos], "-nw") == 0 || strcmp(argv[argPos], "--noWarn") == 0) {
			argPos++;
			noWarn = true;
			if (argPos >= argc) break;
		}
	}
	if (inputFileName.empty()) {
		std::cout << "no input file specified!\n";
		std::cout << "use -h or --help to see all available arguments\n";
		return 1;
	}
	inputFile = fopen(inputFileName.c_str(), "rb");
	if (inputFile == NULL) {
		std::cout << "could not open file for reading!\n";
		return 1;
	}
	outputFileOdd = fopen(outputFileOddName.c_str(), "wb");
	outputFileEven = fopen(outputFileEvenName.c_str(), "wb");
	if (outputFileOdd == NULL || outputFileEven == NULL) {
		std::cout << "could not create output files!\n";
		if (outputFileOdd) fclose(outputFileOdd);
		if (outputFileEven) fclose(outputFileEven);
		return 1;
	}

	fseek(inputFile, 0, SEEK_END);
	long fileLength = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	if (!noWarn) {
		if (fileLength & 0x00000001) std::cout << "[warning] input file is of odd length\n";
	}

	for (long readPos = 0; readPos < fileLength; readPos++) {
		if (!littleEndian) {
			if (readPos & 0x00000001) {
				fputc(fgetc(inputFile), outputFileOdd);
			} else {
				fputc(fgetc(inputFile), outputFileEven);
			}
		} else {
			if (readPos & 0x00000001) {
				fputc(fgetc(inputFile), outputFileEven);
			} else {
				fputc(fgetc(inputFile), outputFileOdd);
			}
		}
	}

	fclose(inputFile);
	fclose(outputFileEven);
	fclose(outputFileOdd);
	return 0;
}
