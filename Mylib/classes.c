#include <stdio.h>
#include <stdlib.h>

// This thing involves a lot of Memory Overhead

// Define the structure for the Person class
struct Person {
    char *name;
    int age;

    // Function pointers for methods
    void (*setName)(struct Person *self, const char *name);
    const char *(*getName)(const struct Person *self);
    void (*setAge)(struct Person *self, int age);
    int (*getAge)(const struct Person *self);
};

// Method to set the name of the person
void setName(struct Person *self, const char *name) {
    // You may want to free the existing name if it's not NULL
    if (self->name != NULL) {
        free(self->name);
    }

    // Allocate memory for the new name
    self->name = strdup(name);
}

// Method to get the name of the person
const char *getName(const struct Person *self) {
    return self->name;
}

// Method to set the age of the person
void setAge(struct Person *self, int age) {
    self->age = age;
}

// Method to get the age of the person
int getAge(const struct Person *self) {
    return self->age;
}

// Constructor function to initialize a new Person object
struct Person *createPerson(const char *name, int age) {
    struct Person *newPerson = (struct Person *)malloc(sizeof(struct Person));

    // Initialize the data members
    newPerson->name = NULL;
    newPerson->age = 0;

    // Assign function pointers to methods
    newPerson->setName = setName;
    newPerson->getName = getName;
    newPerson->setAge = setAge;
    newPerson->getAge = getAge;

    // Set initial values using the methods
    newPerson->setName(newPerson, name);
    newPerson->setAge(newPerson, age);

    return newPerson;
}

// Destructor function to free the memory allocated for a Person object
void destroyPerson(struct Person *person) {
    // Free the dynamically allocated name
    if (person->name != NULL) {
        free(person->name);
    }

    // Free the Person object itself
    free(person);
}

int main() {
    // Create a new Person object
    struct Person *person = createPerson("John Doe", 25);

    // Use the methods to get and set values
    printf("Name: %s\n", person->getName(person));
    printf("Age: %d\n", person->getAge(person));

    // Set new values using the methods
    person->setName(person, "Jane Doe");
    person->setAge(person, 30);

    // Print the updated values
    printf("Updated Name: %s\n", person->getName(person));
    printf("Updated Age: %d\n", person->getAge(person));

    // Destroy the Person object to free memory
    destroyPerson(person);

    return 0;
}
