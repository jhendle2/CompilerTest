#pragma once

namespace Delims {
    using Delim = const char;

    Delim Space = ' ';
    Delim Tab = '\t';
    Delim Newline = '\n';
    Delim Return = '\r';

    Delim Period = '.';
    Delim Comma = ',';
    Delim Colon = ':';
    Delim Semicolon = ';';
    
    Delim Plus = '+';
    Delim Minus = '-';
    Delim Mult = '*';
    Delim Div = '/';
    Delim Mod = '%';
    Delim At = '@';
    Delim And = '&';
    Delim Bar = '|';
    Delim Caret = '^';
    Delim Equal = '=';
    Delim Exclamation = '!';
    Delim Tilde = '~';
    Delim Dollar = '$';
    Delim Hash = '#';

    namespace Paren {
        Delim Open = '(';
        Delim Close = ')';
    };

    namespace Bracket {
        Delim Open = '[';
        Delim Close = ']';
    };

    namespace Brace {
        Delim Open = '{';
        Delim Close = '}';
    };

    namespace Angle {
        Delim Open = '<';
        Delim Close = '>';
    };

    namespace Quote {
        Delim Single = '\'';
        Delim Double = '\"';
    };

    bool isOp(const char& c);
};