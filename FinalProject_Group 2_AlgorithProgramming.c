#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

int displayMenu(char title[], char menu[][20], char instruction[],int maxMenuNumber );
void addstudent(void);
void listAll(void);
void deletestudent(void);
int findstudent(void);
int findnum (int);

struct data{
    int month,day,year;
    };

typedef struct absent {
    int number;
    char name[80];
    char NPM[20];
    char status[20];
    struct absent *next;
    int count;
} Absent;
Absent *firstc,*currentc,*newc;
/* firstc is used to point to first record in list
currentc points to current record in list
newc contains address of new structure/node
*/
int cnum = 0;

int main()
{
    FILE *datafile;
    char *filename = "data.dat";/*declare file name*/
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");/* open file for reading*/
    char menu[6][20]={"Add student", "Remove a student", "List All student", "Modify a data","Find a student by name","Save and Quit"};
    char userValue = '1';

    if(datafile)
    {
        firstc = (struct absent *)malloc(sizeof(struct absent));
        currentc = firstc;
        while(1)
        {
            newc = (struct absent *)malloc(sizeof(struct absent));
            fread(currentc,sizeof(struct absent),1,datafile); // reads data from the given stream into the array pointed to, by ptr.
            if(currentc->next == NULL)
            {
                break;
            }
            currentc->next = newc; //poiunter referencing next node
            currentc->count=0; //initiates count for comments
            currentc = newc; //make current record new
        }
        fclose(datafile);
        cnum = currentc->number;
    }
    fflush(stdin); // clear input buffer
    /*while (userValue != 48) //48 is 0 in ascii
    {
        userValue = displayMenu("\t\t\t===Library of Congress===",menu,"Please select choice!",6);
        switch (userValue)
        {
            case '1':
                puts("Add a new book\n");
                fflush(stdin);
                addNewbook();
                break;
            case '2':
                //edit();
                break;
            case '3':
                listAll();
                break;
            case '4':
                //view_all();
                break;
            case '5':
                //view_all();
                break;
            case '6':
                printf("Save and quit\n");
                default:
                break;
        }
    }*/
    do
    {
	fflush(stdin); // clear input buffer
        puts("\nWelcome To The Student Database");/* print menu messages*/
        puts("-- -----------------------------");
        puts("1 - Add a new student");
        puts("2 - List all student");
        puts("3 - Find student by name ");
        puts("-- -----------------------------");
        puts("Q - Save and quit\n");
        printf("\tYour choice:");
        ch = getchar(); //Fungsi ini meminta inputan satu buah karakter dari keyboard lalu menekan enter
	    ch = toupper(ch);/*changes user input case to upper case*/
        switch(ch)     /*stores in ch variable.*/
        {
            case '1':
                puts("Add a new student\n");
                fflush(stdin);
                addNewstudent();//call addNewcontact function
                break;
            case '2':
                puts("List all students\n");
                listAll();
                break;
            case '3':
                puts("Find a contact by name\n");
                findstudent();
                break;
            case 'Q':
                puts("Save and quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');

    currentc = firstc;

    if(currentc==NULL)
    {
        return(0);
    }
    datafile = fopen(filename,"w");
    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }/* Write each record to disk*/
    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct absent),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);             /*closes data file*/
    return(0);
}

int displayMenu(char title[], char menu[][20], char instruction[],int maxMenuNumber ){
    int i;
    char userInput;

    for ( i=0; i<24; i++) printf("\n");
    printf("%s\n", title);
    for ( i=0; i<maxMenuNumber; i++){
        printf("[%d]. %s\n", i+1, menu[i]);
    }
    printf("\n0: Exit/Back\n");
    printf("%s\n", instruction);
    scanf(" %c",&userInput);
    while ( userInput<48 || userInput > 48 + maxMenuNumber)
    {
        printf("Please enter the correct number!\n");
        scanf(" %c",&userInput);
    }
    return userInput;
}

void addNewstudent(void)
{
    newc = (struct absent *)malloc(sizeof(struct absent));

    if(firstc==NULL)
    {
        firstc = currentc = newc; //hecks to see whether this is the first record in file  //If so, then all pointers are initialized to this record,
    }
    else
    {
        currentc = firstc;      /* make the first record the current one*/

        while(currentc->next != NULL)
            currentc = currentc->next;
                                /* and loop through all records*/
        currentc->next = newc;  /* pointer to next node */
        currentc = newc;        /* make current record the new one*/
    }
    cnum++;

    printf("%27s: %5d\n"," student absent list",cnum);
    currentc->number = cnum;

    printf("%27s: ","Enter name");
    gets(currentc->name);
    printf("%27s: ","Enter NPM");
    gets(currentc->NPM);

    printf("contact added!");
    currentc->count=0;

    currentc->next = NULL; //gives new record a NULL pointer to show it's the last
}

void listAll(void)
{
    if(firstc==NULL)
    {
        printf("There are no contacts to display!");
    }
    else
    {
       printf("%6s %-20s %-20s \n","no","name","NPM");
       puts("------ -------------------- -------------------- ");

       currentc=firstc;

       do
       {
           printf("%6d: %-20s %-20s \n",currentc->number,currentc->name,currentc->NPM);
       }
       while((currentc=currentc->next) != NULL);
    }
}

void deletestudent(void)
{
    int record;
    struct absent *previousa;
    if(firstc==NULL)
    {
        puts("There are no student   to delete!:");
        return;
    }

    listAll();
    printf("Enter student ID to delete: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL)
    {
        if(currentc->number == record)
        {
            if(currentc->number == record)
            firstc=currentc->next;
            else
            previousa->next = currentc->next;

            free(currentc);
            printf("Absent %d deleted!\n",record);
            return;
        }
        else
        {
            previousa = currentc;
            currentc = currentc->next;
        }
    }
    printf("absent %d not found!\n",record);

}

int findstudent(void)
{
    char buff[20];

    if(firstc==NULL)
    {
        puts("There are no student to find!");
        return 1;
    }

    printf("Enter student name: ");
    fflush(stdin);/*clears any text from the input stream*/
    gets(buff);

    currentc=firstc;
    while(currentc !=NULL)
    {
        if(strcmp(currentc->name,buff)==0)
        {
            printf("%6s %-20s %-20s \n","no","name","NPM");
            printf("%6d: %-20s %-20s \n",currentc->number,currentc->name,currentc->NPM);
            return 0;
        }
        else
        {
            currentc=currentc->next;
        }
    }
}

int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

        if(currentc->number == record)
	     {
           return 1;
         }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}

