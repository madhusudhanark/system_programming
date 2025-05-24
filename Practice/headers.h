#include <stdint.h>
#include<stddef.h>
#ifndef HEADERS_H

#define HEADERS_H
extern int int_1;
extern uint16_t x16;
extern uint32_t x32;
extern uint32_t *x32_ptr1;
extern uint32_t **x32_ptr2;


void  addition(uint32_t x,uint32_t y);
void Take_fun_argument(void (*function)(uint32_t fun_var , uint32_t fun_var1),void *ptr);

uint32_t subraction(uint32_t *x,uint32_t *y);

void multiplication(uint32_t x[],uint32_t y[], uint32_t len_x,uint32_t len_y ,uint32_t *sum);
void division(uint32_t *x,uint32_t *y , float *result);

//interrupt functions to demonstrate  
void Interrupt_1(uint32_t var_1 , uint32_t  *var_2  );
void Interrupt_2(uint32_t var_1 , uint32_t  *var_2  );
void Interrupt_3(uint32_t var_1 , uint32_t  *var_2  );
/*the below function created to understand void **/

void swap(void *a, void *b, size_t size);
void swap_check();


#endif