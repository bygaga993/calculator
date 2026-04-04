#include <gtest/gtest.h>

#include "../Operations.h"
#include "../ExpressionParser.h"
#include "../calc.h"

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

TEST(ExpressionTest, MulTest)
{
  MulOperation mul;
  EXPECT_EQ(mul.return_value(5, 2), 10);
  EXPECT_EQ(mul.return_value(-5, 2), -10);
  EXPECT_EQ(mul.return_value(-7, -3), 21);
  EXPECT_EQ(mul.return_value(2, 0), 0);
  EXPECT_EQ(mul.getPriority(), 2);
  EXPECT_FALSE(mul.isNumber());
}

TEST(ExpressionTest, DivTest)
{
  DivOperation div;
  EXPECT_EQ(div.return_value(5, 2), 2.5);
  EXPECT_EQ(div.return_value(-5, 2), -2.5);
  EXPECT_EQ(div.return_value(-3, -3), 1);
  EXPECT_THROW(div.return_value(2, 0), std::exception);
  EXPECT_EQ(div.getPriority(), 2);
  EXPECT_FALSE(div.isNumber());
}

