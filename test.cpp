#include <iostream>
#include <nlohmann/json.hpp>
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

	return 0;
}
