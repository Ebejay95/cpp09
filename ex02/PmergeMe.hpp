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
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define BRIGHT_RED     "\x1b[91m"
# define BRIGHT_GREEN   "\x1b[92m"
# define BRIGHT_YELLOW  "\x1b[93m"
# define BRIGHT_BLUE    "\x1b[94m"
# define BRIGHT_MAGENTA "\x1b[95m"
# define BRIGHT_CYAN    "\x1b[96m"
# define BRIGHT_WHITE   "\x1b[97m"
# define COLOR_RESET "\x1b[0m"

// Generic print_container for containers with iterators
template <typename Container>
void print_container(const Container& container) {
	typename Container::const_iterator it;
	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
}

// Specialized version for std::queue - make it inline to avoid duplicate symbol errors
inline void print_container(const std::queue<int>& q) {
	std::queue<int> temp = q;
	while (!temp.empty()) {
		std::cout << temp.front() << " ";
		temp.pop();
	}
}

// Function to print before sorting
template <typename Container>
void print_before_sort(const Container& container, const std::string& container_name) {
	std::cout << CYAN << "Before sorting with " << container_name << ": " << COLOR_RESET;
	print_container(container);
	std::cout << std::endl;
}

// Function to print after sorting
template <typename Container>
void print_after_sort(const Container& container, const std::string& container_name, double time_taken_ms) {
	std::cout << GREEN << "After sorting with " << container_name << ": " << COLOR_RESET;
	print_container(container);
	std::cout << std::endl;
	std::cout << YELLOW << "Time to process a range of " << container.size()
			  << " elements with " << container_name << ": "
			  << BRIGHT_YELLOW << time_taken_ms << " ms" << COLOR_RESET << std::endl;
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
		void					reset(void);
		int						throw_error(std::string message);
		int						success(double result);
		void					fill_queue(char *arg);
		void					fill_vector(char *arg);
		void					print_queue(void);
		void					print_vector(void);

	public:
								PmergeMe();
								PmergeMe(const PmergeMe& src);
								PmergeMe& operator=(const PmergeMe& src);
								~PmergeMe();
		int						run(int argc, char *argv[]);
};

#endif