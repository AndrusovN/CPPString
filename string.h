#pragma once

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>

const char TERMINATE_SYMBOL = '\0';

class String {
  private:
    size_t data_size;
    size_t buffer_size;
    char* buffer;

    void resize_buffer(size_t new_buffer_size);

    bool matches_substring(const String& foreign, size_t begin_index) const;

    void swap(String& other);

    void set_terminate_at_end();

  public:

    String();

    // make this constructor explicit to prevent 
    // strange statements like: String s = 179;
    explicit String(size_t size, char value=TERMINATE_SYMBOL);

    // make this constructor explicit to prevent problems like:
    // interpreting "a" + 'b' as [String + char] or as [String + String]
    explicit String(char c);

    String(const char* source);

    String(const String& source);

    String& operator = (const String& source);

    String& operator += (const String& other);

    String& operator += (char c);

    char& operator [] (size_t index);

    const char& operator [] (size_t index) const;

    size_t length() const;

    char* data();

    const char* data() const;
    
    size_t size() const;

    size_t capacity() const;

    void push_back(char c);

    void pop_back();

    char& front();

    const char& front() const;

    char& back();

    const char& back() const;

    size_t find(const String& substring) const;

    size_t rfind(const String& substring) const;

    String substr(size_t from, size_t count) const;

    bool empty() const;

    void clear();

    void shrink_to_fit();

    ~String();
};

// The general idea: every incorrect call is UB
// I personally think that stable apps are better and
// I don't like leg-shooting paradigm, but if you ask...

void String::resize_buffer(size_t new_buffer_size) {
    assert(new_buffer_size > data_size);

    char* new_buffer = new char[new_buffer_size];
    std::copy(buffer, buffer + data_size, new_buffer);
    
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_buffer_size;
    set_terminate_at_end();
}

bool String::matches_substring(const String& foreign, size_t begin_index) const {
    assert(begin_index + foreign.size() <= size());

    for(size_t i = 0; i < foreign.size(); ++i) {
        if (buffer[i + begin_index] != foreign[i]) return false;
    }

    return true;
}

void String::swap(String& other) {
    std::swap(buffer, other.buffer);
    std::swap(buffer_size, other.buffer_size);
    std::swap(data_size, other.data_size);
}

void String::set_terminate_at_end() {
    buffer[size()] = TERMINATE_SYMBOL;
}

String::String(): String(0, TERMINATE_SYMBOL) {}

String::String(size_t size, char value) 
        : data_size(size)
        , buffer_size(size + 1)
        , buffer(new char[buffer_size]) {
    
    std::fill(buffer, buffer + data_size, value);
    set_terminate_at_end();
}

String::String(char c) : String(1, c) {}

String::String(const char* source) 
        : data_size(strlen(source))
        , buffer_size(data_size + 1)
        , buffer(new char[buffer_size]) {
    
    std::copy(source, source + data_size, buffer);
    set_terminate_at_end();
}

String::String(const String& source)
        : data_size(source.data_size)
        , buffer_size(source.buffer_size)
        , buffer(new char[buffer_size]) {

    std::copy(source.buffer, source.buffer + buffer_size, buffer);
}

String& String::operator = (const String& source) {
    if (&source == this) return *this;

    String temp = source;
    swap(temp);

    return *this;
}

String& String::operator += (const String& other) {
    size_t new_size = size() + other.size();
    // to have O(1) amortized complexity we have to increase 
    // at least twice data_size each reallocation
    new_size = std::max(new_size, data_size * 2);

    if (new_size > capacity()) {
        // one more byte for terminate character at the end
        resize_buffer(new_size + 1);
    }

    std::copy(other.buffer, other.buffer + other.size(), buffer + data_size);
    data_size += other.size();
    set_terminate_at_end();
    return *this;
}

/* There could be:
 * return *this += String(1, c);
 * But this generates String from char
 * therefore uses more memory allocation
 * So I decided to write a bit more code :)
 * */
String& String::operator += (char c) {
    if (capacity() == size()) {
        resize_buffer(buffer_size * 2);
    }
    buffer[data_size] = c;
    ++data_size;
    set_terminate_at_end();

    return *this;
}

String operator + (String left, const String& right) {
    return left += right;
}

String operator + (String left, char right) {
    return left += right;
}

String operator + (char left, const String& right) {
    String result(left);
    return result += right;
}

bool operator == (const String& left, const String& right) {
    if (left.size() != right.size()) return false;
    
    for (size_t i = 0; i < left.size(); ++i) {
        if (left[i] != right[i]) return false;
    }

    return true;
}

bool operator != (const String& left, const String& right) {
    return !(left == right);
}

bool operator < (const String& left, const String& right) {
    size_t min_size = std::min(left.size(), right.size());

    for(size_t i = 0; i < min_size; ++i) {
        if (left[i] < right[i]) return true;
        if (right[i] < left[i]) return false;
    }

    return left.size() < right.size();
}

bool operator > (const String& left, const String& right) {
    return right < left;
}

bool operator <= (const String& left, const String& right) {
    return !(left > right);
}

bool operator >= (const String& left, const String& right) {
    return right <= left;
}

char& String::operator [] (size_t index) {
    return buffer[index];
}

// don't ban me please... it's not copypaste imho))
const char& String::operator [] (size_t index) const {
    return buffer[index];
}

size_t String::length() const {
    return size();
}

const char* String::data() const {
    return buffer;
}

char* String::data() {
    return buffer;
}

size_t String::size() const {
    return data_size;
}

size_t String::capacity() const {
    // last byte is terminate symbol
    return buffer_size - 1;
}

void String::push_back(char c) {
    *this += c;
}

void String::pop_back() {
    data_size--;
    set_terminate_at_end();
}

const char& String::front() const {
    return buffer[0];
}

char& String::front() {
    return buffer[0];
}

const char& String::back() const {
    return buffer[size() - 1];
}

char& String::back() {
    return buffer[size() - 1];
}

size_t String::find(const String& substring) const {
    if (substring.size() > size()) return size();
    
    for (size_t i = 0; i <= size() - substring.size(); ++i) {
        if (matches_substring(substring, i)) {
            return i;
        }
    }
    return size();
} 

size_t String::rfind(const String& substring) const {
    // to prevent size_t overflow check loop condition with end_index, which is always >0
    // but it's easier to work with begin_index - that's why use 2 variables
    //
    // if substring is empty, on the first step size() will be returned
    for (size_t end_index = size(); end_index >= substring.size(); --end_index) {
        size_t begin_index = end_index - substring.size();
        if (matches_substring(substring, begin_index)) {
            return begin_index;
        }
    }
    return size();
}

String String::substr(size_t from, size_t count) const { 
    String result(count);       
    std::copy(buffer + from, buffer + from + count, result.buffer);
    return result;
}

bool String::empty() const {
    return size() == 0;
}

void String::clear() {
    data_size = 0;
    set_terminate_at_end();
}

void String::shrink_to_fit() {
    resize_buffer(data_size + 1);
}

std::ostream& operator << (std::ostream& out, const String& data) {
    out << data.data();
    return out;
}

std::istream& operator >> (std::istream& in, String& data) {
    data.clear();
    
    char input;
    while(!in.eof() && in.get(input)) {
        if (std::isspace(input)) break;
        data += input;
    }
    return in;
}

String::~String() {
    delete[] buffer;
}

