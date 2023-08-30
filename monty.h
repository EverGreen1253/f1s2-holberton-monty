#ifndef MAIN_H
#define MAIN_H

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

int iswhitespace(char ch);
char *strtrim(char *buffer);
char *remove_internal_spaces(char *o);
int count_valid_cmd_chars(char *s);
void run_cmd(FILE *fp, int line, char *o, instruction_t *ops, stack_t **stack);

void push(stack_t **head, unsigned int n);
void free_list(stack_t *head);
void free_node(stack_t *node);
void pall(stack_t **head, unsigned int n);
int is_valid_cmd(char *c);
int is_valid_val(char *c);

void die(FILE *fp, char *o, int line, stack_t **stack);

#endif
