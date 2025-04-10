#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <locale>
#include <sstream>
#include <chrono>

# define G "\033[0;32m"
# define B "\033[0;34m"
# define Y "\033[0;93m"
# define C "\033[0;36m"
# define M "\033[0;35m"
# define W "\033[0;97m"
# define D "\033[0m"
# define RED "\x1b[31m"

template <typename T>
void print_container(const T& container) {
	typename T::const_iterator it;
	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
}

template <typename T>
void print_before_sort(const T& container, const std::string& container_name) {
	std::cout << C << "Before sorting with " << container_name << ": " << D;
	print_container(container);
	std::cout << std::endl;
}

template <typename T>
void print_after_sort(const T& container, const std::string& container_name, double time_taken_ms) {
	std::cout << G << "After sorting with " << container_name << ": " << D;
	print_container(container);
	std::cout << std::endl;
	std::cout << Y << "Time to process a range of " << D << container.size()
			<< Y << " elements with " << container_name << ": "
			<< D << time_taken_ms << " ms" << std::endl;
}

double processeing_time(std::chrono::steady_clock::time_point start);


template <typename T>
void swap_elements(T& container, size_t el_size, size_t prev_size, size_t i) {
	size_t last_first_half = i + prev_size - 1;
	size_t last_second_half = std::min(i + el_size - 1, container.size() - 1);
	if (container[last_first_half] > container[last_second_half]) {
		size_t second_half_size = std::min(prev_size, container.size() - (i + prev_size));
		for (size_t j = 0; j < second_half_size; j++) {
			std::swap(container[i + j], container[i + prev_size + j]);
		}
	}
}

template <typename T>
void sort_in_elements(T& container, size_t el_size) {
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
}

template <typename T>
void leftover_extract(T& leftover, T& container, bool has_leftover, int count_leftover) {
	if (has_leftover) {
		while (count_leftover) {
			leftover.push_back(container.back());
			container.pop_back();
			count_leftover--;
		}
	}
}

template <typename T>
void leftover_repair(T& leftover, T& container, bool has_leftover, int count_leftover) {

	if (has_leftover) {
		while (count_leftover) {
			container.push_back(leftover.back());
			leftover.pop_back();
			count_leftover--;
		}
	}
}

template <typename T>
void create_elements(T& container, size_t& el_size) {
	if (container.size() <= 1) {
		return;
	}

	bool has_leftover = (container.size() % el_size != 0);
	int count_leftover = container.size() % el_size;
	T leftover;

	leftover_extract(leftover, container, has_leftover, count_leftover);
	sort_in_elements(container, el_size);
	leftover_repair(leftover, container, has_leftover, count_leftover);

	el_size *= 2;

	if ((el_size * 2) < container.size())
		create_elements(container, el_size);
}

template <typename T>
void merge_elements(T& container, size_t& el_size) {
	std::cout << G << "merge_elements " << el_size << D << std::endl;
	print_container(container);
	std::cout << "\n";

	// T a;
	// T b;
	// el_size /= 2;
}

template <typename T>
double ford_johnson_sort(T& container) {
	std::chrono::steady_clock::time_point start;
	size_t el_size = 2;

	start = std::chrono::high_resolution_clock::now();

	if (container.size() <= 1)
		return processeing_time(start);

	create_elements(container, el_size);

	merge_elements(container, el_size);

	return processeing_time(start);
}


class PmergeMe {
	private:
		std::vector<int>	pmerge_me_vector;
		std::deque<int> 	pmerge_me_deque;
		int					error;
		std::string			error_message;
		int					walker;
		int					is_numeric(char *arg);
		int					is_decimal(char c);
		int					throw_error(std::string message);
		void				fill_containers(char *arg);

	public:
							PmergeMe();
							PmergeMe(const PmergeMe& src);
							PmergeMe& operator=(const PmergeMe& src);
							~PmergeMe();
		int					run(int argc, char *argv[]);
};

#endif