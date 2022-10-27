#include <algorithm>
#include <iostream>

namespace MyExceptions {

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

}

class String {
  private:
    size_t size;
    size_t capacity;
    char* buffer;

  public:

    String() : size(0), capacity(0), buffer(nullptr)  {}

    String(char) = delete;

    String(size_t size, char value='\0') 
            : size(size)
            , capacity(size + 1)
            , buffer(new char[capacity]) {
        std::fill(buffer, buffer + size, value);
    }

    String(const char* source);

    String(const String& source);

    String& operator = (const String& other);

    String& operator += (const String& other);

    friend String operator + (String left, const String& right);


    bool operator == (const String& other) const;

    bool operator < (const String& other) const;

    bool operator > (const String& other) const;

    bool operator <= (const String& other) const;

    bool operator >= (const String& other) const;

    char& operator [] (size_t index);

    char operator [] (size_t index) const;

    size_t length() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    void push_back(char c);

    void pop_back();

    char& front();

    const char& front() const;

    char& back();

    const char& back() const;

    size_t find(const String& substring) const;

    size_t rfind(const String& substring) const;

    bool empty() const {
        return (size != 0);
    }

    void shring_to_fit();

    friend std::ostream& operator << (std::ostream& out, const String& data);

    friend std::istream& operator << (std::istream& in, const String& data);

    char* data();

    const char* data() const;

    ~String() {
        if (buffer != nullptr) delete[] buffer;
    }
};

