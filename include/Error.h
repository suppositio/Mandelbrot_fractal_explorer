#pragma once
#include <exception>
#include <string>

namespace suppositio {

class Error : public std::exception {
public:
	Error(const std::string& error_message) :
		error_message_{ error_message } {}
	virtual const char* what() const override {
		return error_message_.c_str();
	}
	virtual ~Error() = default;
private:
	std::string error_message_;
};

class Non_fatal_error : public Error {
public:
	Non_fatal_error(const std::string& error_message) : Error(error_message) {}
	virtual ~Non_fatal_error() = default;
};

class Fatal_error : public Error {
public:
	Fatal_error(const std::string& error_message) : Error(error_message) {}
	virtual ~Fatal_error() = default;
};

} // suppositio