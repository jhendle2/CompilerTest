#include "lexer.hpp"

#include <iostream>

#include "ops_delims.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << t.parent << ":" << t.parent.line_number << ":" << t.offset << ": " << t.text;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Tokens& tokens) {
    os << "[";
    for (const auto& t : tokens) {
        os << "`" << t.text << "`, ";
    }
    os << "]";
    return os;
}

bool Token::operator==(const std::string& str) const {
    return (this->text == str);
}

Token::Token() : offset(0), text(""), parent(FileLine()) {

}
Token::Token(const size_t& offset, const std::string& text, const FileLine& fl) :
offset(offset), text(std::move(text)), parent(fl) {
    
}

Tokens tokenizeLine(const FileLine& fl) {
    Tokens tokens;
    Token token;
    size_t offset = 0;

    auto appendToToken = [&token, &offset](const char& c) {
        token.text += c;
    };

    auto appendToken = [&tokens, &token]() {
        if (token.text.length()==0) return;
        tokens.push_back(token);
        token.text="";
    };

    bool in_string = false;
    const std::string& text = fl.text;
    for (size_t i = 0; i<text.length(); i++) {
        const char& c = text[i];

        if (c == Delims::Quote::Double) {
            in_string = !in_string;
            if (in_string) {
                appendToken();
                appendToToken(c);
            } else {
                appendToToken(c);
                appendToken();
            }
            continue;        
        }

        if (!in_string) {
            if (c == Delims::Space) {
                appendToken();
                continue;
            }

            if (Delims::isOp(c)) {
                appendToken();
                appendToToken(c);
                appendToken();
                continue;
            }
        }

        appendToToken(c);
    }
    appendToken();

    return tokens;
}

/******************************/

SyntaxNode::SyntaxNode() : parent(nullptr) {

}
SyntaxNode::SyntaxNode(const Tokens& tokens) : tokens(tokens), parent(nullptr) {

}
SyntaxNode::SyntaxNode(const FileLine& fl) : tokens(tokenizeLine(fl)), parent(nullptr) {

}

SyntaxNodePtr SyntaxNode::create() {
    return SyntaxNodePtr(new SyntaxNode());
}

SyntaxNodePtr SyntaxNode::create(const std::string& str) {
    Tokens ts = {
        Token(0, "MASTER", FileLine())
    };
    return SyntaxNodePtr(new SyntaxNode(ts));
}
SyntaxNodePtr SyntaxNode::create(const Tokens& tokens) {
    return SyntaxNodePtr(new SyntaxNode(tokens));
}
SyntaxNodePtr SyntaxNode::create(const FileLine& fl) {
    return SyntaxNodePtr(new SyntaxNode(fl));
}

SyntaxNodePtr SyntaxNode::getPtr() {
    return shared_from_this();
}

void SyntaxNode::setParent(const SyntaxNodePtr& snp) {
    this->parent = snp;
}
SyntaxNodePtr SyntaxNode::getParent() const {
    return this->parent;
}
bool SyntaxNode::hasParent() const {
    return (this->parent != nullptr);
}

std::vector<SyntaxNodePtr> SyntaxNode::getChildren() const {
    return this->children;
}
void SyntaxNode::addChild(const SyntaxNodePtr& child) {
    child->setParent(this->getPtr());
    this->children.push_back(child);
}

FileLine SyntaxNode::getOrigin() const {
    if (this->tokens.size() == 0) return FileLine();
    return this->tokens[0].parent;
}
Tokens SyntaxNode::getTokens() const {
    return this->tokens;
}

void SyntaxNode::dump(const size_t& level) const {
    for (size_t i = 0; i<level; i++) std::cout << "* ";
    std::cout << this->tokens << "\n";
    for (const auto& child : children) child->dump(level+1);
}

#include "keywords.hpp"
bool SyntaxNode::isOpenScope() const {
    return (
        tokens.size() > 0 &&
        tokens.back() == Keywords::Begin
    );
}
bool SyntaxNode::isCloseScope() const {
    return (
        tokens.size() > 0 &&
        tokens.back() == Keywords::End
    );
}

#include "console.hpp"
SyntaxNodePtr SyntaxNode::createTree(const FileLines& fls) {
    SyntaxNodePtr master_node = SyntaxNode::create("MASTER");
    SyntaxNodePtr current_node = master_node;

    for (const auto& fl : fls) {
        SyntaxNodePtr snp = SyntaxNode::create(fl);
        current_node->addChild(snp);

        if (snp->isOpenScope()) {
            current_node = snp;
        }

        if (snp->isCloseScope()) {
            if (!current_node->hasParent()) {
                Console::Erro("Mismatched begin/end pair");
            }

            current_node = current_node->getParent();
        }
    }

    return master_node;
}