#include <sstream>
#include <string>
#include <vector>
#include <map>

class KeyValue {
public:
	void parse(const std::string& text);
	void parse(const std::vector<std::string>& lines);

	std::string encode();

private:
	void parse(const std::vector<std::string>& lines, size_t start_line, std::map<std::string, std::string>& data);

	std::string encode(const std::map<std::string, std::string>& data);
};