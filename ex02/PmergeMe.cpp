#include "./PmergeMe.hpp"

double processeing_time(std::chrono::steady_clock::time_point start)
{
	std::chrono::steady_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = end_time - start;
	return elapsed.count();
}

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

int PmergeMe::throw_error(std::string message) {
	std::cout << RED << "Error" << D <<": " << message << std::endl;
	return 1;
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

void PmergeMe::swap_elements(std::vector<int>& container, size_t el_size, size_t prev_size, size_t i) {
	size_t last_first_half = i + prev_size - 1;
	size_t last_second_half = std::min(i + el_size - 1, container.size() - 1);
	if (container[last_first_half] > container[last_second_half]) {
		size_t second_half_size = std::min(prev_size, container.size() - (i + prev_size));
		for (size_t j = 0; j < second_half_size; j++) {
			std::swap(container[i + j], container[i + prev_size + j]);
		}
	}
}

void PmergeMe::sort_in_elements(std::vector<int>& container, size_t el_size) {
	if (el_size == 2) {
		for (size_t i = 0; i < container.size(); i += 2) {
			if (i + 1 < container.size() && container[i] > container[i+1]) {
				std::swap(container[i], container[i+1]);
			}
		}
	}
	else {
		size_t prev_size = el_size / 2;
		for (size_t i = 0; i < container.size(); i += el_size) {
			if (i + prev_size < container.size()) {
				swap_elements(container, el_size, prev_size, i);
			}
		}
	}
	for (size_t i = 0; i < container.size(); i += el_size) {
		for (size_t j = i; j < i + el_size && j < container.size(); j++) {
			std::cout << Y << container[j] << " " << D;
		}
		std::cout << std::endl;
	}
}


void PmergeMe::leftover_extract(std::vector<int>& leftover, std::vector<int>& container, bool has_leftover, int count_leftover) {
	std::cout << G << "leftover_extract" << D << std::endl;
	if (has_leftover) {
		while (count_leftover) {
			leftover.push_back(container.back());
			container.pop_back();
			count_leftover--;
		}
	}
}

void PmergeMe::leftover_repair(std::vector<int>& leftover, std::vector<int>& container, bool has_leftover, int count_leftover) {

	std::cout << G << "leftover_repair" << D << std::endl;
	if (has_leftover) {
		while (count_leftover) {
			container.push_back(leftover.back());
			leftover.pop_back();
			count_leftover--;
		}
	}
}


void PmergeMe::create_elements(std::vector<int>& container, size_t& el_size) {
	if (container.size() <= 1) {
		return;
	}
	std::cout << G << "create_elements" << D << std::endl;

	bool has_leftover = (container.size() % el_size != 0);
	int count_leftover = container.size() % el_size;
	std::vector<int> leftover;

	leftover_extract(leftover, container, has_leftover, count_leftover);
	print_container(container);
	std::cout << ": ";
	print_container_ln(leftover);

	sort_in_elements(container, el_size);

	leftover_repair(leftover, container, has_leftover, count_leftover);
	print_container_ln(container);
	el_size *= 2;
	// std::cout << "el_size: " << el_size << std::endl;
	// std::cout << "count_leftover: " << count_leftover << std::endl;
	// std::cout << "container.size(): " << container.size() << std::endl;
	if ((el_size * 2) < container.size())
	{
		create_elements(container, el_size);
	}
}

double PmergeMe::ford_johnson_sort(std::vector<int>& container) {
	std::chrono::steady_clock::time_point start;
	size_t el_size = 2;

	start = std::chrono::high_resolution_clock::now();

	if (container.size() <= 1)
		return processeing_time(start);

	create_elements(container, el_size);

	return processeing_time(start);
}

int PmergeMe::run(int argc, char *argv[]) {
	if (argc == 1)
		return throw_error("usage is ./PmergeMe [n numeric unsigned arguments]");
	walker = 1;
	while (walker < argc)
	{
		if (!is_numeric(argv[walker]))
			return throw_error(std::string("each argument must be numeric unsigned and \"") + argv[walker] + "\" is not");
		//fill_queue(argv[walker]);
		fill_vector(argv[walker]);
		walker++;
	}
	//double time_queue = 0;
	double time_vector = 0;
	//print_before_sort(pmerge_me_queue, "std::queue<int>");
	print_before_sort(pmerge_me_vector, "std::vector<int>");
//	time_queue = ford_johnson_sort(pmerge_me_queue);
	time_vector = ford_johnson_sort(pmerge_me_vector);
	//print_after_sort(pmerge_me_queue, "std::queue<int>", time_queue);
	print_after_sort(pmerge_me_vector, "std::vector<int>", time_vector);
	return 0;
}

/*
12 9 0 5 17 1 3 16 7 4 43 8 64 2 34 6 45 90 11
(12 9) (0 5) (17 1) (3 16) (7 4) (43 8) (64 2) (34 6) (45 90) 11
(9 12) (0 5) (1 17) (3 16) (4 7) (8 43) (2 64) (6 34) (45 90) 11
(9 12) (0 5) (1 17) (3 16) (4 7) (8 43) (2 64) (6 34) (45 90) 11
((9 12) (0 5)) ((1 17) (3 16)) ((4 7) (8 43)) ((2 64) (6 34)) (45 90) 11
((0 5) (9 12)) ((3 16) (1 17)) ((4 7) (8 43)) ((6 34) (2 64)) (45 90) 11
*/