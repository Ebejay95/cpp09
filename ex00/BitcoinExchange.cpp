#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {
	*this = src;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	if (this != &rhs) {
		this->_database = rhs._database;
	}
	return *this;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 4; i++)
		if (!isdigit(date[i])) return false;
	for (int i = 5; i < 7; i++)
		if (!isdigit(date[i])) return false;
	for (int i = 8; i < 10; i++)
		if (!isdigit(date[i])) return false;

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) return false;
	} else if (month == 2) {
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeapYear ? 29 : 28)) return false;
	}

	return true;
}

bool BitcoinExchange::isValidValue(const float value) const {
	return value >= 0 && value <= 1000;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
	if (_database.find(date) != _database.end())
		return date;

	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

	if (it == _database.begin())
		return it->first;

	if (it != _database.end() && !(date < it->first))
		return it->first;

	--it;
	return it->first;
}

bool BitcoinExchange::loadDatabase(const std::string& databaseFile) {
	std::ifstream file(databaseFile.c_str());
	if (!file.is_open())
		throw FileOpenException();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		float value;

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
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string separator;
		float value;

		if (std::getline(iss, date, '|') && iss >> value) {
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
