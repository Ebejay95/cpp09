#include "./RPN.hpp"

RPN::RPN() : error(0), error_message(""), walker(0) {}

RPN::RPN(const RPN& src) : error(src.error), error_message(src.error_message), walker(src.walker) {
	std::stack<double> temp = src.rpn_stack;
	std::stack<double> reversed;

	while (!temp.empty()) {
		reversed.push(temp.top());
		temp.pop();
	}

	while (!reversed.empty()) {
		rpn_stack.push(reversed.top());
		reversed.pop();
	}
}

RPN& RPN::operator=(const RPN& src) {
	if (this != &src) {
		error = src.error;
		error_message = src.error_message;
		walker = src.walker;

		while (!rpn_stack.empty())
			rpn_stack.pop();

		std::stack<double> temp = src.rpn_stack;
		std::stack<double> reversed;

		while (!temp.empty()) {
			reversed.push(temp.top());
			temp.pop();
		}

		while (!reversed.empty()) {
			rpn_stack.push(reversed.top());
			reversed.pop();
		}
	}
	return *this;
}

RPN::~RPN() {}

int RPN::is_numeric(char c) {
	return std::isdigit(c, std::locale());
}

int RPN::is_decimal(char c) {
	return (c == '.');
}

int RPN::is_rpnchar(char c) {
	return (is_numeric(c) || c == ' ' || c == '/' || c == '+' || c == '*' || c == '-');
}

void RPN::rpn_filter(char val) {
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

int RPN::success(double result) {
	std::cout << "\x1b[32mResult\033[0m: " << result << std::endl;
	reset();
	return 1;
}

int RPN::throw_error(std::string message) {
	std::cout << "\x1b[31mError\033[0m: " << message << std::endl;
	return 1;
}

void RPN::reset(void) {
	while (!rpn_stack.empty()) {
		rpn_stack.pop();
	}
	error = 0;
	error_message = "";
	walker = 0;
}

int RPN::run(char *seed) {
	while (seed[walker] != '\0' && !error)
	{
		rpn_filter(seed[walker]);
		if (error)
			return throw_error(error_message);

		walker++;
	}
	if (walker <= 0)
		return throw_error("empty seeds cannot be processed");
	if (rpn_stack.size() != 1)
		return throw_error("seed not resolvable");
	return success(rpn_stack.top());
}

void RPN::rpn(char val) {
	if (is_numeric(val))
		rpn_push_numeric(val);
	else
		rpn_push_operator(val);
	return;
}

void RPN::rpn_push_numeric(char val) {
	rpn_stack.push(static_cast<double>(val - '0'));
	std::cout << "\x1b[33mrpn_push_numeric\033[0m: " << val << std::endl;
	return;
}

double RPN::calculate(double first, char op, double second) {
	double result = 0.0;

	if (op == '+')
		result = first + second;
	else if (op == '-')
		result = first - second;
	else if (op == '*')
		result = first * second;
	else if (op == '/') {
		if (second == 0) {
			error = 1;
			error_message = "division by zero";
			return 0;
		}
		result = first / second;
	}

	return result;
}

void RPN::rpn_push_operator(char op) {
	if (rpn_stack.size() < 2)
	{
		error = 1;
		error_message = "seed not resolvable (operator requires operants)";
		return;
	}

	double second = rpn_stack.top();
	rpn_stack.pop();
	double first = rpn_stack.top();
	rpn_stack.pop();

	std::cout << "\x1b[33mrpn_push_operator\033[0m: " << op << std::endl;
	std::cout << "\x1b[34mrpn_perform\033[0m: " << first << " "<< op << " " << second << std::endl;

	rpn_stack.push(calculate(first, op, second));
	return;
}