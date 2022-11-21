#pragma once

#include <string>
#include <vector>
#include <memory>

#include "file_reader.hpp"

struct Token;
using Tokens = std::vector<Token>;

struct Token {
    size_t offset;
    std::string text;
    FileLine parent;

    friend std::ostream& operator<<(std::ostream& os, const Token& t);
    friend std::ostream& operator<<(std::ostream& os, const Tokens& tokens);

    Token();
    Token(const size_t& offset, const std::string& text, const FileLine& fl);

    bool operator==(const std::string& str) const;
};

Tokens tokenizeLine(const FileLine& fl);

class SyntaxNode;
using SyntaxNodePtr = std::shared_ptr<SyntaxNode>;

class SyntaxNode : public std::enable_shared_from_this<SyntaxNode> {
private:
    Tokens tokens;
    SyntaxNodePtr parent;
    std::vector<SyntaxNodePtr> children;
public:
    SyntaxNode();
    SyntaxNode(const Tokens& tokens);
    SyntaxNode(const FileLine& fl);

    [[nodiscard]] static SyntaxNodePtr create();
    [[nodiscard]] static SyntaxNodePtr create(const std::string& str);
    [[nodiscard]] static SyntaxNodePtr create(const Tokens& tokens);
    [[nodiscard]] static SyntaxNodePtr create(const FileLine& fl);

    SyntaxNodePtr getPtr();

    void setParent(const SyntaxNodePtr& snp);
    SyntaxNodePtr getParent() const;
    bool hasParent() const;
    
    std::vector<SyntaxNodePtr> getChildren() const;
    void addChild(const SyntaxNodePtr& child);

    FileLine getOrigin() const;
    Tokens getTokens() const;

    void dump(const size_t& level=0) const;

    bool isOpenScope() const;
    bool isCloseScope() const;

    [[nodiscard]] static SyntaxNodePtr createTree(const FileLines& fls);
};