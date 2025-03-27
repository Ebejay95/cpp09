#include <iostream>
#include <stack>
#include <string>
#include <locale>

int is_numeric(char c)
{
	return std::isdigit(c, std::locale());
}

int is_rpnchar(char c)
{
	return (is_numeric(c) || c == ' ' || c == '/' || c == '+' || c == '*' || c == '-');
}

void rpn(int *error, std::string *message, char val)
{
	std::cout << "\x1b[33mrpn\033[0m: " << val << std::endl;
	return;
}

void rpn_filter(int *error, std::string *message, char val)
{
	if (!is_rpnchar(val))
	{
		*error = 1;
		*message = "non allowed char " + std::string(1, val) + " occured";
		return;
	}
	if (val != ' ')
		rpn(error, message, val);
	return;
}

int success(int result)
{
	std::cout << "\x1b[32mResult\033[0m: " << result << std::endl;
	return 1;
}

int throw_error(std::string message)
{
	std::cout << "\x1b[31mError\033[0m: " << message << std::endl;
	return 1;
}

int main(int argc, char *argv[])
{
	int error = 0;
	std::string error_message = "";
	int walker = 0;

	if(argc != 2) {
		return throw_error("usage is ./RPN [quoted string with numbers and operants \"+ - * /\"]");
	}

	while (argv[1][walker] != '\0' && !error)
	{
		rpn_filter(&error, &error_message, argv[1][walker]);
		if (error)
			return throw_error(error_message);
		walker++;
	}

	return success(42);
}