#include "pch.h"

#include <string>
#include <ostream>
#include <gtest/gtest.h>

void add_diamond_line(std::stringstream& oss,
	char letter, int spacesBefore, int spacesBetween)
{
	oss << std::string(spacesBefore, ' ') << letter;
	if (spacesBetween > 0)
		oss << std::string(spacesBetween, ' ') << letter;
}

class AddDiamondLineTestFixture
	: public ::testing::TestWithParam<std::tuple<char, int, int, std::string>> {};

TEST_P(AddDiamondLineTestFixture, AddDiamondLineAndTestLineResult)
{
	std::stringstream oss;
	auto& param = GetParam();

	char letter = std::get<0>(param);
	int spacesBefore = std::get<1>(param);
	int spacesBetween = std::get<2>(param);
	std::string expected = std::get<3>(param);

	add_diamond_line(oss, letter, spacesBefore, spacesBetween);
	EXPECT_EQ(expected, oss.str());
}

INSTANTIATE_TEST_CASE_P(
	DiamondTestSuite,
	AddDiamondLineTestFixture,
	::testing::Values(
		std::make_tuple('A', 1, 0, " A"),
		std::make_tuple('B', 0, 1, "B B"),
		std::make_tuple('A', 2, 0, "  A"),
		std::make_tuple('B', 1, 1, " B B"),
		std::make_tuple('C', 0, 3, "C   C")
	)
);

void create_diamond_top(std::stringstream& oss, char currentLetter, char diamondCenterLetter)
{
	if (currentLetter > diamondCenterLetter) return;

	static constexpr char BASE_A = 'A';
	int n = diamondCenterLetter - BASE_A;
	int currentPos = currentLetter - BASE_A;

	add_diamond_line(oss, currentLetter, n - currentPos, 2 * currentPos - 1);
	
	if (++currentLetter <= diamondCenterLetter)
	{
		oss << '\n';
		create_diamond_top(oss, currentLetter, diamondCenterLetter);
	}
}

class CreateDiamondTopTestFixture
	: public ::testing::TestWithParam<std::tuple<char, std::string>> {};

TEST_P(CreateDiamondTopTestFixture, CreateDiamondAndTestTopFace)
{
	std::stringstream oss;
	auto& param = GetParam();

	char diamondCenterLetter = std::get<0>(param);
	std::string expected = std::get<1>(param);

	create_diamond_top(oss, 'A', diamondCenterLetter);
	EXPECT_EQ(expected, oss.str());
}

INSTANTIATE_TEST_CASE_P(
	DiamondTestSuite,
	CreateDiamondTopTestFixture,
	::testing::Values(
		std::make_tuple('A', "A"),
		std::make_tuple('B', " A\nB B"),
		std::make_tuple('C', "  A\n B B\nC   C")
	)
);

void create_diamond_bot(std::stringstream& oss, char currentLetter, char diamondCenterLetter)
{
	static constexpr char BASE_A = 'A';
	if (currentLetter < BASE_A) return;

	int n = diamondCenterLetter - BASE_A;
	int currentPos = currentLetter - BASE_A;

	add_diamond_line(oss, currentLetter, n - currentPos, 2 * currentPos - 1);

	if (--currentLetter >= BASE_A)
	{
		oss << '\n';
		create_diamond_bot(oss, currentLetter, diamondCenterLetter);
	}
}

class CreateDiamondBotTestFixture
	: public ::testing::TestWithParam<std::tuple<char, std::string>> {};

TEST_P(CreateDiamondBotTestFixture, CreateDiamondAndTestBotFace)
{
	std::stringstream oss;
	auto& param = GetParam();

	char diamondCenterLetter = std::get<0>(param);
	std::string expected = std::get<1>(param);

	create_diamond_bot(oss, diamondCenterLetter, diamondCenterLetter);
	EXPECT_EQ(expected, oss.str());
}

INSTANTIATE_TEST_CASE_P(
	DiamondTestSuite,
	CreateDiamondBotTestFixture,
	::testing::Values(
		std::make_tuple('A', "A"),
		std::make_tuple('B', "B B\n A"),
		std::make_tuple('C', "C   C\n B B\n  A")
	)
);
