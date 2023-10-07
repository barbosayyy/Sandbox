#pragma once

#include <string>
#include <ostream>
#include <glew/glew.h>

#define FALSE	0
#define TRUE	1

// std::string wrapper
class String
{
private:
	std::string _string;

public:
	String() {}
	String(const char* str) : _string(str) {}
	String(const std::string& str) : _string(str) {}

	void append(String& str);
	void append(const std::string& str);
	char& at(int index);

	String operator+(const String& str) const {
		String temp;
		temp._string = this->_string + str._string;
		return temp;
	}
	String operator+(const char* str) const {
		String temp;
		temp._string = str + this->_string;
		return temp;
	}
	String operator+=(const String& str) {
		this->_string += str._string;
	}
	String operator+=(const int& value) {
		this->_string += std::to_string(value);
	}
	bool operator==(const String& str) const{
		return this->_string == str._string;
	}
	friend std::ostream& operator<<(std::ostream& os, const String& str) {
		os << str._string;
		return os;
	}

	const char* c_str() const {
		return _string.c_str();
	}

	operator std::string() const{
		return _string;
	}
};