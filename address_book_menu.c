#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"

#include "address_book_fops.h"

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 */ 
	int i;
	char c;

	switch (type) { 
		//	 * Just an enter key detection
		case 0:
			scanf("%n");
			return 0;
			break;

		case 1:
			//	 * Read an number
			printf("%s\n");
			scanf("%d", &i); 
			
			return i;
			break;
		
		case 2:
			//	 * Read a charcter
			printf("%s\n");
			scanf("%c", &c);
			return c;
			break;
		
		
	}
		
	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 
	
	

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");
	
	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();
		
		option = get_option(NUM, ""); 

		
		if ((address_book-> count == 0) && (option != e_add_contact)) 
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}
		
		switch (option) 
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				//list_contacts(address_book);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	int option;
	ContactInfo newContact;

	
	

	int nameNum = 1;
	//char tempName[30];

	while (option != 0) {
		menu_header("Add Contact");
		
		printf("\n0. Exit\n");
		printf("1. Name : \n");
		printf("2. Phone No. : \n");
		printf("3. Email : \n");

		printf("Please select an option: \n");

		option = get_option(NUM, "");
		switch (option) {
			case 0:
				break;
			
			case 1:
				// Add name
				printf("fart");
				scanf("Enter your contact's name: %s", newContact.name);
				
				nameNum++;
				break;
			case 2:
				// Add phone num
				break;
			case 3:
				// Add email
				break;
		}
	}	
	/*
	char tempName[30];
	char tempPhone[16]; // Australians have 15-digit phone numbers.
	char tempEmail[320]; 

	// struct ContactInfo ci; 
	scanf("Add your contact's name: %s", &tempName);
	scanf("Add your contact's phone number: %s", &tempPhone);
	scanf("Add your contact's email addresses: %s", &tempEmail);
	*/
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
