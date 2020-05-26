//*******************************************************************
// File:   Project2.c
// Author(s):  Ahmed AL Hilal - Ayman Farsi - Amine Benchekroun 
// Date:  12/16/2018
// 
// Component Files: NONE
// Input Files:  stdin
// Output Files:  stdout
//
//*******************************************************************

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>

// Prototype for the project top->down
typedef struct{
	int day;
	int month;
	int year;
}dob;

typedef struct {
	char* firstname;
	char* lastname;
	dob* DateOfBirth;
	char gender;
	char* father;
	char* mother;
	char** children;
	int numChildren;
}Individual;

typedef struct{
	Individual* generation;
	size_t n;
}FamilyTree;

// Helper Functions for dob Struct
dob* make_dob(int d,int m,int y){
	dob* temp = (dob*) malloc(sizeof(dob));
	temp->day = d;
	temp->month=m;
	temp->year=y;
	return temp;
}
// Prints the date of birth
void print_dob(dob* ptr){
	if(ptr)
		printf("         DOB : %d/%d/%d \n",ptr->day,ptr->month,ptr->year);
	else
		printf("Null dob ptr \n");
}

// Helper Functions for Individual Struct
//Makes the Individual Node for it to be added to the FamilyTree
Individual* make_Individual(char* f,char* l, dob* d,char g){
	Individual* temp = (Individual*) malloc(sizeof(Individual));
	temp->children=(char**) malloc(100 * sizeof(char*));
	temp->father=NULL;
	temp->mother=NULL;
	temp->gender=g;
	temp->firstname = malloc(strlen(f)+1);
	temp->lastname = malloc(strlen(l)+1);
	strncpy(temp->firstname,f,strlen(f));
	strncpy(temp->lastname,l,strlen(l));
	temp->DateOfBirth = make_dob(d->day,d->month,d->year);
	temp->numChildren= 0;
	return temp;
}
// Prints the Individual Node with its children, father and mother if exist
void print_Individual(Individual* I){
	if(I){
		printf("\n     *** Individual ***  \n         FirstName : %s \n         LastName: %s \n         Gender : %c \n",I->firstname,I->lastname, I->gender);
		print_dob(I->DateOfBirth);
		if(I->numChildren!=0){
			printf("         Children : \n");
			int i=0;
			for (i;i<I->numChildren;i++){
				if(I->children[i])
					printf("              %s, ",I->children[i]);
			}
			printf("\n");
		}
		else
			printf("         No Children \n");
		if (I->father)
			printf("         Father : %s \n",I->father);
		if (I->mother)
			printf("         Mother : %s \n",I->mother);
		printf("\n\n");
	}else{
		printf("Null Ind Ptr \n");
	}
}
// Helper Functions for FamilyTree
// Initializes a Family Tree to a default NULL Node to be propagated
FamilyTree* init_FamilyTree(){
	int nX=1000;
	FamilyTree* temp = (FamilyTree*) malloc(sizeof(FamilyTree));
	temp->generation=(Individual*) malloc(nX*sizeof(Individual));
	temp->n = 0;
	return temp;
}
// Adds an Individual to the Family Tree
void CreateIndividual(FamilyTree* ft,Individual* newInd){
	if(ft){
		ft->generation[ft->n] = *newInd;
		ft->n++;
	}else{
		printf("Family Tree is not initialized \n");
	}
}
// Returns the number of members in the FamilyTree
int nMembers(FamilyTree* ft){
	if(ft){
		return ft->n;
	}
	return 0;
}
// Prints the Members of FamilyTree
void printMembers(FamilyTree* ft){
	if(ft){
		printf("\n\n *** Members in Family Tree ***  \n");
		int size = ft->n;
		int i=0;
		for(i;i<size;i++){
			printf("     Member %d : %s \n",i+1,ft->generation[i].firstname);
		}
		printf("\n");
	}
}
// Searches for the Individual Name in FamilyTree (both first and last names) and returns the found Node, returns NULL if Member not Found
Individual* getIndividualbyName(FamilyTree* ft,char* Name){
	Individual* ptr = NULL;
	if(ft){
		int size = ft->n;
		int i=0;
		for(i;i<size;i++){
			int comp1 = strcmp(ft->generation[i].firstname,Name);
			int comp2 = strcmp(ft->generation[i].lastname,Name);
			if(comp1==0 ||comp2==0){
				ptr = (Individual*) malloc(sizeof(Individual));
				*ptr = ft->generation[i];
				return ptr;
			}
		}
	}
	return ptr;
}
// Searches for the Individual in FamilyTree by DateOfBirth and returns the found Node, returns NULL if Member of that DateOfBirth is not Found
Individual* getIndividualbydob(FamilyTree* ft,dob* d){
	Individual* ptr = NULL;
	if(ft){
		int size = ft->n;
		int i=0;
		for(i;i<size;i++){
			bool x = d->day== ft->generation[i].DateOfBirth->day;
			bool y = d->month== ft->generation[i].DateOfBirth->month;
			bool z = d->year== ft->generation[i].DateOfBirth->year;

			if(x && y && z){
				ptr = (Individual*) malloc(sizeof(Individual));
				*ptr = ft->generation[i];
				return ptr;
			}
		}
	}
	return ptr;
}
// This func checks for the age difference for an Individual to be added as someone's child i.e parent can not be younger than the child and child cannot be remarkably younger than the parents
bool checkAgeDifference(dob* sonAge,dob* parentAge){
	int yearDiff = parentAge->year - sonAge->year;
	if(yearDiff <0)
		yearDiff *= -1; 
	if(yearDiff<16){
		print_dob(sonAge);
		print_dob(parentAge);
		printf("Child Age does not comply with the condition of makeChild %d \n",yearDiff);
		return false;
	}
	return true;
}
// This function takes the child Node, and parents Node and adds the connection between the nodes making a branch if all necessary conditions satisfy
// Both parents must be specified
// Age condition must satisfy
// Mother Node should have Gender F and Father Node must have Gender M
// Returns true if all good
bool makeChild(Individual* child,Individual* mother,Individual* father){
	if(child && mother && father){
		
		if (mother->gender!='F' || father->gender!='M'){
			printf("Mother Input to makeChild is a Male / Father Input a female \n");
			return false;
		}
		if(checkAgeDifference(child->DateOfBirth,mother->DateOfBirth) &&checkAgeDifference(child->DateOfBirth,father->DateOfBirth)){
			child->mother = malloc(strlen(mother->firstname)+1);
			child->father = malloc(strlen(father->firstname)+1);
			strcpy(child->mother,mother->firstname);
			strcpy(child->father,father->firstname);
			father->children[father->numChildren] = child->firstname;
			mother->children[mother->numChildren] = child->firstname;
			father->numChildren++;
			mother->numChildren++;
			return true;
		}
		return false;
	}else{
		return false;
	}
}
// Returns/Prints the children of that particular Individual with all the partners
void getChildrenP(Individual* I){
	if(I->numChildren!=0){
		printf("Children of Individual %s : ",I->firstname);
		int i=0;
		for (i;i<I->numChildren;i++){
			if(I->children[i])
				printf("%s, ",I->children[i]);
		}
		printf("\n");
	}
}
// Returns/Prints all the children of a particular Union
void getChildren(Individual* mother,Individual* father){
	printf("Children of Individuals %s and %s are : ",mother->firstname,father->firstname);
	if(father && mother){
		if(mother->numChildren!=0){
			if(father->numChildren!=0){
				int i,j;
				i=0;j=0;
				
				for(i;i<mother->numChildren;i++){
					for(j;j<father->numChildren;j++){
						if(mother->children[i] && father->children[j]){
							int c = strcmp(mother->children[i],father->children[j]);
							if(c==0){
								printf("%s, ",mother->children[i]);
								break;
							}
						}
					}
				}
				printf("\n");
			}
		}
	}
}

