#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <ostream>

struct FileLine {
	size_t line_number;
	std::string text;
	std::string origin;

	friend std::ostream& operator<<(std::ostream& os, const FileLine& fl);

	FileLine();
	FileLine(const size_t& line_number, const std::string& text, const std::string& origin);
};

using FileLines = std::vector<FileLine>;

FileLines readFileAsLines(const std::string& file_path);
