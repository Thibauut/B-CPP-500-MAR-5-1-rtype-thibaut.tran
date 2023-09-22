#pragma once
    #include <iostream>
    #include <exception>

namespace ERROR {
    class MyException : public std::exception {
        public:
            MyException(const std::string& message) : message_(message) {
                std::cout << "Error: " << what() << std::endl;
            }
            // Override the what() function to provide a custom error message
            const char* what() const noexcept override {
                return message_.c_str();
            }

    private:
        std::string message_;
    };
}