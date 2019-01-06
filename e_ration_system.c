#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
	char name[20];
	char id[20];
	char cardType[5];
	int age;
	int stocks[5];
	struct node* link;
}*listpointer;
void PerCustomer_BPL(listpointer list)
	{
		list->stocks[0] = 10;
		list->stocks[1] = 5;
		list->stocks[2] = 2;
		list->stocks[3] = 2;
		list->stocks[4] = 2;
	}	
void PerCustomer_APL(listpointer list)
	{
		list->stocks[0] = 5;
		list->stocks[1] = 2;
		list->stocks[2] = 1;
		list->stocks[3] = 1;
		list->stocks[4] = 1;
	}
int tot_stocks[5] = {0};
int	rationEmpty()
	{
		int i;
		for(i = 0; i < 5; i++)
		if(tot_stocks[i] == 0)
		return 1;
		return 0;
	}
listpointer customers;
listpointer last;
void dis_del_stocks(listpointer temp);
listpointer search(char idno[]);
char stock_name[][12] = {"Rice(Kgs)", "Wheat(Kgs)", "Sugar(Kgs)", "Dhal(Kgs)", "Oil(Ltr)"};
void create_list()
{
	//Pre-registered customers
	listpointer first = (listpointer) malloc (sizeof(*first));
	listpointer second = (listpointer) malloc (sizeof(*second));
	strcpy(first->name, "Kiran_raj");
	strcpy(first->id, "1234");
	strcpy(first->cardType, "BPL");
	PerCustomer_BPL(first);
	first->age = 19;
	strcpy(second->name, "kiran");
	strcpy(second->id, "1235");
	strcpy(second->cardType, "APL");
	PerCustomer_APL(second);
	second->age = 18;
	first->link = second;
	listpointer third = (listpointer) malloc (sizeof(*third));
	strcpy(third->name, "Punith");
	strcpy(third->id, "1236");
	strcpy(third->cardType, "APL");
	PerCustomer_APL(third);
	third->age = 12;
	second->link=third;
	listpointer fourth = (listpointer) malloc (sizeof(*fourth));
	strcpy( fourth->name, "nikhil");
	strcpy(fourth->id,"1238");
	strcpy(fourth->cardType, "APL");
	PerCustomer_APL(fourth);
	fourth->age = 20;
	third->link=fourth;
	listpointer fifth=(listpointer)malloc(sizeof(*fifth));
	strcpy(fifth->name, "Ootej");
	strcpy(fifth->id, "1239");
	strcpy(fifth->cardType, "BPL");
	PerCustomer_BPL(fifth);
	fifth->age=25;
	fourth->link = fifth;
	fifth->link=NULL;
	customers = first;
	last = fifth;
}
int check_eligibility()
{
	int income;
	printf("Enter Annual Income:");
	scanf("%d", &income);
	if(income <= 30000)
	return 1;
	if(income <= 50000)
	return 2;
	return 0;
}
void new_customer(int j)
{
	listpointer temp = (listpointer) malloc (sizeof(*temp)), cust;
	listpointer first = customers, trail = NULL;
	int s;
	printf("Enter the following details\n");
	printf("Name:");
	scanf("%s", temp->name);
	printf("7 digit ID:");
	scanf("%s", temp->id);
	printf("Age:");
	scanf("%d", &temp->age);
	if(j == 1)
	{
		strcpy(temp->cardType, "BPL");
		PerCustomer_BPL(temp);
	}
	else
	{
		strcpy(temp->cardType, "APL");
		PerCustomer_APL(temp);
	}
	temp->link = NULL;
	cust = search(temp->id);
	if(cust)
	printf("ID already exists\n");
	else
	{
		while(first)
		{	
			s = strcmp(temp->id, first->id);
			if(s == -1)
			break;
			trail = first;
			first = first->link;
		}
		if(!trail)
		{
			temp->link = customers;
			customers = temp;
		}
		else{
			trail->link = temp;
			temp->link = first;
		}
		printf("--Successfully added to the list--\n");
	}
}
typedef struct{
}ration;
void register_()
{
		int j;
		j = check_eligibility();
		if(j == 0)
		printf("Not eligible for any type of ration card\n");
		else if(j == 1)
		{
			printf("Eligible for BPL card\n");
			new_customer(j);
		}
		else 
		{
			printf("Eligible for APL card\n");
			new_customer(j);
		}
}
void display()
{
	listpointer temp = customers;
	int i = 0;
	while(temp)
	{
		printf("---------------------------------------\n");
		printf("Customer[%d]\n", ++i);
		printf("Name:%s\n", temp->name);
		printf("ID:%s\n", temp->id);
		printf("Age:%d\n", temp->age);
		printf("CardType:%s\n", temp->cardType);
		printf("---------------------------------------\n");
		temp = temp->link;
	}
}
listpointer search(char idno[])
{
	listpointer temp = customers;
	while(temp)
	{
		if(strcmp(temp->id, idno) == 0)
		return temp;
		temp = temp->link;
	}	
		return NULL;
}
void avail_ration()
{
	char idno[20];
	int i, flag;
	listpointer cust;
	if(rationEmpty() == 0)
			{
				printf("Enter the ID of your ration card:");
				scanf("%s", idno);
				cust = search(idno);
				if(cust == NULL)
				printf("Invalid Entry of ID\n");
				else
				{
					flag = 1;
					for(i = 0; i < 5; i++)
					{
						if(!cust->stocks[i])
						{
							flag = 0;
							printf("You have already availed the ration.\n");
							break;
						}
						tot_stocks[i] = tot_stocks[i] - cust->stocks[i];
						if(tot_stocks[i] < 0)
						{
							flag = 0;
							printf("Out of stock. We will inform you after stock is available\n");
							tot_stocks[i] = tot_stocks[i] + cust->stocks[i];
							break;
						}
					}
					if(flag)
					{
						dis_del_stocks(cust);
						printf("All the items delivered.\nThanks for coming\n");
					}
				}
			}
			else
			printf("There is shortage in the ration stock.\n We will inform you the later when the ration arrives\n");
}
void view_info(char idno[])
{
	int i;
	listpointer temp = search(idno);
	if(temp)
	{
		printf("---------------------------------------\n");
		printf("Name:%s\n", temp->name);
		printf("ID:%s\n", temp->id);
		printf("Age:%d\n", temp->age);
		printf("CardType:%s\n", temp->cardType);
		printf("Ration that can be availed:\n");
		for(i = 0; i < 5; i++)
		printf("\t%s:%d\n", stock_name[i], temp->stocks[i]);
		printf("---------------------------------------\n");
	}
	else
	{
		printf("Invalid entry of ID\n");	
	}
}
void delete_info(char idno[])
{
	listpointer trail = NULL, temp, cust = customers;
	temp = search(idno);
	if(temp)
	{
	if(temp == customers)
		customers = customers->link;
	else
	{
		while(cust != temp)
		{
			trail = cust;
			cust = cust->link;
		}
		trail->link = temp->link;
	}
		printf("Customer with ID:%s details removed from the list\n", idno);
		free(temp);
	}
	else
	printf("Invalid Entry of ID no.\n");
}
void dis_del_stocks(listpointer temp)
{
	int i;
	printf("Ration delivered:\n");
	for(i = 0; i < 5; i++)
	{
		printf("\t%s:%d\n", stock_name[i], temp->stocks[i]);
		temp->stocks[i] = 0;
	}
}
void dis_tot_stocks()
{
	int i;
	printf("Ration remaining:\n");
	for(i = 0; i < 5; i++)
	printf("\t%s:%d\n", stock_name[i], tot_stocks[i]);
}
void get_tot_stocks()
{
	int i, s;
	printf("Enter the following quantities given by the govt.\n");
	for(i = 0;i < 5; i++)
	{
		printf("%s:", stock_name[i]);
		scanf("%d", &s);
		tot_stocks[i] += s;
	}
}
void ration_operation()
{
	int choice;
	char idno[20];
	printf("\n");
	printf("press\n1.To avail ration\n2.To register for Ration card\n3.View information\n4.Delete details\n");
	printf("5.Display details of all customers\n6.Display total available ration\n7.If ration from govt arrived\n");
	scanf("%d", &choice);
	if(choice == 1)
	avail_ration();
	else
	if(choice == 2)
	register_();
	else
	if(choice == 3)
	{
		printf("Enter the ID no of the customer:");
		scanf("%s", idno);
		view_info(idno);
	}
	else if(choice == 4)
	{
		printf("Enter the ID no of the customer:");
		scanf("%s", idno);
		delete_info(idno);
	}
	else if(choice == 5)
	display();
	else if(choice == 6)
	dis_tot_stocks();
	else if(choice == 7)
	get_tot_stocks();
}
int main()
{
	int i;
	printf("WELCOME TO RATION CENTRE\n");
	printf("The ID no of the customers are stored in ascending order\n");
	printf("\n");
	create_list();
	get_tot_stocks();
	do
	{
		ration_operation();
		printf("To perform another operation: press 1 else press 0:");
		scanf("%d", &i);
	}while(i);
	printf("-------------------Complete----------------------\n");
}
