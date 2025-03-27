#include "./RPN.hpp"

RPN::RPN() : error(0), error_message(""), walker(0) {}

RPN::RPN(const RPN& src) {
	*this = src;
}

RPN& RPN::operator=(const RPN& src) {
	if (this != &src) {
		//
	}
	return *this;
}

RPN::~RPN() {}

int RPN::is_numeric(char c)
{
	return std::isdigit(c, std::locale());
}

int RPN::is_rpnchar(char c)
{
	return (is_numeric(c) || c == ' ' || c == '/' || c == '+' || c == '*' || c == '-');
}

void RPN::rpn_filter(char val)
{
	if (!is_rpnchar(val))
	{
		error = 1;
		error_message = "non allowed char " + std::string(1, val) + " occured";
		return;
	}
	if (val == ' ') {
		return;
	}
	rpn(val);
	return;
}

int RPN::success(int result)
{
	std::cout << "\x1b[32mResult\033[0m: " << result << std::endl;
	return 1;
}

int RPN::throw_error(std::string message)
{
	std::cout << "\x1b[31mError\033[0m: " << message << std::endl;
	return 1;
}

int RPN::run(char *seed)
{
	while (seed[walker] != '\0' && !error)
	{
		rpn_filter(seed[walker]);
		if (error)
			return throw_error(error_message);

		walker++;
	}
	if (walker <= 0)
		return throw_error("empty seeds cannot be processed");
	return success(42);
}

void RPN::rpn(char val)
{
	std::cout << "\x1b[33mrpn\033[0m: " << val << std::endl;
	if (is_numeric(val))
	{
		rpn_push_numeric(val);
	}
	else
	{
		rpn_push_operator(val);
	}
	return;
}

void RPN::rpn_push_numeric(char val)
{
	std::cout << "\x1b[33mrpn_push_numeric\033[0m: " << val << std::endl;
	return;
}

void RPN::rpn_push_operator(char val)
{
	std::cout << "\x1b[33mrpn_push_operator\033[0m: " << val << std::endl;
	return;
}
