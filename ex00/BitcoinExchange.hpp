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

		bool is_valid_date(const std::string& date) const;
		std::string find_closest_date(const std::string& date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& databaseFile);
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);
		~BitcoinExchange();

		bool load_database(const std::string& databaseFile);
		void process_input_file(const std::string& inputFile);
		float get_exchange_rate(const std::string& date) const;

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
