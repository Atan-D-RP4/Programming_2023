#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Dyn_Arr;

typedef struct {
    Dyn_Arr *(*_new)(void);
    void (*push)(Dyn_Arr *self, int val);
    void (*pop)(Dyn_Arr *self);
    int (*get)(Dyn_Arr *self, size_t index);
    void (*set)(Dyn_Arr *self, size_t index, int val);
    size_t (*size)(Dyn_Arr *self);
    size_t (*capacity)(Dyn_Arr *self);
    void (*free)(Dyn_Arr *self);
} Dyn_Arr_Funcs;

typedef struct {
    Dyn_Arr_Funcs *items;
    size_t count;
    size_t capacity;
} Dyn_ArrVTable;

Dyn_ArrVTable da_vtable = {0};

void nob_da_append(Dyn_ArrVTable *da, Dyn_Arr_Funcs item) {
    if (da->count >= da->capacity) {
        da->capacity = da->capacity == 0 ? 4 : da->capacity * 2;
        da->items = realloc(da->items, da->capacity * sizeof(Dyn_Arr_Funcs));
    }
    da->items[da->count++] = item;
}

size_t Dyn_ArrVTable_register(Dyn_ArrVTable *vtable, Dyn_Arr_Funcs funcs) {
    size_t tag = vtable->count;
    nob_da_append(vtable, funcs);
    return tag;
}

Dyn_Arr *new_dyn_arr(void) {
    Dyn_Arr *arr = malloc(sizeof(Dyn_Arr));
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
    return arr;
}

void dyn_arr_push(Dyn_Arr *self, int val) {
    if (self->size >= self->capacity) {
        self->capacity = self->capacity == 0 ? 4 : self->capacity * 2;
        self->data = realloc(self->data, self->capacity * sizeof(int));
    }
    self->data[self->size++] = val;
}

int dyn_arr_get(Dyn_Arr *self, size_t index) {
    if (index >= self->size) {
        return 0; // or handle the out-of-bounds error
    }
    return self->data[index];
}

void dyn_arr_set(Dyn_Arr *self, size_t index, int val) {
    if (index >= self->size) {
        return; // or handle the out-of-bounds error
    }
    self->data[index] = val;
}

size_t dyn_arr_size(Dyn_Arr *self) {
    return self->size;
}

size_t dyn_arr_capacity(Dyn_Arr *self) {
    return self->capacity;
}

void dyn_arr_free(Dyn_Arr *self) {
    free(self->data);
    free(self);
}

void Dyn_ArrVTable_init(Dyn_ArrVTable *vtable) {
    Dyn_Arr_Funcs new_funcs = {
        ._new = new_dyn_arr,
        .push = dyn_arr_push,
        .get = dyn_arr_get,
        .set = dyn_arr_set,
        .size = dyn_arr_size,
        .capacity = dyn_arr_capacity,
        .free = dyn_arr_free
    };
    vtable->count = 0;
    vtable->capacity = 4;
    vtable->items = malloc(vtable->capacity * sizeof(Dyn_Arr_Funcs));
    size_t new_index = Dyn_ArrVTable_register(vtable, new_funcs);
    // Add other function registrations here
}

Dyn_Arr *da_new(void) {
    return da_vtable.items[0]._new();
}

void da_push(Dyn_Arr *self, int val) {
    da_vtable.items[0].push(self, val);
}

size_t da_size(Dyn_Arr *self) {
    return da_vtable.items[0].size(self);
}

size_t da_capacity(Dyn_Arr *self) {
    return da_vtable.items[0].capacity(self);
}

void da_free(Dyn_Arr *self) {
    da_vtable.items[0].free(self);
}

int main() {
    Dyn_ArrVTable_init(&da_vtable);

    Dyn_Arr *arr = da_new();
    da_push(arr, 10);
    da_push(arr, 20);

    printf("Size: %zu\n", da_size(arr));
    printf("Capacity: %zu\n", da_capacity(arr));

    printf("Value at index 0: %d\n", da_vtable.items[0].get(arr, 0));
    printf("Value at index 1: %d\n", da_vtable.items[0].get(arr, 1));

    da_free(arr);
    free(da_vtable.items);

    return 0;
}
