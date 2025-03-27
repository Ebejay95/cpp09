#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <locale>

class RPN {
	private:
		int				error;
		std::string		error_message;
		int				walker;
		int				is_numeric(char c);
		int				is_rpnchar(char c);
		void			rpn(char val);
		void			rpn_filter(char val);
		void			rpn_push_numeric(char val);
		void			rpn_push_operator(char val);

	public:
						RPN();
						RPN(const RPN& src);
						RPN& operator=(const RPN& src);
						~RPN();
		int				success(int result);
		int				throw_error(std::string message);
		int				run(char *seed);
};

#endif