#include <gtest/gtest.h>

#include "../Operations.h"
#include "../ExpressionParser.h"
#include "../calc.h"
#include "../main_func.h"

class CalculateTest : public testing::Test
{
public:
  ExpressionParser *parser;
  Calculator *calc;
  void SetUp()
  {
    calc = new Calculator();
    calc->RegisterOperation<AddOperation>("+").RegisterOperation<SubOperation>("-").RegisterOperation<DivOperation>("/").RegisterOperation<MulOperation>("*");
    parser = new ExpressionParser(*calc);
  }
  void TearDown()
  {
    delete parser;
    delete calc;
  }
};

void CheckResult( ExpressionParser *parser, const std::string& expr, float expected)
{
    ASSERT_NO_THROW(parser->Parse(expr));
    EXPECT_FLOAT_EQ(
        getResult(parser->getOpTokens(), parser->getNumTokens(), parser->getOrderTokens()),
        expected
    );
}

TEST_F(CalculateTest, Calculate)
{
    CheckResult(parser, "1 + 2", 3.0f);
    CheckResult(parser, "(5 - 2)", 3.0f);
    CheckResult(parser, "(4 * 3)", 12.0f);
    CheckResult(parser, "(8 / 2)", 4.0f);


    CheckResult(parser, "2 + 3 * 4", 14.0f);
    CheckResult(parser, "(2 + 3) * 4", 20.0f);
    CheckResult(parser, "10 - 6 / 2", 7.0f);
    CheckResult(parser, "18 / 3 * 2", 12.0f);

    CheckResult(parser, "((2 + 3) * (4 - 1))", 15.0f);
    CheckResult(parser, "2 * (3 + (4 * 5))", 46.0f);

    CheckResult(parser, "-3", -3.0f);
    CheckResult(parser, "+5", 5.0f);
    CheckResult(parser, "7 * -2", -14.0f);
    CheckResult(parser, "-(2 + 3)", -5.0f);
    CheckResult(parser, "-(-4)", 4.0f);

    CheckResult(parser, "2.5 + 0.5", 3.0f);
    CheckResult(parser, "5 / 2", 2.5f);
    CheckResult(parser, "-5 / 2", -2.5f);
    CheckResult(parser, "(1.5 + 2.5) * 2", 8.0f);

    CheckResult(parser, "0 + 7", 7.0f);
    CheckResult(parser, "5 * 0", 0.0f);
    CheckResult(parser, "0 / 5", 0.0f);
}


TEST_F(CalculateTest, UncorrectExpresison)
{
    EXPECT_THROW(parser->Parse(""), std::runtime_error);
    EXPECT_THROW(parser->Parse("   "), std::runtime_error);
    EXPECT_THROW(parser->Parse("1 +"), std::runtime_error);
    EXPECT_THROW(parser->Parse("2 *"), std::runtime_error);
    EXPECT_THROW(parser->Parse("5 /"), std::runtime_error);
    EXPECT_THROW(parser->Parse("()"), std::runtime_error);
    EXPECT_THROW(parser->Parse("( )"), std::runtime_error);
    EXPECT_THROW(parser->Parse("abc"), std::runtime_error);
    EXPECT_THROW(parser->Parse("2 ^ 3"), std::runtime_error);
    EXPECT_THROW(parser->Parse("1 + a"), std::runtime_error);
}

TEST_F(CalculateTest, ThrowsOnDivisionByZero)
{
    ASSERT_NO_THROW(parser->Parse("5 / 0"));
    EXPECT_THROW(
        getResult(parser->getOpTokens(), parser->getNumTokens(), parser->getOrderTokens()),
        std::runtime_error
    );
}