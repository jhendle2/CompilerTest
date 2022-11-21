#include "ops_delims.hpp"

bool Delims::isOp(const char& c) {
    return (
        c == Period ||
        c == Comma ||
        c == Colon ||
        c == Semicolon ||
        c == Plus ||
        c == Minus ||
        c == Mult ||
        c == Div ||
        c == Mod ||
        c == At ||
        c == And ||
        c == Bar ||
        c == Caret ||
        c == Equal ||
        c == Exclamation ||
        c == Tilde ||
        c == Dollar ||
        c == Hash ||

        c == Paren::Open ||
        c == Paren::Close ||
        c == Bracket::Open ||
        c == Bracket::Close ||
        c == Brace::Open ||
        c == Brace::Close ||
        c == Angle::Open ||
        c == Angle::Close ||
        c == Quote::Single ||
        c == Quote::Double ||
        0
    );
}