#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <locale>
#include <sstream>

class PmergeMe {
	private:
		std::vector<int>		pmerge_me_vector;
		std::queue<int>			pmerge_me_queue;
		int						error;
		std::string				error_message;
		int						walker;
		int						is_numeric(char *arg);
		int						is_decimal(char c);
		int						is_pmmchar(char c);
		void					pmm_filter(char val);
		void					reset(void);
		int						throw_error(std::string message);
		int						success(double result);
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