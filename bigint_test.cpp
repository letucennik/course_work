#include "bigint.h"
#include <gtest/gtest.h>

using big_num_arithmetic::BigInteger;


TEST (TestsPart1, Sign) {
    EXPECT_EQ(BigInteger(42).Sign(), 1);
    EXPECT_EQ(BigInteger(0).Sign(), 0);
    EXPECT_EQ(BigInteger(-3).Sign(), -1);
}

//TEST(TestsPart1, FromString) {
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("-0", 10),
//              BigInteger(0));
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("10", 2), BigInteger(2));
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("-10", 2),
//              BigInteger(-2));
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("ff", 16),
//              BigInteger(255));
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("-ff", 32),
//              BigInteger(-495));
//    EXPECT_EQ(big_num_arithmetic::BigInteger::FromString("0", 36), BigInteger());
//}

TEST(TestsPart1, ToString) {
    EXPECT_EQ(BigInteger(10).ToString(10), "10");
    EXPECT_EQ(BigInteger(5989523).ToString(2), "10110110110010010010011");
    EXPECT_EQ(BigInteger(-5989523).ToString(2), "-10110110110010010010011");
    EXPECT_EQ(BigInteger(0).ToString(33), "0");
    EXPECT_EQ(BigInteger(1).ToString(33), "1");
    EXPECT_EQ(BigInteger(0).ToString(2), "0");
    EXPECT_EQ(BigInteger(-348320943284).ToString(36), "-4g0lanxw");
    EXPECT_EQ(BigInteger(-3345).ToString(26), "-4oh");
    EXPECT_EQ(BigInteger(989523).ToString(17), "be6g4");
}

TEST(TestsPart1, ToInt64) {
    EXPECT_EQ(int64_t(BigInteger(578789)), 578789);
    EXPECT_EQ(int64_t(BigInteger(-323789)), -323789);
    int64_t value = INT64_MAX;
    EXPECT_EQ(int64_t(BigInteger(value)), value);
    value = INT64_MIN;
    EXPECT_EQ(int64_t(BigInteger(value)), value);
    EXPECT_EQ(int64_t(BigInteger(0)), 0);
}

TEST(TestsPart1, EqualNumber) {
    EXPECT_EQ(BigInteger(345671), 345671);
    EXPECT_EQ(BigInteger(0), 0);
    EXPECT_EQ(BigInteger(-3011), -3011);
}

TEST(TestsPart1, EqualBigNumber) {
    EXPECT_EQ(BigInteger(3456111), BigInteger(3456111));
    EXPECT_EQ(BigInteger(0), BigInteger(0));
    EXPECT_EQ(BigInteger(-3011), BigInteger(-3011));
}

TEST(TestsPart1, EqualNumberBigNumber) {
    EXPECT_EQ((3456111), BigInteger(3456111));
    EXPECT_EQ((0), BigInteger(0));
    EXPECT_EQ((-3011), BigInteger(-3011));
}

TEST(TestsPart1, NotEqualNumber) {
    EXPECT_NE(BigInteger(345671), 1);
    EXPECT_NE(BigInteger(345671), 1234567);
    EXPECT_NE(BigInteger(0), -1234);
    EXPECT_NE(BigInteger(1235), 1234);
    EXPECT_NE(BigInteger(-3011), -311011);
    EXPECT_NE(BigInteger(-301111), -311011);
    EXPECT_NE(BigInteger(-301111), 311111);
}

TEST(TestsPart1, NotEqualBigNumbers) {
    EXPECT_NE(BigInteger(345671), BigInteger(-1));
    EXPECT_NE(BigInteger(345671), BigInteger(345672311));
    EXPECT_NE(BigInteger(0), BigInteger(-1234));
    EXPECT_NE(BigInteger(21235), BigInteger(31235));
    EXPECT_NE(BigInteger(-3011), BigInteger(-301223));
    EXPECT_NE(BigInteger(-301111), BigInteger(301111));
    EXPECT_NE(BigInteger(-301111), BigInteger(-301011));
    EXPECT_NE(BigInteger(-111), BigInteger(-3));
}

