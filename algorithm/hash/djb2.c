#include <stdio.h>
#include <stdlib.h>

/*
djb2 Hash Function Analysis:

1. Non-linearity in Finite Binary Arithmetic:
    - Although multiplication and addition are linear operations, in finite-width binary arithmetic, carry propagation introduces non-linear characteristics.
    - A small change in lower bits can cause a carry, affecting higher bits and resulting in widespread changes in the overall result.

2. Why Choose 33 as the Multiplier:
    - Odd Number: Multiplying by an odd number avoids loss of information in lower bits. For example, multiplying by an even number like 2 always results in the least significant bit being 0, reducing the "information content."
    - Form of 2^n + 1: The number 33 can be expressed as 32 + 1, which allows efficient computation using bitwise operations (left shift and addition).
    - Practical Balance: The choice of 33 is not purely based on mathematical theory but is a compromise derived from mathematical analysis and engineering practice.

3. Why Choose 5381 as the Initial Value:
    - Odd Number: Ensures no loss of information during hash computation.
    - Good Binary Properties: The binary representation of 5381 (101010000101) allows for uniform influence on hash value changes during bitwise operations.
    - Practical Performance: While the initial value does not necessarily need to be a prime number, 5381 has shown good performance in practice and is computationally efficient due to its relatively small size.

4. Overflow Considerations:
    - The hash value may overflow on different machines. To handle this, you can take the modulus of the hash value as needed.
    - Using `unsigned long` ensures truncation behavior, which is often acceptable for hash functions.

5. Applicability:
    - This hash function is particularly well-suited for strings.

*/

/* djb2 Hash Function */
unsigned long djb2(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Error: Null string passed to djb2.\n");
        exit(EXIT_FAILURE);
    }

    unsigned long hash = 5381; // Initial hash value
    int c;

    while ((c = *str++)) {
        /*
        Hash computation:
        - Multiply the current hash value by 33 (hash * 33 + c).
        - 33 = 32 + 1, which is efficiently computed as (hash << 5) + hash.
        */
        hash = ((hash << 5) + hash) + c; // Equivalent to hash * 33 + c
    }

    return hash;
}

/* Test the djb2 function */
int main() {
    const char *test_str = "hello";
    unsigned long hash_value = djb2(test_str);
    printf("Hash value for '%s': %lu\n", test_str, hash_value);

    return 0;
}
