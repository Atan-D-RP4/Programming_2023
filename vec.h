/* STB-style vector implementation
 *
 * Must be compiler with GCC as it uses the typeof() function which is a GCC
 * extension.
 */
#ifndef VEC_H_
#define VEC_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    void *(*alloc)(size_t bytes, void *context);
    void *(*free)(size_t bytes, void *ptr, void *context);
    void *context;
} Allocator;

typedef struct {
    size_t length;
    size_t capacity;
    size_t padding;
    Allocator* a;
} Vec_Header;

#ifdef VEC_IMPLEMENTATION

#define ARRAY_INITIAL_CAPACITY 16

#define Vec(T, a) vec_init(sizeof(T), ARRAY_INITIAL_CAPACITY, a)
#define vec_header(a) ((Vec_Header *)(a) - 1)
#define vec_length(a) (vec_header(a)->length)
#define vec_capacity(a) (vec_header(a)->capacity)

void *vec_init(size_t item_size, size_t capacity, Allocator *a);
void *vec_ensure_capacity(void *a, size_t item_count, size_t item_size);

// void *my_alloc(size_t bytes, void *context) {
//     (void)context;
//     return malloc(bytes);
// }
//
// void *my_free(size_t bytes, void *ptr, void *context) {
//     (void)ptr; (void)context;
//     free(ptr);
// }
//
// Allocator my_allocator = {my_alloc, my_free, 0};

void *vec_init(size_t item_size, size_t capacity, Allocator *a) {
    size_t header_size = item_size * capacity + sizeof(Vec_Header);
    size_t vec_size = item_size * capacity;
    size_t total_size = header_size + vec_size;

    void *ptr = a->alloc(total_size, a->context);

    if (ptr) {
        Vec_Header *h = (Vec_Header *)ptr;
        h->capacity = capacity;
        h->length = 0;
        h->a = a;
        void *arr_ptr = h + 1;
        return arr_ptr;
    }

    return NULL;
}

void *vec_ensure_capacity(void *a, size_t item_count, size_t item_size) {
    Vec_Header *h = vec_header(a);
    size_t desired_capacity = h->length + item_count;

    if (h->capacity < desired_capacity) {
        size_t new_capacity = h->capacity * 2;
        while (new_capacity < desired_capacity) {
            new_capacity *= 2;
        }

        size_t new_size = sizeof(Vec_Header) + new_capacity * item_size;
        Vec_Header *new_h = h->a->alloc(new_size, h->a->context);
        assert(new_h != NULL && "Failed to allocate memory");

        if (new_h) {
            size_t old_size = sizeof(*h) + h->length * item_size;
            memcpy(new_h, h, old_size);

            if (h->a->free) {
                h->a->free(old_size, h, h->a->context);
            }

            new_h->capacity = new_capacity;
            h = new_h + 1;
        } else {
            h = 0;
        }
    } else { h += 1; }

    return h;
}

#define vec_append(a, v) ( \
    (a) = vec_ensure_capacity(a, 1, sizeof(v)), \
    (a)[vec_header(a)->length] = (v), \
    &(a)[vec_header(a)->length++]) \

#define vec_insert(a, i, v) ({ \
    (a) = vec_ensure_capacity(a, 1, sizeof(v)); \
    memmove((a) + (i - 1) + 1, (a) + (i - 1), (vec_header(a)->length - (i)) * sizeof(*(a))); \
    (a)[i - 1] = (v); \
    vec_header(a)->length += 1; \
})

#define vec_remove(a, i) ({ \
    Vec_Header* header = vec_header(a); \
    typeof(*(a)) removed_value = (a)[i - 1]; \
    memmove((a) + (i - 1), (a) + (i - 1) + 1, (header->length - (i)) * sizeof(*(a))); \
    header->length -= 1; \
    removed_value; \
})

#define vec_pop_back(a) ({ \
    typeof(*(a)) removed_value = (a)[vec_header(a)->length - 1]; \
    vec_header(a)->length -= 1; \
    removed_value; \
})

#endif // VEC_IMPLEMENTATION
#endif // VEC_H_
