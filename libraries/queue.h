/*
 * queue.h
 *
 *  Created on: 2015-7-6
 *      Author: Jake
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#ifndef QUEUE_DATA_MAX_LENGTH
#define QUEUE_DATA_MAX_LENGTH 20
#endif
class queue {
private:
	unsigned char data[QUEUE_DATA_MAX_LENGTH];
	unsigned char head;
	unsigned char tail;
public:
	void push(unsigned char dat);
	unsigned char pop(void);
	unsigned char isEmpty(void);
	unsigned char available(void);
	int peak(void);
	void flush(void);
};



#endif /* QUEUE_H_ */
