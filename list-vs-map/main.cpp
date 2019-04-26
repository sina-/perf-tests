#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <map>

static std::string LONG_STRING = "this is random but a bit longer than usual string that says nothing";
//static std::string LONG_STRING = "this is random but a bit ";


template<class T, class F>
bool find(const T& list, const F& target) {
	return list.find(target) != list.end();
}

template<>
bool find<std::vector<std::string>>(const std::vector<std::string>& list, const std::string& target) {
	for (auto&& item: list) {
		if (target == item) {
			return true;
		}
	}
	return false;
}

template<>
bool find<std::vector<std::int64_t>>(const std::vector<std::int64_t>& list, const std::int64_t& target) {
	for (auto&& item: list) {
		if (target == item) {
			return true;
		}
	}
	return false;
}

template<>
bool find<std::map<std::string, bool>>(const std::map<std::string, bool>& list, const std::string& target) {
	return list.find(target) != list.end();
}

template<>
bool find<std::map<std::int64_t, bool>>(const std::map<std::int64_t, bool>& list, const std::int64_t& target) {
	return list.find(target) != list.end();
}


template<class T>
void fill(T& items, int n) {
	for (int i = 0; i < n; ++i) {
		auto string = LONG_STRING + std::to_string(i);
		items.emplace_back(string);
	}
}

template<>
void fill<std::map<std::string, bool>>(std::map<std::string, bool>& items, int n) {
	for (int i = 0; i < n; ++i) {
		auto string = LONG_STRING + std::to_string(i);
		items.emplace(string, true);
	}
}

template<>
void fill<std::vector<std::int64_t>>(std::vector<std::int64_t>& items, int n) {
	for (int i = 0; i < n; ++i) {
		items.emplace_back(i);
	}
}

template<>
void fill<std::map<std::int64_t, bool>>(std::map<std::int64_t, bool>& items, int n) {
	for (int i = 0; i < n; ++i) {
		items.emplace(i, true);
	}
}


template<class T, class F>
double bench(int size, const F& target) {
	auto result = std::vector<long>();
	auto list = T{};
	fill(list, size);
	for (int i = 0; i < 10000; ++i) {
		auto now = std::chrono::steady_clock::now();
		volatile auto found = find(list, target);
		auto delta = std::chrono::steady_clock::now() - now;
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
		result.push_back(nanoseconds.count());
	}
	double sum = std::accumulate(result.begin(), result.end(), 0l);
	return sum / result.size();
}

void compare(int sampleSize) {
	std::cout << "Testing sample size: " << sampleSize << "\n";
	auto target = LONG_STRING + std::to_string(5000);
	auto avgTimeVector = bench<std::vector<std::string>>(sampleSize, target);
	std::cout << "Vector version took: " << avgTimeVector << "\n";

	auto avgTimeMap = bench<std::map<std::string, bool>>(sampleSize, target);
	std::cout << "Map version took: " << avgTimeMap << "\n";

	if (avgTimeVector > avgTimeMap) {
		std::cout << "Map was faster by factor of: " << avgTimeVector / avgTimeMap << "\n";
	} else if (avgTimeVector < avgTimeMap) {
		std::cout << "Vector was faster by factor of: " << avgTimeMap / avgTimeVector << "\n";
	} else {
		std::cout << "Both equally as fast! WOW!" << "\n";
	}
	std::cout << "\n";
}


int main() {
	for (int i = 10; i <= 1000000; i *= 10) {
		compare(i);
	}
	return 0;
}