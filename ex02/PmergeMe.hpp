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
#define BGB_RED     "\033[101m"
#define BGB_G "\033[102m"
#define BGB_Y "\033[103m"
#define BGB_B "\033[104m"
#define BGB_M "\033[105m"
#define BGB_C "\033[106m"
#define BGB_W "\033[107m"
#define BG_RED     "\033[41m"
#define BG_G "\033[42m"
#define BG_Y "\033[43m"
#define BG_B "\033[44m"
#define BG_M "\033[45m"
#define BG_C "\033[46m"
#define BG_W "\033[47m"
#define BG_D "\033[49m"

template <typename T>
T generate_jacobsthal(size_t n) {
	T result;

	if (n < 1)
		return result;
	result.push_back(3);
	if (n < 2)
		return result;
	result.push_back(5);
	for (size_t i = 2; i < n; ++i) {
		result.push_back(result[i-1] + 2 * result[i-2]);
	}
	return result;
}

template <typename T>
void binary_insert(T& container, const typename T::value_type& value, size_t start, size_t end) {
	size_t left = start;
	size_t right = end;

	while (left < right) {
		size_t mid = left + (right - left) / 2;
		if (container[mid] < value) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	container.insert(container.begin() + left, value);
}

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

	if (el_size < container.size())
		create_elements(container, el_size);
}

template <typename T>
void container_copy(T& src, T& target, size_t& el_size, size_t& i) {
	for (size_t j = i; j < (i + el_size); j++) {
		target.push_back(src[j]);
	}
}

template <typename T>
void fill_mergables(T& container, T& a, T& b, T& s, T& m, size_t& el_size) {
	size_t group_count = container.size() / el_size;

	for (size_t pair_idx = 0; pair_idx < group_count; pair_idx++) {
		size_t start_pos = pair_idx * el_size;
		if (pair_idx % 2 == 0) {
			for (size_t i = 0; i < el_size && (start_pos + i) < container.size(); i++) {
				b.push_back(container[start_pos + i]);
			}
		} else {
			for (size_t i = 0; i < el_size && (start_pos + i) < container.size(); i++) {
				a.push_back(container[start_pos + i]);
			}
		}
	}

	s.clear();
	m.clear();

	if (!b.empty()) {
		for (size_t i = 0; i < el_size && i < b.size(); i++) {
			s.push_back(b[i]);
		}
	}

	for (size_t i = 0; i < a.size(); i++) {
		s.push_back(a[i]);
	}

	for (size_t i = el_size; i < b.size(); i++) {
		m.push_back(b[i]);
	}
}

template <typename T>
void merge_elements(T& container, size_t& el_size) {
	print_container(container);
	std::cout << "\n";
	if (container.size() <= 1 || el_size == 0) {
		return;
	}

	T a, b, m, s;

	bool has_leftover = (container.size() % el_size != 0);
	int count_leftover = container.size() % el_size;
	T leftover;

	if (has_leftover) {
		for (int i = 0; i < count_leftover; i++) {
			leftover.push_back(container.back());
			container.pop_back();
		}
	}

	fill_mergables(container, a, b, s, m, el_size);

	if (has_leftover) {
		for (int i = count_leftover - 1; i >= 0; i--) {
			if (!m.empty()) {
				m.push_back(leftover[i]);
			} else {
				s.push_back(leftover[i]);
			}
		}
	}
	std::cout << G << "\n\nbefore merging" << D << std::endl;
	std::cout << el_size << "a: " << B;
	print_container(a);
	std::cout << D << "\n";
	std::cout << el_size << "b: " << M;
	print_container(b);
	std::cout << D << "\n";
	std::cout << el_size << "s: " << C;
	print_container(s);
	std::cout << D << "\n";
	std::cout << el_size << "m: " << BG_B;
	print_container(m);
	std::cout << D << "\n";

	T jacobsthal;
	jacobsthal = generate_jacobsthal<T>(static_cast<size_t>(s.size() / el_size));

	std::cout << el_size << "j: " << BG_M;
	print_container(jacobsthal);
	std::cout << D << "\n\n";
	container.clear();

	for (size_t i = 0; i < s.size(); i++) {
		container.push_back(s[i]);
	}

	std::cout << BG_RED;
	print_container(container);
	std::cout << D << "\n";

	for (size_t j = 0; j < jacobsthal.size(); j++) {
		std::cout << G << j << ": " << D << "\n";
		int lower_j = 0;
		if (j > 0)
			lower_j = jacobsthal[j - 1];
		for (int si = jacobsthal[j]; si >= lower_j; si--) {
			std::cout <<" " << si <<" perform binary search in m (retreive ony groups of el_size that fit\n";
		}
		std::cout << "\n";
	}

	std::cout << BG_G;
	print_container(container);
	std::cout << D << "\n";

	if (el_size > 1) {
		el_size /= 2;
		merge_elements(container, el_size);
	}
}

template <typename T>
double ford_johnson_sort(T& container) {
	std::chrono::steady_clock::time_point start;
	size_t el_size = 2;

	start = std::chrono::high_resolution_clock::now();

	if (container.size() <= 1)
		return processeing_time(start);


	create_elements(container, el_size);
	el_size /= 8;
	if (el_size < 1)
		el_size = 1;
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