#pragma once
#include <stack.h>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <stdexcept>

//template <typename T>
class TArithmeticExpression {
	std:: string infix;
	std:: string postfix;
	std:: vector<char> lexems;
	std:: map<char, int> priority;
	std:: map<char, int> operands;

	void Parse();
	void ToPostfix();
public:
	TArithmeticExpression(std::string infx) {
		infix = infx;
		priority = { {'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
		Parse();
		ToPostfix();
	}
	std::string GetInfix() {
		return infix;
	}
	std::string GetPostfix() {
		return postfix;
	}
	std::vector<char> GetOperands();
	int Calculate(const std::map<char, int>& values);
};

void TArithmeticExpression::Parse() {
	for (char c : infix) {
		lexems.push_back(c);
	}
}

void TArithmeticExpression::ToPostfix() {
	Stack<char> st;
	char elem;
	for (char item : lexems) {
		switch (item) {
		case '(':
			st.push(item);
			break;
		case ')':
			if (st.empty()) {
				throw "wrong )";
			}
			elem = st.top();
			st.pop();
			while (elem != '(') {
				postfix += elem;
				elem = st.top();
				st.pop();
			}
			break;
		case '+': case'-': case'*': case'/':
			if (postfix.empty()) {
				throw "incorrect sequence";
			}
			while (!st.empty()) {
				elem = st.top();
				st.pop();
				if (priority[item] <= priority[elem]) {
					postfix += elem;
				}
				else {
					st.push(elem);
					break;
				}
			}
			st.push(item);
			break;
		default:
			if (isalpha(item)) {
				operands.insert({ item, 0 });//??
				postfix += item;
			}
			else throw "wrong lexem";
		}
	}
	while (!st.empty()) {
		elem = st.top();
		st.pop();
		postfix += elem;
	}
}

std::vector<char> TArithmeticExpression:: GetOperands() {
	if (operands.empty()) {
		throw "no operands";
	}
	std::vector<char> op;
	for (const auto& item : operands) {
		op.push_back(item.first);
	}
	return op;
}


int TArithmeticExpression::Calculate(const std::map<char, int>& values) {
	for (auto& val : values) {
		try {
			operands.at(val.first) = val.second;
		}
		catch (std::out_of_range& el) {};
	}
	Stack<int> st;
	int leftOp, rightOp;
	for (char lexem : postfix) {
		switch (lexem) {
		case '+':
			if (st.size() < 2) {
				throw "incorrect sequence";
			}
			rightOp = st.top();
			st.pop();
			leftOp = st.top();
			st.pop();
			st.push(rightOp + leftOp);
			break;
		case '-':
			if (st.size() < 2) {
				throw "incorrect sequence";
			}
			rightOp = st.top();
			st.pop();
			leftOp = st.top();
			st.pop();
			st.push(leftOp - rightOp);
			break;
		case '*':
			if (st.size() < 2) {
				throw "incorrect sequence";
			}
			rightOp = st.top();
			st.pop();
			leftOp = st.top();
			st.pop();
			st.push(leftOp * rightOp);
			break;
		case '/':
			if (st.size() < 2) {
				throw "incorrect sequence";
			}
			rightOp = st.top();
			st.pop();
			leftOp = st.top();
			st.pop();
			st.push(leftOp / rightOp);
			break;
		default:
			st.push(operands[lexem]);
		}
	}
	int res = st.top();
	st.pop();
	if (st.empty()==0) {
		throw "incorrect sequence";
	}
	return res;
}