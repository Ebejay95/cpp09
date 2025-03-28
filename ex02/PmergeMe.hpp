#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <locale>

class PmergeMe {
	private:
		std::vector<int>		pmerge_me_vector;
		int						error;
		std::string				error_message;
		int						walker;
		int						is_numeric(char c);
		int						is_decimal(char c);
		int						is_pmmchar(char c);
		void					pmm_filter(char val);
		void					pmm_push_operator(char val);
		void					reset(void);
		int						success(double result);

	public:
								PmergeMe();
								PmergeMe(const PmergeMe& src);
								PmergeMe& operator=(const PmergeMe& src);
								~PmergeMe();
		int						throw_error(std::string message);
		int						run(char *seed);
};

#endif