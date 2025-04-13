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
double ford_johnson_sort(T& container) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::duration<double, std::micro> elapsed;
	start = std::chrono::high_resolution_clock::now();

	if (container.size() <= 1)
	{
		end_time = std::chrono::high_resolution_clock::now();
		elapsed = end_time - start;
		return elapsed.count();
	}

	end_time = std::chrono::high_resolution_clock::now();
	elapsed = end_time - start;
	return elapsed.count();
}



class PmergeMeItem {
    private:
        int value;
        int index;

    public:
        PmergeMeItem();
        PmergeMeItem(int v, int i = 0);  // Note the default parameter here
        PmergeMeItem(const PmergeMeItem& other);

        PmergeMeItem& operator=(const PmergeMeItem& other);
        int getValue() const;
        int getIndex() const;
        void setValue(int v);
        void setIndex(int i);

        bool operator<(const PmergeMeItem& other);
        bool operator>(const PmergeMeItem& other);
        bool operator==(const PmergeMeItem& other);
        bool operator!=(const PmergeMeItem& other);
        bool operator<=(const PmergeMeItem& other);
        bool operator>=(const PmergeMeItem& other);
};

inline std::ostream& operator<<(std::ostream& os, const PmergeMeItem& item);

class PmergeMe {
	private:
		std::vector<PmergeMeItem>	pmerge_me_vector;
		std::deque<PmergeMeItem> 	pmerge_me_deque;
		int							error;
		std::string					error_message;
		int							walker;
		int							is_numeric(char *arg);
		int							is_decimal(char c);
		int							throw_error(std::string message);
		void						fill_containers(char *arg);

	public:
									PmergeMe();
									PmergeMe(const PmergeMe& src);
									PmergeMe& operator=(const PmergeMe& src);
									~PmergeMe();
		int							run(int argc, char *argv[]);
};

#endif
