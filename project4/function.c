#include <stdio.h>
#include <string.h>
#include "type.h"
// function body of insert function
int Insert_function(data *ptr)
{
	char buffer[100];
	int length, idx = 0, test = 0;
	int input;
	WAIT_FOR_ENTER_KEY;
	printf("enter the name :");
	scanf("%[^\n]", buffer);
	length = strlen(buffer);
	if (length > MAX_NAME_LENGTH)
	{
		printf("name size is too large!!!\n");
		return;
	}
	strcpy(ptr -> name, buffer);
	printf("enter the phone number\n");
	for (idx = 0; idx < MAX_PH; idx++)
	{
	WAIT_FOR_ENTER_KEY;
	scanf("%s", buffer);
	length = strlen(buffer);
	if (length > MAX_PH_LENGTH || length != 8)
	{
		printf(" phone number size is 8\n");
		idx--;
		continue;
	}
	strcpy((ptr -> phone+idx)[10], buffer);
	printf("1. To enter next ph num, 2. exit\n");
	scanf("%d", &input);
	if (input == 2)
	{
		test = 1;
		break;
	}
	}
	printf("enter the email id :");
	WAIT_FOR_ENTER_KEY;
	scanf("%s", buffer);
	length = strlen(buffer);
	strcpy(ptr -> email, buffer);
	if (test == 1)
		return idx;
	return (idx - 1);
}
//************************************************************************************************************************
//function body of search function
void Search_function(data *ptr, int size, int *result)
{
	int search_by, idx, jdx, kdx, Total_ph_number[MAX_PH];
	char buffer[100];
	data *arr[15];
	printf("search by\n"
			"1. name\n"
			"2. email\n"
			"3. phone number\n");
	scanf("%d",&search_by);
	switch (search_by)
	{
		case 1:
			printf("enter the name:");
			scanf("%s", buffer);
			// loop for checking whether the name present or not
			for (jdx = 0,idx = 0; idx <= size; idx++)
			{
				if (!strcmp((ptr + idx) -> name, buffer))
				{
					arr[jdx] = ptr + idx;
					Total_ph_number[jdx] = result[idx];
					jdx++;
				}
			}
			Display_function(arr,jdx - 1, Total_ph_number);
			break;
		case 2:
			printf("enter the mail id: ");
			scanf("%s", buffer);
			for (jdx = 0,idx = 0; idx <= size; idx++)
			{
				if (!strcmp((ptr + idx) -> email, buffer))
				{
					arr[jdx] = ptr + idx;
					Total_ph_number[jdx] = result[idx];
					jdx++;
				}
			}
			Display_function(arr,jdx - 1, Total_ph_number);
			break;
		case 3:
			printf("enter the mobile number: ");
			scanf("%s", buffer);
			for (jdx = 0, idx = 0; idx <= size; idx++)
			{
				for (kdx = 0; kdx <= result[idx]; kdx++)
				{
					if (!strcmp(((ptr + idx) -> phone + kdx)[10], buffer ))
					{
					arr[jdx] = ptr + idx;
					Total_ph_number[jdx] = result[idx];
					jdx++;
					break;
					}
				}
			}
			Display_function(arr,jdx - 1, Total_ph_number);
			break;
	}

}
//***************************************************************************************************************************
//function body of modify function
void Modify_function(data *ptr, int size, int *phone_num)
{
	char name[30];
	char email[30];
	char buffer[50];
	int input, jdx, idx, length, test = 0;
	printf("enter the name which you want to edit data:");
		scanf("%s",name);
	printf("enter the email which u want to edit data: ");
	scanf("%s", email);
	printf("which data u want to edit\n"
			"1. name\n"
			"2. phone number\n"
			"3. email\n");
	scanf("%d",&input);
	
	for (idx = 0; idx <= size; idx++)
	{
		if ((!strcmp((ptr + idx) -> name, name)) &&(!strcmp((ptr + idx) -> email, email)))
		{
			switch (input)
			{
				case 1:
					printf("enter the new name: ");
					WAIT_FOR_ENTER_KEY;
					scanf("%s",buffer);
					strcpy((ptr + idx) -> name, buffer);
					break;
				case 2:
					printf("enter new phone numbers");
					for (jdx = 0; jdx < MAX_PH; jdx++)
					{
						WAIT_FOR_ENTER_KEY;
						scanf("%s", buffer);
						length = strlen(buffer);
						if (length > MAX_PH_LENGTH || length != 8)
						{
							printf(" phone number size is 8\n");
							jdx--;
							continue;
						}
						strcpy(((ptr + idx) -> phone + jdx)[10], buffer);
						printf("1. To enter next ph num, 2. exit\n");
						scanf("%d", &input);
						if (input == 2)
						{
							test = 1;
							break;
						}
					}
					if (test == 1)
						phone_num[idx] = jdx;
					phone_num[idx] = jdx - 1;
					break;
				case 3:
					printf("enter new email id");
					WAIT_FOR_ENTER_KEY;
					scanf("%s", buffer);
					strcpy((ptr + idx) -> name, buffer);
					break;
			}
		}
	}
}
//***********************************************************************************************************************
//function body of Display function
void Display_function(data **ptr, int size, int *result)
{
	int idx, jdx;

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("|%-20.20s\t|%-20s\t|%-30s\t|\n", "Name", "Phone number", "email id");
	printf("---------------------------------------------------------------------------------------------------------\n");
	for (idx = 0; idx <= size; idx++)
	{
		jdx = 0;
		printf("|%-20.20s\t|%-20s\t|%-30s\t|\n", (*ptr + idx) -> name, ((*ptr + idx) -> phone + jdx)[10], (*ptr + idx) -> email);
		for (jdx = 1; jdx <= result[idx]; jdx++)
		{
		printf("|%-20.20s\t|%-20s\t|%-30s\t|\n"," ",((*ptr + idx) -> phone + jdx)[10], " ");
		}
	}
	printf("---------------------------------------------------------------------------------------------------------\n");

}
//**********************************************************************************************************************88
void Save_function(FILE *ptr, data *contact, int size, int *ph_length)
{
	char *temp = "NAME,Phone num,Email id\n";
	fwrite(temp,strlen(temp),1,ptr);
	char buffer[300];
	int idx, jdx =0;
	for (idx = 0; idx <= size; idx++)
	{
	fwrite((contact + idx) -> name,strlen((contact + idx) -> name),1,ptr);
	fwrite(",",1,1,ptr);
	for (jdx = 0; jdx <= ph_length[idx]; jdx++)
	{
	fwrite(((contact + idx) -> phone + jdx)[10],8,1,ptr);
	fwrite("*",1,1,ptr);
	}
	fwrite(",",1,1,ptr);
	fwrite((contact + idx) -> email,strlen((contact + idx) -> name),1,ptr);
	fwrite("\n",1,1,ptr);
	}
}
