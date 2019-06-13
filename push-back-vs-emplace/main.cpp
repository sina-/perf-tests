#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <numeric>

struct BigStruct {
	BigStruct() = default;
	BigStruct(double a, double b, const std::string& c, double d, long long int e, long long int f, long long int g,
			  long long int h) : a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h) {}

	double a = 1;
	double b = 1;
	std::string c = "asdfhkajsdfhwerkqjhqwerkjlhsadfasfhjhkhdsaf";
	double d = 1;
	long long e = 1;
	long long f = 1;
	long long g = 1;
	long long h = 1;
};


double bench_pushBack(size_t size) {
	auto result = std::vector<int>();
	auto storage = std::vector<BigStruct>();
	for (int i = 0; i < size; ++i) {
		auto now = std::chrono::steady_clock::now();
		auto s = BigStruct{1., 2., std::string("3124712387648127364871sdkjfhsakjfdh"), 3., 4, 5, 6, 7};
		storage.push_back(s);
		auto delta = std::chrono::steady_clock::now() - now;
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
		result.push_back(nanoseconds.count());
	}
	double sum = std::accumulate(result.begin(), result.end(), 0l);
	return sum / result.size();
}

double bench_emplaceBack(size_t size) {
	auto result = std::vector<int>();
	auto storage = std::vector<BigStruct>();
	for (int i = 0; i < size; ++i) {
		auto now = std::chrono::steady_clock::now();
		storage.emplace_back(1., 2., std::string("3124712387648127364871sdkjfhsakjfdh"), 3., 4, 5, 6, 7);
		auto delta = std::chrono::steady_clock::now() - now;
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
		result.push_back(nanoseconds.count());
	}
	double sum = std::accumulate(result.begin(), result.end(), 0l);
	return sum / result.size();
}

int main() {
	size_t size = 1000000;
	std::cout << "Testing push_back vs emplace_back: \n";
	auto avgP = bench_pushBack(size);
	std::cout << "push_back took: " << avgP << " ns\n";

	auto avgE = bench_emplaceBack(size);
	std::cout << "emplace_back took: " << avgE << " ns\n";

	if (avgP > avgE) {
		std::cout << "emplace_back was faster by factor of: " << avgP / avgE << "\n";
	} else if (avgP < avgE) {
		std::cout << "push_back was faster by factor of: " << avgE / avgP << "\n";
	} else {
		std::cout << "Both equally as fast! WOW!" << "\n";
	}
	std::cout << "\n";
	return 0;
}