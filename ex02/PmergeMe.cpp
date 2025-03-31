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

int PmergeMe::success(double result) {
	std::cout << G << result << D << std::endl;
	reset();
	return 1;
}

int PmergeMe::throw_error(std::string message) {
	std::cout << RED << "Error" << D <<": " << message << std::endl;
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

void PmergeMe::print_queue(void) {
	std::stringstream ss;
	std::queue<int> temp = pmerge_me_queue;
	size_t length = pmerge_me_queue.size();

	while (!temp.empty())
	{
		ss << temp.front() << " ";
		temp.pop();
	}
	std::cout << Y << "  Queue(" << length << "):  " << D << ss.str() << std::endl;
}

void PmergeMe::print_vector(void) {
	std::stringstream ss;
	std::vector<int>::iterator	it;
	size_t length = pmerge_me_vector.size();
	it = pmerge_me_vector.begin();
	while (it != pmerge_me_vector.end())
	{
		ss << *it << " ";
		it++;
	}
	std::cout << Y << "  Vector(" << length << "): " << D << ss.str() << std::endl;
}

int PmergeMe::run(int argc, char *argv[]) {
	if (argc == 1)
		return throw_error("usage is ./PmergeMe [n numeric unsigned arguments]");
	walker = 1;
	while (walker < argc)
	{
		if (!is_numeric(argv[walker]))
			return throw_error(std::string("each argument must be numeric unsigned and \"") + argv[walker] + "\" is not");
		fill_queue(argv[walker]);
		fill_vector(argv[walker]);
		walker++;
	}
	double time_taken = 0;
	print_before_sort(pmerge_me_queue, "std::queue<int>");
	print_before_sort(pmerge_me_vector, "std::vector<int>");
	print_after_sort(pmerge_me_queue, "std::queue<int>", time_taken);
	print_after_sort(pmerge_me_vector, "std::vector<int>", time_taken);
	return success(42);
}