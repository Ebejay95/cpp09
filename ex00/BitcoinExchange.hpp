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

	// Private member functions
	bool isValidDate(const std::string& date) const;
	bool isValidValue(const float value) const;
	std::string findClosestDate(const std::string& date) const;

public:
	// Constructors and destructor
	BitcoinExchange();
	BitcoinExchange(const std::string& databaseFile);
	BitcoinExchange(const BitcoinExchange& src);
	~BitcoinExchange();

	// Operator overloads
	BitcoinExchange& operator=(const BitcoinExchange& rhs);

	// Public member functions
	bool loadDatabase(const std::string& databaseFile);
	void processInputFile(const std::string& inputFile);
	float getExchangeRate(const std::string& date) const;

	// Exceptions
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
