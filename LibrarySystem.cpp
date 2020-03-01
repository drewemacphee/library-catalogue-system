//C++ Assignment 1 Question 1: Sort function
//Drew MacPhee

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//structure
struct libraryCommands {
    char author[50];
    char libName[40];
    char publisher[40];
    char title[50];
    float replace;
    char genre[40];
    int indexnum;
    char curLoan[50];
    char dueDate[10];
    struct libraryCommands *next;
};

//function headers
struct libraryCommands *NewEntry();
void addEntry(struct libraryCommands *start);
void Browse(struct libraryCommands *start);
struct libraryCommands *Delete(struct libraryCommands *start);
void SearchAuthor(struct libraryCommands *start);
void SearchTitle(struct libraryCommands *start);
void Modify(struct libraryCommands *start);
void NewFile(FILE *p_file); 
void Save(struct libraryCommands *start, FILE *p_file);
struct libraryCommands *Load(struct libraryCommands *start, FILE *p_file);
void Sort(struct libraryCommands *start);
struct libraryCommands *swapA(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight);
 struct libraryCommands *swapB(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight);
 struct libraryCommands *swapC(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight);
 struct libraryCommands *swapD(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight);

int main ()
{
    struct libraryCommands *start, *last, *new2;
    FILE *p_file;
    start = 0;
    last = 0;
    new2 = 0;
    int entryCount, load;

    int run = 1;
    int choice;
    int ch;
    //prompt user to start with new data or load previously saved data
    puts("Would you like to:\n");
    puts("1. Load a previously saved library database");
    puts("2. Load a new database\n");
    scanf("%d", &load);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if(load == 1)
    {
        //if old data, show success message for load and present options in case statement
        start = Load(start, p_file);
    }
    else if(load == 2)
    {
        //if new data, there are currently no entries. would you like to add an entry?
        NewFile(p_file); 
    }

    while (run == 1)
    {
        puts("Please choose an option:");
        puts("1. Add new entry");
        puts("2. Browse entries");
        puts("3. Modify existing entry ");
        puts("4. Delete entry");
        puts("5. Save entries ");
        puts("6. Sort entries alphabetically");
        puts("7. Search by book title");
        puts("8. Search by author");

        scanf("%d", &choice);
        while ((ch = getchar()) != '\n' && ch != EOF);

        //call function for different options
        switch(choice) 
        {
            case 1:
            if (start == 0)
            {
                start = NewEntry();
            }
            else
            {
                addEntry(start);
            };
            break;
            case 2: Browse(start); break;
            case 3: Modify(start); break;
            case 4: start = Delete(start); break;
            case 5: Save(start, p_file); break;
            case 6: Sort(start); break;
            case 7: SearchTitle(start);
            case 8: SearchAuthor(start); break;
            default: puts("Error. You did not choose a specified option.");
            
        }
    }

    return 0;
}

//this function will sort the titles alphabetically and display the new sorted list of entries
//This function has been refactored for Assignment 1 of C++

void Sort(struct libraryCommands *start) 
{
    struct libraryCommands *end, *left, *lastLeft, *right, *lastRight;
    int count = 1;
    end = start;
    bool swap;

    //Find address of end 
    while (end->next != NULL)
    {
        end = end->next;
        count++;
    }

    left = start;
    lastLeft = start;
    lastRight = left;
    right = left;

    //outer loop compares left-most
    for(int i = 0; i < (count - 1); i++)
    {
        //inner loop compares each to the right of outer loop
        for(int j = (i + 1); j < count; j++ )
        {   
            //move comparison to the right 
            lastRight = right;
            right = right->next;

            if (strcmp(left->title, right->title) > 0) {
                swap = true;
            }
            else 
            {
                swap = false;
            }
            
            // swap start and end 
            if (swap == true && left == start && right->next == NULL)
            {
                start = swapA(start, left, lastLeft, right, lastRight);
                
                struct libraryCommands *leftTemp;
                leftTemp = left;
                left = right;
                lastLeft = left;
                right = leftTemp;
            }
            //swap start and inner node
            else if (swap == true && left == start && right->next != NULL)
            {
                start = swapB(start, left, lastLeft, right, lastRight);

                struct libraryCommands *rightTemp;
                rightTemp = right;
                right = left;
                left = rightTemp;
                lastLeft = left;
            }
            //swap end and inner node
            else if (swap == true && left != start && right->next == NULL)
            {
                start = swapC(start, left, lastLeft, right, lastRight );

                struct libraryCommands *rightTemp;
                rightTemp = right;
                right = left;
                left = rightTemp;
                lastRight = left;
            }
            //swap two inner nodes
            else if (swap == true && left != start && right->next != NULL)
            {
                start = swapD(start, left, lastLeft, right, lastRight);

                struct libraryCommands *rightTemp;
                rightTemp = right;
                right = left;
                //if the swap is side by side
                if ( lastRight == left) {
                    lastRight = rightTemp;
                }
                left = rightTemp;

            }
        }
        lastLeft = left;
        left = left->next;
        right = left;
    }    
    printf("\nBelow are your entries sorted in alphabetical order.\n");
    Browse(start);
}

