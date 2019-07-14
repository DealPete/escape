#include <random>

std::random_device rd; // obtain a random number from hardware
std::mt19937 engine(rd()); // seed the generator

int rnd(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}
