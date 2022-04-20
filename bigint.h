#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

namespace big_num_arithmetic {

    struct DivisionByZeroError : std::exception {};

    class BigInteger {
    public:
        static int32_t internal_base;

        explicit BigInteger(int64_t);
        BigInteger();

        int Sign() const;
        void Negate();
        void Abs();

        static BigInteger FromString(const std::string& number, int base);

        std::string ToString(int base) const;

        explicit operator int64_t() const;

        bool operator==(const BigInteger& number) const;
        bool operator!=(const BigInteger& number) const;
        bool operator>=(const BigInteger& number) const;
        bool operator<=(const BigInteger& number) const;
        bool operator>(const BigInteger& number) const;
        bool operator<(const BigInteger& number) const;

        bool operator==(int64_t number) const;
        bool operator!=(int64_t number) const;
        bool operator>=(int64_t number) const;
        bool operator<=(int64_t number) const;
        bool operator>(int64_t number) const;
        bool operator<(int64_t number) const;

        friend bool operator==(int64_t first_value, const BigInteger& number);
        friend bool operator!=(int64_t first_value, const BigInteger& number);
        friend bool operator>(int64_t first_value, const BigInteger& number);
        friend bool operator<(int64_t first_value, const BigInteger& number);
        friend bool operator>=(int64_t first_value, const BigInteger& number);
        friend bool operator<=(int64_t first_value, const BigInteger& number);

        BigInteger operator+(const BigInteger& number) const;
        BigInteger operator-(const BigInteger& number) const;
        BigInteger operator*(const BigInteger& number) const;
        BigInteger operator/(const BigInteger& number) const;

        BigInteger operator+(int64_t number) const;
        BigInteger operator-(int64_t number) const;
        BigInteger operator/(int64_t number) const;
        BigInteger operator*(int64_t number) const;

        BigInteger operator*=(const BigInteger& number);
        BigInteger operator/=(const BigInteger& number);
        BigInteger operator+=(const BigInteger& number);
        BigInteger operator-=(const BigInteger& number);

        BigInteger operator-=(int64_t number);
        BigInteger operator+=(int64_t number);
        BigInteger operator*=(int64_t number);
        BigInteger operator/=(int64_t number);

        friend BigInteger operator+(int64_t first_value, const BigInteger& number);
        friend BigInteger operator*(int64_t first_value, const BigInteger& number);
        friend BigInteger operator-(int64_t first_value, const BigInteger& number);
        friend BigInteger operator/(int64_t first_value, const BigInteger& number);

        uint32_t operator%(uint32_t number) const;

        BigInteger operator-() const;

        BigInteger operator++();
        BigInteger operator--();
        BigInteger operator++(int);
        BigInteger operator--(int);

        friend std::istream& operator>> (std::istream& in, BigInteger& number);
        friend std::ostream& operator<< (std::ostream& out, const BigInteger& number);

    private:
        int sign_;
        std::vector<int32_t> big_number_;
        BigInteger DifferenceOfModuleNumbers(const BigInteger& first_value,
                                             const BigInteger& second_value) const;
        void RemoveZero(BigInteger& number) const;
        static const int32_t MIN_LENGTH_FOR_KARATSUBA = 4;
    };

}  // namespace big_num_arithmetic


