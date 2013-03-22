/**
 * @author Julian Martinez del Campo
 * @file hash_table.h
 * @note this hash table is expanded from a hash table I wrote for CMPT399: Compilers.
 * 
 * This file provides a generic hash table.
 *
 * This hash table is implemented using separate chaining. This ensures
 * at the most O(n) efficiency. However on average the lookup time should be
 * closer to O(1).
 *
 * This hash table can be used with any data type. Remember to select the
 * proper deletion options, as the values in this table can point to objects that
 * are already allocated, if removal options are set the data will be freed from
 * memory. If you decide that the data should be kept beyond the life of the 
 * hash table, use the keep options.
 */
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

/** some pre defined hash table sizes */
#define DEFAULT_HT_SIZE 211
#define SMALL_HT_SIZE 211
#define MEDIUM_HT_SIZE 503
#define LARGE_HT_SIZE 20011

/** some macros to work with delete options */
#define IS_KEEP_DATA( x ) ( (x) & 0x1 )
#define IS_KEEP_KEY( x ) ( (x) & 0x2 )

/** return codes */
typedef enum _hash_table_status {
    HT_OK = 0,              /**< everything's ok */
    HT_ITEM_NOT_FOUND,      /**< item was not found */
    HT_MEMORY_ERROR,        /**< error allocating memory */
    HT_COPY_KEY_ERROR,      /**< copy function not set */
    HT_COPY_VAL_ERROR,      /**< copy value function not set */
    HT_PRINT_ERROR,         /**< print function not set */
    HT_HASH_ERROR,          /**< hash function not set */
    HT_COMPARATOR_ERROR,    /**< comparator function not set */
    HT_INVLD_CAPACITY,      /**< invalid table capacity */
    HT_KEY_CONFLICTS,       /**< a key conflict occured (same key) */
    HT_FULL                /**< hash table is full */
} HTStatus;

/** 
 * delete options
 *
 * Options can be bitwise OR'd to get combinations. For example, to free the
 *  key from memory but keep the data allocated, use the following combination:
 *  HT_REMOVE_KEY | HT_KEEP_DATA, etc...
 */
typedef enum _hash_table_delete_options {
    HT_REMOVE_DATA = 0x1,   /**< remove data when deleting table */
    HT_REMOVE_KEY  = 0x2,   /**< remove the key */
    HT_REMOVE_ALL  = 0x3,   /**< keep data and key when deleting table */
    HT_KEEP_DATA   = 0x0,   /**< keep data */
    HT_KEEP_KEY    = 0x0,   /**< keep key */
    HT_KEEP_ALL    = 0x0   /**< keep all */
} HTDeleteOptions;

/**
 * This holds a table entry
 *
 * An entry consists of:
 *  - a key
 *  - a value associated with that key
 *  - a pointer to the next entry (if there are collisions)
 */
typedef struct _hash_table_entry {
    void * key;                                         /**< holds the key */
    void * value;                                       /**< holds the value associated with the key */
    struct _hash_table_entry * next;                    /**< next link in list */
} HTEntry;

/**
 * A hash table
 * 
 * This holds the actual hash table and associated data. This structure
 * keeps track of
 *  - the usage (how many items are currently in the table)
 *  - the capacity of the table (prime numbers are better)
 *  - deletion options (whether or not to deallocate keys and/or values)
 * This structure also contains function pointers that are used by the
 * hash table functions to perform actions. The functions required are
 *  - copy_key a function that copies the key. 
 *      This funciton must allocate memory.
 *  - copy_val a function that copies the value asssociated with the key. 
 *      This funciton must allocate memory.
 *  - comparator a funciton that compares keys stored in the table.
 *      It returns 0 if keys are the same, else return non-zero
 *  - hash a function that hashes a key
 *  - print a function that prints an HTEntry struct
 */
typedef struct _hash_table {
    HTEntry ** table;                                   /**< the actual table */
    int usage;                                          /**< how many items are in table */
    int capacity;                                       /**< size of table */
    int options;                                        /**< options for removing objects, see HTDeleteOptions for details */
    void * (*copy_key)( void * );                       /**< copy key in table */
    void * (*copy_val)( void * );                       /**< copy value in table */
    int (*comparator)( const void *, const void * );    /**< compare values in table */
    unsigned long (*hash)( void *, int );                /**< hash function */
    void (*print)( const HTEntry * );                   /**< print function */
} HashTable;

/** functions to manipulate table */
HashTable * new_htable( int init_capacity );
HTStatus init_htable( HashTable ** table, 
                  int options,
                  void * (*copy_key)( void * ), 
                  void * (*copy_val)( void * ), 
                  int (*comparator)( const void *, const void *), 
                  unsigned long (*hash)( void *, int), 
                  void (*print)( const HTEntry * ) );
void destroy_htable( HashTable ** table );
void clear_htable( HashTable ** table );
HTStatus resize_htable( HashTable ** table, int new_capacity );
HTStatus insert_htable( HashTable ** table, void * key, void * data );
HTStatus edit_htable( HashTable ** table, void * key, void * new_data );
void * lookup_htable( HashTable ** table, void * key );
HTStatus remove_htable( HashTable ** table, void * key );
HTStatus print_htable( HashTable * table );
int capacity_htable( HashTable * table );
int usage_htable( HashTable * table );
double load_htable( HashTable * table );

#endif /*  _HASH_TABLE_H_ */
