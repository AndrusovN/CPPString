#include <algorithm>
#include <assert.h>
#include <cstring>
#include <iostream>

class BaseException {
  public:
    virtual void printError() const = 0;
};

class IndexOutOfRangeException : public BaseException {
    size_t requested_index;
    size_t max_index;

  public:

    IndexOutOfRangeException(size_t requested_index, size_t max_index) 
            : requested_index(requested_index)
            , max_index(max_index) {}


    void printError() const override {
        std::cerr << "Index out of range exception! " <<
                "Index should be in [0; " << max_index <<
                "), but " << requested_index << " is given" << std::endl;
    }
};

class EmptyStringCallException : public BaseException {
    public:

        void printError() const override {
            std::cerr << "Attempt to access elements of " << 
                "empty string caused an exception!" << std::endl;
        }
};

bool is_separating_character(char c) {
    return (c == '\n') ||
        (c == '\r') ||
        (c == '\0') ||
        (c == ' ');
}

class String {
  private:
    size_t data_size;
    size_t buffer_size;
    char* buffer;

    void resize_buffer(size_t new_buffer_size);

    void exception_if_wrong_index(size_t index) const;

    void exception_if_empty_string() const;

    bool matches_substring(const String& foreign, size_t begin_index) const;

    void swap(String& other);

  public:

    String();

    String(size_t size, char value='\0');

    //to prevent calls like String('A'), which will be interpreted as String(65, '\0');
    String(char) = delete;

    String(const char* source);

    String(const String& source);

    String& operator = (const String& source);

    String& operator = (const char* source);

    String& operator += (const String& other);

    String& operator += (char c);

    char& operator [] (size_t index);

    char operator [] (size_t index) const;

    char& at(size_t index);

    char at(size_t index) const;

    size_t length() const;

    char* data();

    const char* data() const;
    
    size_t size() const;

    size_t capacity() const;

    void push_back(char c);

    void pop_back();

    char& front();

    char front() const;

    char& back();

    char back() const;

    size_t find(const String& substring) const;

    size_t rfind(const String& substring) const;

    String substr(size_t from, size_t count) const;
    
    bool empty() const;

    void clear();

    void shrink_to_fit();

    ~String();
};

void String::resize_buffer(size_t new_buffer_size) {
    assert(new_buffer_size > data_size);

    char* new_buffer = new char[new_buffer_size];
    std::fill(new_buffer, new_buffer + new_buffer_size, '\0');
    std::copy(buffer, buffer + data_size, new_buffer);
    
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_buffer_size;
}

void String::exception_if_wrong_index(size_t index) const {
    // since index is size_t it's always >= 0 so check only upper bound
    if (data_size <= index) {
        throw new IndexOutOfRangeException(index, data_size);
    }
}

void String::exception_if_empty_string() const {
    if (empty()) {
        throw new EmptyStringCallException();
    }
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

String::String(): String(0, '\0') {}

String::String(size_t size, char value) 
        : data_size(size)
        , buffer_size(size + 1)
        , buffer(new char[buffer_size]) {
    
    std::fill(buffer, buffer + data_size, value);
    buffer[data_size] = '\0';
}

String::String(const char* source) 
        : data_size(strlen(source))
        , buffer_size(data_size + 1)
        , buffer(new char[buffer_size]) {
    
    std::copy(source, source + data_size, buffer);
    buffer[data_size] = '\0';
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

String& String::operator = (const char* source) {
    String temp(source);
    swap(temp);

    return *this;
}

String& String::operator += (const String& other) {
    size_t new_size = size() + other.size();
    // to have O(1) amortized complexity we have to increase 
    // at least twice data_size each reallocation
    new_size = std::max(new_size, data_size * 2);

    if (new_size > capacity()) {
        // one more byte for \0 at the end
        resize_buffer(new_size + 1);
    }

    std::copy(other.buffer, other.buffer + other.size(), buffer + data_size);
    data_size += other.size();

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
    buffer[data_size] = '\0';

    return *this;
}

String operator + (String left, const String& right) {
    return left += right;
}

String operator + (String left, char right) {
    return left += right;
}

String operator + (char left, const String& right) {
    String result(1, left);
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
    return !(left < right);
}

char& String::operator [] (size_t index) {
    return buffer[index];
}

// don't ban me please... it's not copypaste imho))
char String::operator [] (size_t index) const {
    return buffer[index];
}

char& String::at(size_t index) {
    exception_if_wrong_index(index);
    return buffer[index];
}

char String::at(size_t index) const {
    exception_if_wrong_index(index);
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
    return buffer_size - 1;
}

void String::push_back(char c) {
    *this += c;
}

void String::pop_back() {
    exception_if_empty_string();
    data_size--;
    buffer[data_size] = '\0';
}

char String::front() const {
    return (*this).at(0);
}

char& String::front() {
    return (*this).at(0);
}

char String::back() const {
    return (*this).at(size() - 1);
}

char& String::back() {
    return (*this).at(size() - 1);
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
    // now we have to use signed integer values because of i >= 0 check
    // so we don't need first check that substring size is leq size
    for (long long i = static_cast<long long>(size()) - static_cast<long long>(substring.size()); i >= 0; --i) {
        if (matches_substring(substring, i)) {
            return i;
        }
    }
    return size();
}

String String::substr(size_t from, size_t count) const {
    if (count == 0) return String(); 
    exception_if_wrong_index(from);
    exception_if_wrong_index(from + count - 1);
    if (from + count < from) throw new IndexOutOfRangeException(size() - from, count);
    
    String result(count, '\0');
    std::copy(buffer + from, buffer + from + count, result.buffer);
    return result;
}

bool String::empty() const {
    return size() == 0;
}

void String::clear() {
    std::fill(buffer, buffer + data_size, '\0');
    data_size = 0;
}

void String::shrink_to_fit() {
    resize_buffer(data_size + 1);
}

std::ostream& operator << (std::ostream& out, const String& data) {
    for(size_t i = 0; i < data.size(); ++i) {
        out << data[i];
    }
    return out;
}

std::istream& operator >> (std::istream& in, String& data) {
    data.clear();
    
    char input;
    while(in.get(input)) {
        if (is_separating_character(input)) break;
        data += input;
    }
    return in;
}

String::~String() {
    delete[] buffer;
}

