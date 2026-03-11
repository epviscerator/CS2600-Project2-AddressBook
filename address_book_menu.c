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
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */

	// `type` is either NONE (0), NUM(1), or CHAR(2) for enter key,
	// number, and character detection, respectively.
	// `const char *msg` is the prompt that will be provided to the
	// user to enter their input
	// using this function is how we'll get input from the user, along
	// with the enum with e_first_opt, e_second_opt, etc.

	int option;

	printf(msg);

	switch (type) {
		case NONE:
			do {
				option = getchar();
			} while (option != '\n');
			return option;
			break;
		case NUM:
			scanf("%d", &option);
			return option;
			break;
		case CHAR:
			scanf(" %c", &option);
			return option;
			break;
	}
	return 0;
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
				/* Add your implementation to call add_contacts function here */
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
				break;
				/* Add your implementation to call list_contacts function here */
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
	
	ContactInfo newContact;
	//strcpy(newContact.name[0], "#");
	printf("Enter the name for the new contact: ");
	scanf("%s", newContact.name[0]);
	for (int i = 0; i < 5; i++) {
		strcpy(newContact.phone_numbers[i], "#");
		strcpy(newContact.email_addresses[i], "#");
	}
	int option;
	int itemIndex;
	do {
		menu_header("Add Contact:");

		printf("\n0. Back\n");
		printf("1. Name       : %s\n", newContact.name[0]);
		printf("2. Phone No 1 : %s\n", newContact.phone_numbers[0]);
		printf("            2 : %s\n", newContact.phone_numbers[1]);
		printf("            3 : %s\n", newContact.phone_numbers[2]);
		printf("            4 : %s\n", newContact.phone_numbers[3]);
		printf("            5 : %s\n", newContact.phone_numbers[4]);
		printf("3. Email ID 1 : %s\n", newContact.email_addresses[0]);
		printf("            2 : %s\n", newContact.email_addresses[1]);
		printf("            3 : %s\n", newContact.email_addresses[2]);
		printf("            4 : %s\n", newContact.email_addresses[3]);
		printf("            5 : %s\n", newContact.email_addresses[4]);

		printf("\n");
		option = get_option(NUM, "Please select an option: ");

		switch (option) {
			case e_first_opt:
				break;
			case e_second_opt:
				char namePlaceholder[NAME_LEN];
				printf("Enter the name: ");
				scanf("%s", namePlaceholder);
				strcpy(newContact.name[0], namePlaceholder);
				break;
			case e_third_opt:
				char numberPlaceholder[NUMBER_LEN];
				printf("Enter which phone number (1-5) to edit: ");
				scanf("%d", &itemIndex);
				printf("Enter the phone number (type '#' to mark as blank): ");
				scanf("%s", numberPlaceholder);
				strcpy(newContact.phone_numbers[itemIndex-1], numberPlaceholder);
				break;
			case e_fourth_opt:
				char emailPlaceholder[EMAIL_ID_LEN];
				printf("Enter which email (1-5) to edit: ");
				scanf("%d", &itemIndex);
				printf("Enter the email (type '#' to mark as blank): ");
				scanf("%s", emailPlaceholder);
				strcpy(newContact.email_addresses[itemIndex-1], emailPlaceholder);
				break;
		}
	} while (option != e_first_opt);
	do {
		option = get_option(CHAR, "Enter 'Y' to Save and 'N' to Discard: ");
	} while (option != 'Y' && option != 'N');
	if (option == 'Y') {
		strcpy(address_book->list[address_book->count].name[0], newContact.name[0]);
		address_book->list[address_book->count].si_no = (address_book->count + 1);
		for (int i = 0; i < 5; i++) {
			strcpy(address_book->list[address_book->count].phone_numbers[i], newContact.phone_numbers[i]);
			strcpy(address_book->list[address_book->count].email_addresses[i], newContact.email_addresses[i]);
		}
		address_book->count = address_book->count + 1;
		address_book->list = realloc(address_book->list, sizeof(ContactInfo) * (address_book->count + 1));
		if (address_book->list == NULL) {
			fprintf(stderr, "Error: not enough memory to add contact");
			exit(1);
		}
	}
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	int option;
	menu_header(msg);

	printf("\n0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	printf("\n");

	option = get_option(NUM, "Please select an option: ");
	switch (option) {
		case e_first_opt:
			return e_fail;
			break;
		case e_second_opt:
			char namePlaceholder[NAME_LEN];
			printf("Enter the name: ");
			scanf("%s", namePlaceholder);
			strcpy(namePlaceholder, strcmp(namePlaceholder, "#") == 0 ? "" : namePlaceholder); // "#" is not allowed
			menu_header("Search Result:");
			printf("\n==============================\n");
			for(int i = 0; i < address_book->count; i++) {
				if (strcmp(address_book->list[i].name[0], namePlaceholder) == 0) {
					printf("| %d, %s, %s, %s\n",
						address_book->list[i].si_no,
						address_book->list[i].name[0],
						address_book->list[i].phone_numbers[0],
						address_book->list[i].email_addresses[0]
					);
					for (int j = 1; j < 5; j++) {
						printf("| %s, %s\n",
							address_book->list[i].phone_numbers[j],
							address_book->list[i].email_addresses[j]
						);
					}
				}
			}
			break;
		case e_third_opt:
			char numberPlaceholder[NUMBER_LEN];
			printf("Enter the phone number: ");
			scanf("%s", numberPlaceholder);
			strcpy(numberPlaceholder, strcmp(numberPlaceholder, "#") == 0 ? "" : numberPlaceholder);
			menu_header("Search Result:");
			printf("\n==============================\n");
			for(int i = 0; i < address_book->count; i++) {
				for (int f = 0; f < 5; f++) {
					if (strcmp(address_book->list[i].phone_numbers[f], numberPlaceholder) == 0) {
						printf("| %d, %s, %s, %s\n",
							address_book->list[i].si_no,
							address_book->list[i].name[0],
							address_book->list[i].phone_numbers[0],
							address_book->list[i].email_addresses[0]
						);
						for (int j = 1; j < 5; j++) {
							printf("| %s, %s\n",
								address_book->list[i].phone_numbers[j],
								address_book->list[i].email_addresses[j]
							);
						}
					}
				}	
			}
			break;
		case e_fourth_opt:
			char emailPlaceholder[EMAIL_ID_LEN];
			printf("Enter the email: ");
			scanf("%s", emailPlaceholder);
			strcpy(emailPlaceholder, strcmp(emailPlaceholder, "#") == 0 ? "" : emailPlaceholder);
			menu_header("Search Result:");
			printf("\n==============================\n");
			for(int i = 0; i < address_book->count; i++) {
				for (int f = 0; f < 5; f++) {
					if (strcmp(address_book->list[i].email_addresses[f], emailPlaceholder) == 0) {
						printf("| %d, %s, %s, %s\n",
							address_book->list[i].si_no,
							address_book->list[i].name[0],
							address_book->list[i].phone_numbers[0],
							address_book->list[i].email_addresses[0]
						);
						for (int j = 1; j < 5; j++) {
							printf("| %s, %s\n",
								address_book->list[i].phone_numbers[j],
								address_book->list[i].email_addresses[j]
							);
						}
					}
				}	
			}
			break;
		case e_fifth_opt:
			int siNoPlaceholder;
			printf("Enter the serial number: ");
			scanf("%d", &siNoPlaceholder);
			menu_header("Search Result:");
			printf("\n==============================\n");
			for(int i = 0; i < address_book->count; i++) {
				if (address_book->list[i].si_no == siNoPlaceholder) {
					printf("| %d, %s, %s, %s\n",
						address_book->list[i].si_no,
						address_book->list[i].name[0],
						address_book->list[i].phone_numbers[0],
						address_book->list[i].email_addresses[0]
					);
					for (int j = 1; j < 5; j++) {
						printf("| %s, %s\n",
							address_book->list[i].phone_numbers[j],
							address_book->list[i].email_addresses[j]
						);
					}
				}
			}
			break;
	}
	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	search("", address_book, 0, 0, "Search Contacts:", e_search_contact);
}