TEST(TestsPart1, NotEqualNumberBigNumber) {
    EXPECT_NE((345671), BigInteger(-1));
    EXPECT_NE((345671), BigInteger(345672311));
    EXPECT_NE((0), BigInteger(-1234));
    EXPECT_NE((21235), BigInteger(31235));
    EXPECT_NE((-3011), BigInteger(-301223));
    EXPECT_NE((-301111), BigInteger(301111));
    EXPECT_NE((-301111), BigInteger(-301011));
    EXPECT_NE((-111), BigInteger(-3));
}

TEST(TestsPart1, LessOrEqualBigNumbers) {
    EXPECT_LE(BigInteger(-1), BigInteger(345671));
    EXPECT_LE(BigInteger(345671), BigInteger(345672311));
    EXPECT_LE(BigInteger(0), BigInteger(0));
    EXPECT_LE(BigInteger(21235), BigInteger(31235));
    EXPECT_LE(BigInteger(-301223), BigInteger(-3011));
    EXPECT_LE(BigInteger(-301111), BigInteger(301111));
    EXPECT_LE(BigInteger(-301111), BigInteger(-301011));
    EXPECT_LE(BigInteger(-111), BigInteger(-3));
    EXPECT_LE(BigInteger(3), BigInteger(3));
    EXPECT_LE(BigInteger(-11113), BigInteger(-11113));
}

TEST(TestsPart1, LessOrEqualNumberBigNumbers) {
    EXPECT_LE((-1), BigInteger(345671));
    EXPECT_LE((345671), BigInteger(345672311));
    EXPECT_LE((0), BigInteger(0));
    EXPECT_LE((21235), BigInteger(31235));
    EXPECT_LE((-301223), BigInteger(-3011));
    EXPECT_LE((-301111), BigInteger(301111));
    EXPECT_LE((-301111), BigInteger(-301011));
    EXPECT_LE((-111), BigInteger(-3));
    EXPECT_LE((3), BigInteger(3));
    EXPECT_LE((-11113), BigInteger(-11113));
}

TEST(TestsPart1, LessOrEqualNumbers) {
    EXPECT_LE(BigInteger(-1), 345671);
    EXPECT_LE(BigInteger(345671), 345672311);
    EXPECT_LE(BigInteger(0), 0);
    EXPECT_LE(BigInteger(21235), 31235);
    EXPECT_LE(BigInteger(-301223), -3011);
    EXPECT_LE(BigInteger(-301111), 301111);
    EXPECT_LE(BigInteger(-301111), -301011);
    EXPECT_LE(BigInteger(-111), -3);
    EXPECT_LE(BigInteger(3), 3);
    EXPECT_LE(BigInteger(-11113), -11113);
}

TEST(TestsPart1, GreaterOrEqualNumberBigNumber) {
    EXPECT_GE((345671), BigInteger(-1));
    EXPECT_GE((34567433431), BigInteger(342311));
    EXPECT_GE((0), BigInteger(0));
    EXPECT_GE((41235), BigInteger(31235));
    EXPECT_GE((-323), BigInteger(-3011));
    EXPECT_GE((301111), BigInteger(-301111));
    EXPECT_GE((-301011), BigInteger(-301111));
    EXPECT_GE((-111), BigInteger(-3434));
    EXPECT_GE((3), BigInteger(3));
    EXPECT_GE((-11113), BigInteger(-11113));
}

TEST(TestsPart1, GreaterOrEqualBigNumbers) {
    EXPECT_GE(BigInteger(345671), BigInteger(-1));
    EXPECT_GE(BigInteger(34567433431), BigInteger(342311));
    EXPECT_GE(BigInteger(0), BigInteger(0));
    EXPECT_GE(BigInteger(41235), BigInteger(31235));
    EXPECT_GE(BigInteger(-323), BigInteger(-3011));
    EXPECT_GE(BigInteger(301111), BigInteger(-301111));
    EXPECT_GE(BigInteger(-301011), BigInteger(-301111));
    EXPECT_GE(BigInteger(-111), BigInteger(-3434));
    EXPECT_GE(BigInteger(3), BigInteger(3));
    EXPECT_GE(BigInteger(-11113), BigInteger(-11113));
}

TEST(TestsPart1, GreaterOrEqualNumbers) {
    EXPECT_GE(BigInteger(345671), -1);
    EXPECT_GE(BigInteger(34567433431), 342311);
    EXPECT_GE(BigInteger(0), 0);
    EXPECT_GE(BigInteger(41235), 31235);
    EXPECT_GE(BigInteger(-323), -3011);
    EXPECT_GE(BigInteger(301111), -301111);
    EXPECT_GE(BigInteger(-301011), -301111);
    EXPECT_GE(BigInteger(-111), -3434);
    EXPECT_GE(BigInteger(3), 3);
    EXPECT_GE(BigInteger(-11113), -11113);
}

