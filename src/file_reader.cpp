#include "file_reader.hpp"

#include <fstream>
#include <iostream>

FileLine::FileLine() : line_number(0), text(""), origin("") {}

FileLine::FileLine(const size_t& line_number, const std::string& text, const std::string& origin) :
line_number(line_number), text(std::move(text)), origin(std::move(origin)) {

}

std::ostream& operator<<(std::ostream& os, const FileLine& fl) {
	os << fl.origin << ":" << fl.line_number << ": " << fl.text;
	return os;
}

const std::string WHITESPACE = " \t\n\r";
static std::string rstrip(const std::string& s) {
	if (s.length() == 0) return s;
	const size_t i = s.find_last_not_of(WHITESPACE);
	return s.substr(0, i+1);
}
static std::string lstrip(const std::string& s) {
	if (s.length() == 0) return s;
	const size_t i = s.find_first_not_of(WHITESPACE);
	return s.substr(i);
}
static std::string strip(const std::string& s) {
	return lstrip(rstrip(s));
}
       
FileLines readFileAsLines(const std::string& file_path) {
	FileLines file_as_lines;

	std::ifstream file_in(file_path);
	std::string line;
	size_t line_number = 0;
	while (std::getline(file_in, line)) {

		line_number++;

		const std::string text = strip(line);
		if (line.length() == 0) continue;

		FileLine fl {line_number, text, file_path};
		file_as_lines.push_back(fl);
	}

	return file_as_lines;
}
