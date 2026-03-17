#include <gtest/gtest.h>

#include "../Operations.h"
#include "../ExpressionParser.h"
#include "../calc.h"

TEST(HelloTest, BasicAssertions)
{
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}

TEST(ExpressionTest, AddTest)
{
  AddOperation add;
  EXPECT_EQ(add.return_value(5, 2), 7);
  EXPECT_EQ(add.return_value(-5, 2), -3);
  EXPECT_EQ(add.return_value(-7, -3), -10);
  EXPECT_EQ(add.return_value(2, 0), 2);
  EXPECT_EQ(add.getPriority(), 1);
  EXPECT_FALSE(add.isNumber());
}

TEST(ExpressionTest, SubTest)
{
  SubOperation sub;
  EXPECT_EQ(sub.return_value(5, 2), 3);
  EXPECT_EQ(sub.return_value(-5, 2), -7);
  EXPECT_EQ(sub.return_value(-7, -3), -4);
  EXPECT_EQ(sub.return_value(2, 0), 2);
  EXPECT_EQ(sub.getPriority(), 1);
  EXPECT_FALSE(sub.isNumber());
}

class ParserTest : public testing::Test
{
public:
  ExpressionParser *parser;
  Calculator *calc;
  void SetUp()
  {
    calc = new Calculator();
    calc->RegisterOperation<AddOperation>("+");
    parser = new ExpressionParser(*calc);
  }
  void TearDown()
  {
    delete parser;
    delete calc;
  }
};

TEST_F(ParserTest, parse)
{
  parser->Parse("(1 + 2)");

  const auto &numbers = parser->getNumTokens().size();
  const auto &operations = parser->getOpTokens().size();
  EXPECT_EQ(numbers, 2);
  EXPECT_EQ(operations, 1);
}
