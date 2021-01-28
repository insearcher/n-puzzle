#include "gtest/gtest.h"

#include "Move.hpp"
#include "Puzzle.hpp"
#include "Parser.hpp"

class MoveTests : public ::testing::Test {
public:
    static void TestInvalidMove(const std::string &input,
                         const IMove &move) {
        Puzzle *puzzle = CreatePuzzle(input);
        Puzzle *new_puzzle = move.Execute(*puzzle);

        ASSERT_EQ(new_puzzle, nullptr);

        delete puzzle;
        delete new_puzzle;
    }

    static void TestValidMove(const std::string &input,
                       const std::string &input_target,
                       const IMove &move) {
        Puzzle *puzzle = CreatePuzzle(input);
        Puzzle *target = CreatePuzzle(input_target);

        Puzzle *new_puzzle = move.Execute(*puzzle);

        ASSERT_EQ(*new_puzzle, *target);

        delete puzzle;
        delete new_puzzle;
        delete target;
    }

private:
    static Puzzle *CreatePuzzle(const std::string& input) {
        Parser parser;
        std::stringstream iss;
        iss << input;
        return parser.Parse(iss);
    }
};

TEST_F(MoveTests, MoveLeft_Wrong1) {
    const std::string input = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "0 8 7\n";

    MoveTests::TestInvalidMove(input, MoveLeft());
}

TEST_F(MoveTests, MoveLeft_Wrong2) {
    const std::string input = "3\n"
                              "0 2 3\n"
                              "4 5 6\n"
                              "1 8 7\n";

    MoveTests::TestInvalidMove(input, MoveLeft());
}

TEST_F(MoveTests, MoveDown_Wrong1) {
    const std::string input = "3\n"
                              "0 2 3\n"
                              "4 5 6\n"
                              "1 8 7\n";

    MoveTests::TestInvalidMove(input, MoveDown());
}

TEST_F(MoveTests, MoveDown_Wrong2) {
    const std::string input = "3\n"
                              "1 2 0\n"
                              "4 5 6\n"
                              "7 8 3\n";

    MoveTests::TestInvalidMove(input, MoveDown());
}

TEST_F(MoveTests, MoveRight_Wrong1) {
    const std::string input = "3\n"
                              "1 2 0\n"
                              "4 5 6\n"
                              "7 8 3\n";

    MoveTests::TestInvalidMove(input, MoveRight());
}

TEST_F(MoveTests, MoveRight_Wrong2) {
    const std::string input = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 8 0\n";

    MoveTests::TestInvalidMove(input, MoveRight());
}

TEST_F(MoveTests, MoveUp_Wrong1) {
    const std::string input = "3\n"
                              "7 2 3\n"
                              "4 5 6\n"
                              "0 8 1\n";

    MoveTests::TestInvalidMove(input, MoveUp());
}

TEST_F(MoveTests, MoveUp_Wrong2) {
    const std::string input = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 8 0\n";

    MoveTests::TestInvalidMove(input, MoveUp());
}

TEST_F(MoveTests, MoveUp_Ok1) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "4 0 6\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "4 8 6\n"
                               "7 0 3\n";

    MoveTests::TestValidMove(input, target, MoveUp());
}

TEST_F(MoveTests, MoveUp_Ok2) {
    const std::string input = "3\n"
                              "1 0 5\n"
                              "4 2 6\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "4 0 6\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveUp());
}

TEST_F(MoveTests, MoveLeft_Ok1) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "4 0 6\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "0 4 6\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveLeft());
}

TEST_F(MoveTests, MoveLeft_Ok2) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "6 4 0\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "6 0 4\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveLeft());
}

TEST_F(MoveTests, MoveDown_Ok1) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "4 0 6\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 0 5\n"
                               "4 2 6\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveDown());
}

TEST_F(MoveTests, MoveDown_Ok2) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "4 8 6\n"
                              "7 0 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "4 0 6\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveDown());
}

TEST_F(MoveTests, MoveRight_Ok1) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "4 0 6\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "4 6 0\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveRight());
}

TEST_F(MoveTests, MoveRight_Ok2) {
    const std::string input = "3\n"
                              "1 2 5\n"
                              "0 6 4\n"
                              "7 8 3\n";
    const std::string target = "3\n"
                               "1 2 5\n"
                               "6 0 4\n"
                               "7 8 3\n";

    MoveTests::TestValidMove(input, target, MoveRight());
}
