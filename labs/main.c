#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include "spi.h"

node *head = NULL;  //head node 
int TEMP_BUFF[100]; // circular buffer array to store temp values

int main()
{

    int wrtie_index = 0;
    int loop_count = 0;
    while(loop_count < 10)
    {
            wrtie_index = wrtie_index % 10;
            TEMP_BUFF[wrtie_index++] = spi_master_send(0x01);
            printf("from printf  main %d\n",TEMP_BUFF[wrtie_index-1]);
            push_end(TEMP_BUFF[wrtie_index-1]);
            usleep(100000);
            loop_count++;
            //wrtie_index++;

    }
    display();
    return 0;
}