TEST(TestsPart1, LesslBigNumbers) {
    EXPECT_LT(BigInteger(-1), BigInteger(345671));
    EXPECT_LT(BigInteger(345671), BigInteger(345672311));
    EXPECT_LT(BigInteger(21235), BigInteger(31235));
    EXPECT_LT(BigInteger(-301223), BigInteger(-3011));
    EXPECT_LT(BigInteger(-301111), BigInteger(-301011));
    EXPECT_LT(BigInteger(-301111), BigInteger(301111));
    EXPECT_LT(BigInteger(-111), BigInteger(-3));
}

TEST(TestsPart1, LesslNumberBigNumber) {
    EXPECT_LT((-1), BigInteger(345671));
    EXPECT_LT((345671), BigInteger(345672311));
    EXPECT_LT((21235), BigInteger(31235));
    EXPECT_LT((-301223), BigInteger(-3011));
    EXPECT_LT((-301111), BigInteger(-301011));
    EXPECT_LT((-301111), BigInteger(301111));
    EXPECT_LT((-111), BigInteger(-3));
}

TEST(TestsPart1, LessNumbers) {
    EXPECT_LT(BigInteger(-1), 345671);
    EXPECT_LT(BigInteger(345671), 345672311);
    EXPECT_LT(BigInteger(21235), 31235);
    EXPECT_LT(BigInteger(-301223), -3011);
    EXPECT_LT(BigInteger(-301111), 301111);
    EXPECT_LT(BigInteger(-301111), -301011);
    EXPECT_LT(BigInteger(-111), -3);
}

TEST(TestsPart1, GreaterBigNumbers) {
    EXPECT_GT(BigInteger(345671), BigInteger(-1));
    EXPECT_GT(BigInteger(34567433431), BigInteger(342311));
    EXPECT_GT(BigInteger(41235), BigInteger(31235));
    EXPECT_GT(BigInteger(-323), BigInteger(-3011));
    EXPECT_GT(BigInteger(301111), BigInteger(-301111));
    EXPECT_GT(BigInteger(-301011), BigInteger(-301111));
    EXPECT_GT(BigInteger(-111), BigInteger(-3434));
}

TEST(TestsPart1, GreaterNumberBigNumber) {
    EXPECT_GT((345671), BigInteger(-1));
    EXPECT_GT((34567433431), BigInteger(342311));
    EXPECT_GT((41235), BigInteger(31235));
    EXPECT_GT((-323), BigInteger(-3011));
    EXPECT_GT((301111), BigInteger(-301111));
    EXPECT_GT((-301011), BigInteger(-301111));
    EXPECT_GT((-111), BigInteger(-3434));
}

TEST(TestsPart1, GreaterNumbers) {
    EXPECT_GT(BigInteger(345671), -1);
    EXPECT_GT(BigInteger(34567433431), 342311);
    EXPECT_GT(BigInteger(41235), 31235);
    EXPECT_GT(BigInteger(-323), -3011);
    EXPECT_GT(BigInteger(301111), -301111);
    EXPECT_GT(BigInteger(-301011), -301111);
    EXPECT_GT(BigInteger(-111), -3434);
}

TEST(TestsPart1, AdditionBigNumbers) {
    EXPECT_EQ(BigInteger(71) + BigInteger(71), BigInteger(142));
    EXPECT_EQ(BigInteger(9999) + BigInteger(1), BigInteger(10000));
    EXPECT_EQ(BigInteger(9999) + BigInteger(0), BigInteger(9999));
    EXPECT_EQ(BigInteger(0) + BigInteger(1213), BigInteger(1213));
    EXPECT_EQ(BigInteger(-1234534) + BigInteger(31), BigInteger(-1234503));
    EXPECT_EQ(BigInteger(-34) + BigInteger(123324), BigInteger(123290));
    EXPECT_EQ(BigInteger(99997735) + BigInteger(33235), BigInteger(100030970));
    EXPECT_EQ(BigInteger(-323) + BigInteger(-3011), BigInteger(-3334));
    EXPECT_EQ(BigInteger(-99232) + BigInteger(-99893011), BigInteger(-99992243));
    EXPECT_EQ(BigInteger(301111) + BigInteger(-301111), BigInteger(0));
    EXPECT_EQ(BigInteger(78900) + BigInteger(-301), BigInteger(78599));
    EXPECT_EQ(BigInteger(78900) + BigInteger(-301), BigInteger(78599));
    EXPECT_EQ(BigInteger(70) + BigInteger(-677301), BigInteger(-677231));
}

