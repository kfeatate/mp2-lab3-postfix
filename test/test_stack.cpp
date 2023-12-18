#include "stack.h"
#include "gtest.h"

TEST(Stack, can_create_stack_with_positive_length) {
	EXPECT_NO_THROW(Stack<int> stack(5));
}

TEST(Stack, cant_create_too_large_stack)
{
    EXPECT_ANY_THROW(Stack<int> stack(MAX_STACK_SIZE + 1));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
    EXPECT_ANY_THROW(Stack<int> stack(-5));
}

TEST(Stack, can_create_copied_stack)
{
    Stack<int> st(10);
    EXPECT_NO_THROW(Stack<int> st1(st));
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
    Stack<int> st(10);
    for (int i = 0; i < 10; i++) {
        st.push(i);
   }
    Stack<int> tmp(st);
    EXPECT_EQ(st, tmp);
}

TEST(Stack, can_push) {
    Stack<int> st(5);
    EXPECT_NO_THROW(st.push(1));
}

TEST(Stack, can_push_in_full_stack) {
    Stack<int> st(5);
    for (int i = 0; i <5 ; i++) {
        st.push(i);
    }
    EXPECT_NO_THROW(st.push(6));
}

TEST(Stack, can_show_top_element) {
    Stack<int> st(5);
    for (int i = 0; i < 5; i++) {
        st.push(i);
    }
    EXPECT_EQ(st.top(), 4);
}

TEST(Stack, cant_show_top_element_in_empty_stack) {
    Stack<int> st(5);
    EXPECT_ANY_THROW(st.top());
}

TEST(Stack, can_pop) {
    Stack<int> st(5);
    for (int i = 0; i < 5; i++) {
        st.push(i);
    }
    EXPECT_NO_THROW(st.pop());
}

TEST(Stack, cant_pop_empty_stack) {
    Stack<int> st(5);
    EXPECT_ANY_THROW(st.pop());
}

TEST(Stack, checking_for_emptiness_return_true) {
    Stack<int> st(5);
    EXPECT_EQ(st.empty(), 1);
}

TEST(Stack, checking_for_emptiness_return_false) {
    Stack<int> st(5);
    for (int i = 0; i < 5; i++) {
        st.push(i);
    }
    EXPECT_EQ(st.empty(), 0);
}

TEST(Stack, can_get_size) {
    Stack<int> st(5);
    EXPECT_EQ(st.size(), 5);
}

