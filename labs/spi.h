
#include<stdio.h>
#include<stdint.h>
#define MADHU_H 2
extern int TEMP_BUFF[];

typedef struct node
{
  char* str;
  int data;
  void(*fnptr)(void);
  struct node *next;
}node;

extern node  *head;

int spi_sensor_read(uint8_t command);
int spi_master_send(uint8_t command);
void display();
void push_end(int data);



