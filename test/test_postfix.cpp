#include "gtest.h"
#include "postfix.h"

TEST(TArithmeticExpression, can_create) {
	std::string str = "a+b";
	EXPECT_NO_THROW(TArithmeticExpression expr(str));
}

TEST(TArithmeticExpression, can_from_infix_to_postfix) {
	std::string str = "a+b";
	TArithmeticExpression expr(str);
	std::string tmp = "ab+";
	EXPECT_EQ(tmp, expr.GetPostfix());
}

TEST(TArithmeticExpression, can_get_infix) {
	std::string str = "a+b";
	TArithmeticExpression expr(str);
	EXPECT_NO_THROW(expr.GetInfix());
}

TEST(TArithmeticExpression, can_get_operands) {
	std::string str = "a+b";
	TArithmeticExpression expr(str);
	EXPECT_NO_THROW(expr.GetOperands());
}

TEST(TArithmeticExpression, can_correct_count) {
	std::string str = "a+b+c";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}, {operands[2], 3} };
	EXPECT_EQ(9, expr.Calculate(values));
}

TEST(TArithmeticExpression, can_correct_count_expression_with_parentheses) {
	std::string str = "a+(b-c)";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}, {operands[2], 3} };
	EXPECT_EQ(3, expr.Calculate(values));
}

TEST(TArithmeticExpression, can_correct_count_long_expression) {
	std::string str = "(a*b-c*(d+e+f))/h";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}, {operands[2], 3}, {operands[3], 0}, {operands[4], 2}, {operands[5], 1}, {operands[6], 2} };
	EXPECT_EQ(-2, expr.Calculate(values));
}

TEST(TArithmeticExpression, cant_count_expression_with_wrong_parentheses) {
	std::string str = "a+(b-c)*{d+e}";
	EXPECT_ANY_THROW(TArithmeticExpression expr(str));
}

TEST(TArithmeticExpression, cant_count_expression_with_wrong_operands) {
	std::string str = "5+3-4";
	EXPECT_ANY_THROW(TArithmeticExpression expr(str));
}

TEST(TArithmeticExpression, cant_count_expression_that_begin_with_sign) {
	std::string str = "+a*(c-d)";
	EXPECT_ANY_THROW(TArithmeticExpression expr(str));
}

TEST(TArithmeticExpression, cant_count_expression_with_twice_sign) {
	std::string str = "a+-b";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}};
	EXPECT_ANY_THROW(expr.Calculate(values));
}

TEST(TArithmeticExpression, can_count_expression) {
	std::string str = "a*(b-c+d)/(e+f)";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}, {operands[2], 3}, {operands[3], 4}, {operands[4], 1}, {operands[5], 2} };
	EXPECT_EQ(2, expr.Calculate(values));
}

TEST(TArithmeticExpression, cant_count_expression_with_twice_parentheses) {
	std::string str = "(a+b))";
	EXPECT_ANY_THROW(TArithmeticExpression expr(str));
}

TEST(TArithmeticExpression, cant_count_expression_without_signs) {
	std::string str = "abc";
	TArithmeticExpression expr(str);
	std::vector<char> operands = expr.GetOperands();
	std::map<char, int> values = { {operands[0], 1}, {operands[1], 5}, {operands[2], 3} };
	EXPECT_ANY_THROW(expr.Calculate(values));
}

TEST(TArithmeticExpression, cant_count_expression_without_operands) {
	std::string str = "(+-)";
	EXPECT_ANY_THROW(TArithmeticExpression expr(str));
}