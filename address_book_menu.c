#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"

#include "address_book_fops.h"

#define PAGE_SIZE 10
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
			getchar();
			return 0;

		case 1:
			//	 * Read an number
			printf("%s\n", msg);
			scanf("%d", &i);
			return i; 
		
		case 2:
			//	 * Read a charcter
			printf("%s\n", msg);
			scanf(" %c", &c);
			return c;
		
		default:
		return -1;
		
	}
		
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (&option == "Y")
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
	int start = *index;
	int end = start + PAGE_SIZE;
	int i;
	char option;

	if(end > address_book->count)
	{
		end = address_book->count;
	}

	printf("\n%s\n", title);
	printf("------------------------------------------\n");

	for(i = start; i < end; i++)
	{
		printf("%d. %s | %s | %s\n",
		       address_book->list[i].si_no,
		       address_book->list[i].name[0],
		       address_book->list[i].phone_numbers[0],
		       address_book->list[i].email_addresses[0]);
	}

	printf("------------------------------------------\n");
	printf("%s", msg);

	scanf(" %c", &option);

	if(option == 'n' && end < address_book->count)
	{
		*index += PAGE_SIZE;
	}
	else if(option == 'p' && *index >= PAGE_SIZE)
	{
		*index -= PAGE_SIZE;
	}
	else if(option == 'q')
	{
		return e_success;
	}

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
	ContactInfo newContact;

	int nameNum = 1;
	char tempName[30];

	printf("Enter phone number: ");
	scanf("%s", newContact.phone_numbers[0]);

	printf("Enter email address: ");
	scanf("%s", newContact.email_addresses[0]);

		int phoneNumNum = 0;
		option = get_option(NUM, "");
		switch (option) {
			case 0:
				break;
			
			case 1:
				// Add name
				printf("Enter your contact's name: ");
				scanf("%s", newContact.name);
				
				//nameNum++;
				break;
			case 2:
				char tempPhoneChar[NAME_LEN];
				printf("Enter phone number: ");
				
				scanf("%s", tempPhoneChar);
				int tempNumber; 
				tempNumber= atoi(tempPhoneChar);
				if (tempNumber < 0) {
					printf("Invalid input, cannot have a negative phone number");
				}
				else {
					strcpy(newContact.phone_numbers[phoneNumNum], tempPhoneChar);
					phoneNumNum++;
				}
				

				break;
			case 3:
				printf("Enter email: ");
				scanf("%s", newContact.email_addresses);

				break;
			
			default:
				printf("Invalid option\n");
		}
	
	}	
	
	address_book->count++; 

	
	newContact.si_no = address_book->count; 
	address_book->list = &newContact; 

	return e_success;
}
	


Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */

	//int i;
	//int found = 0;

	printf("\nSearch Results\n");
	printf("----------------------------------\n");

	for(int i = 0; i < address_book->count; i++)
{
	if(field == 1)
	{
		if((field == 1 && strcmp(str, *address_book->list[i].name)) == 0)
		{
			if(strcmp(str, address_book->list[i].name[j]) == 0)
			{
				printf("Found: %s\n", address_book->list[i].name[j]);
			}
		}
		else if(field == 2 && strcmp(str, *address_book->list[i].phone_numbers) == 0)
		{
			found = 1;
		}
		else if(field == 3 && strcmp(str, *address_book->list[i].email_addresses) == 0)
		{
			if(strcmp(str, address_book->list[i].phone_numbers[j]) == 0)
			{
				printf("Found phone\n");
			}
		}
	}

	else if(field == 3)
	{
		for(int j = 0; j < EMAIL_ID_COUNT; j++)
		{
			if(strcmp(str, address_book->list[i].email_addresses[j]) == 0)
			{
				printf("Found email\n");
			}
		}
	}
}

	printf("----------------------------------\n");

	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	int option = -1;
	char searchStr[100];

	/*
	if(address_book->count == 0)
{
	printf("No contacts available\n");
	return e_success;
}
	*/
	while(option != 0)
	{
		menu_header("Search Contact");

		printf("0. Exit\n");
		printf("1. Search by Name\n");
		printf("2. Search by Phone\n");
		printf("3. Search by Email\n");

		printf("Select option: ");
		option = get_option(NUM, "");

		switch(option)
		{
			case 0:
				return e_success;

			case 1:
				printf("Enter name: ");
				scanf("%s", searchStr);

				search(searchStr, address_book,
				       address_book->count,
				       1,
				       "",
				       0);
				break;

			case 2:
				printf("Enter phone number: ");
				scanf("%s", searchStr);

				search(searchStr, address_book,
				       address_book->count,
				       2,
				       "",
				       0);
				break;

			case 3:
				printf("Enter email: ");
				scanf("%s", searchStr);

				search(searchStr, address_book,
				       address_book->count,
				       3,
				       "",
				       0);
				break;

			default:
				printf("Invalid option\n");
		}
	}

	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	int option;
	int subOption;
	int siNoToEdit; // After search
	int indexToEdit; // Edit Email/Phone Number
	ContactInfo searchContact;

	menu_header("Search Contact to Edit by:");

	printf("\n0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	printf("Please select an option: \n");
	
	option = get_option(NUM, "");
	switch (option) {
		case e_first_opt:
			break;
		
		case e_second_opt:
			printf("Enter the Name: ");
			scanf("%s", searchContact.name[0]);
			// search for contact, etc. etc.
			search(searchContact.name[0], address_book, address_book->count, 1, "", 0);
			printf("Select a Serial Number to Edit: ");
			scanf("%d", siNoToEdit);
			for(int i = 0; i < address_book->count; i++) {
				if (address_book->list[i].si_no == siNoToEdit) {
					menu_header("Edit Contact:");
					
					printf("\n0. Exit\n");
					printf("1. Name       : %s\n", address_book->list[i].name[0]);
					printf("2. Phone No 1 : %s\n", address_book->list[i].phone_numbers[0]);
					for(int p = 1; p < sizeof(address_book->list[i].phone_numbers); p++) {
						if (address_book->list[i].phone_numbers[p][0] != '\0') {
							printf("            %d : %s\n", p+1, address_book->list[i].phone_numbers[p]);
						}
					}
					printf("3. Email ID 1 : %s\n", address_book->list[i].email_addresses[0]);
					for(int e = 1; e < sizeof(address_book->list[i].email_addresses); e++) {
						if (address_book->list[i].email_addresses[e][0] != '\0') {
							printf("            %d : %s\n", e+1, address_book->list[i].email_addresses[e]);
						}
					}
					
					printf("Please select an option: ");
					
					subOption = get_option(NUM, "");
					if(subOption == e_second_opt) {
						printf("Enter new Name: ");
						scanf("%s", address_book->list[i].name[0]);
					}
					if(subOption == e_third_opt) {
						printf("Enter Phone Number index (1-5) to be changed: ");
						scanf("%d", indexToEdit);
						indexToEdit = indexToEdit < 1 || indexToEdit > 5 ? 1 : indexToEdit;
						printf("Enter new Phone Number: ");
						scanf("%s", address_book->list[i].phone_numbers[indexToEdit-1]);
					}
					if(subOption == e_fourth_opt) {
						printf("Enter Email index (1-5) to be changed: ");
						scanf("%d", indexToEdit);
						indexToEdit = indexToEdit < 1 || indexToEdit > 5 ? 1 : indexToEdit;
						printf("Enter new Email: ");
						scanf("%s", address_book->list[i].email_addresses[indexToEdit-1]);
					}
				}
			}
			break;

		case e_third_opt:
			printf("Enter the Phone Number: ");
			scanf("%s", searchContact.phone_numbers[0]);
			// search for contact, etc. etc.
			break;

		case e_fourth_opt:
			printf("Enter the Email Address: ");
			scanf("%s", searchContact.email_addresses[0]);
			// search
			break;

		case e_fifth_opt:
			printf("Enter the Serial Number: ");
			scanf("%d", &searchContact.si_no);
			// search
			break;
	}
}

Status delete_contact(AddressBook *address_book)
{
	if(address_book->count == 0)
{
	printf("No contacts available\n");
	return e_fail;
}
	
	char name[NAME_LEN];
	int i, j;

	printf("Enter contact name to delete: ");
	// Get input
	scanf("%s", name);

	for(i = 0; i < address_book->count; i++)
	{
		if(strcmp(name, address_book->list[i].name[0]) == 0)
		{
			// shift contacts up
			for(j = i; j < address_book->count - 1; j++)
			{
				address_book->list[j] = address_book->list[j + 1];
			}

			address_book->count--;

			printf("Contact deleted successfully\n");
			return e_success;
		}
	}
	printf("Contact not found\n");
	return e_fail;
}