int main(){
	
	// Testing dob struct
	dob* t0 = make_dob(1,10,1978);
	dob* t1 = make_dob(12,11,1981);
	dob* t2 = make_dob(13,1,1968);
	dob* t3 = make_dob(14,2,1996);
	dob* t4 = make_dob(15,3,1994);
	
	dob* t5 = make_dob(16,6,1976);
	dob* t6 = make_dob(17,9,1980);
	dob* t7 = make_dob(18,12,1982);
	dob* t8 = make_dob(19,10,1999);
	dob* t9 = make_dob(10,10,1998);

	// print_dob(t1);
	
	// Testing Individual struct and make_Individual
	Individual* mfirst = make_Individual("Alex","Hales",t0,'M');
	Individual* msecond = make_Individual("Luke","Ronchi",t1,'M');
	Individual* mthird = make_Individual("Joe","Root",t2,'M');
	Individual* mfourth = make_Individual("Ranveer","Singh",t3,'M');
	Individual* mfifth = make_Individual("John","Cena",t4,'M');

	Individual* ffirst = make_Individual("Martha","Wayne",t5,'F');
	Individual* fsecond = make_Individual("Scarllet","Johanasson",t6,'F');
	Individual* fthird = make_Individual("Deepika","Padukone",t7,'F');
	Individual* ffourth = make_Individual("Anjelina","Joulie",t8,'F');
	Individual* ffifth = make_Individual("Brie","Bella",t9,'F');	
	
	// Creating a family Tree
	FamilyTree* ft = init_FamilyTree();
	// Add male members in a family Tree
	CreateIndividual(ft,mfirst);
	CreateIndividual(ft,msecond);
	CreateIndividual(ft,mthird);
	CreateIndividual(ft,mfourth);
	CreateIndividual(ft,mfifth);
	// Add Female Member in a family Tree
	CreateIndividual(ft,ffirst);
	CreateIndividual(ft,fsecond);
	CreateIndividual(ft,fthird);
	CreateIndividual(ft,ffourth);
	CreateIndividual(ft,ffifth);
	// Print Members in the family Tree
	printMembers(ft);
	printf("\n");
	
	// Testing getIndividual() and makeChild()
	Individual* son = getIndividualbydob(ft,t3);
	Individual* mother = getIndividualbydob(ft,t5);
	Individual* father = getIndividualbydob(ft,t0);
	makeChild(son,mother,father);
	print_Individual(son);
	printf("\n");

	// Takes a younger Individual and makes it a child of two older Members making a union if it already doesn't exist
	son = getIndividualbydob(ft,t4);
	makeChild(son,mother,father);
	print_Individual(son);
	printf("\n");

	// Takes a younger Individual and makes it a child of two older Members making a union if it already doesn't exist
	son = getIndividualbydob(ft,t8);
	makeChild(son,mother,father);
	// Validating the Results
	print_Individual(son);
	print_Individual(mother);
	print_Individual(father);
	
	// Validating Union Children and Individual Children
	printf("\n");
	getChildren(mother,father);
	printf("\n");
	getChildrenP(mother);
	printf("\n");

	// Takes a younger Individual and makes it a child of two older Members making a union if it already doesn't exist
	son = getIndividualbydob(ft,t9);
	mother = getIndividualbydob(ft,t6);
	makeChild(son,mother,father);
	
	// Validating Union Children and Individual Children
	getChildren(mother,father);
	printf("\n");
	getChildrenP(father);
	printf("\n");
	getChildrenP(mother);
	printf("\n");

	// Validating Results
	print_Individual(son);
	print_Individual(mother);
	print_Individual(father);
	
}
