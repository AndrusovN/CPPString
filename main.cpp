#include <iostream>
#include <gtest/gtest.h>
#include <new>
#include <string>
#include "string.h"

int new_count = 0;

void* operator new[](size_t size) {
    ++new_count;
    void* p = malloc(size);
    if (p == nullptr) throw std::bad_alloc();
    return p;
}

void check_last_symbol(const String& s) {
    ASSERT_EQ('\0', s.data()[s.size()]);
}

TEST(ConstructorTests, CstyleStringLength) {
    String s = "abcd";
    ASSERT_EQ(4, s.length());
    ASSERT_EQ(4, s.capacity());
}

TEST(ConstructorTests, CstyleStringValue) {
    const char* cstring = "abcd";
    String s(cstring);
    for(size_t i = 0; i < 4; ++i) {
        ASSERT_EQ(cstring[i], s[i]);
    }
    check_last_symbol(s);
}

TEST(ConstructorTests, SizeNCharLength) {
    size_t size = 4;
    String s(size, 'e');
    
    ASSERT_EQ(size, s.size());
    ASSERT_EQ(size, s.capacity());
}

TEST(ConstructorTests, SizeNCharValue) {
    char value = 'e';
    size_t size = 4;
    String s(size, value);

    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQ(value, s[i]);
    }
    check_last_symbol(s);
}

TEST(OperatorTests, EqualityEQ) {
    String s1 = "abcd";
    String s2 = "abcd";

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);
}

TEST(OperatorTests, EqualityEmpty) {
    String s1, s2;
    
    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);
}

TEST(OperatorTests, EqualityNEQSize) {
    String s1 = "abcd";
    String s2 = "abcde";

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);
}

TEST(OperatorTests, EqualityNEQValue) {
    String s1 = "abcd";
    String s2 = "qwer";

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);
}

