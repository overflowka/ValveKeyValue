#include "KeyValue.h"

std::map<std::string, std::string> root_;

void KeyValue::parse(const std::string& text) {
	std::stringstream ss(text);
	std::string line;
	std::vector<std::string> lines;
	while (getline(ss, line)) lines.push_back(line);

	KeyValue::parse(lines);
}

void KeyValue::parse(const std::vector<std::string>& lines) {
	KeyValue::parse(lines, 0, root_);
}

std::string KeyValue::encode() {
	return KeyValue::encode(root_);
}

void KeyValue::parse(const std::vector<std::string>& lines, size_t start_line, std::map<std::string, std::string>& data) {
	size_t line_number = start_line;
	while (line_number < lines.size()) {
		std::string line = lines[line_number++];

		if (line.empty()) continue;
		if (line[0] == '/') continue;
		if (line[0] == '}') break;

		size_t key_end = line.find_first_of(" \t");
		std::string key = line.substr(1, key_end - 2);

		if (line[key_end] == '{') {
			std::map<std::string, std::string> block;
			parse(lines, line_number, block);
			data[key] = encode(block);
		}
		else {
			size_t value_start = line.find_first_not_of(" \t", key_end);
			size_t value_end = line.find_last_not_of(" \t");
			std::string value = line.substr(value_start + 1, value_end - value_start - 1);

			data[key] = value;
		}
	}
}

std::string KeyValue::encode(const std::map<std::string, std::string>& data) {
	std::stringstream ss;

	for (const auto& [_, value] : data) {
		std::string val = value;
		size_t pos = 0;

		while ((pos = val.find("\t", pos)) != std::string::npos) {
			val.replace(pos, 2, ": ");
			pos += 1;
		}

		ss << "\"" << val << "\"\n";
	}

	return ss.str();
}