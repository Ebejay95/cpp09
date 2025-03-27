#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <locale>
#include <limits>

class RPN {
	private:
		std::stack<double>		rpn_stack;
		int						error;
		std::string				error_message;
		int						walker;
		int						is_numeric(char c);
		int						is_decimal(char c);
		int						is_rpnchar(char c);
		void					rpn(char val);
		void					rpn_filter(char val);
		void					rpn_push_numeric(char val);
		void					rpn_push_operator(char val);
		double					calculate(double first, char op, double second);
		void					reset(void);

	public:
								RPN();
								RPN(const RPN& src);
								RPN& operator=(const RPN& src);
								~RPN();
		int						success(double result);
		int						throw_error(std::string message);
		int						run(char *seed);
};

#endif