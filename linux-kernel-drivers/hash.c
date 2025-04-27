/*
 * Multiplicative Hash Function
 * 1. Avoid using modulo operation (%): Modulo is a relatively slow operation,
 *    especially on hardware that does not support integer division.
 * 2. GOLDEN_RATIO_64 is a variant of an irrational number, used to minimize hash collisions.
 *    It ensures that different input values, after the multiplication transformation,
 *    are evenly distributed in the 64-bit space.
 * 3. Right shift operation (64 - bits): By retaining the high bits and discarding
 *    the low bits, the final hash value is ensured to be in the range of 0 to 2^bits - 1.
 */

static __always_inline u32 hash_64_generic(u64 val, unsigned int bits)
{
#if BITS_PER_LONG == 64
    /* For 64-bit processors, use efficient 64x64-bit multiplication */
    return val * GOLDEN_RATIO_64 >> (64 - bits);
#else
    /* For 32-bit processors, use 32x32-bit multiplication to handle 64-bit input */
    return hash_32((u32)val ^ __hash_32(val >> 32), bits);
#endif
}

/*
 * Data Structure Definitions
 * hlist_head: The head of a hash linked list, pointing to the first node in the list.
 * hlist_node: A node in the hash linked list, containing pointers to the next node
 *             and the previous node's pointer.
 */

struct hlist_head {
    struct hlist_node *first; // Points to the first node in the list
};

struct hlist_node {
    struct hlist_node *next;  // Points to the next node
    struct hlist_node **pprev; // Points to the previous node's next pointer
};

/*
 * Hash Table Definition Macro
 * DEFINE_HASHTABLE(name, bits): Defines a hash table with 2^bits buckets.
 * Each bucket is initialized to HLIST_HEAD_INIT.
 */

#define DEFINE_HASHTABLE(name, bits)						\
    struct hlist_head name[1 << (bits)] =					\
            { [0 ... ((1 << (bits)) - 1)] = HLIST_HEAD_INIT }

