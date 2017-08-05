#ifndef TYPE_H
#include <stdio.h>
#define TYPE_H
#define MAX_CONTACTS 15
#define MAX_PH_LENGTH 10
#define MAX_PH 5
#define MAX_NAME_LENGTH 15
#define MAX_EMAIL_LENGTH 25
#define WAIT_FOR_ENTER_KEY while(getchar() != '\n')
typedef struct
{
	char name[MAX_NAME_LENGTH];
	char email[MAX_EMAIL_LENGTH];
	char phone[MAX_PH][MAX_PH_LENGTH];
}data;

typedef enum
{
	failure,
	success,
}return_t;

int Insert_function(data *);
void Search_function(data *, int, int *);
void Modify_function(data *, int, int *);
void Display_function(data **, int, int *);
void Save_function(FILE *, data *, int, int *);
#endif
