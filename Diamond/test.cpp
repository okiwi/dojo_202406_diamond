#include "pch.h"

#include <string>
#include <ostream>

/*
* "chaine"
* R"(
* ")
*/

/*
	oss << std::endl;
	oss << ' ' << 'A' << std::endl;
	oss << "B B" << std::endl;
	oss << " A";
*/

int countNbOfLines(std::string diamond) {
	return diamond.length();
}

std::string diamond(char letter) {
	std::stringstream oss;

	if (letter == 'B') {
		oss << R"(
 A
B B
 A)";
	}
	else {
		oss << R"(
  A
 B B
C   C
 B B
  A)";
	}

	return oss.str();
}

void addSpaces(std::stringstream &os, int count) {
	
	for (; count > 0; count--) {
		os << '_';
	}
}

std::string diamondDelta(char letter) {
	std::stringstream oss;
	int first=(int)'B';
	int last = (int)letter;
	oss << std::endl;
	addSpaces(oss, last - first + 1);
	oss << 'A' << std::endl;
	while(first!=last){
		addSpaces(oss, last - first);
		oss << (char)first;
		addSpaces(oss, 2*(first-(int)'A'-2)+1);
		oss << std::endl;
		first++;
	}
	while (first != (int)'A'){
		addSpaces(oss, last - first);
		oss << (char)first;
		addSpaces(oss, 2 * (first - (int)'A'-2) + 1);
		oss << std::endl;
		first--;
	}
	addSpaces(oss, last - first);
	oss << 'A';
	return oss.str();
}

TEST(DiamondTestSuite, TestDiamondB) {
  EXPECT_EQ(diamond('B'), R"(
 A
B B
 A)");
}

TEST(DiamondTestSuite, TestDiamondC) {
	EXPECT_EQ(diamond('C'), R"(
  A
 B B
C   C
 B B
  A)");
}

TEST(DiamondTestSuite, TestAddOneSpace) {
	std::stringstream oss;
	addSpaces(oss, 1);
	EXPECT_EQ("_", oss.str() );
	}

TEST(DiamondTestSuite, TestDiamondDeltaC) {
	EXPECT_EQ(diamondDelta('C'), R"(
__A
_B_
C___
_B_
__A)");
}