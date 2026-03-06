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
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
