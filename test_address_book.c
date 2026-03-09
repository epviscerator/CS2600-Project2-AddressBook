// Importing unity and address book 
#include "unity.h"
#include "address_book.h"


void setUp(void){
}

void tearDown(void){
}

/* 
Testing to see if the structure in address_book.h is setting everything equal to null
So book.fp is seeing if the file pointer becomes null 
book.list is checking to see if the contact pointer is null 
and 0, book.count is ensuring that there are no contacts when starting the program 
*/ 

void test_address_book_creation(void){
    AddressBook book = {0}; // setting everything to zero
    
    // Setting up tests
    TEST_ASSERT_NULL(book.fp);
    TEST_ASSERT_NULL(book.list);
    TEST_ASSERT_EQUAL_INT(0, book.count);
}

// Testing to see if default file is correctly named
void test_default_csv_file_(void){
    TEST_ASSERT_EQUAL_STRING("address_book.csv", DEFAULT_FILE);
}


// Setting up main where tests functions are called
int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_address_book_creation);
    RUN_TEST(test_default_csv_file_);

    return UNITY_END();
}
