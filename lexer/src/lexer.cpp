#include <lexer/lexer.h>
#include <lexer/token.h>
#include <iostream>
int CurTok;
std::string IdentifierStr;
double NumVal;

// It's called to return the next token from standard input
// gettok works by calling getchar() function to read chars one at a time

int gettok() {
  static int LastChar = ' ';
  // The first thing we need to do is ignore whitespaces between tokens
  while (isspace(LastChar)) {
    LastChar = getchar();
  }
  if (isalpha(LastChar)) {

    IdentifierStr = LastChar;
    while (isalnum(LastChar = getchar())) IdentifierStr += LastChar;
    if (IdentifierStr == "def") return tok_def;
    if (IdentifierStr == "extern") return tok_extern;
    return tok_identifier;

  } else if (isdigit(LastChar) || LastChar == '.') {

    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;

  } else if (LastChar == '#') {

    // Handling comments by skipping to the end of the line
    // and return the next token
    do {
      LastChar = getchar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    
    if (LastChar != EOF) return gettok();

  } else if (LastChar == EOF) {

    // Finally, if the input doesn't match one of the above cases
    // it's either an operator character like '+' or the end of the file
    return tok_eof;
  }

  int ThisChar = LastChar;
  LastChar = getchar();
  std::cout << ThisChar << std::endl;
  return ThisChar;
}

int getNextToken() { return CurTok = gettok(); }
