#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Puzzle.hpp"
#include "Parser.hpp"
#include "Output.hpp"

class ParserTests : public ::testing::Test {
public:
    static void TestInvalidPuzzle(const std::string &input) {
        std::stringstream iss;
        iss << input;

        Parser field_parser;

        try {
            field_parser.Parse(iss);
            ASSERT_TRUE(false);
        } catch (ParseException &ex) {
            std::cout << ex.what() << std::endl;
        } catch (std::exception &ex) {
            ASSERT_TRUE(false);
        }
    }
};

TEST_F(ParserTests, InvalidField_EmptyInput) {
    const std::string input;

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_OneComment) {
    const std::string input = "# comment";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_ZeroSize) {
    const std::string input = "0\n"
                              "# comment\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_NegativeSize) {
    const std::string input = "-1\n"
                              "# comment\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_TooSmallSize) {
    const std::string input = "1\n"
                              "# comment\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_WrongSize) {
    const std::string input = "fa\n"
                              "# comment\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_OverflowSize) {
    const std::string input = "99999999999999999999999999999\n"
                              "# comment\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_WrongColumnSize) {
    const std::string input = "3\n"
                              "1\n"
                              "3\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_WrongRowSize1) {
    const std::string input = "3\n"
                              "1 3 4\n"
                              "# comment1\n"
                              "# comment2\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_WrongRowSize2) {
    const std::string input = "3\n"
                              "1 3 4\n"
                              "# comment1\n"
                              "# comment2\n"
                              "\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_EmptyCell) {
    const std::string input = "3\n"
                              "1 3 4\n"
                              "4 # comment1\n"
                              "# comment2\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidSymbol1) {
    const std::string input = "3\n"
                              "1 C 4\n"
                              "# comment1\n"
                              "# comment2";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidSymbol2) {
    const std::string input = "3\n"
                              "1 23a 4\n"
                              "# comment1\n"
                              "# comment2";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidSymbol3) {
    const std::string input = "3\n"
                              "1 23 4\n"
                              "# comment1\n"
                              "# comment2\n"
                              "32 0 12\n"
                              "c";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidSymbol4) {
    const std::string input = "3\n"
                              "1 23                           c #kek\n"
                              "# comment1\n"
                              "# comment2\n"
                              "32 0\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidCell1) {
    const std::string input = "5\n"
                              "1 2 -1 4 5\n"
                              "6 7 8 9 10\n"
                              "11 12 13 14 15\n"
                              "16 17 18 19 20\n"
                              "21 22 23 24 0\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidCell2) {
    const std::string input = "5\n"
                              "1 2 0 4 5\n"
                              "6 7 8 9 10\n"
                              "11 12 13 14 15\n"
                              "16 17 18 19 20\n"
                              "21 22 23 24 0\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, InvalidField_InvalidCell3) {
    const std::string input = "5\n"
                              "1 2 25 4 5\n"
                              "6 7 8 9 10\n"
                              "11 12 13 14 15\n"
                              "16 17 18 19 20\n"
                              "21 22 23 24 0\n";

    TestInvalidPuzzle(input);
}

TEST_F(ParserTests, ValidField) {
    const std::string input = "5\n"
                              "1 2 3 4 5\n"
                              "6 7 8 9 10\n"
                              "11 12 13 14 15\n"
                              "16 17 18 19 20\n"
                              "21 22 23 24 0\n";

    std::stringstream iss;
    iss << input;

    ASSERT_NO_THROW(
            Parser field_parser;
            Puzzle field = field_parser.Parse(iss);

            std::cout << field;
    );
}