TEST(TestsPart1, AdditionNumberBigNumber) {
    EXPECT_EQ(static_cast<int64_t>(71) + BigInteger(71), BigInteger(142));
    EXPECT_EQ(static_cast<int64_t>(-1234534) + BigInteger(31),
              BigInteger(-1234503));
    EXPECT_EQ(static_cast<int64_t>(-34) + BigInteger(123324), BigInteger(123290));
    EXPECT_EQ(static_cast<int64_t>(99997735) + BigInteger(33235),
              BigInteger(100030970));
    EXPECT_EQ(static_cast<int64_t>(-323) + BigInteger(-3011), BigInteger(-3334));
    EXPECT_EQ(static_cast<int64_t>(-99232) + BigInteger(-99893011),
              BigInteger(-99992243));
    EXPECT_EQ(static_cast<int64_t>(301111) + BigInteger(-301111), BigInteger(0));
    EXPECT_EQ(static_cast<int64_t>(78900) + BigInteger(-301), BigInteger(78599));
    EXPECT_EQ(static_cast<int64_t>(78900) + BigInteger(-301), BigInteger(78599));
    EXPECT_EQ(static_cast<int64_t>(70) + BigInteger(-677301),
              BigInteger(-677231));
}

TEST(TestsPart1, AdditionNumbers) {
    EXPECT_EQ(BigInteger(71) + static_cast<int64_t>(71), BigInteger(142));
    EXPECT_EQ(BigInteger(-1234534) + static_cast<int64_t>(31),
              BigInteger(-1234503));
    EXPECT_EQ(BigInteger(-34) + static_cast<int64_t>(123324), BigInteger(123290));
    EXPECT_EQ(BigInteger(99997735) + static_cast<int64_t>(33235),
              BigInteger(100030970));
    EXPECT_EQ(BigInteger(-323) + static_cast<int64_t>(-3011), BigInteger(-3334));
    EXPECT_EQ(BigInteger(-99232) + static_cast<int64_t>(-99893011),
              BigInteger(-99992243));
    EXPECT_EQ(BigInteger(301111) + static_cast<int64_t>(-301111), BigInteger(0));
    EXPECT_EQ(BigInteger(78900) + static_cast<int64_t>(-301), BigInteger(78599));
    EXPECT_EQ(BigInteger(78900) + static_cast<int64_t>(-301), BigInteger(78599));
    EXPECT_EQ(BigInteger(70) + static_cast<int64_t>(-677301),
              BigInteger(-677231));
}

TEST(TestsPart1, DifferenceBigNumbers) {
    EXPECT_EQ(BigInteger(71) - BigInteger(-71), BigInteger(142));
    EXPECT_EQ(BigInteger(71) - BigInteger(0), BigInteger(71));
    EXPECT_EQ(BigInteger(0) - BigInteger(-71), BigInteger(71));
    EXPECT_EQ(BigInteger(34) - BigInteger(31), BigInteger(3));
    EXPECT_EQ(BigInteger(34) - BigInteger(324), BigInteger(-290));
    EXPECT_EQ(BigInteger(-99997735) - BigInteger(33235), BigInteger(-100030970));
    EXPECT_EQ(BigInteger(-323) - BigInteger(3011), BigInteger(-3334));
    EXPECT_EQ(BigInteger(99232) - BigInteger(-99893011), BigInteger(99992243));
    EXPECT_EQ(BigInteger(301111) - BigInteger(301111), BigInteger(0));
    EXPECT_EQ(BigInteger(78900) - BigInteger(301), BigInteger(78599));
    EXPECT_EQ(BigInteger(10000) - BigInteger(301), BigInteger(9699));
    EXPECT_EQ(BigInteger(1000000020) - BigInteger(99991231),
              BigInteger(900008789));
    EXPECT_EQ(BigInteger(-301) - BigInteger(-78900),
              BigInteger(78599));
}

