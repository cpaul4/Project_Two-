/* This project creates a list with elements that contain a key and a data value. The lists are sorted with the keys in numerical order. */

#include <stdio.h>
#include <malloc.h>

typedef struct dummy_element 
{
	int key;
	int data;
	struct dummy_element *next;
} element;

element *List_head;   /* This element will always be the start of the list */

void Repository_init();

int Repository_insert (int key, int data);

int Repository_delete (int key, int data);

int Repository_get (int key, int *data);

void Repository_print(int print_elements);

unsigned int counter; /* This integer counts the number of elements in the list */

void Repository_init() /*The list is initialized to zero. */
{
	List_head=NULL;
	counter=0;
}
	
int Repository_insert(int key, int data) /*Elements are inserted in numerical order by key. */
{ 
	element *pelement;
	element *relement;

	if (List_head==NULL) /*Starts the list. */
	{
		pelement=malloc(sizeof(element));
		if (pelement==NULL)
		{
			return -1;
		}
		pelement->key=key;
		pelement->data=data;
		pelement->next=NULL;
		List_head=pelement;
		return 1;
	}
	
	pelement=List_head;
	counter++;
	if (key==pelement->key)
	{
		return 0;
	}
	else if (key<pelement->key)
	{
		pelement=malloc(sizeof(element));
		pelement->key=key;
		pelement->data=data;
		pelement->next=List_head;
		List_head=pelement;
		return 1;
	}
	else
	{
		while (pelement->next!=NULL && pelement->next->key<=key) /*Runs through the elements to insert the new element. */
		{		
			pelement=pelement->next;
			counter++;
			if (pelement->key==key)
			{	
				return 0;
			}
		}		
		relement=malloc(sizeof(element));	
		if (relement==NULL)
		{
			return -1;
		}
		else
		{	
			relement->key=key;
			relement->data=data;
			if (pelement->next==NULL)
			{
				pelement->next=relement;
				counter++;
				relement->next=NULL;
				return 1;
			}
			else 
			{
				relement->next=pelement->next;
				pelement->next=relement;
				counter+=2;
				return 1;
			}
		}
	}
}

int Repository_delete (int key, int data)  /*Deletes the element with a key equal to the key in the parameter. */
{
	element *pelement;
	element *temp;

	if (List_head==NULL) /*If there are no elements in the list, it returns a 0. */
	{
		return 0;
	}
	pelement=List_head;
	counter++;
	if (List_head->key==key)
	{
		List_head=List_head->next;
		counter++;
		free(pelement);
		return 1;
	}
	else
	{	
		while (pelement->next!=NULL && pelement->next->key<=key)
		{
			if (pelement->next->key==key)
			{
				temp=pelement->next;
				pelement->next=pelement->next->next; 
				counter+=2;
				free(temp); 
				return 1;
			}
			pelement=pelement->next;
			counter++;
		} 
	}
	return 0;
} 

int Repository_get (int key, int *data) /*Finds an element with a key equal to the parameter. */
{
	element *pelement;
	if (List_head==NULL)
	{
		return 0;
	}
	else
	{
		pelement=List_head;
		counter++;
		if (pelement->key==key)
		{
			*data=pelement->data; /*The data value in the element is passed to the parameter. */
			return 1;
		}
		else
		{
			while (pelement->next!=NULL && pelement->key<=key)
			{
				pelement=pelement->next;
				counter++;
				if (pelement->key==key)
				{
					*data=pelement->data;
					return 1;
				}
			}
		}
	}
	return 0;
}

void Repository_print (int print_elements) /*Prints out the counter, the size of the list, and the elements in the list. */
{
	element *pelement;
	int size=0;
	if (List_head==NULL)
	{
		printf("There are no numbers in the repository\n");
	}
	else
	{
		pelement=List_head;
		size++;
		if (print_elements!=0) /* Only prints out the elements if the parameter does not equal 0. */
		{
			printf("The values are:\n(%d, %d)\n", pelement->key, pelement->data);
		}
		while (pelement->next!=NULL)
		{
			pelement=pelement->next;
			if (print_elements!=0)
			{
				printf("(%d, %d)\n", pelement->key, pelement->data);
			}
			size++;
		}
		printf("The current size of the repository: %d\n", size);
	}
	
	printf("The number of 'next' steps performed: %u\n", counter);
	
}

