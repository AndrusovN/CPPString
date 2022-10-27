#include <iostream>
#include <gtest/gtest.h>
#include "string.h"

void CheckLastSymbol(const String& s) {
    ASSERT_EQ('\0', s.data()[s.size()])
}

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
    check_last_symbol();
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
    check_last_symbol();
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
    check_last_symbol(s2);
}

TEST(OperatorTests, Assign) {
    String s1("cringe"), s2;
    s2 = s1;

    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
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

TEST(OperatorTests, PlusEqTwoNotEmpty) {
    String s1("ab"), s2("oba");
    s1 += s2;

    ASSERT_EQ(String("aboba"), s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqSecondEmpty) {
    String s1("cringe"), s2;
    s1 += s2;

    ASSERT_EQ(String("cringe"), s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqFirstEmpty) {
    String s1, s2("some");
    s1 += s2;

    ASSERT_EQ(s2, s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqTwoEmpty) {
    String s1, s2;
    s1 += s2;

    ASSERT_EQ(s2, s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqSame) {
    String s1("aba");
    s1 += s1;

    ASSERT_EQ(String("abaaba"), s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusTwoNotEmpty) {
    String s1("ab"), s2("oba");

    auto result = s1 + s2;
    ASSERT_EQ(String("aboba"), result);
    check_last_symbol(result);
}

TEST(OperatorTests, PlusSame) {
    String s1("aba");

    auto result = s1 + s1;
    ASSERT_EQ(String("abaaba"), result);
    check_last_symbol(result);
}

TEST(OperatorTests, PlusEmpty) {
    String s1("aba"), s2;

    auto result1 = s1 + s2;
    ASSERT_EQ(s1, result1);
    check_last_symbol(result1);
    
    auto result2 = s2 + s1;
    ASSERT_EQ(s1, result2);
    check_last_symbol(result2);
}

TEST(OperatorTests, PlusChar) {
    String s("abob");
    char c = 'a';

    ASSERT_EQ(String("aboba"), s + c);
    ASSERT_EQ(String("aabob"), c + s);
    check_last_symbol(s + c);
    check_last_symbol(c + s);
}

TEST(OperatorTests, PlusCharEmptyString) {
    String s;
    char c = 'a';

    ASSERT_EQ(String("a"), s + c);
    ASSERT_EQ(String("a"), c + s);
    check_last_symbol(s + c);
    check_last_symbol(c + s);
}

TEST(OperatorTests, PlusCharTwice) {
    String s("ab");

    auto result1 = s + 'b' + 'a';
    ASSERT_EQ(String("abba"), result1);
    check_last_symbol(result1);

    auto result2 = 'b' + ('a' + s);
    ASSERT_EQ(String("baab"), result2);
    check_last_symbol(result2);
}

TEST(OperatorTests, PlusEqChar) {
    String s("cring");
    s += 'e';

    ASSERT_EQ(String("cringe"), s);
    check_last_symbol(s);
}

TEST(OperatorTests, PlusEqCharEmpty) {
    String s;
    s += 'a';

    ASSERT_EQ(String("a"), s);
    check_last_symbol(s);
}

TEST(OperatorTests, PlusEqTwice) {
    String s1("ab"), s2("ob"), s3("a");
    
    (s1 += s2) += s3;

    ASSERT_EQ(String("aboba"), s1);
    check_last_symbol(s1);
}

TEST(MethodTests, LengthEmpty) {
    String s;

    ASSERT_EQ(0, s.length());
}

TEST(MethodTests, LengthFull) {
    String s("cringe");

    ASSERT_EQ(6, s.length());
}

TEST(MethodTests, PushBack) {
    String s("cring");
    s.push_back('e');

    ASSERT_EQ(String("cringe"), s);
    check_last_symbol(s);
}

TEST(MethodTests, PushBackNull) {
    String s("cringe");
    s.push_back('\0');

    String s_check("cringea");
    s[6] = '\0';
    String s_wrong("cringe");
    ASSERT_EQ(s_check, s);
    ASSERT_NEQ(s_wrong, s);
    check_last_symbol(s);
}

TEST(MethodTests, PushBackEmpty) {
    String s;
    s.push_back('c');

    ASSERT_EQ(String("c"), s);
    check_last_symbol(s);
}

TEST(MethodTests, PopBack) {
    String s("cringea");
    s.pop_back();

    ASSERT_EQ(String("cringe"), s);
    check_last_symbol(s);
}

TEST(MethodTests, PopBackEmpty) {
    String s;
    ASSERT_THROW(s.pop_back(), EmptyStringCallException*);
}

TEST(MethodTests, FrontConst) {
    const String s("cringe");

    ASSERT_EQ('c', s.front());
}

TEST(MethodTests, FrontConstEmpty) {
    const String s;

    ASSERT_THROW(s.front(), EmptyStringCallException*);
}

TEST(MethodTests, Front) {
    String s("cringe");

    ASSERT_EQ('c', s.front());
}

TEST(MethodTests, FrontChange) {
    String s("kringe");
    s.front() = 'c';

    ASSERT_EQ(String("cringe"), s);
}

TEST(MethodTests, FrontEmpty) {
    String s;

    ASSERT_THROW(s.front(), EmptyStringCallException*);
}

TEST(MethodTests, BackConst) {
    String s("cringe");

    ASSERT_EQ('e', s.back());
    check_last_symbol(s);
}

TEST(MethodTests, BackConstEmpty) {
    String s;

    ASSERT_THROW(s.back(), EmptyStringCallException*);
}

TEST(MethodTests, Back) {
    String s("cringe");

    ASSERT_EQ('e', s.back());
    check_last_symbol(s);
}

TEST(MethodTests, BackEmpty) {
    String s;

    ASSERT_THROW(s.back(), EmptyStringCallException*);
}

TEST(MethodTests, BackChange) {
    String s("cringa");
    s.back() = 'e';

    ASSERT_EQ(String("cringe"), s);
    check_last_symbol(s);
}

TEST(MethodTests, FindSingle) {
    String s("test");

    ASSERT_EQ(1, s.find(String("es")));
}

TEST(MethodTests, FindMultiple) {
    String s("aaaaa");
    
    ASSERT_EQ(0, s.find(String("a")));
}

TEST(MethodTests, FindNone) {
    String s("test");

    ASSERT_EQ(4, s.find(String("aboba")));
}

TEST(MethodTests, RFindSingle) {
    String s("test");

    ASSERT_EQ(1, s.rfind(String("es")));
}

TEST(MethodTests, RFindMultiple) {
    String s("aaaaa");

    ASSERT_EQ(4, s.rfind(String("a")));
}

TEST(MethodTests, RFindNone) {
    String s("test");

    ASSERT_EQ(4, s.rfind(String("aboba")));
}

TEST(MethodTests, Substr) {
    String s("test");
    
    auto result = s.substr(1, 2);
    ASSERT_EQ(String("es"), result);
    check_last_symbol(result);
}

TEST(MethodTests, SubstrEmpty) {
    String s("test");

    auto result = s.substr(1, 0);
    ASSERT_EQ(String(), result);
    check_last_symbol(result);
}

TEST(MethodTests, SubstrOnEmpty) {
    String s;

    ASSERT_ANY_THROW(s.substr(0, 1));
}

TEST(MethodTests, SubstrEmptyOnEmpty) {
    String s;

    ASSERT_NO_THROW(s.substr(0, 0));
    
    auto result = s.substr(0, 0);
    ASSERT_EQ(String(), result);
    check_last_symbol(result);
}

TEST(MethodTests, SubstrEmptyOnEmptyNotZero) {
    String s;

    ASSERT_ANY_THROW(s.substr(1, 0));
}

TEST(MethodTests, SubstrNegative) {
    String s("test");

    ASSERT_ANY_THROW(s.substr(2, -1));
}

TEST(MethodTests, SubstrTooLong) {
    String s("test");

    ASSERT_THROW(s.substr(1, 4), IndexOutOfRangeException*);
}

TEST(MethodTests, SubstrFromNegative) {
    String s("test");

    ASSERT_THROW(s.substr(-1, 2), IndexOutOfRangeException*);
}

TEST(MethodTests, EmptyFalse) {
    String s("test");

    ASSERT_FALSE(s.empty());
}

TEST(MethodTests, EmptyTrue) {
    String s;

    ASSERT_TRUE(s.empty());
}

TEST(MethodTests, EmptyFromEmptyCharset) {
    String s("");

    ASSERT_TRUE(s.empty());
}

TEST(MethodTests, Clear) {
    String s("test");
    s.clear();

    ASSERT_TRUE(s.empty());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.get_capacity(), 5);
    check_last_symbol(s);
}

TEST(MethodTests, ClearEmpty) {
    String s;
    ASSERT_NO_THROW(s.clear());
    s.clear();

    ASSERT_TRUE(s.empty());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.get_capacity(), 0);
    check_last_symbol(s);
}

TEST(MethodTests, ShrinkToFit) {
    String s("test");
    s.push_back('c');
    s.shrink_to_fit();

    ASSERT_EQ(6, s.get_capacity());
    ASSERT_EQ(String("testc"), s);
    ASSERT_EQ(s.size(), s.capacity());
    check_last_symbol(s);
}

TEST(MethodTests, ShrinkToFitEmpty) {
    String s;
    s.shrink_to_fit();

    ASSERT_EQ(0, s.get_capacity());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.size(), s.capacity());
    check_last_symbol(s);
}

TEST(MethodTests, Data) {
    String s1("test");
    String s2(s1.data());

    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

TEST(MethodTests, DataTwice) {
    String s("test");
    char* data1 = s.data();
    char* data2 = s.data();

    ASSERT_EQUALS(data1, data2);
}

TEST(MethodTests, Size) {
    String s("test");

    ASSERT_EQ(4, s.size());
}

TEST(MethodTests, SizeEmpty) {
    String s;

    ASSERT_EQ(0, s.size());
}

TEST(MethodTests, SizeExtended) {
    String s("test");
    s.push_back('c');

    ASSERT_EQ(5, s.size());
}

TEST(MethodTests, Capacity) {
    String s("cringe");

    ASSERT_EQ(6, s.capacity());
}

TEST(MethodTests, CapacityEmpty) {
    String s;

    ASSERT_EQ(0, s.capacity());
}

TEST(MethodTests, CapacityExtended) {
    String s("test");
    s.push_back('c');

    ASSERT_TRUE(s.size() < s.capacity());
}

TEST(IOTests, InputOneWord) {
    std::stringstream simulation;
    const char* text = "test";
    simulation << text;
    String s;
    simulation >> s;

    ASSERT_EQ(String(text), s);
    check_last_symbol(s);
}

TEST(IOTests, InputTwoWords) {
    std::stringstream simulation;
    simulation << "this is";
    String s1, s2;
    simulation >> s1 >> s2;

    ASSERT_EQ(String("this"), s1);
    ASSERT_EQ(String("is"), s2);
    check_last_symbol(s1);
    check_last_symbol(s2);
}

TEST(IOTests, Output) {
    std::stringstream simulation;
    String s1("mytest");
    simulation << s1;

    String s2;
    simulation >> s2;
    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

