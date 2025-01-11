#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
  char *name;
  int   age;
  float height;
};

struct Person *Person_create(char *name, int age, float height)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);
  who->name   = strdup(name);
  who->age    = age;
  who->height = height;
  return who;
}

void Person_print(struct Person *who)
{
  printf("name : %s\n", who->name);
  printf("age : %d\n", who->age);
  printf("height : %f\n", who->height);
}

void Person_destroy(struct Person *who)
{
  // assert(who != NULL);

  free(who->name);
  free(who);
}

int main()

{
  struct Person *joe   = Person_create("Joe Alex", 32, 64);
  struct Person *frank = Person_create("Frank Blank", 20, 72);
  Person_print(joe);
  Person_print(frank);
  Person_destroy(joe);
  Person_destroy(NULL);
}
