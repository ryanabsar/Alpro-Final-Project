# Student List

Student list is a final project for algorithm and programming class at Faculty of Engineering Universitas Indonesia. The program uses a file to store student name.
## Group 2 Member
- ### Aldi Sumaputra - 1806228133
- ### Ryan Absar Ilmi - 1806187581

## Features

- Add new student.
- List all student
- Find student name by NPM

## Pictures

### Main menu
![](https://raw.githubusercontent.com/ryanabsar/Alpro-Final-Project/master/MainMenu.jpg)
### Add Student
![](https://raw.githubusercontent.com/ryanabsar/Alpro-Final-Project/master/addstudent.png)
### Student List
![](https://raw.githubusercontent.com/ryanabsar/Alpro-Final-Project/master/liststudent.png)
### Find Student NPM
![](https://raw.githubusercontent.com/ryanabsar/Alpro-Final-Project/master/NPM%20Student.png)



## Struct

```c
typedef struct absent {
    int number;
    char name[80];
    char NPM[20];
    char status[20];
    struct absent *next;
    int count;
} Absent;
Absent *firstc,*currentc,*newc;
```
## Add New Student

```c
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
```


## [Reference ](https://www.codewithc.com/mini-project-in-c-bank-management-system/ "https://www.codewithc.com/mini-project-in-c-bank-management-system/ ")
