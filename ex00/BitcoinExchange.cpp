#include "BitcoinExchange.hpp"

// Constructors and destructor
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {
	*this = src;
}

BitcoinExchange::~BitcoinExchange() {}

// Operator overloads
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	if (this != &rhs) {
		this->_database = rhs._database;
	}
	return *this;
}

// Private member functions
bool BitcoinExchange::isValidDate(const std::string& date) const {
	// Check format YYYY-MM-DD
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// Check year, month, day are digits
	for (int i = 0; i < 4; i++)
		if (!isdigit(date[i])) return false;
	for (int i = 5; i < 7; i++)
		if (!isdigit(date[i])) return false;
	for (int i = 8; i < 10; i++)
		if (!isdigit(date[i])) return false;

	// Extract values
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	// Check ranges
	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// Check appropriate number of days for the month
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) return false;
	} else if (month == 2) {
		// Check for leap year
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeapYear ? 29 : 28)) return false;
	}

	return true;
}

bool BitcoinExchange::isValidValue(const float value) const {
	return value >= 0 && value <= 1000;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
	// If the exact date exists, return it
	if (_database.find(date) != _database.end())
		return date;

	// Find the closest date that is lower than the input date
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

	// If the date is less than the earliest date, return the first date
	if (it == _database.begin())
		return it->first;

	// If the date is greater than or equal to a date in the database, go back one step
	if (it != _database.end() && !(date < it->first))
		return it->first;

	// Otherwise, return the previous date
	--it;
	return it->first;
}

// Public member functions
bool BitcoinExchange::loadDatabase(const std::string& databaseFile) {
	std::ifstream file(databaseFile.c_str());
	if (!file.is_open())
		throw FileOpenException();

	std::string line;
	// Skip header line
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		float value;

		// Parse date and value separated by comma
		if (std::getline(iss, date, ',') && iss >> value) {
			if (isValidDate(date)) {
				_database[date] = value;
			}
		}
	}

	if (_database.empty())
		throw InvalidDatabaseException();

	return true;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const {
	std::string closestDate = findClosestDate(date);
	std::map<std::string, float>::const_iterator it = _database.find(closestDate);

	if (it != _database.end())
		return it->second;

	return 0.0f;
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
		throw FileOpenException();

	std::string line;
	// Skip header line
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string separator;
		float value;

		// Parse date and value separated by pipe (|)
		if (std::getline(iss, date, '|') && iss >> value) {
			// Trim whitespace from date
			date.erase(0, date.find_first_not_of(" \t"));
			date.erase(date.find_last_not_of(" \t") + 1);

			if (!isValidDate(date)) {
				std::cout << "Error: bad input => " << line << std::endl;
			} else if (value < 0) {
				std::cout << "Error: not a positive number." << std::endl;
			} else if (value > 1000) {
				std::cout << "Error: too large a number." << std::endl;
			} else {
				float rate = getExchangeRate(date);
				float result = value * rate;
				std::cout << date << " => " << value << " = " << result << std::endl;
			}
		} else {
			std::cout << "Error: bad input => " << line << std::endl;
		}
	}
}