TEST(TestsPart1, DifferenceNumbers) {
    EXPECT_EQ(BigInteger(71) - static_cast<int64_t>(-71), BigInteger(142));
    EXPECT_EQ(BigInteger(34) - static_cast<int64_t>(31), BigInteger(3));
    EXPECT_EQ(BigInteger(34) - static_cast<int64_t>(324), BigInteger(-290));
    EXPECT_EQ(BigInteger(-99997735) - static_cast<int64_t>(33235),
              BigInteger(-100030970));
    EXPECT_EQ(BigInteger(-323) - static_cast<int64_t>(3011), BigInteger(-3334));
    EXPECT_EQ(BigInteger(99232) - static_cast<int64_t>(-99893011),
              BigInteger(99992243));
    EXPECT_EQ(BigInteger(301111) - static_cast<int64_t>(301111), BigInteger(0));
    EXPECT_EQ(BigInteger(78900) - static_cast<int64_t>(301), BigInteger(78599));
    EXPECT_EQ((BigInteger(-301) - static_cast<int64_t>(-78900)),
              BigInteger(78599));
}

TEST(TestsPart1, DifferenceNumberBigNumber) {
    EXPECT_EQ(static_cast<int64_t>(71) - BigInteger(-71), BigInteger(142));
    EXPECT_EQ(static_cast<int64_t>(34) - BigInteger(31), BigInteger(3));
    EXPECT_EQ(static_cast<int64_t>(34) - BigInteger(324), BigInteger(-290));
    EXPECT_EQ(static_cast<int64_t>(-99997735) - BigInteger(33235),
              BigInteger(-100030970));
    EXPECT_EQ(static_cast<int64_t>(-323) - BigInteger(3011), BigInteger(-3334));
    EXPECT_EQ(static_cast<int64_t>(99232) - BigInteger(-99893011),
              BigInteger(99992243));
    EXPECT_EQ(static_cast<int64_t>(301111) - BigInteger(301111), BigInteger(0));
    EXPECT_EQ(static_cast<int64_t>(78900) - BigInteger(301), BigInteger(78599));
    EXPECT_EQ(static_cast<int64_t>(-301) - BigInteger(-78900), BigInteger(78599));
}

TEST(TestsPart1, MultiplicationBigNumbers) {
    EXPECT_EQ(BigInteger(123) * BigInteger(48), BigInteger(5904));
    EXPECT_EQ(BigInteger(12123993) * BigInteger(0), BigInteger(0));
    EXPECT_EQ(BigInteger(12123993) * BigInteger(12), BigInteger(145487916));
    EXPECT_EQ(BigInteger(0) * BigInteger(-1211), BigInteger(0));
    EXPECT_EQ(BigInteger(12389) * BigInteger(-1211), BigInteger(-15003079));
    EXPECT_EQ(BigInteger(-12389) * BigInteger(-1), BigInteger(12389));
    EXPECT_EQ(BigInteger(-52872389) * BigInteger(-79941),
              BigInteger(4226671649049));
}

TEST(TestsPart1, MultiplicationNumberBigNumber) {
    EXPECT_EQ(123 * BigInteger(48), BigInteger(5904));
    EXPECT_EQ(12123993 * BigInteger(0), BigInteger(0));
    EXPECT_EQ(12123993 * BigInteger(12), BigInteger(145487916));
    EXPECT_EQ(0 * BigInteger(-1211), BigInteger(0));
    EXPECT_EQ(12389 * BigInteger(-1211), BigInteger(-15003079));
    EXPECT_EQ((-12389) * BigInteger(-1), BigInteger(12389));
    EXPECT_EQ((-52872389) * BigInteger(-79941),
              BigInteger(4226671649049));
}

TEST(TestsPart1, MultiplicationNumbers) {
    EXPECT_EQ(BigInteger(123) * static_cast<int64_t>(48), BigInteger(5904));
    EXPECT_EQ(BigInteger(12123993) * static_cast<int64_t>(0), BigInteger(0));
    EXPECT_EQ(BigInteger(12123993) * static_cast<int64_t>(12),
              BigInteger(145487916));
    EXPECT_EQ(BigInteger(0) * static_cast<int64_t>(-1211), BigInteger(0));
    EXPECT_EQ(BigInteger(12389) * static_cast<int64_t>(-1211),
              BigInteger(-15003079));
    EXPECT_EQ(BigInteger(-12389) * static_cast<int64_t>(-1), BigInteger(12389));
    EXPECT_EQ(BigInteger(-52872389) * static_cast<int64_t>(-79941),
              BigInteger(4226671649049));
}

