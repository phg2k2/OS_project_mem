#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        if (q == NULL || proc == NULL) return;
        if (q->size >= MAX_QUEUE_SIZE) {
                return;
        }
        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
	        if (empty(q)) return NULL;
        struct pcb_t * proc = NULL;
        uint32_t highest_priority;
        #ifdef MLQ_SCHED
        highest_priority = q->proc[0]->prio;
        #else
        highest_priority = q->proc[0]->priority;
        #endif
        uint32_t highest_index = 0;
        for (int i = 1; i < q->size; i++) {
                uint32_t cur_priority;
                #ifdef MLQ_SCHED
                cur_priority = q->proc[i]->prio;
                #else
                cur_priority = q->proc[i]->priority;
                #endif
                if (highest_priority > cur_priority) {
                        highest_index = i;
                        highest_priority = cur_priority;
                }
        }
        proc = q->proc[highest_index];
        for (int i = highest_index; i < q->size - 1; i++) {     
                q->proc[i] = q->proc[i + 1];
        }
        q->size--;
        return proc;
}

