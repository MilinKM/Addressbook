#include <stdio.h>
#include "type.h"
int main(int argc, char *argv[])
{
if (argc != 1)
{
	printf("pass valid arguments\n");
	return failure;
}
int decesion, idx = 0, result[15], input = 1;
data contacts[15];
data *ptr = contacts;
while (input == 1)
{
printf("1. Insert\n"
	   "2. Search\n"
	   "3. Modify\n"
	   "4. Display\n"
	   "5. Save DB\n"
	   "6. Exit\n");
scanf("%d",&decesion);
FILE *src;
src = fopen("addressbook.csv","w+");
switch (decesion)
{
	case 1:
		if (idx > 14)
		{
			printf("contact memory full\n");
			break;
		}
		result[idx] = Insert_function(&contacts[idx]);
		idx++;
		break;
	case 2:
		Search_function(contacts, (idx - 1),result);
		break;
	case 3:
		Modify_function(contacts, (idx - 1), result);
		break;
	case 4:
		Display_function(&ptr, (idx - 1), result);
		break;
	case 5:
		printf("1. save\n"
				"2. exit\n");
		int to_save;
		scanf("%d",&to_save);
		if (to_save == 1)
			Save_function(src, contacts, (idx - 1), result);
		break; 
	case 6:
		return success;
		break;

}
printf("1. continue 0. exit\n");
scanf("%d",&input);
}
}
