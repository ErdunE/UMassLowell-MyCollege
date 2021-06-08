#ifndef queue_h//
#define queue_h//
#include "status.h"

typedef void* QUEUE;

QUEUE queue_init_default(void);
Status queue_enqueue(QUEUE hQueue, int item);
Status queue_service(QUEUE hQueue);
Boolean queue_empty(QUEUE hQueue);

int queue_front(QUEUE hQueue, Status* pStatus_code);
int queue_get_size(QUEUE hQueue);
void queue_destroy(QUEUE* phQueue);

#endif
