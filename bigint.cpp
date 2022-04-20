#include "bigint.h"
#include <algorithm>

namespace big_num_arithmetic {

    int BigInteger::internal_base = 10000;
    const int BigInteger::MIN_LENGTH_FOR_KARATSUBA;

    BigInteger::BigInteger(int64_t number) {
        if (number > 0) {
            sign_ = 1;
        }
        if (number == 0) {
            sign_ = 0;
            big_number_.push_back(0);
        }
        if (number < 0) {
            sign_ = -1;
        }
        while (number != 0) {
            big_number_.push_back(std::abs(number % internal_base));
            number /= internal_base;
        }
    }

    BigInteger::BigInteger() {
        sign_ = 0;
        big_number_.push_back(0);
    }

    int BigInteger::Sign() const {
        return sign_;
    }

    void BigInteger::Negate() {
        sign_ *= (-1);
    }

    void BigInteger::Abs() {
        if (sign_ != 0) {
            sign_ = 1;
        }
    }

    BigInteger BigInteger::DifferenceOfModuleNumbers(const BigInteger& first_value,
                                                     const BigInteger& second_value)
    const {
        BigInteger first_number = first_value;
        BigInteger second_number = second_value;
        int changes = 0;
        int length = first_number.big_number_.size();
        second_number.big_number_.resize(length);
        for (int i = 0; i < first_number.big_number_.size(); i++) {
            if (first_number.big_number_[i] - second_number.big_number_[i] + changes
                < 0) {
                first_number.big_number_[i] =
                        first_number.big_number_[i] - second_number.big_number_[i] + changes
                        + internal_base;
                changes = -1;
            } else {
                first_number.big_number_[i] =
                        first_number.big_number_[i] - second_number.big_number_[i] + changes;
                changes = 0;
            }
        }
        first_number.sign_ = 1;
        RemoveZero(first_number);
        return first_number;
    }

    void BigInteger::RemoveZero(BigInteger& number) const {
        int positions = 0;
        for (int i = number.big_number_.size() - 1; i >= 0; i--) {
            if (number.big_number_[i] == 0) {
                positions++;
            } else {
                break;
            }
        }
        int length = number.big_number_.size() - positions;
        if (length == 0) {
            number = BigInteger(0);
            return;
        }
        number.big_number_.resize(length);
    }

    BigInteger BigInteger::FromString(const std::string& number, int base) {
        BigInteger big_number;
        int position_of_first_digit = 0;
        if (number[0] == '-') {
            position_of_first_digit = 1;
        }
        for (int i = position_of_first_digit; i < number.size(); i++) {
            int64_t digit = -1;
            if (number[i] >= '0' && number[i] <= '9') {
                digit = number[i] - '0';
            } else if (number[i] >= 'a' && number[i] <= 'z') {
                digit = number[i] - 'a' + 10;
            } else {
                throw std::runtime_error("Invalid symbol at index " + std::to_string(i));
            }
            if (digit >= base) {
                throw std::runtime_error("Invalid symbol at index " + std::to_string(i));
            }
            big_number = big_number * static_cast<int64_t>(base) + digit;
        }
        if (number[0] == '-') {
            big_number.sign_ = -big_number.sign_;
        }
        return big_number;
    }

    BigInteger::operator int64_t() const {
        if (*this > INT64_MAX) {
            throw std::runtime_error("int64_t overflow");
        }
        if (*this < INT64_MIN) {
            throw std::runtime_error("int64_t overflow");
        }
        int64_t answer = 0;
        for (int i = big_number_.size() - 1; i >= 0; i--) {
            answer = answer * internal_base + big_number_[i];
        }
        answer = answer * sign_;
        return answer;
    }

    std::string BigInteger::ToString(int base) const {
        if (base < 2 || base > 36) {
            throw std::logic_error("Invalid base");
        }
        BigInteger current = *this;
        current.sign_ = abs(sign_);
        std::string answer;
        while (current != static_cast<int64_t>(0)) {
            int64_t value = int64_t(current % static_cast<uint32_t>(base));
            current = current / static_cast<int64_t>(base);
            char digit;
            if (value < 10) {
                digit = value + '0';
            } else {
                digit = value - 10 + 'a';
            }
            answer += digit;
        }
        std::reverse(answer.begin(), answer.end());
        if (sign_ == -1) {
            answer = '-' + answer;
        }
        if (sign_ == 0) {
            answer = answer + '0';
        }
        return answer;
    }

    bool BigInteger::operator==(const BigInteger& number) const {
        if (sign_ != number.sign_) {
            return false;
        }
        return big_number_ == number.big_number_;
    }