//below are the 4 swap functions
//swapA will swap start and end nodes
struct libraryCommands *swapA(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight)
{
    struct libraryCommands *temp;
    temp = right->next; // same as null

    right->next = left->next;
    lastRight->next = left;
    left->next = temp;
    start = right;

    return start;
}

//swapB will swap start and inner node
struct libraryCommands *swapB(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight)
{
    struct libraryCommands *temp;
    temp = right->next;
    right->next = left->next;
    lastRight->next = left;
    left->next = temp;
    start = right;

    return start;
}

//swapC swap inner and end
struct libraryCommands *swapC(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight)
{
    lastLeft->next = right;
    lastRight->next = left;
    right->next = left->next;
    left->next = NULL;

    return start;
}

//swapD will swap two inner nodes
struct libraryCommands *swapD(struct libraryCommands *start, struct libraryCommands *left, struct libraryCommands *lastLeft,
 struct libraryCommands *right, struct libraryCommands *lastRight)
{
    struct libraryCommands *temp;
    temp = right->next;
    lastLeft->next = right;
    //if the swap is not side by side
    if( lastRight != left) {
        lastRight->next = left;
    }
    left->next = temp;
    right->next = lastRight;

    return start;
}

//this function will load a previously saved database of entries
struct libraryCommands *Load(struct libraryCommands *start, FILE *p_file)
{
    char filename[15] = "database.txt";
    struct libraryCommands *current, *new2;
    int numOfNodes = 0, counter = 0;

    //open file for reading the binary file that was saved
    p_file = fopen(filename, "rb");
    if(p_file == NULL)
    {
        puts("Error opening file.");
        exit(1);
    }
    
    //get number of nodes from file
    fscanf(p_file, "%d", &numOfNodes);
    
    //loop through entries in file the amount of saved nodes
    while (counter < numOfNodes) {
        //check if current is the start node
        if(start == 0)
        {
            new2 = (struct libraryCommands *)malloc(sizeof(struct libraryCommands));
            if (new2 == NULL)
            {
                puts("Memory allocation error");
                exit(1);
            }
            start = new2;
            //read in first struct of binary file
            fread(start, sizeof(struct libraryCommands), 1, p_file);
            start->next = NULL;
            current = start;
        }
        //if not first node
        else if (start != 0)
        {
            new2 = (struct libraryCommands *)malloc(sizeof(struct libraryCommands));
            if (new2 == NULL)
            {
                puts("Memory allocation error");
                exit(1);
            }
            //set next to new space allocated, and set current to struct of new mem allocated
            current->next = new2;
            current = new2;
            //read in entry to current struct and set current->next to null because it is end of list
            fread(current, sizeof(struct libraryCommands), 1, p_file);
            current->next = NULL;
        } 
        //increase counter to get next node
     counter ++;
    }


    fclose(p_file);
   
    return start;
}

//this function will save the entries to the save file database.txt
void Save(struct libraryCommands *start, FILE *p_file)
{
    char filename[15] = "database.txt";
    struct libraryCommands *current;
    int numOfNodes;
    int *num;

    current = start;

    //loop through to get a total count of nodes and add node for final structure
    for(numOfNodes = 0; current->next != NULL; numOfNodes++)
    {
        current = current->next;
    }
    numOfNodes = numOfNodes + 1;

    //open file for writing with w to write over old data
    p_file = fopen(filename, "wb");
    if(p_file == NULL)
    {
        puts("Error opening file.");
        exit(1);
    }
    //write the number of nodes to the beginning of the file
    //fwrite(*num, sizeof(int), 1, p_file);
    fprintf(p_file, "%d", numOfNodes);

    current = start;
    //loops through all structs to write to file
    while(current->next != NULL)
    {
        fwrite(current, sizeof(struct libraryCommands), 1, p_file);
        current = current->next;
    }
    //write last struct to file
    fwrite(current, sizeof(struct libraryCommands), 1, p_file);

//success message for user
    if(&fwrite != 0)
    {
        puts("\nYou have saved all the current library entries.\n");
    }
    else
    {
        puts("\nError saving the entries to the save file.\n");
    }
    fclose(p_file);
}
//This function will overwrite the old save file with new data
void NewFile(FILE *p_file)
{
    
    char filename[15] = "database.txt";

    //open file for writing with w to write over old data
    p_file = fopen(filename, "wb");
    if(p_file == NULL)
    {
        puts("Error opening file.");
        exit(1);
    }

    fclose(p_file);
}

