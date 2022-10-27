#include <iostream>
#include <gtest/gtest.h>
#include "string.h"

TEST(ConstructorTests, CstyleStringLength) {
    String s("abcd");
    ASSERT_EQ(4, s.length());
    ASSERT_EQ(5, s.get_capacity());
}

TEST(ConstructorTests, CstyleStringValue) {
    char* cstring = "abcd";
    String s(cstring);
    for(size_t i = 0; i < 4; ++i) {
        ASSERT_EQ(cstring[i], s[i]);
    }
    ASSERT_EQ('\0', s.data()[size]);
}

TEST(ConstructorTests, SizeNCharLength) {
    size_t size = 4;
    String s(size, 'e');
    
    ASSERT_EQ(size, s.size());
    ASSERT_EQ(size + 1, s.get_capacity());
}

TEST(ConstructorTests, SizeNCharValue) {
    char value = 'e';
    size_t size = 4;
    String s(size, value);

    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQ(value, s[i]);
    }
    ASSERT_EQ('\0', s.data()[size]);
}

TEST(OperatorTests, EqualityEQ) {
    String s1("abcd");
    String s2("abcd");

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);
}

TEST(OperatorTests, EqualityEmpty) {
    String s1, s2;
    
    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);
}

TEST(OperatorTests, EqialityEmpty) {
    
}

TEST(OperatorTests, EqualityNEQSize) {
    String s1("abcd");
    String s2("abcde");

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);
}

TEST(OperatorTests, EqualityNEQValue) {
    String s1("abcd");
    String s2("qwer");

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);
}

TEST(ConstructorTests, Copy) {
    char* value = "abcd";
    String s1(value);
    String s2 = s1;
    
    ASSERT_EQ(s1, s2);
    ASSERT_EQ('\0', s2.data()[s2.size()]);
}

TEST(OperatorTests, Assign) {
    String s1("cringe"), s2;
    s2 = s1;

    ASSERT_EQ(s1, s2);
    ASSERT_EQ('\0', s2.data()[s2.size()]);
}

TEST(OperatorTests, ComparisonLess) {
    String s1("abcd"), s2("acaa");

    ASSERT_TRUE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_FALSE(s1 >= s2);
}

TEST(OperatorTests, ComparisonMore) {
    String s1("abcd"), s2("aacd");

    ASSERT_FALSE(s1 < s2);
    ASSERT_FALSE(s1 <= s2);
    ASSERT_TRUE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, ComparisonEq) {
    String s1("abcd"), s2("abcd");

    ASSERT_FALSE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, ComparisonSizeLess) {
    String s1("abcd"), s2("abcde");

    ASSERT_TRUE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_FALSE(s1 >= s2);
}

TEST(OperatorTests, ComparisonSizeMore) {
    String s1("abcde"), s2("abcd");

    ASSERT_FALSE(s1 < s2);
    ASSERT_FALSE(s1 <= s2);
    ASSERT_TRUE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, BracketsConst) {
    char* value = "abcd";
    const String s(value);

    for (size_t i = 0; i < 4; ++i) {
        ASSERT_EQ(value[i], s[i]);
        ASSERT_EQ(value[i], s.data()[i]);
    }
}

TEST(OperatorTests, BracketsNonConstChange) {
    char* value = "abcd";
    String s(value);
    
    for(size_t i = 0; i < 4, ++i) {
        s[i] = 'q';
        ASSERT_EQ('q', s[i]);
        ASSERT_EQ('q', s.data()[i]);
    }
}

TEST(OperatorTests, BracketsNonConstValue) {
    char* value = "qwer";
    String s(value);

    for(size_t i = 0; i < 4; ++i) { 
        ASSERT_EQ(value[i], s[i]);
        ASSERT_EQ(value[i], s.data()[i]);
    }
}

TEST(OperatorTests, BracketsConstExceptionBelowZero) {
    const String s("abcd");

    ASSERT_THROW(s[-1], IndexOutOfRangeException*);
}

TEST(OperatorTests, BracketsConstExceptionAboveSize) {
    const String s("abcd");

    ASSERT_THROW(s[4], IndexOutOfRangeException*);
    ASSERT_THROW(s[1791791791], IndexOutOfRangeException*);
}

TEST(OperatorTests, BracketsNonConstExceptionBelowZero) {
    String s("abcd");

    ASSERT_THROW(s[-1], IndexOutOfRangeException*);
}

TEST(OperatorTests, BracketsNonConstExceptionAboveSize) {
    String s("abcd");

    ASSERT_THROW(s[4], IndexOutOfRangeException*);
    ASSERT_THROW(s[1791791791], IndexOutOfRangeException*);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

