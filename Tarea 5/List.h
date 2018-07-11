

#ifndef LIST_H_
#define LIST_H_

typedef void *Type;
typedef struct strList *List;

typedef enum {false, true} Bool;

List list_create(void);

int list_size(List l);

void list_add(List l, Type data);

Type list_get(List l, int p);

void list_set(List l, Type data, int p);

Type list_remove(List l, int p);

void list_destroy(List l);

void list_insert(List who, Type data, int index);

#endif /* LIST_H_ */