//This function will be used to modify an entry in the list
void Modify(struct libraryCommands *start)
{
    struct libraryCommands *current;
    int ch, entryMod;
    char keep;

    current = start;

    puts("Which entry would you like to modify?\n");
    scanf("%d", &entryMod);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if( start == 0)
    {
        puts("There are currently no entries to modify. ");
    }
    else 
    {
//loop to entry to be modified
        for(int i = 1; i < entryMod; i++) 
        {
            current = current->next;
        }

        puts("You wish to modify this entry:\n");
        printf("Author: %s\n", (*current).author);
        printf("Library Name: %s\n", (*current).libName);
        printf("Publisher: %s\n", (*current).publisher);
        printf("Title: %s\n", (*current).title);
        printf("Replacement Cost: $%.2f\n", (*current).replace);
        printf("Genre: %s\n", (*current).genre);
        printf("Index Number: %d\n", (*current).indexnum);
        printf("Currently on loan to: %s\n", (*current).curLoan);
        printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);

        puts("y or n?\n");
        scanf("%c", &keep);
        while ((ch = getchar()) != '\n' && ch != EOF);

//prompt for which element to change in object
        if(keep == 'y')
        {
            puts("Please enter the number corresponding to the data you wish to change: \n");
            puts("1. Author \n2. Library Name \n3. Publisher \n4. Title\n5. Replacement Cost \n6. Genre \n7.Index Number \n8. Currently on Loan to \n9. Due Date \n");
            scanf("%d", &entryMod);
            while ((ch = getchar()) != '\n' && ch != EOF);
            if(entryMod == 1)
            {
                puts("Please enter author:");
                scanf("%[^\n]s", (*current).author);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 2)
            {
                puts("Please enter library name:");
                scanf("%[^\n]s", (*current).libName);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 3)
            {
                puts("Please enter publisher:");
                scanf("%[^\n]s", (*current).publisher);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 4)
            {
                puts("Please enter title:");
                scanf("%[^\n]s", (*current).title);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 5)
            {
                puts("Please enter replacement cost:");
                scanf("%f", &(*current).replace);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 6)
            {
                puts("Please enter genre:");
                scanf("%[^\n]s", (*current).genre);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 7)
            {
                puts("Please enter index number:");
                scanf("%d", &(*current).indexnum);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 8)
            {
                puts("Please enter currently on loan to:");
                scanf("%[^\n]s", (*current).curLoan);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else if (entryMod == 9)
            {
                puts("Please enter due date:");
                scanf("%[^\n]s", (*current).dueDate);
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
        }
    }
    
}

//This function will be used to search through the book titles (exact matches)
void SearchTitle(struct libraryCommands *start)
{
    struct libraryCommands *current;
    char title[50];
    int ch;
    int count = 0;

    current = start;

    //prompt user for title
    puts("Please enter an author to search for: \n");
    scanf("%[^\n]s", title);
    while ((ch = getchar()) != '\n' && ch != EOF);

    //scan through the list and compare current->title to the input title
    while(current->next != NULL)
    {
        //if a match, output whole struct to screen
        if(strcmp(current->title, title) == 0)
        {
            printf("Author: %s\n", (*current).author);
            printf("Library Name: %s\n", (*current).libName);
            printf("Publisher: %s\n", (*current).publisher);
            printf("Title: %s\n", (*current).title);
            printf("Replacement Cost: $%.2f\n", (*current).replace);
            printf("Genre: %s\n", (*current).genre);
            printf("Index Number: %d\n", (*current).indexnum);
            printf("Currently on loan to: %s\n", (*current).curLoan);
            printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);
            count++;
        }
        current = current->next;
    }
    //check if theres a match in the last node
    if(strcmp(current->title, title) == 0)
    {
        printf("Author: %s\n", (*current).author);
        printf("Library Name: %s\n", (*current).libName);
        printf("Publisher: %s\n", (*current).publisher);
        printf("Title: %s\n", (*current).title);
        printf("Replacement Cost: $%.2f\n", (*current).replace);
        printf("Genre: %s\n", (*current).genre);
        printf("Index Number: %d\n", (*current).indexnum);
        printf("Currently on loan to: %s\n", (*current).curLoan);
        printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);
        count++;
    }
    //total matches of titles
    printf("There were %d match(es).\n", count);

}