TEST(ConstructorTests, Copy) {
    const char* value = "abcd";
    String s1(value);
    String s2 = s1;
    
    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

TEST(OperatorTests, Assign) {
    String s1 = "cringe", s2;
    s2 = s1;

    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

TEST(OperatorTests, AssignSelf) {
    String s1 = "cringe", s2 = s1;
    s2 = s2;
    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

TEST(OperatorTests, AssignCharArr) {
    String s1 = "test";
    s1 = "cringe";

    ASSERT_EQ("cringe", s1);
}

TEST(OperatorTests, ComparisonLess) {
    String s1 = "abcd", s2 = "acaa";

    ASSERT_TRUE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_FALSE(s1 >= s2);
}

TEST(OperatorTests, ComparisonMore) {
    String s1 = "abcd", s2 = "aacd";

    ASSERT_FALSE(s1 < s2);
    ASSERT_FALSE(s1 <= s2);
    ASSERT_TRUE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, ComparisonEq) {
    String s1 = "abcd", s2 = "abcd";

    ASSERT_FALSE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, ComparisonSizeLess) {
    String s1 = "abcd", s2 = "abcde";

    ASSERT_TRUE(s1 < s2);
    ASSERT_TRUE(s1 <= s2);
    ASSERT_FALSE(s1 > s2);
    ASSERT_FALSE(s1 >= s2);
}

TEST(OperatorTests, ComparisonSizeMore) {
    String s1 = "abcde", s2 = "abcd";

    ASSERT_FALSE(s1 < s2);
    ASSERT_FALSE(s1 <= s2);
    ASSERT_TRUE(s1 > s2);
    ASSERT_TRUE(s1 >= s2);
}

TEST(OperatorTests, BracketsConst) {
    const char* value = "abcd";
    const String s(value);

    for (size_t i = 0; i < 4; ++i) {
        ASSERT_EQ(value[i], s[i]);
        ASSERT_EQ(value[i], s.data()[i]);
    }
}

TEST(OperatorTests, BracketsNonConstChange) {
    const char* value = "abcd";
    String s(value);
    
    for(size_t i = 0; i < 4; ++i) {
        s[i] = 'q';
        ASSERT_EQ('q', s[i]);
        ASSERT_EQ('q', s.data()[i]);
    }
}

TEST(OperatorTests, BracketsNonConstValue) {
    const char* value = "qwer";
    String s(value);

    for(size_t i = 0; i < 4; ++i) { 
        ASSERT_EQ(value[i], s[i]);
        ASSERT_EQ(value[i], s.data()[i]);
    }
}

TEST(OperatorTests, AtConstExceptionBelowZero) {
    const String s = "abcd";

    ASSERT_THROW(s.at(-1), IndexOutOfRangeException*);
}

TEST(OperatorTests, AtConstExceptionAboveSize) {
    const String s = "abcd";

    ASSERT_THROW(s.at(4), IndexOutOfRangeException*);
    ASSERT_THROW(s.at(1791791791), IndexOutOfRangeException*);
}

TEST(OperatorTests, AtNonConstExceptionBelowZero) {
    String s = "abcd";

    ASSERT_THROW(s.at(-1), IndexOutOfRangeException*);
}

TEST(OperatorTests, AtNonConstExceptionAboveSize) {
    String s = "abcd";

    ASSERT_THROW(s.at(4), IndexOutOfRangeException*);
    ASSERT_THROW(s.at(1791791791), IndexOutOfRangeException*);
}

TEST(OperatorTests, PlusEqTwoNotEmpty) {
    String s1 = "ab", s2 = "oba";
    s1 += s2;

    ASSERT_EQ("aboba", s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqSecondEmpty) {
    String s1 = "cringe", s2;
    s1 += s2;

    ASSERT_EQ("cringe", s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusEqFirstEmpty) {
    String s1, s2 = "some";
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
    String s1 = "aba";
    s1 += s1;

    ASSERT_EQ("abaaba", s1);
    check_last_symbol(s1);
}

TEST(OperatorTests, PlusTwoNotEmpty) {
    String s1 = "ab", s2 = "oba";

    auto result = s1 + s2;
    ASSERT_EQ("aboba", result);
    check_last_symbol(result);
}

TEST(OperatorTests, PlusSame) {
    String s1 = "aba";

    auto result = s1 + s1;
    ASSERT_EQ("abaaba", result);
    check_last_symbol(result);
}

TEST(OperatorTests, PlusEmpty) {
    String s1 = "aba", s2;

    auto result1 = s1 + s2;
    ASSERT_EQ(s1, result1);
    check_last_symbol(result1);
    
    auto result2 = s2 + s1;
    ASSERT_EQ(s1, result2);
    check_last_symbol(result2);
}

TEST(OperatorTests, PlusChar) {
    String s = "abob";
    char c = 'a';

    ASSERT_EQ("aboba", s + c);
    ASSERT_EQ("aabob", c + s);
    check_last_symbol(s + c);
    check_last_symbol(c + s);
}

TEST(OperatorTests, PlusCharEmptyString) {
    String s;
    char c = 'a';

    ASSERT_EQ("a", s + c);
    ASSERT_EQ("a", c + s);
    check_last_symbol(s + c);
    check_last_symbol(c + s);
}

TEST(OperatorTests, PlusCharTwice) {
    String s = "ab";

    auto result1 = s + 'b' + 'a';
    ASSERT_EQ("abba", result1);
    check_last_symbol(result1);

    auto result2 = 'b' + ('a' + s);
    ASSERT_EQ("baab", result2);
    check_last_symbol(result2);
}

TEST(OperatorTests, PlusEqChar) {
    String s = "cring";
    s += 'e';

    ASSERT_EQ("cringe", s);
    check_last_symbol(s);
}

TEST(OperatorTests, PlusEqCharEmpty) {
    String s;
    s += 'a';

    ASSERT_EQ("a", s);
    check_last_symbol(s);
}

TEST(OperatorTests, PlusEqTwice) {
    String s1 = "ab", s2 = "ob", s3 = "a";
    
    (s1 += s2) += s3;

    ASSERT_EQ("aboba", s1);
    check_last_symbol(s1);
}

TEST(MethodTests, LengthEmpty) {
    String s;

    ASSERT_EQ(0, s.length());
}

TEST(MethodTests, LengthFull) {
    String s = "cringe";

    ASSERT_EQ(6, s.length());
}

TEST(MethodTests, PushBack) {
    String s = "cring";
    s.push_back('e');

    ASSERT_EQ("cringe", s);
    check_last_symbol(s);
}

TEST(MethodTests, PushBackNull) {
    String s = "cringe";
    s.push_back('\0');

    String s_check = "cringea";
    s_check[6] = '\0';
    String s_wrong = "cringe";
    ASSERT_EQ(s_check, s);
    ASSERT_NE(s_wrong, s);
    check_last_symbol(s);
}

TEST(MethodTests, PushBackEmpty) {
    String s;
    s.push_back('c');

    ASSERT_EQ("c", s);
    check_last_symbol(s);
}

TEST(MethodTests, PopBack) {
    String s = "cringea";
    s.pop_back();

    ASSERT_EQ("cringe", s);
    check_last_symbol(s);
}

TEST(MethodTests, PopBackEmpty) {
    String s;
    ASSERT_THROW(s.pop_back(), EmptyStringCallException*);
}

TEST(MethodTests, FrontConst) {
    const String s = "cringe";

    ASSERT_EQ('c', s.front());
}

TEST(MethodTests, FrontConstEmpty) {
    const String s;

    ASSERT_ANY_THROW(s.front());
}

TEST(MethodTests, Front) {
    String s = "cringe";

    ASSERT_EQ('c', s.front());
}

TEST(MethodTests, FrontChange) {
    String s = "kringe";
    s.front() = 'c';

    ASSERT_EQ("cringe", s);
}

TEST(MethodTests, FrontEmpty) {
    String s;

    ASSERT_ANY_THROW(s.front());
}

TEST(MethodTests, BackConst) {
    const String s = "cringe";

    ASSERT_EQ('e', s.back());
    check_last_symbol(s);
}

TEST(MethodTests, BackConstEmpty) {
    const String s;

    ASSERT_ANY_THROW(s.back());
}

TEST(MethodTests, Back) {
    String s = "cringe";

    ASSERT_EQ('e', s.back());
    check_last_symbol(s);
}

TEST(MethodTests, BackEmpty) {
    String s;

    ASSERT_ANY_THROW(s.back());
}

TEST(MethodTests, BackChange) {
    String s = "cringa";
    s.back() = 'e';

    ASSERT_EQ("cringe", s);
    check_last_symbol(s);
}

TEST(MethodTests, FindSingle) {
    String s = "test";

    ASSERT_EQ(1, s.find("es"));
}

TEST(MethodTests, FindMultiple) {
    String s = "aaaaa";
    
    ASSERT_EQ(0, s.find("a"));
}

TEST(MethodTests, FindNone) {
    String s = "test";

    ASSERT_EQ(4, s.find("aboba"));
}

TEST(MethodTests, FindNoneSmall) {
    String s = "test";

    ASSERT_EQ(4, s.find("q"));
}

TEST(MethodTests, FindEmpty) {
    String s = "test";

    ASSERT_EQ(0, s.find(String()));
}

TEST(MethodTests, RFindSingle) {
    String s = "test";

    ASSERT_EQ(1, s.rfind("es"));
}

TEST(MethodTests, RFindMultiple) {
    String s = "aaaaa";

    ASSERT_EQ(4, s.rfind("a"));
}

TEST(MethodTests, RFindNone) {
    String s = "test";

    ASSERT_EQ(4, s.rfind("aboba"));
}

TEST(MethodTests, RFindNoneSmall) {
    String s = "test";

    ASSERT_EQ(4, s.rfind("q"));
}

TEST(MethodTests, RFindEmpty) {
    String s = "test";

    ASSERT_EQ(4, s.rfind(String()));
}

TEST(MethodTests, Substr) {
    String s = "test";
   
    new_count = 0; 
    auto result = s.substr(1, 2);
    ASSERT_EQ(1, new_count);
    ASSERT_EQ("es", result);
    check_last_symbol(result);
}

TEST(MethodTests, SubstrEmpty) {
    String s = "test";

    new_count = 0;
    auto result = s.substr(1, 0);
    ASSERT_EQ(1, new_count);
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
    
    new_count = 0;
    auto result = s.substr(0, 0);
    ASSERT_EQ(1, new_count);
    ASSERT_EQ(String(), result);
    check_last_symbol(result);
}

TEST(MethodTests, SubstrEmptyOnEmptyNotZero) {
    String s;

    ASSERT_NO_THROW(s.substr(1, 0));
}

TEST(MethodTests, SubstrNegative) {
    String s = "test";

    ASSERT_ANY_THROW(s.substr(2, -1));
}

TEST(MethodTests, SubstrTooLong) {
    String s = "test";

    ASSERT_THROW(s.substr(1, 4), IndexOutOfRangeException*);
}

TEST(MethodTests, SubstrFromNegative) {
    String s = "test";

    ASSERT_THROW(s.substr(-1, 2), IndexOutOfRangeException*);
}

TEST(MethodTests, EmptyFalse) {
    String s = "test";

    ASSERT_FALSE(s.empty());
}

TEST(MethodTests, EmptyTrue) {
    String s;

    ASSERT_TRUE(s.empty());
}

TEST(MethodTests, EmptyFromEmptyCharset) {
    String s = "";

    ASSERT_TRUE(s.empty());
}

TEST(MethodTests, Clear) {
    String s = "test";
    s.clear();

    ASSERT_TRUE(s.empty());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.capacity(), 4);
    check_last_symbol(s);
}

TEST(MethodTests, ClearEmpty) {
    String s;
    ASSERT_NO_THROW(s.clear());
    s.clear();

    ASSERT_TRUE(s.empty());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.capacity(), 0);
    check_last_symbol(s);
}

TEST(MethodTests, ShrinkToFit) {
    String s = "test";
    s.push_back('c');
    s.shrink_to_fit();

    ASSERT_EQ("testc", s);
    ASSERT_EQ(s.size(), s.capacity());
    check_last_symbol(s);
}

TEST(MethodTests, ShrinkToFitEmpty) {
    String s;
    s.shrink_to_fit();

    ASSERT_EQ(0, s.capacity());
    ASSERT_EQ(String(), s);
    ASSERT_EQ(s.size(), s.capacity());
    check_last_symbol(s);
}

TEST(MethodTests, Data) {
    String s1 = "test";
    String s2(s1.data());

    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

TEST(MethodTests, DataTwice) {
    String s = "test";
    char* data1 = s.data();
    char* data2 = s.data();

    ASSERT_EQ(data1, data2);
}

TEST(MethodTests, Size) {
    String s = "test";

    ASSERT_EQ(4, s.size());
}

TEST(MethodTests, SizeEmpty) {
    String s;

    ASSERT_EQ(0, s.size());
}

TEST(MethodTests, SizeExtended) {
    String s = "test";
    s.push_back('c');

    ASSERT_EQ(5, s.size());
}

TEST(MethodTests, Capacity) {
    String s = "cringe";

    ASSERT_EQ(6, s.capacity());
}

TEST(MethodTests, CapacityEmpty) {
    String s;

    ASSERT_EQ(0, s.capacity());
}

TEST(MethodTests, CapacityExtended) {
    String s = "test";
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

    ASSERT_EQ("this", s1);
    ASSERT_EQ("is", s2);
    check_last_symbol(s1);
    check_last_symbol(s2);
}

TEST(IOTests, Output) {
    std::stringstream simulation;
    String s1 = "mytest";
    simulation << s1;

    String s2;
    simulation >> s2;
    ASSERT_EQ(s1, s2);
    check_last_symbol(s2);
}

std::streambuf* move_cerr_to_other_stringstream(std::stringstream& other) {
    std::streambuf* old = std::cerr.rdbuf();
    std::cerr.rdbuf(other.rdbuf());
    return old;
}

TEST(ExceptionTests, IndexOutOfRangePrint) {
    try {
        throw new IndexOutOfRangeException(10, 5);
    } catch(IndexOutOfRangeException* e) {
        std::stringstream buffer;
        auto oldbuf = move_cerr_to_other_stringstream(buffer);

        e->printError();
        std::string error(std::istreambuf_iterator<char>(buffer), {});

        std::cerr.rdbuf(oldbuf);

        ASSERT_EQ("Index out of range exception! Index should be in [0; 5), but 10 is given\n", error);
    }
}

TEST(ExceptionTests, EmptyStringCallPrint) {
    try {
        throw new EmptyStringCallException();
    } catch(EmptyStringCallException* e) {
        std::stringstream buffer;
        auto oldbuf = move_cerr_to_other_stringstream(buffer);

        e->printError();
        std::string error(std::istreambuf_iterator<char>(buffer), {});

        std::cerr.rdbuf(oldbuf);
        ASSERT_EQ("Attempt to access elements of empty string caused an exception!\n", error);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

