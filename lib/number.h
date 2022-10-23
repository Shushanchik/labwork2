#pragma once
#include <cinttypes>
#include <iostream>
#include <cmath>
const int uint2022_size = 68;
const int radix = 1000000000;
struct uint2022_t {
    unsigned int digits[uint2022_size] = {0 };
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator * (const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator * (uint32_t lhs_int, const uint2022_t& rhs);

uint2022_t operator * (const uint2022_t& lhs, uint32_t rhs_int);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator < (const uint2022_t lhs, const uint2022_t rhs);

bool operator <= (const uint2022_t lhs, const uint2022_t rhs);

bool operator == (const uint2022_t& lhs, const uint2022_t& rhs);

bool operator != (const uint2022_t& lhs, const uint2022_t& rhs);

bool operator >= (const uint2022_t lhs, const uint2022_t rhs);

bool operator > (const uint2022_t lhs, const uint2022_t rhs);
std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
