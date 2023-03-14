#include <iostream>
#include <nlohmann/json.hpp>
#include "request/Unsplash.h"

using json = nlohmann::json;

int main() {
	std::cout << "eee";

	json j;
	j["test"] = "heeey";
	j["eeee"] = 34;
	j["eggs"] = 123.333;
	j["test"] = { {"eggs", 123}, {"banana", 69.99}};

	std::cout << j.dump() << std::endl;

	auto jj = json::parse("{\"b\":123,\"ee\":\"fereferf\"}");
	std::cout << "b=" << jj["b"] << ", ee=" << jj["ee"] << std::endl;

	Unsplash* unsplash = new Unsplash();
	auto abc = unsplash->getRandomBackground();
	std::cout << "URL=" << abc->getURL() << "\nDESC=" << abc->getDescription() << std::endl;

	return 0;
}
