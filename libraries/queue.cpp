/*
 * queue.cpp
 *
 *  Created on: 2015-7-6
 *      Author: Jake
 */
#include "queue.h"
void queue::push(unsigned char dat) {
	data[head++] = dat;
	if (head >= QUEUE_DATA_MAX_LENGTH)
		head = 0;
}
unsigned char queue::pop(void) {
	unsigned char temp = tail;
	tail++;
	if(tail >= QUEUE_DATA_MAX_LENGTH)
		tail = 0;
	return data[temp];
}
unsigned char queue::isEmpty(void) {
	if(tail == head)
		return 1;
	else
		return 0;
}
unsigned char queue::available(void) {
	if(tail > head)
		return head + QUEUE_DATA_MAX_LENGTH - tail;
	else
		return head - tail;
}
int queue::peak(void) {
	if(head == tail)
		return -1;
	else
		return (int)data[tail];
}
//void queue::flush(void) {
//	tail = head;
//}