//This function will be used to search through the authors (exact matches)
void SearchAuthor(struct libraryCommands *start) 
{
    struct libraryCommands *current;
    char author[50];
    int ch;
    int count = 0;

    current = start;

    //prompt for author name input
    puts("Please enter an author to search for: \n");
    scanf("%[^\n]s", author);
    while ((ch = getchar()) != '\n' && ch != EOF);
    //scan through whole linked list and compare current->author with the input
    while(current->next != NULL)
    {
        //if a match, output whole struct to screen
        if(strcmp(current->author, author) == 0)
        {
            printf("Author: %s\n", (*current).author);
            printf("Library Name: %s\n", (*current).libName);
            printf("Publisher: %s\n", (*current).publisher);
            printf("Title: %s\n", (*current).title);
            printf("Replacement Cost: $%.2f\n", (*current).replace);
            printf("Genre: %s\n", (*current).genre);
            printf("Index Number: %d\n", (*current).indexnum);
            printf("Currently on loan to: %s\n", (*current).curLoan);
            printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);
            count++;
        }
        current = current->next;
    }
    //check if theres a match in the last node
    if(strcmp(current->author, author) == 0)
    {
        printf("Author: %s\n", (*current).author);
        printf("Library Name: %s\n", (*current).libName);
        printf("Publisher: %s\n", (*current).publisher);
        printf("Title: %s\n", (*current).title);
        printf("Replacement Cost: $%.2f\n", (*current).replace);
        printf("Genre: %s\n", (*current).genre);
        printf("Index Number: %d\n", (*current).indexnum);
        printf("Currently on loan to: %s\n", (*current).curLoan);
        printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);
        count++;
    }
    //total matches
    printf("There were %d matches.\n", count);
    
}
//This function will be used to delete entries from the list
struct libraryCommands *Delete(struct libraryCommands *start) 
{
    int entryDel, ch;
    struct libraryCommands *current, *current2;
    char keep;

    current = start;

    puts("Which entry would you like to delete?\n");
    scanf("%d", &entryDel);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if( start == 0)
    {
        puts("There are currently no entries to delete. ");
    }
    else 
    {
        //loop through to entry to be deleted and display to user
        for(int i = 1; i < entryDel; i++) 
        {
            current = current->next;
        }

        puts("You want to delete:\n");
        printf("Author: %s\n", (*current).author);
        printf("Library Name: %s\n", (*current).libName);
        printf("Publisher: %s\n", (*current).publisher);
        printf("Title: %s\n", (*current).title);
        printf("Replacement Cost: $%.2f\n", (*current).replace);
        printf("Genre: %s\n", (*current).genre);
        printf("Index Number: %d\n", (*current).indexnum);
        printf("Currently on loan to: %s\n", (*current).curLoan);
        printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);

        puts("y or n?\n");
        scanf("%c", &keep);
        while ((ch = getchar()) != '\n' && ch != EOF);

        if(keep == 'y')
        {
            //if the entry is the start of the list
            if(entryDel == 1) 
            {
                free(start);
                start = start->next;
            }
            //if the entry is the last in the list
            else if(current->next == NULL)
            {
                current = start;
                current2 = current->next;
                while(current2->next != NULL) 
                {
                    current = current2;
                    current2 = current->next;
                }
                free(current->next);
                current->next = NULL;
                if(start == current)
                {
                    start = NULL;
                }
            }
            //if the entry is in the middle of the list
            else
            {
                current = start;
                //point to element before the one to be deleted
                for(int j = 1; j < (entryDel - 1); j++)
                {
                    current = current->next;
                }
                current2 = current->next;
                free(current->next);
                current->next = current2->next;
            }
            puts("Success, entry was deleted.\n");
        }
    }
    
    return start;
}

