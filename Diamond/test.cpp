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