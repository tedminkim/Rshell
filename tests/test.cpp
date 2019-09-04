#include "../src/rshell.cpp"
#include "../src/commands.h"
#include "../src/execute.cpp"
#include "../src/connector.cpp"

#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

TEST(ParseTest, noInput) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("\n", oss.str());
}

TEST(ParseTest, oneCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test \n", oss.str());
}
TEST(ParseTest, aANDb) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test&&test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test && test \n", oss.str());
}
TEST(ParseTest, aANDbWithSpaces) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "   test   &&     test   ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test && test \n", oss.str());
}
TEST(ParseTest, aORb) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || test \n", oss.str());
}
TEST(ParseTest, aORbWithSpaces) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "    test    ||    test    ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || test \n", oss.str());
}
TEST(ParseTest, aNEXTb) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test;test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test ; test \n", oss.str());
}
TEST(ParseTest, aNEXTbWithSpaces) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "   test   ;  test   ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test ; test \n", oss.str());
}
TEST(ParseTest, oneCommand_with_Spaces) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "      test    ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test \n", oss.str());
}
TEST(ParseTest, allConnectors_correctSyntax) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test || test ; test && test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || test ; test && test \n", oss.str());
}
TEST(ParseTest, allConnectors_noSpaces) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||test; test&&test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || test ; test && test \n", oss.str());
}
TEST(ParseTest, twoConnectors) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||; test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || ; test \n", oss.str());
}
TEST(ParseTest, startWithAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "&&test||; test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("&& test || ; test \n", oss.str());
}
TEST(ParseTest, spaceAndBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "     &&test||; test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("&& test || ; test \n", oss.str());
}
TEST(ParseTest, orBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "||test||; test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("|| test || ; test \n", oss.str());
}
TEST(ParseTest, spaceOrBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "       ||test||; test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("|| test || ; test \n", oss.str());
}
TEST(ParseTest, semicBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = ";;;;;test || test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; ; ; ; ; test || test \n", oss.str());
}
TEST(ParseTest, spaceSemicBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "        ;test || test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; test || test \n", oss.str());
}
TEST(ParseTest, semicSpaceBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "; test ||test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; test || test \n", oss.str());
}
TEST(ParseTest, spaceSemicSpaceBegin) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "         ; test || test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; test || test \n", oss.str());
}
TEST(ParseTest, spaceAroundSemic) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "         ;          test || test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; test || test \n", oss.str());
}
TEST(ParseTest, spaceAroundOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test        ||       test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || test \n", oss.str());
}
TEST(ParseTest, spaceBetweenCommands) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test        test   ||       test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test        test || test \n", oss.str());
}
TEST(ParseTest, spaceBeforeComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test test||test; test     #test; ; ||&&";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test test || test ; test \n", oss.str());
}
TEST(ParseTest, oneComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "#";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("\n", oss.str());
}
TEST(ParseTest, oneSemic) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "; ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; \n", oss.str());
}
TEST(ParseTest, oneAnd) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "&&";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("&& \n", oss.str());
}
TEST(ParseTest, oneOr) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "||";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("|| \n", oss.str());
}
TEST(ParseTest, spaceBeforeOneNext) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "            ; ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; \n", oss.str());
}
TEST(ParseTest, spaceBeforeOneAnd) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "             &&";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("&& \n", oss.str());
}
TEST(ParseTest, spaceBeforeOneOr) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "           ||";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("|| \n", oss.str());
}
TEST(ParseTest, spaceAfterOneNext) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = ";            ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("; \n", oss.str());
}
TEST(ParseTest, spaceAfterOneAnd) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "&&              ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("&& \n", oss.str());
}
TEST(ParseTest, spaceAfterOneOr) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "||            ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("|| \n", oss.str());
}
TEST(ParseTest, exit) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, exitOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit||";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, exitAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit&&";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, exitNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit; ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, exitOrExit) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit||exit";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, commentExitOrExit) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "#exit||exit";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("\n", oss.str());
}
TEST(ParseTest, exitComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit#||exit";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, testConnectorExit) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test ||    exit    ";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || exit \n", oss.str());
}
TEST(ParseTest, exitOrCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "exit||test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("exit \n", oss.str());
}
TEST(ParseTest, commentAfterConnector) {  
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||#test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || \n", oss.str());
}
TEST(ParseTest, spaceBeforeCommentAfterConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||         #test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || \n", oss.str());
}
TEST(ParseTest, spaceBeforeAndAfterCommentAfterConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "test||         #           test";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("test || \n", oss.str());
}
TEST(ParseTest, OpenParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "() []";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( ) [ ] \n", oss.str());
}
TEST(ParseTest, parenthesesAroundCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test)";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( test ) \n", oss.str());
}
TEST(ParseTest, doubleParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "((test))";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( ( test ) ) \n", oss.str());
}
TEST(ParseTest, bracketsAroundCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[test]";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("[ test ] \n", oss.str());
}
TEST(ParseTest, parenthesesAroundAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test   &&    test  )";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( test && test ) \n", oss.str());
}
TEST(ParseTest, bracketsAroundAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   && test     ]";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("[ test && test ] \n", oss.str());
}
TEST(ParseTest, parenthesesAroundOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test||    test  )";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( test || test ) \n", oss.str());
}
TEST(ParseTest, bracketsAroundOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   ||   test     ]";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("[ test || test ] \n", oss.str());
}
TEST(ParseTest, parenthesesAroundNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test    ;test  )";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( test ; test ) \n", oss.str());
}
TEST(ParseTest, bracketsAroundNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   ;   test     ]";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("[ test ; test ] \n", oss.str());
}
TEST(ParseTest, multipleParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(echo a&&echo b)||(echo c||echo d)";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( echo a && echo b ) || ( echo c || echo d ) \n", oss.str());
}
TEST(ParseTest, multipleLayerParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "( (  test    ||test)   ||( echo a   &&ls  ; ls     -l) && (test   ; aa) )";
  rs->parser(s, cmdToParse, oss);
  EXPECT_EQ("( ( test || test ) || ( echo a && ls ; ls     -l ) && ( test ; aa ) ) \n", oss.str());
}