//This function will be used to print out the current entries 
void Browse(struct libraryCommands *start) {
    
    struct libraryCommands *current;
    int count = 1;

    if(start == 0)
    {
        puts("There are currently no entries. ");
    }
    else 
    {
        current = start;
        //output the entries until the endof the list is reached (extra entry print out for the remaining node)
        while (current->next != 0)
        {
            printf("%d.", count);
            printf("Author: %s\n", (*current).author);
            printf("Library Name: %s\n", (*current).libName);
            printf("Publisher: %s\n", (*current).publisher);
            printf("Title: %s\n", (*current).title);
            printf("Replacement Cost: $%.2f\n", (*current).replace);
            printf("Genre: %s\n", (*current).genre);
            printf("Index Number: %d\n", (*current).indexnum);
            printf("Currently on loan to: %s\n", (*current).curLoan);
            printf("Due Date (YYYY/MM/DD): %s\n\n", (*current).dueDate);
            current = current->next;
            count ++;
        }
        printf("%d.", count);
        printf("Author: %s\n", (*current).author);
        printf("Library Name: %s\n", (*current).libName);
        printf("Publisher: %s\n", (*current).publisher);
        printf("Title: %s\n", (*current).title);
        printf("Replacement Cost: $%.2f\n", (*current).replace);
        printf("Genre: %s\n", (*current).genre);
        printf("Index Number: %d\n", (*current).indexnum);
        printf("Currently on loan to: %s\n", (*current).curLoan);
        printf("Due Date (YYYY/MM/DD): %s\n", (*current).dueDate);
        puts("End of entries.\n\n");
    }
    
}

//This function will be used if there is already a start node
void addEntry(struct libraryCommands *start) {
    struct libraryCommands *current, *new2;
    int ch;

    //scan through until end of list
    current = start;
    while (current->next != NULL)
    {
        current = current->next;
    }
    
    //add new entry at the end of the list
    new2 = (struct libraryCommands *)malloc(sizeof(struct libraryCommands));
    if (new2 == NULL)
        {
            puts("Memory allocation error");
            exit(1);
        }

    current->next = new2;
    current = new2;

    //prompt for input
    puts("Please enter author:");
    scanf("%[^\n]s", (*current).author);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter library name:");
    scanf("%[^\n]s", (*current).libName);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter publisher:");
    scanf("%[^\n]s", (*current).publisher);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter title of book:");
    scanf("%[^\n]s", (*current).title);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter replacement cost:");
    scanf("%f", &(*current).replace);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter genre:");
    scanf("%[^\n]s", (*current).genre);
    while ((ch = getchar()) != '\n' && ch != EOF);  
    puts("Please enter index number:");
    scanf("%d", &(*current).indexnum);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter currently on loan to:");
    scanf("%[^\n]s", (*current).curLoan);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter due date:");
    scanf("%[^\n]s", (*current).dueDate);
    while ((ch = getchar()) != '\n' && ch != EOF);
    //set the next pointer to null
    new2->next = 0;
}

//This function will be used if no entries have been added and a start node needs to be created and return start node
struct libraryCommands *NewEntry() {

    struct libraryCommands *start, *new2;
    int ch;

    //create entry for head 
    new2 = (struct libraryCommands *)malloc(sizeof(struct libraryCommands));
    if (new2 == NULL)
    {
        puts("Memory allocation error");
        exit(1);
    }
    //if allocated without issues prompt user for entry
    // use [^\n] to include whitespaces within the character arrays/strings of input
    start = new2;
    puts("Please enter author:");
    scanf("%[^\n]s", (*start).author);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter library name:");
    scanf("%[^\n]s", (*start).libName);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter publisher:");
    scanf("%[^\n]s", (*start).publisher);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter title of book:");
    scanf("%[^\n]s", (*start).title);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter replacement cost:");
    scanf("%f", &(*start).replace);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter genre:");
    scanf("%[^\n]s", (*start).genre);
    while ((ch = getchar()) != '\n' && ch != EOF);  
    puts("Please enter index number:");
    scanf("%d", &(*start).indexnum);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter currently on loan to:");
    scanf("%[^\n]s", (*start).curLoan);
    while ((ch = getchar()) != '\n' && ch != EOF);
    puts("Please enter due date:");
    scanf("%[^\n]s", (*start).dueDate);
    while ((ch = getchar()) != '\n' && ch != EOF);
    //set link pointer to null 
    start->next = 0;

    return start;
}