TEST(TestsPart1, DivisionNumbers) {
    EXPECT_EQ(BigInteger(608400) / 2, BigInteger(304200));
    EXPECT_EQ(BigInteger(6040000000) / 604, BigInteger(10000000));
    EXPECT_EQ(BigInteger(123) / static_cast<int64_t>(48), BigInteger(2));
    EXPECT_EQ(BigInteger(312123993) / static_cast<int64_t>(999),
              BigInteger(312436));
    EXPECT_EQ(BigInteger(-3993) / static_cast<int64_t>(1111112), BigInteger(0));
    EXPECT_EQ(BigInteger(0) / static_cast<int64_t>(-1211), BigInteger(0));
    EXPECT_EQ(BigInteger(12389) / static_cast<int64_t>(-1211), BigInteger(-10));
    EXPECT_EQ(BigInteger(-12389) / static_cast<int64_t>(-1), BigInteger(12389));
    EXPECT_EQ(BigInteger(-524329) / static_cast<int64_t>(79941),
              BigInteger(-6));
}

TEST(TestsPart1, DivisionBigNumbers) {
    EXPECT_EQ((BigInteger(123) / BigInteger(48)), BigInteger(2));
    EXPECT_EQ((BigInteger(312123993) / BigInteger(999)), BigInteger(312436));
    EXPECT_EQ((BigInteger(-3993) / BigInteger(1111112)), BigInteger(0));
    EXPECT_EQ(BigInteger(0) / BigInteger(-1211), BigInteger(0));
    EXPECT_EQ(BigInteger(11200000000) / BigInteger(112),
              BigInteger(100000000));
    EXPECT_EQ((BigInteger(608400) / BigInteger(2)),
              BigInteger(304200));
    EXPECT_EQ((BigInteger(12389) / BigInteger(-1211)),
              BigInteger(-10));
    EXPECT_EQ((BigInteger(-12389) / BigInteger(-1)),
              BigInteger(12389));
//    EXPECT_EQ((BigInteger::FromString("6980968409385345343049", 10)
//               / BigInteger::FromString("432943243224243", 10)),
//              (BigInteger::FromString("16124442", 10)));
    EXPECT_EQ(BigInteger(-524329) / BigInteger(79941),
              BigInteger(-6));
}

TEST(TestsPart1, CompoundAssignmentOperators) {
    BigInteger number;
    number += BigInteger(9497837542);
    EXPECT_EQ(number, BigInteger(9497837542));
    number -= 12342345;
    EXPECT_EQ(number, BigInteger(9485495197));
    number /= 1042320;
    EXPECT_EQ(number, BigInteger(9100));
    number *= 123;
    EXPECT_EQ(number, BigInteger(1119300));

    number /= BigInteger(10000);
    EXPECT_EQ(number, BigInteger(111));
    number += BigInteger(10234);
    EXPECT_EQ(number, BigInteger(10345));
    number -= BigInteger(10000);
    EXPECT_EQ(number, BigInteger(345));
    number *= BigInteger(98);
    EXPECT_EQ(number, BigInteger(33810));
}

TEST(TestsPart1, ModuloNumbers) {
    EXPECT_EQ(BigInteger(123) % static_cast<uint32_t>(48), 27);
    EXPECT_EQ(BigInteger(312123993) % static_cast<uint32_t>(999), 429);
    EXPECT_EQ(BigInteger(-3993) % static_cast<uint32_t>(1111112), 1107119);
    EXPECT_EQ(BigInteger(43) % static_cast<uint32_t>(1112), 43);
    EXPECT_EQ(BigInteger(0) % static_cast<uint32_t>(-1211), 0);
    EXPECT_EQ(BigInteger(-12389) % static_cast<uint32_t>(1), 0);
    EXPECT_EQ(BigInteger(12389) % static_cast<uint32_t>(1), 0);
    EXPECT_EQ(BigInteger(-524329) % static_cast<uint32_t>(79941),
              35258);
}

