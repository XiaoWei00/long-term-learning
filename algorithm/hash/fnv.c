/*
FNV Hash Algorithm
References:
- http://www.isthe.com/chongo/tech/comp/fnv/
- https://datatracker.ietf.org/doc/html/draft-eastlake-fnv-03

FNV-1a Algorithm Steps:
1. Initialize the hash value with `offset_basis`.
2. For each byte in the input data:
   a. XOR the hash value with the current byte.
   b. Multiply the hash value by the prime `FNV_prime`.
3. Return the final hash value.

Key Features:
- **XOR Transformation**: Increases randomness and avoids hash values being influenced by specific data patterns.
- **Multiplication by Prime**: Ensures better bit spread, improving uniformity of hash distribution.

Optimization Notes:
- The prime `FNV_prime` is a large prime close to a power of 2. Multiplication can be optimized using shifts and additions:
  `hash × 16777619 = (hash << 24) + (hash << 8) + (hash × 3)`
- Modern CPUs have highly optimized multiplication instructions, so direct multiplication is usually faster.
- For processors without hardware multiplication (e.g., early ARM or 8-bit/16-bit MCUs), shift-add optimization may be more efficient.

Caution:
- Using powers of 2 as the prime can lead to low-bit pattern repetition. For example, multiplication by `2^16` causes the lower 16 bits to become zero, losing information from the original data.
*/

/* ===========================
 * FNV-1a 32-bit Hash Algorithm
 * =========================== */

// Constants
#define FNV_OFFSET_BASIS_32  0x811c9dc5  // Initial hash value
#define FNV_PRIME_32         0x01000193  // Prime (16777619)

// FNV-1a 32-bit Implementation
uint32_t fnv1a_32(const void *data, size_t length) {
    uint32_t hash = FNV_OFFSET_BASIS_32;  // Initialize hash value
    const uint8_t *ptr = (const uint8_t *)data;

    for (size_t i = 0; i < length; i++) {
        hash ^= ptr[i];       // XOR with current byte
        hash *= FNV_PRIME_32; // Multiply by prime to increase bit spread
    }

    return hash;
}

/* ===========================
 * FNV-1a 64-bit Hash Algorithm
 * =========================== */

// Constants
#define FNV_OFFSET_BASIS_64  0xcbf29ce484222325ULL  // Initial hash value
#define FNV_PRIME_64         0x100000001b3ULL       // Prime (1099511628211)

// FNV-1a 64-bit Implementation
uint64_t fnv1a_64(const void *data, size_t length) {
    uint64_t hash = FNV_OFFSET_BASIS_64;  // Initialize hash value
    const uint8_t *ptr = (const uint8_t *)data;

    for (size_t i = 0; i < length; i++) {
        hash ^= ptr[i];       // XOR with current byte
        hash *= FNV_PRIME_64; // Multiply by prime to increase bit spread
    }

    return hash;
}
