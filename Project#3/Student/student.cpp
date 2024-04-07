#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include"student.h"

// Global Linked List initially set to zero
struct student* head = NULL;

int main(void) {
	// Read the input file and create the linked list
	// ReadInputFile calls helper function AddToList to
	// create list in sorted order
	ReadInputFile("D:\\DataStructure\\Project#3\\data\\student.txt",head);

	// print the current list to the outputfile output.txt
	PrintToFile("D:\\DataStructure\\Project#3\\data\\output.txt",head);

	// Read and process the dropped students file delete.txt
	// It uses helper function DeleteStudent to remove
	// the from the list
	ProcessDeleteFile("D:\\DataStructure\\Project#3\\data\\delete.txt",head);

	// Print the updated linked list to the file update.txt
	PrintToFile("D:\\DataStructure\\Project#3\\data\\update.txt",head);

	// Delete the Entire Linked List before exiting the program
	DeleteList(head);

	return 0;
}
void ReadInputFile(const char* filename) {
	struct student tmp; 
	// temporary student structure
	// open up the input file for read mode
	// if it can¡¯t open print error message
	// while you still have data to read
	// read one students data into temporary structure tmp
	// after you have gotten all the data for one student
	// call the function AddToList
}

void ProcessDeleteFile(const char* filename) {
	// create string deleteSSN
	// open up the file for read mode, print error message if not present
	// while you still have data to read
	// read a string from the file
	// call the function DeleteStudent with argument SSN that you read in
}

void DeleteList(void) {
	// start from the head and remove each entry
	// from the list and free up the space via calling the function free
}

void PrintToFile(const char* filename) {
	// open up file for write mode
	// print the linked list student by student to the
	// output file. Sample output in section 5.1 & 5.2
}

void AddToList(struct student* addStudent) {
	// malloc a new student
	// copy contents of argument student to the new student
	// is linked list empty? if so, new student is head
	// if not, search through the linked list to find appropriate
	// spot within the linked list
	// Concerns:
	// - what if new student ends up being the first? change head
	// - what if new student ends up in the middle? update pointers
	// - what if new studend is last?
}

void DeleteStudent(char* SSN) {
	// search through the linked list to see if SSN exists
	// If so, remove it from the linked list
	// Concerns:
	// - what if deleted student is the head? update head
	// - what if deleted student is in the middle? update pointers
	// - what if deleted student is at the tail? 
}