    bool BigInteger::operator!=(const BigInteger& number) const {
        if (sign_ != number.sign_) {
            return true;
        }
        return big_number_ != number.big_number_;
    }

    bool BigInteger::operator>=(const BigInteger& number) const {
        return *this == number || *this > number;
    }

    bool BigInteger::operator<=(const BigInteger& number) const {
        return *this == number || *this < number;
    }

    bool BigInteger::operator>(const BigInteger& number) const {
        if (sign_ != number.sign_) {
            return sign_ > number.sign_;
        }
        if (sign_ > 0) {
            if (big_number_.size() != number.big_number_.size()) {
                return big_number_.size() > number.big_number_.size();
            }
            for (int i = number.big_number_.size() - 1; i >= 0; i--) {
                if (big_number_[i] < number.big_number_[i]) {
                    return false;
                }
                if (big_number_[i] > number.big_number_[i]) {
                    return true;
                }
            }
        } else {
            if (big_number_.size() != number.big_number_.size()) {
                return big_number_.size() < number.big_number_.size();
            }
            for (int i = number.big_number_.size() - 1; i >= 0; i--) {
                if (big_number_[i] > number.big_number_[i]) {
                    return false;
                }
                if (big_number_[i] < number.big_number_[i]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool BigInteger::operator<(const BigInteger& number) const {
        if (sign_ != number.sign_) {
            return sign_ < number.sign_;
        }
        if (sign_ > 0) {
            if (big_number_.size() != number.big_number_.size()) {
                return big_number_.size() < number.big_number_.size();
            }
            for (int i = number.big_number_.size() - 1; i >= 0; i--) {
                if (big_number_[i] > number.big_number_[i]) {
                    return false;
                }
                if (big_number_[i] < number.big_number_[i]) {
                    return true;
                }
            }
        } else {
            if (big_number_.size() != number.big_number_.size()) {
                return big_number_.size() > number.big_number_.size();
            }
            for (int i = number.big_number_.size() - 1; i >= 0; i--) {
                if (big_number_[i] < number.big_number_[i]) {
                    return false;
                }
                if (big_number_[i] > number.big_number_[i]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool BigInteger::operator==(int64_t number) const {
        BigInteger value(number);
        return *this == value;
    }

    bool BigInteger::operator!=(int64_t number) const {
        BigInteger value(number);
        return *this != value;
    }

    bool BigInteger::operator>=(int64_t number) const {
        BigInteger value(number);
        return *this >= value;
    }

    bool BigInteger::operator<=(int64_t number) const {
        BigInteger value(number);
        return *this <= value;
    }

    bool BigInteger::operator>(int64_t number) const {
        BigInteger value(number);
        return *this > value;
    }

    bool BigInteger::operator<(int64_t number) const {
        BigInteger value(number);
        return *this < value;
    }

    BigInteger BigInteger::operator+(const BigInteger& number) const {
        BigInteger addition;
        if (sign_ == 0) {
            return number;
        }
        if (number.sign_ == 0) {
            return *this;
        }
        if (sign_ == number.sign_) {
            int length = std::max(number.big_number_.size(), big_number_.size());
            int changes = 0;
            BigInteger first_value = number;
            BigInteger second_value = *this;
            first_value.big_number_.resize(length);
            second_value.big_number_.resize(length);
            addition.big_number_.resize(length);
            addition.sign_ = sign_;
            for (int i = 0; i < length; i++) {
                addition.big_number_[i] =
                        (first_value.big_number_[i] + second_value.big_number_[i] + changes)
                        % internal_base;
                changes =
                        (first_value.big_number_[i] + second_value.big_number_[i] + changes)
                        / internal_base;
            }
            if (changes == 1) {
                addition.big_number_.push_back(1);
            }
        } else {
            if (*this < number) {
                BigInteger value = *this;
                value.sign_ = -sign_;
                addition = number - value;
            } else {
                BigInteger value = number;
                value.sign_ = -number.sign_;
                addition = *this - value;
            }
        }
        return addition;
    }

    BigInteger BigInteger::operator+(const int64_t number) const {
        BigInteger value(number);
        BigInteger addition = *this + value;
        return addition;
    }

    BigInteger BigInteger::operator+=(const BigInteger& number) {
        *this = *this + number;
        return *this;
    }

    BigInteger BigInteger::operator+=(int64_t number) {
        *this = *this + number;
        return *this;
    }

    BigInteger BigInteger::operator-(const BigInteger& number) const {
        BigInteger difference = *this;
        if (number.sign_ == static_cast<int64_t>(0)) {
            return difference;
        }
        if (sign_ == 0) {
            difference = number;
            difference.sign_ = -number.sign_;
            return difference;
        }
        if (sign_ != number.sign_) {
            BigInteger value = number;
            value.sign_ = -number.sign_;
            difference = *this + value;
        } else {
            if (*this < number) {
                if (sign_ == 1) {
                    difference = DifferenceOfModuleNumbers(number, *this);
                } else {
                    difference = DifferenceOfModuleNumbers(*this, number);
                }
                difference.sign_ *= (-1);
            } else {
                if (sign_ == -1) {
                    difference = DifferenceOfModuleNumbers(number, *this);
                } else {
                    difference = DifferenceOfModuleNumbers(*this, number);
                }
            }
        }
        return difference;
    }

    BigInteger BigInteger::operator-(const int64_t number) const {
        BigInteger value(number);
        BigInteger difference = *this - value;
        return difference;
    }

    BigInteger BigInteger::operator-=(const BigInteger& number) {
        *this = *this - number;
        return *this;
    }

    BigInteger BigInteger::operator-=(const int64_t number) {
        *this = *this - number;
        return *this;
    }

    BigInteger BigInteger::operator*(const BigInteger& number) const {
        BigInteger multiplication;
        if (number == static_cast<int64_t>(0) || *this == static_cast<int64_t>(0)) {
            return multiplication;
        }

        BigInteger first_value = *this;
        BigInteger second_value = number;

        int length = std::max(first_value.big_number_.size(), second_value.big_number_.size());
        first_value.big_number_.resize(length);
        second_value.big_number_.resize(length);

        int new_size = 2 * length;
        multiplication.big_number_.resize(new_size);

        if (length >= MIN_LENGTH_FOR_KARATSUBA){
            int first_part_length = (length + 1) / 2;

            BigInteger first_value_first_part, second_value_first_part;
            first_value_first_part.big_number_.resize(first_part_length);
            second_value_first_part.big_number_.resize(first_part_length);
            first_value_first_part.sign_ = 1;
            second_value_first_part.sign_ = 1;

            for (int i = 0; i < first_part_length; i++){
                first_value_first_part.big_number_[i] = first_value.big_number_[i];
                second_value_first_part.big_number_[i] = second_value.big_number_[i];
            }

            BigInteger first_value_second_part, second_value_second_part;
            first_value_second_part.big_number_.resize(length - first_part_length);
            second_value_second_part.big_number_.resize(length - first_part_length);
            first_value_second_part.sign_ = 1;
            second_value_second_part.sign_ = 1;

            for (int i = first_part_length; i < length; i++){
                first_value_second_part.big_number_[i - first_part_length] = first_value.big_number_[i];
                second_value_second_part.big_number_[i - first_part_length] = second_value.big_number_[i];
            }

            BigInteger product_of_sums = (first_value_first_part + first_value_second_part) *
                                         (second_value_first_part + second_value_second_part);
            BigInteger product_of_first_parts = first_value_first_part * second_value_first_part;
            BigInteger product_of_second_parts = first_value_second_part * second_value_second_part;
            BigInteger middle_part_sum = product_of_sums - product_of_first_parts - product_of_second_parts;

            for (int i = 0; i < product_of_first_parts.big_number_.size(); i++){
                multiplication.big_number_[i] += product_of_first_parts.big_number_[i];
            }
            for (int i = 0; i < middle_part_sum.big_number_.size(); i++){
                multiplication.big_number_[i + first_part_length] += middle_part_sum.big_number_[i];
            }
            for (int i = 0; i < product_of_second_parts.big_number_.size(); i++){
                multiplication.big_number_[i + 2 * first_part_length] += product_of_second_parts.big_number_[i];
            }

            int changes = 0;
            for (int i = 0; i < new_size; i++){
                multiplication.big_number_[i] += changes;
                changes = multiplication.big_number_[i] / internal_base;
                multiplication.big_number_[i] -= changes * internal_base;
            }

        }
        else {
            int changes = 0;
            for (int i = 0; i < number.big_number_.size(); i++) {
                for (int j = 0; j < big_number_.size(); j++) {
                    int current = multiplication.big_number_[i + j]
                                  + number.big_number_[i] * big_number_[j] + changes;
                    changes = current / internal_base;
                    multiplication.big_number_[i + j] = current - changes * internal_base;
                    if (changes > 0 && j == big_number_.size() - 1) {
                        multiplication.big_number_[i + j + 1] += changes;
                        changes = 0;
                    }
                }
            }
        }

        RemoveZero(multiplication);
        multiplication.sign_ = sign_ * number.sign_;
        return multiplication;
    }

    BigInteger BigInteger::operator*=(const BigInteger& number) {
        *this = *this * number;
        return *this;
    }

    BigInteger BigInteger::operator*(int64_t number) const {
        BigInteger value(number);
        BigInteger multiplication = *this * value;
        return multiplication;
    }

    BigInteger BigInteger::operator*=(int64_t number) {
        *this = *this * number;
        return *this;
    }

    BigInteger BigInteger::operator/(const BigInteger& number) const {
        if (number == static_cast<int64_t>(0)) {
            throw DivisionByZeroError();
        }
        if (*this == static_cast<int64_t>(0)) {
            return BigInteger(0);
        }
        BigInteger current;
        BigInteger answer;
        BigInteger changes;
        BigInteger value = number;
        value.sign_ = std::abs(number.sign_);
        answer.big_number_.clear();
        for (int i = big_number_.size() - 1; i >= 0; i--) {
            current = current * static_cast<int64_t>(internal_base)
                      + static_cast<int64_t>(big_number_[i]);
            if (current >= value) {
                int64_t left = 0, right = internal_base;
                while (right - left > 1) {
                    int64_t mid = left + (right - left) / 2;
                    BigInteger multiplication = mid * value;
                    if (multiplication <= current) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
                answer.big_number_.push_back(left);
                changes = current - left * value;
                current = changes;
            } else {
                answer.big_number_.push_back(0);
            }
        }
        std::reverse(answer.big_number_.begin(), answer.big_number_.end());
        RemoveZero(answer);
        answer.sign_ = sign_ * number.sign_;
        if (answer.big_number_.size() == 1 && answer.big_number_[0] == 0) {
            answer.sign_ = 0;
        }
        return answer;
    }

    BigInteger BigInteger::operator/=(const BigInteger& number) {
        *this = *this / number;
        return *this;
    }

    BigInteger BigInteger::operator/(const int64_t number) const {
        BigInteger value(number);
        BigInteger division = *this / value;
        return division;
    }

    BigInteger BigInteger::operator/=(const int64_t number) {
        *this = *this / number;
        return *this;
    }

    BigInteger operator/(int64_t first_value, const BigInteger& number) {
        BigInteger value(first_value);
        BigInteger answer = value / number;
        return answer;
    }

    uint32_t BigInteger::operator%(const uint32_t number) const {
        if (number == static_cast<int64_t>(0)) {
            throw DivisionByZeroError();
        }
        BigInteger value = *this;
        value.sign_ = abs(sign_);
        int64_t answer = int64_t(value
                                 - (value / static_cast<int64_t>(number))
                                   * (number));
        if (sign_ == -1 && answer != 0) {
            answer -= number;
        }
        answer = std::abs(answer);
        return static_cast<uint32_t>(answer);
    }

    BigInteger BigInteger::operator++(int) {
        BigInteger answer = *this;
        *this += 1;
        return answer;
    }

    BigInteger BigInteger::operator--(int) {
        BigInteger answer = *this;
        *this -= 1;
        return answer;
    }

    BigInteger BigInteger::operator++() {
        *this += 1;
        return *this;
    }

    BigInteger BigInteger::operator--() {
        *this -= 1;
        return *this;
    }

    BigInteger BigInteger::operator-() const {
        BigInteger value = *this;
        value.sign_ = -sign_;
        return value;
    }

    BigInteger operator+(int64_t first_value, const BigInteger& number) {
        BigInteger answer = number + first_value;
        return answer;
    }

    BigInteger operator*(int64_t first_value, const BigInteger& number) {
        BigInteger answer = number * first_value;
        return answer;
    }

    BigInteger operator-(int64_t first_value, const BigInteger& number) {
        BigInteger answer = static_cast<int64_t>(-1) * (number - first_value);
        return answer;
    }

    bool operator==(int64_t first_value, const BigInteger& number) {
        return number == first_value;
    }

    bool operator!=(int64_t first_value, const BigInteger& number) {
        return number != first_value;
    }

    bool operator>(int64_t first_value, const BigInteger& number) {
        return number < first_value;
    }

    bool operator<(int64_t first_value, const BigInteger& number) {
        return number > first_value;
    }

    bool operator>=(int64_t first_value, const BigInteger& number) {
        return number <= first_value;
    }

    bool operator<=(int64_t first_value, const BigInteger& number) {
        return number >= first_value;
    }

    std::istream& operator>> (std::istream& in, BigInteger& number)
    {
        std::string input_string;
        in >> input_string;
        number = BigInteger::FromString(input_string, 10);
        return in;
    }

    std::ostream& operator<< (std::ostream& out, const BigInteger& number)
    {
        out << number.ToString(10) << "\n";
        return out;
    }

}  // namespace big_num_arithmetic
