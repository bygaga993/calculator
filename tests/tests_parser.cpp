#include <gtest/gtest.h>

#include "../Operations.h"
#include "../ExpressionParser.h"
#include "../calc.h"


class ParserTest : public testing::Test
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

TEST_F(ParserTest, ParseSimpleAddition)
{
  EXPECT_NO_THROW(parser->Parse("(1 + 2)"));
  EXPECT_EQ(parser->getNumTokens().size(), 2);
  EXPECT_EQ(parser->getOpTokens().size(), 1);
  EXPECT_EQ(parser->getOrderTokens().size(), 3);

  EXPECT_NO_THROW(parser->Parse("-1"));
  EXPECT_EQ(parser->getNumTokens().size(), 1);
  EXPECT_EQ(parser->getOpTokens().size(), 0);
  EXPECT_EQ(parser->getOrderTokens().size(), 1);

  EXPECT_NO_THROW(parser->Parse("7 * -(5 + 3)"));
  EXPECT_EQ(parser->getNumTokens().size(), 4);
  EXPECT_EQ(parser->getOpTokens().size(), 3);
  EXPECT_EQ(parser->getOrderTokens().size(), 7);

  EXPECT_NO_THROW(parser->Parse("+5"));
  EXPECT_EQ(parser->getNumTokens().size(), 1);
  EXPECT_EQ(parser->getOpTokens().size(), 0);
  EXPECT_EQ(parser->getOrderTokens().size(), 1);

  EXPECT_NO_THROW(parser->Parse("7 * +(7 + 3)"));
  EXPECT_EQ(parser->getNumTokens().size(), 3);
  EXPECT_EQ(parser->getOpTokens().size(), 2);
  EXPECT_EQ(parser->getOrderTokens().size(), 5);
}

TEST_F(ParserTest, ThrowsOnInvalidExpression)
{
    EXPECT_THROW(parser->Parse("(1 + )"), std::exception);
    EXPECT_THROW(parser->Parse("(1 + 3"), std::exception);
    EXPECT_THROW(parser->Parse(") + 7"), std::exception);
    EXPECT_THROW(parser->Parse("?/"), std::exception);
    EXPECT_THROW(parser->Parse("*7"), std::exception);
    EXPECT_THROW(parser->Parse("--3"), std::exception);
    EXPECT_THROW(parser->Parse("++7"), std::exception);
}