Status edit_contact(AddressBook *address_book)
{

	int ret = search("", address_book, 0, 0, "Search Contacts to Edit by: ", e_edit_contact); 
	int serialnumbertoedit; 
	int contactindextoedit;
	int option;
	int itemIndex;
	ContactInfo placeholderContact;

	if (ret == e_fail) {
		return e_fail;
	}

	printf("Enter the serial number to edit: ");
	scanf("%d", &serialnumbertoedit);
	for (int i = 0; i < address_book->count; i++){
		if (address_book->list[i].si_no == serialnumbertoedit){
			contactindextoedit = i;

			strcpy(placeholderContact.name[0], address_book->list[contactindextoedit].name[0]);
			for(int j = 0; j < 5; j++){
				strcpy(placeholderContact.phone_numbers[j], address_book->list[contactindextoedit].phone_numbers[j]);
				strcpy(placeholderContact.email_addresses[j], address_book->list[contactindextoedit].email_addresses[j]);
			}
		}
	}
	
	do {
		menu_header("Edit Contact:");

		printf("\n0. Back\n");
		printf("1. Name       : %s\n", placeholderContact.name[0]);
		printf("2. Phone No 1 : %s\n", placeholderContact.phone_numbers[0]);
		printf("            2 : %s\n", placeholderContact.phone_numbers[1]);
		printf("            3 : %s\n", placeholderContact.phone_numbers[2]);
		printf("            4 : %s\n", placeholderContact.phone_numbers[3]);
		printf("            5 : %s\n", placeholderContact.phone_numbers[4]);
		printf("3. Email ID 1 : %s\n", placeholderContact.email_addresses[0]);
		printf("            2 : %s\n", placeholderContact.email_addresses[1]);
		printf("            3 : %s\n", placeholderContact.email_addresses[2]);
		printf("            4 : %s\n", placeholderContact.email_addresses[3]);
		printf("            5 : %s\n", placeholderContact.email_addresses[4]);

		printf("\n");
		
		option = get_option(NUM, "Please select an option: ");

		switch (option) {
			case e_first_opt:
				break;
			case e_second_opt:
				char namePlaceholder[NAME_LEN];
				printf("Enter the name: ");
				scanf("%s", namePlaceholder);
				strcpy(placeholderContact.name[0], namePlaceholder);
				break;
			case e_third_opt:
				char numberPlaceholder[NUMBER_LEN];
				printf("Enter which phone number (1-5) to edit: ");
				scanf("%d", &itemIndex);
				printf("Enter the phone number (type '#' to mark as blank): ");
				scanf("%s", numberPlaceholder);
				strcpy(placeholderContact.phone_numbers[itemIndex-1], numberPlaceholder);
				break;
			case e_fourth_opt:
				char emailPlaceholder[EMAIL_ID_LEN];
				printf("Enter which email (1-5) to edit: ");
				scanf("%d", &itemIndex);
				printf("Enter the email (type '#' to mark as blank): ");
				scanf("%s", emailPlaceholder);
				strcpy(placeholderContact.email_addresses[itemIndex-1], emailPlaceholder);
				break;
		}
	} while (option != e_first_opt);
	do {
		option = get_option(CHAR, "Enter 'Y' to Save Changes and 'N' to Discard: ");
	} while (option != 'Y' && option != 'N');

	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	search("", address_book, 0, 0, "Search Contacts to Delete by:", e_delete_contact);
	int siNo2Delete;
	printf("Enter the serial number to delete: \n");
	scanf("%d", &siNo2Delete);
	for(int i = 0; i < address_book->count; i++) {
		if (address_book->list[i].si_no == siNo2Delete) {
			for (int j = i; j < (address_book->count - 1); j++) {
				address_book->list[j].si_no = address_book->list[j+1].si_no;
				strcpy(address_book->list[j].name[0], address_book->list[j+1].name[0]);
				for (int k = 0; k < 5; k++){
					strcpy(address_book->list[j].phone_numbers[k], address_book->list[j+1].phone_numbers[k]);
					strcpy(address_book->list[j].email_addresses[k], address_book->list[j+1].email_addresses[k]);
				}
			}
			address_book->count--;
			address_book->list = realloc(address_book->list, sizeof(ContactInfo) * (address_book->count));
			if (address_book->list == NULL) {
				fprintf(stderr, "Error: not enough memory after deletion");
				exit(1);
			}
		}
	}
}
