#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange {
	private:
		std::map<std::string, float> _database;

		bool isValidDate(const std::string& date) const;
		bool isValidValue(const float value) const;
		std::string findClosestDate(const std::string& date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& databaseFile);
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);
		~BitcoinExchange();

		bool loadDatabase(const std::string& databaseFile);
		void processInputFile(const std::string& inputFile);
		float getExchangeRate(const std::string& date) const;

		class FileOpenException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Error: could not open file.";
				}
		};

		class InvalidDatabaseException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Error: invalid database format.";
				}
		};
};

#endif
