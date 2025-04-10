#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <locale>
#include <sstream>
#include <chrono>

// Define Colours
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

inline void print_container(const std::queue<int>& q) {
	std::queue<int> temp = q;
	while (!temp.empty()) {
		std::cout << temp.front() << " ";
		temp.pop();
	}
}

template <typename T>
void print_container_ln(const T& container) {
	typename T::const_iterator it;
	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

inline void print_container_ln(const std::queue<int>& q) {
	std::queue<int> temp = q;
	while (!temp.empty()) {
		std::cout << temp.front() << " ";
		temp.pop();
	}
	std::cout << std::endl;
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
			<< D << time_taken_ms << " ms"  << std::endl;
}

double processeing_time(std::chrono::steady_clock::time_point start);

class PmergeMe {
	private:
		std::vector<int>        pmerge_me_vector;
		std::queue<int>         pmerge_me_queue;
		int                     error;
		std::string             error_message;
		int                     walker;
		int                     is_numeric(char *arg);
		int                     is_decimal(char c);
		int                     throw_error(std::string message);
		void                    fill_queue(char *arg);
		void                    fill_vector(char *arg);

		void leftover_extract(std::vector<int>& leftover, std::vector<int>& container, bool has_leftover, int count_leftover);
		void leftover_repair(std::vector<int>& leftover, std::vector<int>& container, bool has_leftover, int count_leftover);
		void swap_elements(std::vector<int>& container, size_t el_size, size_t prev_size, size_t i);
		void sort_in_elements(std::vector<int>& container, size_t pair_size);
		void create_elements(std::vector<int>& container, size_t& el_size);
		double ford_johnson_sort(std::vector<int>& container);
		double ford_johnson_sort(std::queue<int>& container);

	public:
							PmergeMe();
							PmergeMe(const PmergeMe& src);
							PmergeMe& operator=(const PmergeMe& src);
							~PmergeMe();
		int                 run(int argc, char *argv[]);
};

#endif