#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Was previously commented out.
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

#include "address_book_fops.h"
#include "address_book_menu.h"

Status load_file(AddressBook *address_book)
{
	int ret = access(DEFAULT_FILE, F_OK); // Checks for file existence

	if (ret == 0)
	{
		/* 
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "r"); // Opens the file
	}
	else
	{
		address_book->fp = fopen(DEFAULT_FILE, "w"); // Creates a file for adding entries
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	
	 //Open file in write mode
	address_book->fp = fopen(DEFAULT_FILE, "w");

	//check if file is open
	if (address_book->fp == NULL)
	{
		return e_fail;
	}
	//Loop through and save each contact
	for(int i = 0; i < address_book->count; i++)
	{
		fprintf(address_book->fp, "%d,%s,%s,%s\n",
			address_book->list[i].si_no,
			address_book->list[i].name[0],
			address_book->list[i].phone_numbers[0],
			address_book->list[i].email_addresses[0]);
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	//closes the file
	fclose(address_book->fp);

	printf("Contacts saved successfully\n");

	return e_success;
}