TEST(TestsPart1, Increment) {
    BigInteger number(123);
    EXPECT_EQ(number++, BigInteger(123));
    EXPECT_EQ(number, BigInteger(124));
    number = BigInteger(9999);
    EXPECT_EQ(++number, BigInteger(10000));
    EXPECT_EQ(number, BigInteger(10000));
    number = BigInteger(-123);
    EXPECT_EQ(number++, BigInteger(-123));
    EXPECT_EQ(number, BigInteger(-122));
    number = BigInteger(-1120);
    EXPECT_EQ(++number, BigInteger(-1119));
    EXPECT_EQ(number, BigInteger(-1119));
    number = BigInteger(-1);
    EXPECT_EQ(number++, BigInteger(-1));
    EXPECT_EQ(number, BigInteger(0));
    number = BigInteger(-1);
    EXPECT_EQ(++number, BigInteger(0));
    EXPECT_EQ(number, BigInteger(0));
    number = BigInteger(0);
    EXPECT_EQ(++number, BigInteger(1));
    EXPECT_EQ(number, BigInteger(1));
    number = BigInteger(0);
    EXPECT_EQ(number++, BigInteger(0));
    EXPECT_EQ(number, BigInteger(1));
}

TEST(TestsPart1, Decrement) {
    BigInteger number = BigInteger(123);;
    EXPECT_EQ(number--, BigInteger(123));
    EXPECT_EQ(number, BigInteger(122));
    number = BigInteger(9999);
    EXPECT_EQ(--number, BigInteger(9998));
    EXPECT_EQ(number, BigInteger(9998));
    number = BigInteger(-123);
    EXPECT_EQ(number--, BigInteger(-123));
    EXPECT_EQ(number, BigInteger(-124));
    number = BigInteger(-1118);
    EXPECT_EQ(--number, BigInteger(-1119));
    EXPECT_EQ(number, BigInteger(-1119));
    number = BigInteger(1);
    EXPECT_EQ(number--, BigInteger(1));
    EXPECT_EQ(number, BigInteger(0));
    number = BigInteger(1);
    EXPECT_EQ(--number, BigInteger(0));
    EXPECT_EQ(number, BigInteger(0));
    number = BigInteger(0);
    EXPECT_EQ(--number, BigInteger(-1));
    EXPECT_EQ(number, BigInteger(-1));
    number = BigInteger(0);
    EXPECT_EQ(number--, BigInteger(0));
    EXPECT_EQ(number, BigInteger(-1));
}

//TEST(TestsPart1, Exceptions) {
//    EXPECT_THROW(big_num_arithmetic::BigInteger::FromString("asd", 11),
//                 std::runtime_error);
//    EXPECT_THROW(big_num_arithmetic::BigInteger::FromString("1111 ", 11),
//                 std::runtime_error);
//    EXPECT_THROW(big_num_arithmetic::BigInteger::FromString("!1142 ", 11),
//                 std::runtime_error);
//    EXPECT_THROW(big_num_arithmetic::BigInteger::FromString("a1-45", 17),
//                 std::runtime_error);
//    EXPECT_THROW(big_num_arithmetic::BigInteger::FromString("aaa4b5yxz", 17),
//                 std::runtime_error);
//
//    EXPECT_THROW(BigInteger(65264).big_num_arithmetic::BigInteger::ToString(1),
//                 std::logic_error);
//    EXPECT_THROW(BigInteger(65264).big_num_arithmetic::BigInteger::ToString(0),
//                 std::logic_error);
//    EXPECT_THROW(BigInteger(-65264).big_num_arithmetic::BigInteger::ToString(37),
//                 std::logic_error);
//    EXPECT_THROW(BigInteger(-65264).big_num_arithmetic
//    ::BigInteger::ToString(4424),
//                 std::logic_error);
//    EXPECT_THROW(BigInteger(-6564).big_num_arithmetic::BigInteger::ToString(-992),
//                 std::logic_error);
//
//    EXPECT_THROW(BigInteger(-656) / BigInteger(0),
//                 big_num_arithmetic::DivisionByZeroError);
//    EXPECT_THROW(BigInteger(-656) / 0, big_num_arithmetic::DivisionByZeroError);
//    EXPECT_THROW(BigInteger(534556) % 0, big_num_arithmetic::DivisionByZeroError);
//}

