#include "./PmergeMe.hpp"

PmergeMe::PmergeMe() : error(0), error_message(""), walker(0) {}

PmergeMe::PmergeMe(const PmergeMe& src) :
	pmerge_me_vector(src.pmerge_me_vector),
	pmerge_me_queue(src.pmerge_me_queue),
	error(src.error),
	error_message(src.error_message),
	walker(src.walker) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
	if (this != &src) {
		pmerge_me_vector = src.pmerge_me_vector;
		pmerge_me_queue = src.pmerge_me_queue;
		error = src.error;
		error_message = src.error_message;
		walker = src.walker;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

int PmergeMe::is_numeric(char *arg) {
	int i = 0;
	while (arg[i]) {
		if (!std::isdigit(arg[i], std::locale()))
			return 0;
		i++;
	}
	if (i == 0)
		return 0;
	return 1;
}

int PmergeMe::is_decimal(char c) {
	return (c == '.');
}

int PmergeMe::is_pmmchar(char c) {
	return (std::isdigit(c, std::locale()) || c == ' ' || c == '/' || c == '+' || c == '*' || c == '-');
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

void PmergeMe::fill_queue(char *arg) {
	std::stringstream ss(arg);
	int num;
	ss >> num;
	pmerge_me_queue.push(num);
}

void PmergeMe::fill_vector(char *arg) {
	std::stringstream ss(arg);
	int num;
	ss >> num;
	pmerge_me_vector.push_back(num);
}

int PmergeMe::run(int argc, char *argv[]) {
	if (argc == 1)
		return throw_error("usage is ./PmergeMe [n numeric unsigned arguments]");
	walker = 1;
	while (walker < argc)
	{
		if (!is_numeric(argv[walker]))
			return throw_error(std::string("each argument must be numeric unsigned and ") + argv[walker] + " is not");
		fill_queue(argv[walker]);
		fill_vector(argv[walker]);
		walker++;
	}
	if (walker <= 1)
		return throw_error("empty seeds cannot be processed");
	return success(42);
}