#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <locale>
#include <sstream>
#include <chrono>
#include <iomanip>

# define G "\033[0;32m"
# define B "\033[0;34m"
# define Y "\033[0;93m"
# define C "\033[0;36m"
# define M "\033[0;35m"
# define W "\033[0;97m"
# define D "\033[0m"
# define RED "\x1b[31m"
#define BGB_RED "\033[101m"
#define BGB_G "\033[102m"
#define BGB_Y "\033[103m"
#define BGB_B "\033[104m"
#define BGB_M "\033[105m"
#define BGB_C "\033[106m"
#define BGB_W "\033[107m"
#define BG_RED "\033[41m"
#define BG_G "\033[42m"
#define BG_Y "\033[43m"
#define BG_B "\033[44m"
#define BG_M "\033[45m"
#define BG_C "\033[46m"
#define BG_W "\033[47m"
#define BG_D "\033[49m"

static int recursion_depth = 0;

template <typename T>
void print_container(const T& container, size_t grouper = 0) {
	typename T::const_iterator it;
	size_t comparer = 0;
	for (it = container.begin(); it != container.end(); ++it) {
		if (grouper != 0 && comparer % grouper == 0)
			std::cout << "| ";
		else if (grouper != 0 && comparer % (grouper / 2) == 0)
			std::cout << ": ";
		std::cout << *it << " ";
		comparer++;
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
			<< D << time_taken_ms << " microseconds" << std::endl;
}

template <typename T>
void leftover_extract(T& container, typename T::value_type& leftover, bool& has_leftover) {
	has_leftover = (container.size() % 2 != 0);
	if (has_leftover) {
		leftover = container.back();
		container.pop_back();
	}
}

template <typename T>
void fill_mergables(T& container, T& a, T& b) {
	for (size_t i = 0; i < container.size(); i += 2) {
		if (i + 1 < container.size()) {
			b.push_back(container[i]);
			a.push_back(container[i+1]);
		} else {
			b.push_back(container[i]);
		}
	}
}

template <typename T>
T generate_jacobsthal(size_t size) {
	T jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);

	while (jacobsthal.back() < static_cast<int>(size)) {
		int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}

	return jacobsthal;
}

template <typename T>
size_t binary_search_position(const T& s, const typename T::value_type& item) {
	size_t left = 0;
	size_t right = s.size();

	while (left < right) {
		size_t mid = left + (right - left) / 2;
		if (s[mid] < item) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	return left;
}

template <typename T>
double ford_johnson_sort(T& container) {
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end_time;
	std::chrono::duration<double, std::micro> elapsed;
	bool has_leftover;
	typename T::value_type leftover;
	T a, b, s, j;

	recursion_depth++;
	std::string prefix(recursion_depth * 2, ' ');

	start = std::chrono::high_resolution_clock::now();

	if (container.size() <= 1) {
		end_time = std::chrono::high_resolution_clock::now();
		elapsed = end_time - start;
		recursion_depth--;
		return elapsed.count();
	}

	leftover_extract(container, leftover, has_leftover);

	for (size_t i = 0; i < container.size(); i += 2) {
		if (i + 1 < container.size()) {
			if (container[i] > container[i+1]) {
				std::swap(container[i], container[i+1]);
			}
		}
	}

	fill_mergables(container, a, b);

	if (a.size() > 1) {
		ford_johnson_sort(a);
	}

	s = a;

	j = generate_jacobsthal<T>(b.size());

	T inserted(b.size(), 0);

	for (size_t jdex = 0; jdex < j.size(); jdex++) {
		int j_value = j[jdex];
		int idx = j_value - 1;

		if (idx < static_cast<int>(b.size()) && !inserted[idx]) {
			size_t pos = binary_search_position(s, b[idx]);
			s.insert(s.begin() + pos, b[idx]);
			inserted[idx] = 1;
		}

		int prev_idx = (jdex > 0) ? j[jdex - 1] : 0;

		for (int i = idx - 1; i > prev_idx; i--) {
			if (i >= static_cast<int>(b.size()) || inserted[i]) {
				continue;
			}

			size_t pos = binary_search_position(s, b[i]);
			s.insert(s.begin() + pos, b[i]);
			inserted[i] = 1;
		}
	}

	bool remaining = false;
	for (size_t i = 0; i < b.size(); i++) {
		if (!inserted[i]) {
			if (!remaining) {
				remaining = true;
			}

			size_t pos = binary_search_position(s, b[i]);
			s.insert(s.begin() + pos, b[i]);
			inserted[i] = 1;
		}
	}

	container = s;

	if (has_leftover) {
		size_t pos = binary_search_position(container, leftover);
		container.insert(container.begin() + pos, leftover);
	}

	end_time = std::chrono::high_resolution_clock::now();
	elapsed = end_time - start;
	recursion_depth--;
	return elapsed.count();
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
		int							run(int argc, char *argv[]);
};

#endif