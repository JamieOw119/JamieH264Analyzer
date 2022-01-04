#pragma once

#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

const std::string coeffTokenMap[1][62] = {
	{ "1", "000101", "01", "00000111", "000100", "001", "000000111", "00000110", "0000101", "00011", "0000000111", "000110", "00000101", "000011", "00000000111", "0000000110", "000000101", "0000100", "0000000001111", "00000000110", "0000000101", "00000100", "0000000001011", "0000000001110", "00000000101", "000000100", "0000000001000", "0000000001010", "0000000001101", "0000000100", "00000000001111", "00000000001110", "0000000001001", "00000000100", "00000000001011", "00000000001010", "00000000001101", "0000000001100", "000000000001111", "000000000001110", "00000000001001", "00000000001100", "000000000001011", "000000000001010", "000000000001101", "00000000001000", "0000000000001111", "000000000000001", "000000000001001", "000000000001100", "0000000000001011", "0000000000001110", "0000000000001101", "000000000001000", "0000000000000111", "0000000000001010", "0000000000001001", "0000000000001100", "0000000000000100", "0000000000000110", "0000000000000101", "0000000000001000" }
};

const std::string totalZerosMap[16][16] = {
	{ "", "1", "111", "0101", "00011", "0101", "000001", "000001", "000001", "000001", "00001", "0000", "0000", "000", "00", "0" },
	{ "", "011", "110", "111", "111", "0100", "00001", "00001", "0001", "000000", "00000", "0001", "0001", "001", "01", "1" },
	{ "", "010", "101", "110", "0101", "0011", "111", "101", "00001", "0001", "001", "001", "01", "1", "1" },
	{ "", "0011", "100", "101", "0100", "111", "110", "100", "011", "11", "11", "010", "1", "01" },
	{ "", "0010", "011", "0100", "110", "110", "101", "101", "11", "10", "10", "1", "001" },
	{ "", "00011", "0101", "0011", "101", "101", "100", "11", "10", "001", "01", "011" },
	{ "", "00010", "0100", "100", "100", "100", "011", "010", "010", "01", "0001" },
	{ "", "000011", "0011", "011", "0011", "011", "010", "0001", "001", "0000", "1" },
	{ "", "000010", "0010", "0010", "011", "0010", "0001", "001", "000000" },
	{ "", "0000011", "00011", "00011", "0010", "00001", "001", "000000" },
	{ "", "0000010", "00010", "00010", "00010", "0001", "000000" },
	{ "", "00000011", "000011", "000001", "00001", "00000" },
	{ "", "00000010", "000010", "00001", "00000" },
	{ "", "000000011", "000001", "000000" },
	{ "", "000000010", "000000" },
	{ "", "000000001" }
};

const std::string runBeforeMap[15][8] = {
	{ "", "1", "1", "11", "11", "11", "11", "111" },
	{ "", "0", "01", "10", "10", "10", "000", "110" },
	{ "", "", "00", "01", "01", "011", "001", "101" },
	{ "", "", "", "00", "001", "010", "011", "100" },
	{ "", "", "", "", "000", "001", "010", "011" },
	{ "", "", "", "", "", "000", "101", "010" },
	{ "", "", "", "", "", "", "100", "001" },
	{ "", "", "", "", "", "", "", "0001" },
	{ "", "", "", "", "", "", "", "00001" },
	{ "", "", "", "", "", "", "", "000001" },
	{ "", "", "", "", "", "", "", "0000001" },
	{ "", "", "", "", "", "", "", "00000001" },
	{ "", "", "", "", "", "", "", "000000001" },
	{ "", "", "", "", "", "", "", "0000000001" },
	{ "", "", "", "", "", "", "", "00000000001" }
};
