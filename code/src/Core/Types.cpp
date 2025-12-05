#include "Types.h"

namespace Sb {

	void String::append(const std::string& str)
	{
		this->_string += str;
	}

	char& String::at(int index)
	{
		return this->_string.at(index);
	}

	bool String::empty()
	{
		return this->_string.empty();
	}
}