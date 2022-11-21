#include <iostream>

#include "file_reader.hpp"
#include "lexer.hpp"

int main() {
	FileLines file_as_lines = readFileAsLines("./examples/file.lang");

	SyntaxNodePtr master_node = SyntaxNode::createTree(file_as_lines);
	master_node->dump();

	return EXIT_SUCCESS;
}