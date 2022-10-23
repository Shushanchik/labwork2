#include "number.h"


uint2022_t from_uint (uint32_t i) {
    uint2022_t uint2022;
    uint2022.digits[0] = i%radix;
    uint2022.digits[1] = (i-i%radix)/radix;
    for (int digit_index = 2; digit_index < uint2022_size; digit_index++) {
        uint2022.digits[digit_index] = 0;
    }
    return uint2022_t();
}

uint2022_t from_string (const char* buff) {
    uint2022_t uint2022{};
    int number_length = sizeof buff;
    int digit_index;
    int string_index;
    for (digit_index = 0; digit_index <= number_length - 2; digit_index += 9) {
        string_index = (number_length - 2) - digit_index;
        for (int int_index = string_index; int_index > string_index - 9; int_index--) {
            uint2022.digits[digit_index] += (int(buff[int_index]) - int('0'))*(pow(10, string_index - int_index));
        }
    }
    for (int int_index = string_index%9; int_index > 0; int_index--) {
        uint2022.digits[digit_index++] += (int(buff[int_index]) - int('0'))* pow(10, string_index - int_index);
    }
    while (digit_index < uint2022_size) {uint2022.digits[digit_index++] = 0;}
    return uint2022_t();
}

uint2022_t operator + (const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t sum;
    int sum_overflow = 0;
    for (int digit_index = 0; digit_index < uint2022_size; digit_index++) {
        int sum_of_digits = lhs.digits[digit_index] + rhs.digits[digit_index];
        sum.digits[digit_index] = (sum_of_digits + sum_overflow) % radix;
        sum_overflow = (sum_of_digits - sum_of_digits % radix) / radix;
    }
    return sum;
}

uint2022_t operator - (const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t difference;
    int diff_overflow = 0;
    for (int digit_index = 0; digit_index < uint2022_size; digit_index--) {
        int diff_of_digits = lhs.digits[digit_index] - rhs.digits[digit_index];
        difference.digits[digit_index] = (diff_of_digits - diff_overflow) % radix;
        int criterium = radix + (diff_of_digits - diff_overflow);
        diff_overflow = 1 - ((criterium - criterium%radix) / radix);
    }
    return difference;
}

uint2022_t operator * (const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint2022_t digit_result;
    int mult_overflow = 0;
    for (int lhs_digit_index = 0; lhs_digit_index < uint2022_size; lhs_digit_index++) {
        for (int exponent = 0; exponent < lhs_digit_index; exponent++) {digit_result.digits[exponent] = 0;}
        for (int rhs_digit_index = 0; rhs_digit_index < uint2022_size; rhs_digit_index++) {
            int multiplication_of_digits = lhs.digits[lhs_digit_index]*rhs.digits[rhs_digit_index];
            digit_result.digits[rhs_digit_index+lhs_digit_index] =
                    (multiplication_of_digits + mult_overflow) % radix;
            mult_overflow = ( (multiplication_of_digits + mult_overflow)
                              - (multiplication_of_digits) % radix )
                            / radix;
        }
        result = result + digit_result;
    }
    return result;
}

uint2022_t operator * (uint32_t lhs_int, const uint2022_t& rhs) {
    uint2022_t lhs = from_uint(lhs_int);
    uint2022_t result;
    uint2022_t digit_result;
    int mult_overflow = 0;
    for (int lhs_digit_index = 0; lhs_digit_index < uint2022_size; lhs_digit_index++) {
        for (int exponent = 0; exponent < lhs_digit_index; exponent++) {digit_result.digits[exponent] = 0;}
        for (int rhs_digit_index = 0; rhs_digit_index < uint2022_size; rhs_digit_index++) {
            int multiplication_of_digits = lhs.digits[lhs_digit_index]*rhs.digits[rhs_digit_index];
            digit_result.digits[rhs_digit_index+lhs_digit_index] =
                    (multiplication_of_digits + mult_overflow) % radix;
            mult_overflow = ( (multiplication_of_digits + mult_overflow)
                              - (multiplication_of_digits) % radix )
                            / radix;
        }
        result = result + digit_result;
    }
    return result;
}

uint2022_t operator * (const uint2022_t& lhs, uint32_t rhs_int) {
    uint2022_t rhs = from_uint(rhs_int);
    uint2022_t result;
    uint2022_t digit_result;
    int mult_overflow = 0;
    for (int lhs_digit_index = 0; lhs_digit_index < uint2022_size; lhs_digit_index++) {
        for (int exponent = 0; exponent < lhs_digit_index; exponent++) {digit_result.digits[exponent] = 0;}
        for (int rhs_digit_index = 0; rhs_digit_index < uint2022_size; rhs_digit_index++) {
            int multiplication_of_digits = lhs.digits[lhs_digit_index]*rhs.digits[rhs_digit_index];
            digit_result.digits[rhs_digit_index+lhs_digit_index] =
                    (multiplication_of_digits + mult_overflow) % radix;
            mult_overflow = ( (multiplication_of_digits + mult_overflow)
                              - (multiplication_of_digits) % radix )
                            / radix;
        }
        result = result + digit_result;
    }
    return result;
}

uint2022_t operator / (const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint2022_t remainder;
    uint2022_t divided;
    int digit_index = uint2022_size - 1;
    while (digit_index >= 0) {
        divided = remainder * radix + from_uint(lhs.digits[digit_index]);
        int l = 0, r = radix, result_digit = (l+r)/2;
        while (not(
                (divided >= rhs * result_digit) and
                (divided < rhs * (result_digit + 1) or (result_digit + 1 == radix))
        )) {
            if (divided < rhs * result_digit) {r = (l+r)/2;}
            if (divided == rhs * (result_digit + 1)) {
                result_digit++;
                break;
            }
            if (divided > rhs * (result_digit + 1)) {l = (l+r)/2;}
            result_digit = (l + r)/2;
        }
        remainder = divided - rhs * result_digit;
        result.digits[digit_index--] = result_digit;
    }
    return result;
}

bool operator < (const uint2022_t lhs, const uint2022_t rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] < rhs.digits[digit_index]);
}

bool operator <= (const uint2022_t lhs, const uint2022_t rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] <= rhs.digits[digit_index]);
}

bool operator == (const uint2022_t& lhs, const uint2022_t& rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] == rhs.digits[digit_index]);
}

bool operator != (const uint2022_t& lhs, const uint2022_t& rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] != rhs.digits[digit_index]);
}

bool operator >= (const uint2022_t lhs, const uint2022_t rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] >= rhs.digits[digit_index]);
}

bool operator > (const uint2022_t lhs, const uint2022_t rhs) {
    int digit_index = uint2022_size - 1;
    while (lhs.digits[digit_index] == rhs.digits[digit_index] and digit_index > 0) {digit_index--;}
    return (lhs.digits[digit_index] > rhs.digits[digit_index]);
}

std::ostream& operator << (std::ostream& stream, const uint2022_t& value) {
    bool first_digit = true;
    for (int digit_index = 1; digit_index <= uint2022_size; digit_index++) {
        int exponent = radix/10;
        while (exponent > value.digits[uint2022_size - digit_index] and first_digit) {
            stream << '0';
            exponent /= 10;
        }
        std::cout << value.digits[digit_index];
        first_digit = false;
    }
    return stream;
}
