#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include "spi.h"


// Simulated SPI sensor (slave)
int spi_sensor_read(uint8_t command) 
{
    printf("%d\n",TEMP_BUFF[0]);

 switch (command) 
 {
    case 0x01: return rand();// Example: temperature
    case 0x02: return 0x5A;// Example: humidity
    default: return 0x00;// Unknown command
}
}

// Simulated SPI master
int  spi_master_send(uint8_t command)
 {
    
    //printf("Master sends command: 0x%02X\n", command);
    int response = spi_sensor_read(command);
    //printf("Sensor responds with: %d\n", response);
    return response;
}

void task1()
{
    printf("task1");
}
void task2()
{
    printf("task2");
}

void task3()
{
    printf("task3");
}
