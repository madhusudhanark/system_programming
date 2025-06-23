
#define MADHU_H 2
extern int TEMP_BUFF[];
extern node*head;
typedef struct node
{
  char* str;
  const int data;
  void(*fnptr)(void);
  struct node *next;
}node;

int spi_sensor_read(uint8_t command);
int spi_master_send(uint8_t command);



