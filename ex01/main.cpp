#include "./RPN.hpp"

int main(int argc, char *argv[])
{
	RPN rpn;
	if(argc != 2) {
		return rpn.throw_error("usage is ./RPN [quoted string with numbers and operants \"+ - * /\"]");
	}
	return rpn.run(argv[1]);
}