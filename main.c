#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
	printf("num2en [number]\n");
}

// Regular Number
char* number_str(char c) {
	switch (c) {
		case '0':
			return "zero";
		case '1':
			return "one";
		case '2':
			return "two";
		case '3':
			return "three";
		case '4':
			return "four";
		case '5':
			return "five";
		case '6':
			return "six";
		case '7':
			return "seven";
		case '8':
			return "eight";
		case '9':
			return "nine";
		default:
			return "???";
	}
}

// Tens place
char* tens_str(char c) {
	switch (c) {
		case '2':
			return "twenty";
		case '3':
			return "thirty";
		case '4':
			return "forty";
		case '5':
			return "fifty";
		case '6':
			return "sixty";
		case '7':
			return "seventy";
		case '8':
			return "eighty";
		case '9':
			return "ninety";
		default:
			return "???";
	}
}

// Weird ones (e.g., sixteen, thirteen)
char* weird_str(char c) {
	switch (c) {
		case '3':
			return "thir";
		case '4':
			return "four";
		case '5':
			return "fif";
		case '6':
			return "six";
		case '7':
			return "seven";
		case '8':
			return "eigh";
		case '9':
			return "nine";
		default:
			return "???";
	}
}

void tens(char* num, int i, int* skipSpace, int* skipLast) {
	if (num[i] > '1') {
		printf("%s", tens_str(num[i]));
	} else if (num[i] == '0') {
		*skipSpace = 1;
		return;
	} else {
		if (num[i+1] >= '3') {
			printf("%steen", weird_str(num[i+1]));
		} else {
			if (num[i+1] == '1')
				printf("eleven");
			if (num[i+1] == '2')
				printf("twelve");
		}
		*skipLast = 1;
		return;
	}

	if (num[i+1] != '0') {
		printf("-");
		*skipSpace = 1;
	}
}

int isNumber(char* num, int len) {
	for (int i = 0; i < len; i++) {
		if (num[i] < '0' || num[i] > '9')
			if (num[i] != '-')
				return 0;	
	}
	return 1;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		print_help();
		exit(1);
	}

	// Save some info
	char* num = argv[1];
	int size = strlen(num);

	// Check that this is a real number
	if (!isNumber(num, size)) {
		print_help();
		exit(1);
	}

	// Set a max
	if (size > 12) {
		printf("That number is too large... Sorry!\n");
		exit(1);
	}

	// Check for negative
	int start = 0;
	if (num[0] == '-') {
		printf("negative ");
		start = 1;
	}

	// Iterate through each place
	for (int i = start; i < size; i++) {
		int place = size - i;

		// Single
		if (place == 1) {
			if (size > 1 && num[i] == '0')
				continue;
			printf("%s", number_str(num[i]));
		}

		// Tens
		else if ((place - 2) % 3 == 0) {
			int skip = 0;
			int last = 0;
			tens(num, i, &skip, &last);

			if (num[i] == '1') {
				if (place == 5) {
					printf(" thousand");
				} else if (place == 8) {
					printf(" million");
				} else if (place == 11) {
					printf(" billion");
				}
			}

			if (last == 1) {
				i++;
			}
			if (skip == 1) {
				goto skipSpace;
			}
		}

		// Hundreds
		else if (place % 3 == 0) {
			if (num[i] != '0')
				printf("%s hundred", number_str(num[i]));
			else
				continue;
		}

		// Thousands
		else if (place == 4) {
			if (num[i] != '0')
				printf("%s thousand", number_str(num[i]));
			else
				continue;
		}

		// Million
		else if (place == 7) {
			if (num[i] != '0')
				printf("%s million", number_str(num[i]));
			else
				continue;
		}

		// Billion
		else if (place == 10) {
			if (num[i] != '0')
				printf("%s billion", number_str(num[i]));
			else
				continue;
		}

		if (place != 1)
			printf(" ");
		
		skipSpace:
		continue;
	}
	printf("\n");

	return 0;
}