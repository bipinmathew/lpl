#include "gtest/gtest.h"

EXPECT_EQ(3,parse("1+2"));
EXPECT_EQ(7,parse("1+2*3"));
EXPECT_EQ(7,parse("1+2*3.0"));
EXPECT_EQ(21,parse("(1+2)*(3+4)"));
EXPECT_EQ(14,parse("(1*2)+(3*4)"));
EXPECT_EQ(10,parse("9+(1+2)/0"));
EXPECT_EQ(10,parse("+++"));
EXPECT_EQ(6,parse("3+++3"));
EXPECT_EQ(3,parse("1+2"));
EXPECT_EQ(6,parse("1+2+3"));
EXPECT_EQ(7,parse("3+4.0"));
EXPECT_EQ(11,parse("5.0+6"));
EXPECT_EQ(2,parse("1*2"));
EXPECT_EQ(6,parse("1*2*3"));
EXPECT_EQ(12,parse("3*4.0"));
EXPECT_EQ(30,parse("5.0*6"));
