#include "./PmergeMe.hpp"

int main(int argc, char *argv[])
{
	PmergeMe pmergeMe;
	if(argc != 2) {
		return pmergeMe.throw_error("usage is ./PmergeMe [quoted string with positive int numbers]");
	}
	return pmergeMe.run(argv[1]);
}