#include "./PmergeMe.hpp"

PmergeMe::PmergeMe() : error(0), error_message(""), walker(0) {}

PmergeMe::PmergeMe(const PmergeMe& src) :
	pmerge_me_vector(src.pmerge_me_vector),
	pmerge_me_deque(src.pmerge_me_deque),
	error(src.error),
	error_message(src.error_message),
	walker(src.walker) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
	if (this != &src) {
		pmerge_me_vector = src.pmerge_me_vector;
		pmerge_me_deque = src.pmerge_me_deque;
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

int PmergeMe::throw_error(std::string message) {
	std::cout << RED << "Error" << D <<": " << message << std::endl;
	return 1;
}

void PmergeMe::fill_containers(char *arg) {
	std::stringstream ss(arg);
	int num;
	ss >> num;
	pmerge_me_vector.push_back(num);
	pmerge_me_deque.push_back(num);
}

int PmergeMe::run(int argc, char *argv[]) {
	if (argc == 1)
		return throw_error("usage is ./PmergeMe [n numeric unsigned arguments]");
	walker = 1;
	while (walker < argc)
	{
		if (!is_numeric(argv[walker]))
			return throw_error(std::string("each argument must be numeric unsigned and \"") + argv[walker] + "\" is not");
		fill_containers(argv[walker]);
		walker++;
	}
	double time_deque = 0;
	double time_vector = 0;
	print_before_sort(pmerge_me_deque, "std::deque<int>");
	print_before_sort(pmerge_me_vector, "std::vector<int>");
	time_deque = ford_johnson_sort(pmerge_me_deque);
	time_vector = ford_johnson_sort(pmerge_me_vector);
	print_after_sort(pmerge_me_deque, "std::deque<int>", time_deque);
	print_after_sort(pmerge_me_vector, "std::vector<int>", time_vector);
	return 0;
}
