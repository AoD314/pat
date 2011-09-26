
#include "pat_function.hpp"

int main(int argc, const char ** argv)
{

	PAT_Func func(argc, argv);

	func.set_max_iter(100000);

	func.run_auto_tune();

	func.print_info();

	return 0;
}
