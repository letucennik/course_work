#include <iostream>
#include "bigint.h"

using namespace big_num_arithmetic;

enum OperationType {
    kIncrement,
    kDecrement,
    kInt64,
    kAddition,
    kDivision,
    kDifference,
    kMultiplication,
    kModule,
    kEqual,
    kNotEqual,
    kLessOrEqual,
    kGreaterOrEqual,
    kGreater,
    kLess
};

OperationType TranslateToOperationType(std::string &s) {
    if (s == "+") {
        return kAddition;
    }
    if (s == "-") {
        return kDifference;
    }
    if (s == "*") {
        return kMultiplication;
    }
    if (s == "/") {
        return kDivision;
    }
    if (s == "%") {
        return kModule;
    }
    if (s == "==") {
        return kEqual;
    }
    if (s == "!=") {
        return kNotEqual;
    }
    if (s == ">") {
        return kGreater;
    }
    if (s == "<") {
        return kLess;
    }
    if (s == ">=") {
        return kGreaterOrEqual;
    }
    if (s == "<=") {
        return kLessOrEqual;
    }
    if (s == "++") {
        return kIncrement;
    }
    if (s == "--") {
        return kDecrement;
    }
    if (s == "int64_t") {
        return kInt64;
    }
}

void OneArgument(OperationType operation, BigInteger &value) {
    std::string answer;
    switch (operation) {
        case kIncrement :
            value++;
            answer = value.ToString(10);
            std::cout << answer;
            break;
        case kDecrement :
            value--;
            answer = value.ToString(10);
            std::cout << answer;
            break;
        case kInt64 :
            try {
                int64_t answer_value = int64_t(value);
            } catch (std::runtime_error) {
                std::cout << "int64_t overflow\n";
                return;
            }
            int64_t answer_value = int64_t(value);
            std::cout << answer_value;
            break;
    }
}

void TwoArguments(OperationType operation,
                  BigInteger &first_value,
                  BigInteger &second_value) {
    std::string answer;
    BigInteger value;
    switch (operation) {
        case kAddition :
            value = first_value + second_value;
            answer = value.ToString(10);
            std::cout << answer << "\n";
            break;
        case kDifference :
            value = first_value - second_value;
            answer = value.ToString(10);
            std::cout << answer << "\n";
            break;
        case kMultiplication :
            value = first_value * second_value;
            answer = value.ToString(10);
            std::cout << answer << "\n";
            break;
        case kDivision:
            try {
                value = first_value / second_value;
                answer = value.ToString(10);
                std::cout << answer << "\n";
            } catch (big_num_arithmetic::DivisionByZeroError) {
                std::cout << "Error: division by zero\n";
                return;
            }
            break;
        case kEqual:
            if (first_value == second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kNotEqual:
            if (first_value != second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kLess:
            if (first_value < second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kLessOrEqual:
            if (first_value <= second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kGreater:
            if (first_value > second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kGreaterOrEqual:
            if (first_value >= second_value) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            break;
        case kModule:
            try {
                auto module = first_value % int64_t(second_value);
                std::cout << module << "\n";
            } catch (big_num_arithmetic::DivisionByZeroError) {
                std::cout << "Error: division by zero\n";
                return;
            }
            break;
    }
}


int main() {
    std::cout << "Enter operation: \n";
    std::string operation;
    std::cin >> operation;
    OperationType name_of_operation = TranslateToOperationType(operation);
    BigInteger first_number, second_number;
    if (name_of_operation <= kInt64) {
        std::cout << "Enter single argument: \n";
        std::cin >> first_number;
        OneArgument(name_of_operation, first_number);
    } else if (name_of_operation <= kLess) {
        std::cout << "Enter two arguments: \n";
        std::cin >> first_number >> second_number;
        TwoArguments(name_of_operation, first_number, second_number);
    }
    return 0;
}