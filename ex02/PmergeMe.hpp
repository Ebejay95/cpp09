#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <locale>
#include <sstream>

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

template <typename T>
double ford_johnson_sort(const T& container) {
	size_t n;
	std::chrono::steady_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	n = container.size();
	std::cout << n << std::endl;
	std::chrono::steady_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = end_time - start_time;
	return elapsed.count();
}

class PmergeMe {
	private:
		std::vector<int>		pmerge_me_vector;
		std::queue<int>			pmerge_me_queue;
		int						error;
		std::string				error_message;
		int						walker;
		int						is_numeric(char *arg);
		int						is_decimal(char c);
		int						throw_error(std::string message);
		void					fill_queue(char *arg);
		void					fill_vector(char *arg);

	public:
								PmergeMe();
								PmergeMe(const PmergeMe& src);
								PmergeMe& operator=(const PmergeMe& src);
								~PmergeMe();
		int						run(int argc, char *argv[]);
};

#endif