//PARSE TESTING ENDS, VERIFY TESTING BEGINS

TEST(VerifyTest, emptyInput) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, singleCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, spaceAroundSingleCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "      test    ";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, AllThreeConnectorsProper) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test || test ; test && test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, noSpaceAllConnectors) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test||test; test&&test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, twoAdjacentConnectors) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test||; test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, startWithAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "&&test||; test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, startWithSpaceAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "     &&test||; test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, startWithOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "||test||; test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, startWithSpaceOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "       ||test||; test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, startWithNOTNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = ";test || test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, startWithSpaceNOTNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "        ;test || test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, startWithNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "; test || test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, startWithSpaceNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "         ; test || test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, spaceAroundStartNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "         ;          test || test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, spaceAroundConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test        ||       test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, spaceBetweenItems) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test        test   ||       test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, spaceBeforeComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test test||test; test     #test; ; ||&&";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, singleComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "#";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, singleNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "; ";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, singleAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "&&";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, singleOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "||";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, spaceBeforeSingleNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "            ; ";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, exitOrexit) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "exit||exit";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, commentExitOrExit) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "#exit||exit";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, exitComment) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "exit#||exit";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, testConnectorExit) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test ||    exit    ";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, exitOrCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "exit||test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, commentAfterConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test||#test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, spaceBeforeCommentAfterConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test||         #test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, spaceBeforeAndAfterCommentAfterConnector) {
  vector<string> cmdToParse;
  ostringstream oss;
  string s = "test||         #           test";
  rShell* rs = new rShell();
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, OpenParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "() []";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, SingleOpenParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, SingleClosedParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "     )";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, SingleOpenBracket) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "  [   ";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, SingleClosedBracket) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "]    ";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Invalid input", oss.str());
}
TEST(VerifyTest, parenthesesAroundCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test)";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, bracketsAroundCommand) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[test]";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, parenthesesAroundAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test   &&    test  )";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, bracketsAroundAnd) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   && test     ]";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, parenthesesAroundOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test||    test  )";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, bracketsAroundOr) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   ||   test     ]";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, parenthesesAroundNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(test    ;test  )";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, bracketsAroundNext) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "[    test   ;   test     ]";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, multipleParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "(echo a&&echo b)||(echo c||echo d)";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, multipleLayerParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = " (  test    ||test)  ||( ( echo a   &&ls  ; ls     -l) && (test   ; aa) )";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
TEST(VerifyTest, doubleParentheses) {
  vector<string> cmdToParse;
  ostringstream oss;
  rShell* rs = new rShell();
  string s = "((test))";
  rs->verify(s, cmdToParse, oss);
  EXPECT_EQ("Valid input", oss.str());
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
