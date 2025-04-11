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
T generate_jacobsthal(int n) {
	T result;

	if (n < 1)
		return result;
	result.push_back(3);
	if (n < 2)
		return result;
	result.push_back(5);
	for (int i = 2; i < n; ++i) {
		result.push_back(result[i-1] + 2 * result[i-2]);
		if (result[i-1] + 2 * result[i-2] > n)
			break;
	}
	return result;
}

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
		auto start_pos = container.size() - count_leftover;
		for (int i = 0; i < count_leftover; i++) {
			leftover.push_back(container[start_pos + i]);
		}
		while (count_leftover) {
			container.pop_back();
			count_leftover--;
		}
	}
}

template <typename T>
void leftover_repair(T& leftover, T& container, bool has_leftover) {
	if (has_leftover) {
		for (size_t i = 0; i < leftover.size(); i++) {
			container.push_back(leftover[i]);
		}
		leftover.clear();
	}
}

template <typename T>
void odd_leftover_insert(T& container, T& leftover, size_t& el_size) {
	size_t local_size = el_size / 2;
	if (local_size < 1)
		local_size = 1;

	//std::cout << BG_RED << "odd_leftover_insert " << local_size << "\n";
	//print_container(container);
	//std::cout << "\n";
	//print_container(leftover);
	//std::cout << D << std::endl;

	// If leftover is empty, nothing to do
	if (leftover.empty())
		return;

	// Process leftover elements in pairs of size local_size
	while (leftover.size() >= local_size) {
		// Take a pair (chunk) of size local_size from leftover
		auto chunk_begin = leftover.begin();
		auto chunk_end = chunk_begin + local_size;

		// Extract the value to compare (the last element in the chunk)
		auto compare_value = *(chunk_begin + local_size - 1);

		// Binary search to find insertion point
		size_t left = 0;
		size_t right = container.size() / local_size;

		if (right == 0) {
			// If container is empty or doesn't have complete groups, just insert at beginning
			container.insert(container.begin(), chunk_begin, chunk_end);
			leftover.erase(chunk_begin, chunk_end);
			continue;
		}

		while (left < right) {
			size_t mid = left + (right - left) / 2;
			size_t mid_pos = mid * local_size;

			// Compare the last value of current container chunk
			if (mid_pos + local_size - 1 < container.size()) {
				auto container_compare_value = container[mid_pos + local_size - 1];

				if (container_compare_value < compare_value) {
					left = mid + 1;
				} else {
					right = mid;
				}
			} else {
				right = mid;
			}
		}

		size_t insert_pos = left * local_size;

		// Insert the chunk at insert_pos
		container.insert(container.begin() + insert_pos, chunk_begin, chunk_end);

		// Remove inserted elements from leftover
		leftover.erase(chunk_begin, chunk_end);
	}
}

template <typename T>
void create_elements(T& container, size_t& el_size) {
	//std::cout << G << el_size << " create_elements: ";
	//print_container(container, el_size);
	//std::cout << D << "\n";
	if (container.size() <= 1) {
		return;
	}

	bool has_leftover = (container.size() % el_size != 0);
	int count_leftover = container.size() % el_size;
	T leftover;

	leftover_extract(leftover, container, has_leftover, count_leftover);
	sort_in_elements(container, el_size);

	if (leftover.size() > (el_size / 2)) {
		odd_leftover_insert(container, leftover, el_size);
		leftover_repair(leftover, container, has_leftover);
	} else {
		leftover_repair(leftover, container, has_leftover);
	}

	//std::cout << Y << el_size << " create_elements: ";
	//print_container(container, el_size);
	//std::cout << D << "\n";

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
void binary_search_insert_group(T& container, const T& group_to_insert, size_t el_size) {
	if (container.empty()) {
		for (size_t i = 0; i < group_to_insert.size(); i++) {
			container.push_back(group_to_insert[i]);
		}
		return;
	}
	//std::cout << "group to insert: ";
	//print_container(group_to_insert, el_size);
	//std::cout << "\n";
	size_t container_groups = container.size() / el_size;
	size_t insert_group_idx = 0;
	bool found = false;

	for (size_t i = 0; i < container_groups && !found; i++) {
		size_t current_group_last_idx = (i + 1) * el_size - 1;
		if (current_group_last_idx < container.size()) {
			size_t insert_group_last_idx = group_to_insert.size() - 1;
			if (container[current_group_last_idx] > group_to_insert[insert_group_last_idx]) {
				insert_group_idx = i;
				found = true;
			}
		}
	}

	if (!found) {
		insert_group_idx = container_groups;
	}

	size_t insert_pos = insert_group_idx * el_size;

	for (size_t i = 0; i < group_to_insert.size(); i++) {
		container.insert(container.begin() + insert_pos + i, group_to_insert[i]);
	}
	//std::cout << "container after insert: ";
	//print_container(container, el_size);
	//std::cout << "\n";
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
	//std::cout << el_size << "container: ";
	//print_container(container, el_size);
	//std::cout << D << "\n";
	if (container.size() <= 1 || el_size == 0) {
		return;
	}

	T a, b, m, s;

	bool has_leftover = (container.size() % el_size != 0);
	int count_leftover = container.size() % el_size;
	T leftover;

	leftover_extract(leftover, container, has_leftover, count_leftover);

	fill_mergables(container, a, b, s, m, el_size);

	T jacobsthal;
	jacobsthal = generate_jacobsthal<T>(static_cast<size_t>(s.size() / el_size));

	//std::cout << el_size << "a: ";
	//print_container(a, el_size);
	//std::cout << D << "\n";
	//std::cout << el_size << "b: ";
	//print_container(b, el_size);
	//std::cout << D << "\n";
	//std::cout << el_size << "s: ";
	//print_container(s, el_size);
	//std::cout << D << "\n";
	//std::cout << el_size << "m: ";
	//print_container(m, el_size);
	//std::cout << D << "\n";
	//std::cout << el_size << "l: ";
	//print_container(leftover, el_size);
	//std::cout << D << "\n";
	container.clear();

	for (size_t i = 0; i < s.size(); i++) {
		container.push_back(s[i]);
	}

	for (size_t j = 0; j < jacobsthal.size(); j++) {
		int lower_j = 0;
		if (j > 0)
			lower_j = jacobsthal[j - 1];

		for (int si = jacobsthal[j]; si > lower_j; si--) {
			if (si <= static_cast<int>(m.size() / el_size)) {

				size_t group_idx = si - 1;
				T current_group;

				for (size_t k = 0; k < el_size && (group_idx * el_size + k) < m.size(); k++) {
					current_group.push_back(m[group_idx * el_size + k]);
				}

				if (!current_group.empty()) {
					binary_search_insert_group(container, current_group, el_size);
				}
			}
		}
	}

	leftover_repair(leftover, container, has_leftover);

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

///7 2 7 10 7 6 4 5 10 6 6 5 3 3 3 3 7 8 5 4 1 8 3 6 4 2 10