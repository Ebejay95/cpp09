#include "./PmergeMe.hpp"

PmergeMe::PmergeMe() : error(0), error_message(""), walker(0) {}

PmergeMe::PmergeMe(const PmergeMe& src) : error(src.error), error_message(src.error_message), walker(src.walker) {

}

PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
	if (this != &src) {
		error = src.error;
		error_message = src.error_message;
		walker = src.walker;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

int PmergeMe::is_numeric(char c) {
	return std::isdigit(c, std::locale());
}

int PmergeMe::is_decimal(char c) {
	return (c == '.');
}

int PmergeMe::is_pmmchar(char c) {
	return (is_numeric(c) || c == ' ' || c == '/' || c == '+' || c == '*' || c == '-');
}

void PmergeMe::pmm_filter(char val) {
	if (!is_pmmchar(val))
	{
		error = 1;
		error_message = "non allowed char " + std::string(1, val) + " occured";
		return;
	}
	if (val == ' ') {
		return;
	}
	return;
}

int PmergeMe::success(double result) {
	std::cout << "\x1b[32m" << result << "\033[0m" << std::endl;
	reset();
	return 1;
}

int PmergeMe::throw_error(std::string message) {
	std::cout << "\x1b[31mError\033[0m: " << message << std::endl;
	return 1;
}

void PmergeMe::reset(void) {
	error = 0;
	error_message = "";
	walker = 0;
}

int PmergeMe::run(char *seed) {
	while (seed[walker] != '\0' && !error)
	{
		if (walker % 2 == 1 && seed[walker] != ' ')
			return throw_error("operators and numbers must be separated by space");
		if (seed[walker + 1] == '\0' && seed[walker] == ' ')
			return throw_error("operators and numbers must be separated by space");
		pmm_filter(seed[walker]);
		if (error)
			return throw_error(error_message);

		walker++;
	}
	if (walker <= 0)
		return throw_error("empty seeds cannot be processed");
	return success(42);
}



