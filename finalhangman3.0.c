#include <stdio.h>   // input and output
#include <string.h>  // strlen()
#include <ctype.h>   // toupper()
#include <stdlib.h>  // exit()
#include<unistd.h>
#include<windows.h>
#include <time.h>    // srand(), rand()

#define NUM_OF_WORDS   25           // The number of words in the words list.
#define NUM_OF_CHANCES 5            // The number of tries allowed before hanging the hangman
#define TRUE           1            // Bool for TRUE
#define FALSE          0            // Bool for FALSE

/* Prototypes */
void show_heading_rules();
void scold_and_quit();
void see_in_word(char, const char [], char *, const size_t, unsigned int *);
void show_word_clue(const size_t);
char name[10];
static int k[10];
void getword(char*);
void random(char []);
void intro (void);
void random(char *a)
{   int m,n;
	srand(time(NULL));
	m=rand() % (strlen(name)-1)+0;
	n=rand() % (strlen(name)-1)+0;
	k[n]=1;
	k[m]=1;
	a[m]=name[m];
	a[n]=name[n];
}
/* Shows the game heading and prints out the rules of the game. */
void show_heading_rules()
{
    printf("\n\t\t\t\tHANGMAN\n\n");
    printf(" Hint :Hangman is a game where you are expected to guess a word in a certain number of chances that is"
          " before you hang the hangman.\n\n");
    printf("A word has been chosen, begin guessing it. Good luck\n\n");
    printf("Guess the Word: ");
}
void intro ()
{int a,b;

for(a=0;a<10;a++)
    {
        system("cls");
        b=0;
        while(b!=a)
        {
        printf("    \n");
        b++;
        }
           printf("            |   |    /\\      |\\  |   /----   |\\  /|   /\\      |\\  |\n");
           printf("            |---|   /--\\     | \\ |   |  __   | \\/ |  /--\\     | \\ |\n");
           printf("            |   |  /    \\    |  \\|   |___|   |    | /    \\    |  \\|\n");
           Sleep(150);


    }
           printf("\n\n\n                               press any key  !!!                        ");
           printf("\n \n                        HINT : KEEP YOUR CAPLOCKS KEY ON\n");
    getch();
    system("cls");
}

void getword(char *a)
 {
 	do
 	{
	 *a=getch();
		if(*a>=65&&*a<=90)
		{
			printf("*");
			a++;
		}
		}while(*a!=13);
	*a='\0';
   }
 
/* Exit the game after printing a mean message. This is called after maximum chances are reached */
void scold_and_quit()
{
    printf("\n\nYou loss . Better try next time . THE END....\n\n");
    printf("\n\n\n ---------------------------- GAME OVER --------------------------------\n");
    exit(0);
}

/*
   Show the word that is selected randomly as a space seperated '_' character.
   where each letter in the word is replaced by a underscore and each underscore is
   seperated by a single white space.
   This is called when a word has been chosen randomly.

   Param: Takes length of the word chosen as a parameter.
*/
void show_word_clue(const size_t len)
{
    size_t i; // Loop counter.
    for(i = 0; i < len; i++)
    if(k[i]==1)
    printf(" %c ",name[i]);
    else
        printf(" _ ");
    printf("\n\n");
}


/*
    Check wether the word guessed by the user is actually in the chosen word.

    Param:
            char guessed      -- The char that has been guessed by the user.
            const char word[] -- The randomly chosen word.
            char *a           -- Dynamically allocated pointer to character array, which stores
                                 '_' for wrong guesses and the character guessed itself for
                                 the correct guesses
            const size_t len  -- The length of the chosen word.
            unsigned *found   -- The value is set to true if guessed is correct and false if not.
*/
void see_in_word(char guessed, const char word[], char *a, const size_t len, unsigned int *found)
{
    size_t i;
for(i = 0; i < len; i++)
    {
    	if(k[i]==1)
    	continue;
        if(guessed == word[i])
        {
            /*
               If the guessed word appears in the chosen word, then store that letter in
               the 'a' array and make the found variable as true since correct letter is
               guessed.
            */
            *(a + i) = guessed;
            *found = TRUE;
            k[i]=1;
            break; /*DISPLAY ONLY ONE WORD FOR SAME LETTERS IN THE WORD*/
        }

    }
     for(i = 0; i < len; i++)
     {
     	if(k[i]==1)
     	printf(" %c ",*(a + i));
     	else
     	printf(" _ ");
	 }


    if(strcmp(a, word) == 0) // If the 'a' array is equal to the guessed word, then congragulate and exit.
    {
        printf("\n\nYou did it. Well done.  \n\n");
        printf("========================CONGRATULATION========================");
        exit(0);
    }

    return;

}

/* Begin here -- Main */

int main()
{
     int score=0;
    /* Draw  the characters for hangman */
    char *hanged[]={
                     "|=====|\n"
                     "      |\n"
                     "      |\n"
                     "      |\n"
                     "     ===\n",
                     "|=====|\n"
                     "O     |\n"
                     "      |\n"
                     "      |\n"
                     "     ===\n",
                     "|=====|\n"
                     "O     |\n"
                     "|     |\n"
                     "      |\n"
                     "     ===\n",
                     "|=====|\n"
                     "O     |\n"
                     "|     |\n"
                     "|     |\n"
                     "     ===\n",
                     " |=====|\n"
                     " O     |\n"
                     " |     |\n"
                    "/ \\    |\n"
                     "     ===\n"

    };
    intro();
	printf("\n Enter a word to guess : \t");
 
    /* Initialize words to be chosen*/
    getword(name);
    /* Call the function that shows rules and prints the game heading */
    show_heading_rules();
    /* Initialize a random function to guess a word randomly */
	/* Varaibles for the game */
    char guessed; // The letter that user guesses
    size_t len = strlen(name); // length of the chosen word
    size_t i = 0;               // Loop variable.
    unsigned int found = FALSE; // By default, the letter guessed by the user is false.
    unsigned int chances = 0;   // Number of chances before the hangman is hanged.
    /* Allocate a holder to store the letters that are correctly guessed by the user */
    char a[10];
    random(a);
	/* Show the word chosen, but use '_' to represent each letter in the word */
	
    show_word_clue(len);

	printf("\nGuess a letter: ");

    /* The loop to handle input and play the game*/
    while(1)
    {
        /* Take input from the user */
        guessed = toupper(getchar());
        /* Stop from processing the \n char*/
        if(guessed != '\n'){ // Ignore '\n'.
            printf("\nGuess a letter: ");
            /* Test whether the letter guessed appears in the chosen word */
            see_in_word(guessed, name, a, len, &found);
            if(found== TRUE)
            {
                score=score+10;
                printf("\nThe letter exists");
                printf("\nChances left : %d \t \n",(5-chances));
                printf("\n Your Current Score : \t%d \n",score);
            }
            /* Handler for all the misguessed letters */
            if(found == FALSE) // If the user did not guess correctly
            {
                if(chances >= 4) // If maaximum chances have been used
                {
                    printf("\n\n%s\n\n", hanged[chances++]); // Draw the final character.
                    scold_and_quit(); // exit the game, with a mean message.
                }
                /* Print a message and increment the number of chances and hecnce printing the corresponding hangman */
                printf("\n\nToo bad. Wrong guess. Try again\n");
                printf("\nChances left : %d\t",(4-chances));
                printf("\nYour Score: \t%d",score);
                printf("\n\n%s\n\n", hanged[chances++]);
            }

            found = FALSE; // Again initialize to fault either the correct letter was guessed or not.
        }
    }
}


