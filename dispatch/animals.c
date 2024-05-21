#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../nob.h"

typedef struct {
    const char **items;
    size_t count;
    size_t capacity;
} Toilet;

#define toilet_place(toilet, item) nob_da_append(toilet, item)

void toilet_lookinto(Toilet *toilet)
{
    fprintf(stdout, "Toilet Contains:\n");
    if (toilet->count == 0) {
        fprintf(stdout, "\tNothing\n");
        return;
    }
    for (size_t i = 0; i < toilet->count; i++) {
        fprintf(stdout, "\tToilet: %s\n", toilet->items[i]);
    }
}

void toilet_flush(Toilet *toilet)
{
    fprintf(stdout, "Flushing Toilet\n");
    toilet->count = 0;
}

// Interface BEGIN
// interface Animal
typedef struct {
    size_t tag;
    void *data;
} Animal;

typedef struct {
    void (*say)(void *);
    void (*poop)(void *, Toilet *toilet);
} AnimalMethods;

struct {
    AnimalMethods *items;
    size_t count;
    size_t capacity;
} ANIMAL_VTABLE = { 0 };

size_t vtable_register(AnimalMethods methods) {
    size_t index = ANIMAL_VTABLE.count;
    nob_da_append(&ANIMAL_VTABLE, methods);
    return index;
}

void animal_say(Animal animal)
{
    ANIMAL_VTABLE.items[animal.tag].say(animal.data);
}

void animal_poop(Animal animal, Toilet *toilet)
{
    ANIMAL_VTABLE.items[animal.tag].poop(animal.data, toilet);
}
// Interface END

// class Dog BEGIN
size_t DOG_TAG = 0;
typedef struct {
    const char *colon;
} Dog_Data;

Animal dog_new(void)
{
    Dog_Data *dog = calloc(1, sizeof(Dog_Data));
    dog->colon = "DOG_POOP";
    return (Animal) { DOG_TAG, dog };
}

void dog_say(void *data)
{
    Dog_Data *dog = (Dog_Data *)data;
    fprintf(stdout, "*BARK*\n");
}

void dog_poop(void *data, Toilet *toilet)
{
    Dog_Data *dog = (Dog_Data *)data;
    if (dog->colon) {
        toilet_place(toilet, dog->colon);
        dog->colon = NULL;
    }
}

// class Dog END

// class Cat BEGIN
size_t CAT_TAG = 0;
typedef struct {
    const char *colon;
} Cat_Data;

Animal cat_new(void)
{
    Cat_Data *cat = calloc(1, sizeof(Cat_Data));
    cat->colon = "CAT_POOP";
    return (Animal) { CAT_TAG, cat };
}

void cat_say(void *data)
{
    Cat_Data *cat = (Cat_Data *)data;
    fprintf(stdout, "*MEOW*\n");
}

void cat_poop(void *data, Toilet *toilet)
{
    Cat_Data *cat = (Cat_Data *)data;
    if (cat->colon) {
        toilet_place(toilet, cat->colon);
        cat->colon = NULL;
    }
}

void Animal_init(void)
{
    DOG_TAG = vtable_register((AnimalMethods) { dog_say, dog_poop });
    CAT_TAG = vtable_register((AnimalMethods) { cat_say, cat_poop });
}

int main(void)
{
    Animal_init();
    Toilet toilet = { 0 };
    struct {
        Animal *items;
        size_t count;
        size_t capacity;
    } animals = { 0 };

    nob_da_append(&animals, dog_new());
    nob_da_append(&animals, cat_new());

    toilet_lookinto(&toilet);

    for (size_t i = 0; i < animals.count; i++) {
        animal_say(animals.items[i]);
        animal_poop(animals.items[i], &toilet);
    }

    toilet_lookinto(&toilet);
    toilet_flush(&toilet);
    toilet_lookinto(&toilet);

    for (size_t i = 0; i < animals.count; i++) {
        animal_say(animals.items[i]);
        animal_poop(animals.items[i], &toilet);
    }
    toilet_lookinto(&toilet);

    return 0;
}
