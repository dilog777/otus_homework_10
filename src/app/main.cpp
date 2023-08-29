#include <iostream>
#include <thread>

#include <async.h>



int main(int, char **)
{
	std::size_t bulk = 5;
	auto h = async::connect(bulk);
	auto h2 = async::connect(bulk);
	async::receive(h, "1", 1);
	async::receive(h2, "1\n", 2);
	async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
	async::receive(h, "b\nc\nd\n}\n89\n", 11);
	async::disconnect(h);
	async::disconnect(h2);


	std::cout << "int main(int, char **) 1" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "int main(int, char **) 2" << std::endl;

	return 0;
}
