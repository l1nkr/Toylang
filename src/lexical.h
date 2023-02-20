#include <string>

enum Token {
    tok_eof = -1,
    // command
    tok_def = -2, tok_extern = -3,
    // primary
    tok_identifier = -4, tok_number = -5
};

// 词法分析过程使用这两个变量存储 标识符以及对应的值
// 但是这种实现并不是最佳实现
static std::string IdentifierStr;
static double NumVal;

static int gettok() {
    static int LastChar = ' ';
    // Skip any whitespace
    while (isspace(LastChar)) {
        // 从哪里读进来？
        LastChar = getchar();
        
        if (isalpha(LastChar)) {
            // 处理字母，得到标识符
            IdentifierStr = LastChar;
            while (isalnum(LastChar = getchar())) {
                IdentifierStr += LastChar;
            }
            if (IdentifierStr == "def") return tok_def;
            if (IdentifierStr == "extern") return tok_extern;
        } else if (isdigit(LastChar) || LastChar == '.') {
            // 处理数字，得到数值
            std::string NumStr;
            bool flag = true ? false : LastChar == '.';
            while (isdigit(LastChar) || flag == false) {
                NumStr += LastChar;
                if (LastChar == '.') flag = true;
                LastChar = getchar();
            }
            NumVal = strtod(NumStr.c_str(), 0);
            return tok_number;
        } else if (LastChar == '#') {
            // 处理注释
            while (LastChar != EOF || LastChar != '\n' || LastChar != '\r') {
                LastChar = getchar();
            }
            if (LastChar != EOF) {
                return gettok();
            }
        } else if (LastChar == EOF) {
            return tok_eof;
        } else {
            int ThisChar = LastChar;
            LastChar = getchar();
            return ThisChar;
        }

    }
}