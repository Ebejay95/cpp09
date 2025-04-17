#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange exchange("data.csv");
		exchange.process_input_file(argv[1]);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
