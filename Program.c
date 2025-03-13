
/*
Miar Taweel
*/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

//defining the pointer to the node as a standard value type
typedef struct node* arrow;
typedef arrow stack;
typedef struct nodeA* arrowA;
typedef arrowA stackA;

//building the structure of the two types of stacks' nodes
struct node{
char element;
struct node* next;

};

struct nodeA{
char element[1000];
struct nodeA* next;

};


//The prototypes for all functions

stackA createEmptyA();

int match(char  ,char );

int isEmpty(stack );

int isEmptyA(stackA );

void pop(stack );

void popA(stackA );

stack createEmpty();

void DisposeStack( stack );

void makeEmptyA(stackA );

void makeEmpty(stack );

char top(stack );

const char*  topA(stackA );

void push (stack  , char );

void pushA (stackA  , char a[1000] );

int paraValid(char a[1000]);

int signValid(char a[1000]);

void printStack(stack );

int compare(char a, char b);

stackA infixPre(char a[100][100], int);

stackA reverse(char a[1000]);

double evaluate(char a[][100],int  );

int main()
{  FILE *f,*pp;// declaring and initialising the files pointers
char tryout[10000];//Declaration of a test array

int size=0;
char read=NULL;



char v[20];//A string for the name of the file

//initialising values
int i=0;
int l=0;

stackA s=createEmptyA();

 printf("\nPlease Enter The files name :\n") ;// Asking the user to provide the files' name
         scanf("%s",v);
         strcat(v,".txt");

         while (access(v, F_OK) != 0) {//Checking if the file exists
                printf("\nFile doesnt Exist\nPlease insert a valid file name:") ;
                scanf("%s",v);
                strcat(v,".txt");

         }
           f = fopen (v, "r");

              while (1) {//A loop to count the amount of numbers in the file

                   fscanf(f, "%s", tryout);
                  if (feof(f))
                        break;

                      size++;

                    }
                    char a[size][1000];//Declaration of arrays of strings for the given equations

           fclose(f);

while(1){//A loop for printing the menu and executing the operations
printf("\nPlease Choose one of the following:\n1.Read Equations from the file\n2.Print Invalid Equations\n3.Convert From infix to prefix\n4.Evaluate the prefix\n5.Check validity\n6.Print report to file\n7.Exit\n");
     int x;
     scanf("%d",&x) ;


     //if conditions for each case(operation) of the menu
     if (x==1){


      //Reading the values from the file , placing them in an array and printing them on the screen
     if (read!=NULL)
         printf("the file has already been read");
     else{

         f = fopen (v, "r");//opening the file
         printf("\nThe equations read are: ");

           i=0;
           while (1) {// A loop to read the file

            fscanf(f, "%s", a[i]);
            if (feof(f))
                break;
            printf("\n%d.%s", i+1,a[i]);
            i++;


              }
              read='r';
             }
            }


    else if (x==2){//Printing invalid equations

        if(read==NULL){
            printf("Please read the file first");

        }else {

             printf("\nThe following equations are invalid:\n");
                for(int k=0 ;k<size;k++){
                    if ((paraValid(a[k])==0)||(signValid(a[k])==0)){

                        printf("Equation No%d=%s\n",k+1,a[k]);

                }

            }}


    }else if (x==3){// From infix to Prefix case

    if(read==NULL){//Checking if the file has been read
        printf("Please read the file first");

        }else {

         for(int k=0;k<size;k++){
         if ((paraValid(a[k])==1)&&(signValid(a[k])==1)){
          stackA ans= reverse(a[k]);//reversing the equation and returning a stack

         char answ[100][100];
         int p=0;
         while(!isEmptyA(ans)){// a loop to insert the stacks contents into a multi dimensional array
          strcpy(answ[p],topA(ans));
          popA(ans);
          p++;

        }
        int s = p;
        p=0;
        ans =infixPre(answ,s);// finding the post fix of the reversed equation the reverses again

        printf("Equation No%d-> %s = ",k+1,a[k]);

        while(!isEmptyA(ans)){// Printing the answers stack contents

          strcpy(answ[p],topA(ans));
          printf("%s ",answ[p]);
          popA(ans);
          p++;

        }
     printf("\n\n");
        }
        }}


    }else if(x==4){//Evaluating the equation

      if(read==NULL){
        printf("Please read the file first");

        }else {
         for(int k=0;k<size;k++){
         if ((paraValid(a[k])==1)&&(signValid(a[k])==1)){//testing if valid
         stackA ans= reverse(a[k]);//reversing the equation and returning a stack

         char answ[100][100];
         int p=0;
         while(!isEmptyA(ans)){// a loop to insert the stacks contents into a multi dimensional array

              strcpy(answ[p],topA(ans));
              popA(ans);
              p++;

        }
        int s = p;
        p=0;
        ans =infixPre(answ,s);// finding the post fix of the reversed equation the reverses again which makes the prefix

        printf("Equation No%d Prefix->  ",k+1);

        while(!isEmptyA(ans)){//Placing the prefix into a multi dimensional array

          strcpy(answ[p],topA(ans));
          printf("%s ",answ[p]);
          popA(ans);
          p++;

        } s=p;

         double res=evaluate( answ, s );//Evaluating the prefix
         printf("\n  Result = %f\n",res);//printing the answer


        }
        }}




    }else if(x==5){
    if(read==NULL){//Testing validity case
    printf("Please read the file first");

    }else {


        for(int k=0 ;k<size;k++){// A loop which tests the validity of each equation

            printf("Equation No%d=",k+1);
            if ((paraValid(a[k])==0)||(signValid(a[k])==0))
                    printf("invalid");
                    else  printf("valid");

            printf("\n");
    }}


    }else if (x==6){//Printing into the file case

       if(read==NULL){
        printf("Please read the file first");

        }else{
            pp = fopen ("output.txt","w");//opening the file
            for(int k=0;k<size;k++){

                printf("\nEquation No.%d  ",k+1);
                fprintf(pp,"\nEquation No.%d  ",k+1);//printing the equation number to the file
                printf("\n  Equation: %s",a[k]);
                fprintf(pp,"\n  Equation: %s",a[k] );//printing the equation to the file

            if ((paraValid(a[k])==1)&&(signValid(a[k])==1)){//testing validity
                     stackA ans= reverse(a[k]);

                    char answ[100][100];
                    int p=0;
                    while(!isEmptyA(ans)){
                          strcpy(answ[p],topA(ans));
                          popA(ans);
                          p++;

                     }

                    int s = p;
                    p=0;
                    ans =infixPre(answ,s);// converting to prefix

                    printf("\n  valid");
                    fprintf(pp,"\n  valid ");//printing valid for valid equations to the file
                    printf("\n  Prefix: ");
                    fprintf(pp,"\n  Prefix: ");

                    while(!isEmptyA(ans)){

                      strcpy(answ[p],topA(ans));
                      printf("%s ",answ[p]);
                      fprintf(pp,"%s ",answ[p]);//Printing the prefix to the file
                      popA(ans);
                      p++;

                    } s=p;

                    double res=evaluate( answ, s );//evaluating the prefix
                    printf("\n  Result = %f\n",res);
                    fprintf(pp,"\n  Result = %f\n",res);// printing the evaluations result to the file



            }
             else {printf("\n  invalid\n");fprintf(pp,"\n  invalid\n");}//printing invalid for invalid equations to the file
            }fclose(pp);//closing the file

        }


    }else if(x==7){//Exit case
    break;

    }
    else {
        printf("Invalid input please enter again");

    }





}


fclose(f);
    return 0;
}

//All functions:


stack createEmpty(){//Creates an empty stack of characters

stack s;
s=(stack)(malloc(sizeof(struct node )));

if (s==NULL){
    printf("OUT OF SPACE");
}
s->next=NULL;
makeEmpty(s);
return s;

}

stackA createEmptyA(){//Creates an empty stack of strings

stackA s;
s=(stackA)(malloc(sizeof(struct nodeA )));

if (s==NULL){
    printf("OUT OF SPACE");
}
s->next=NULL;
makeEmptyA(s);
return s;

}

void makeEmpty(stack s){//Empties the stack of characters

 if (s==NULL){
    printf("OUT OF SPACE");
}
else{
while(isEmpty(s)!=1){

    printf("here");
        pop(s);
}
}}

void makeEmptyA(stackA s){//Empties the stack of strings

 if (s==NULL){
    printf("OUT OF SPACE");
}
else{
while(isEmptyA(s)!=1){

    printf("here");
        popA(s);
}

}
}

int isEmpty(stack s){//Checks if the stack of characters is empty

return s->next==NULL;

}

int isEmptyA(stackA s){//Checks if the stack of strings is empty

return s->next==NULL;

}

void pop(stack s){//deletes the first node of the stack of characters
arrow first=s->next;
if (isEmpty(s))
   printf("");
else {
    s->next =first->next;
    free(first);

}
}

void popA(stackA s){//deletes the first node of the stack of strings
arrowA first=s->next;
if (isEmptyA(s))
  printf("");
else {
    s->next =first->next;
    free(first);

}
}

char top(stack s){//gets the first node of the stack of characters


 if (isEmpty(s)){
    printf("");
    return 0;

 }else
    return s->next->element;

}

const char* topA(stackA s){//gets the first node of the stack of strings
//printf("here");
 if (isEmptyA(s)){
   printf("Stack is empty");
    return 0;

 }else
 // printf("here2");
  //printf("%s",s->next->element);
    return s->next->element;


}

void push (stack s , char x){//Adds a note to the stack of characters

arrow temp= (arrow )(malloc(sizeof(struct node )));
if (s==NULL){
    printf("OUT OF SPACE");
}else{
temp->element=x;
temp->next=s->next;
s->next=temp;

}


}

void pushA (stackA s , char a[100]){//Adds a note to the stack of characters

arrowA temp= (arrowA )(malloc(sizeof(struct nodeA )));
if (s==NULL){
    printf("OUT OF SPACE");
}else{
    //printf("%s",a);

strcpy(temp->element, a);
temp->next=s->next;
s->next=temp;

//printf("%s",s->next->element);
}


}

void DisposeStack( stack S ){//Deletes the stack of characters
makeEmpty( S );
 free( S );
}

 int paraValid(char a[1000]){//Checks if the parentheses are valid
     int k;
     stack test=createEmpty();//a stack to stack the parenthesis
     char e[1000]={};
     int i=0,j=0;

     while(i<strlen(a)){ // A loop that takes only the parenthesis and places them into an array

            if ((a[i]=='[')||(a[i]=='(')||(a[i]=='<')||(a[i]==')')||(a[i]==']')||(a[i]=='>')){
             e[j]=a[i];
             j++;

            }

            i++;

     }
    i=0;
    while (i<strlen(e)){// A loop that checks each element of the new array


    if   ((e[i]=='[')||(e[i]=='(')||(e[i]=='<')){// if its a opening parenthesis push into the stack

            push(test,e[i]);
           }

     else if ((e[i]==']')||(e[i]==')')||(e[i]=='>')){// if its a closing parenthesis push into the stack

            if ((match(top(test),e[i]))==0||isEmpty(test)){// if the top element doesn't match or the stack is empty return invalid

                    return 0;

            }else { // if it matches then pop the top element
               pop(test);

            }


     }

    i++;
    }


      if(isEmpty(test)){// if it was the array checked each element and the stack is empty then its valid
        return 1;
    }


   else {
     return 0;}// if the stack isnt empty after checking each element then its invalid

 }

 int match(char a ,char b){//Checks if the parentheses are match each other

       if((a=='[')&&(b==']')){
        return 1;

      }
        else if((a=='<')&&(b=='>')){
        return 1;

      }else if((a=='(')&&(b==')')){
        return 1;

      }else return 0;

 }

 int signValid(char a[1000]){//Checks if the signs are valid


     stack test=createEmpty();//A stack of characto test validity of the signs
     char e[1000]={};
     int counts =0,countnum=0;
     int div=0;
     int i=0,j=0;

     while(i<strlen(a)){//A loop to test each element of the equation

            if (isdigit(a[i])){// The number case
              if((top(test)==']')||(top(test)==')')||(top(test)=='>')){// if its number and the top element saved in the stack is a closing parenthesis then its invalid
                return 0;
              }else if(a[i]=='0'&&div==1&&!isdigit(a[i+1])){//Dividing by zero case
                return 0;
              }
                else {// if not push the digit into the stack
                push(test,a[i]);
                }
               countnum++;// counts if a digit was passed

            }else if (!isdigit(a[i])){// if its not a digit
                div=0;
                if(((a[i]=='[')||(a[i]=='(')||(a[i]=='<'))&&(isdigit(top(test)))){// if its a opening parenthesis and the top element saved in the stack is a number then its invalid
                        return 0;


                   }if(((a[i]=='[')||(a[i]=='(')||(a[i]=='<'))&&((top(test)==']')||(top(test)==')')||(top(test)=='>'))){// if its a opening parenthesis and the top element saved in the stack is a closing  parenthesis then its invalid

                        return 0;

                   }else if(((a[i]==']')||(a[i]==')')||(a[i]=='>'))&&isEmpty(test)){// if its a closing parenthesis and the stack is empty(an operator was the previous input) its invalid

                    return 0;

                   }else if((a[i]==']')||(a[i]==')')||(a[i]=='>')){//if its a closing parenthesis and none of the previous where achieved then add it to the stack

                    push(test,a[i]);

                   }else if (((a[i]=='*')||(a[i]=='+')||(a[i]=='/')||(a[i]=='^'))&&(isEmpty(test))){// if its an operator except for "-" and the stack is empty(an operator was the previous input) its invalid
                       return 0;

                   }else { // if its an operator and none of the previous where achieved then pop all elements of the stack
                          if (a[i]=='/'){
                            div=1;}


                          while(!isEmpty(test)){
                             pop(test);

                          }counts++;//counts when an operator exists

                   }

            }
            i++;

     }

    if (counts==0||countnum==0){// if an operator or a number doesn't exist in the equation then its invalid
        return 0;

    }else if (isEmpty(test)){// if the its empty(an operator was the last input) then its invalid
    return 0;

    } else//if none of the previous where achieved then its valid
      return 1;



 }

 void printStack(stack s){//prints the stack of characters
     char a[1000];
     char b[1000];

     int i=0,k=0;
    // printf("here");
     while(!isEmpty(s)){

        a[i]=top(s);
        pop(s);
        i++;

     }
     i=strlen(a)-1;

    while(i>=0){
       push(s, a[i]);
        i--;


    }
    i=strlen(a)-1;
    while (i>=0){

      b[k]=a[i];
      i--;
      k++;
    }
    printf("%s",b);

 }

stackA infixPre(char a[100][100], int ss){//Transforms the equation from infix to prefix
stack s = createEmpty();
stackA ans = createEmptyA();
int r=0;
char word[1000];

char w[100];

     for(int i=0;i<ss;i++){//

    if (strlen(a[i])>1){

          strcpy(w,a[i]);
          strcat(word,w);
          pushA(ans,w);




       } else if(strlen(a[i])==1&& isdigit(a[i][0])){

          strcpy(w,a[i]);
          strcat(word,w);
          pushA(ans,w);
       }
       else if (strlen(a[i])==1&&((a[i][0]=='-')||(a[i][0]=='+')||(a[i][0]=='*')||(a[i][0]=='/')||(a[i][0]=='^')))
		{
        strcpy(w," ");

		w[0]=' ';
		strcat(word,w);

			while ((!isEmpty(s))&& (top(s)!=')') && ((compare(top(s),(a[i][0])))==1))
			{

				  strcpy(w," ");
		           w[0]=top(s);
                 strcat(word,w);
                 pushA(ans,w);

				pop(s);
			}

			push(s,a[i][0]);


		}else if(a[i][0]==')'||a[i][0]==']'||a[i][0]=='>'){

		     push(s,')');


		}
		else if (a[i][0] == '('||a[i][0] == '['||a[i][0] == '<')

		{
			while ((!isEmpty(s)) && (top(s) != ')')) {

				  strcpy(w," ");
		         w[0]=top(s);
               strcat(word,w);
               pushA(ans,w);
				pop(s);

				if (top(s) == ')')
                    break;
			}


			pop(s);

		}

     }
     while (!isEmpty(s)) {

		  strcpy(w," ");
		  w[0]=top(s);

         strcat(word,w);
         pushA(ans,w);
		pop(s);



	}

	return ans;
    }

int compare(char a, char b){//compares the priorities of the signs
int x,y;
if (a==b)
    return 0;
//giving each operator a different value to compare
if (a=='+'){
    x=0;
}else if (a=='-'){
    x=0;
}else if (a=='*'){
    x=2;
}else if (a=='/'){
    x=2;
}else if (a=='^'){
    x=3;
}

if (b=='+'){
    y=0;
}else if (b=='-'){
    y=0;
}else if (b=='*'){
    y=2;
}else if (b=='/'){
    y=2;
}else if (a=='^'){
    x=3;
}

if (x>y)
    return 1;
else if (x<y)
    return -1;
 else return 0;



}

int getSize(stack s){//gets the size of the stack of characters
    char a[1000];
    char b[1000];

     int i=0,k=0;
     while(!isEmpty(s)){//pops all elements places them into an array

        a[i]=top(s);
        pop(s);
        i++;

     }

     i=strlen(a)-1;

    while(i>=0){//Returns all the arrays elements into the stack
       push(s, a[i]);
        i--;


    }
    i=strlen(a)-1;


 return(strlen(a));// returns the number of elements



}

 stackA reverse(char a[1000]){//seperates the equations numbers from signs and puts them into a stack

stackA ans =createEmptyA();// A stack to stack the answer into

int i=0;char num[100];

while(i<strlen(a)){

    int j=0;int x=0;
    strcpy(num, "l");

    if (i==0&&a[i]=='-'){// the equation starts with negative case
        num[j]=a[i];
        i++;
        j++;

    }else if (a[i]=='-'&&!isdigit(a[i-1])&&a[i-1]!=')'&&a[i-1]!='>'&&a[i-1]!=']'){//a number is negative case

        num[j]=a[i];
        i++;
        j++;

    }else if (!isdigit(a[i])){//A sign case
        num[j]=a[i];
    }

    while(isdigit(a[i])){//A loop that keeps reading numbers until it reaches a sign

        num[j]=a[i];
        j++;
        i++;
        x=1;

    }
     if (x==1){

        i--;
         }

      i++;

    pushA(ans,num);// Add the elements which was just read to the stack

}

return ans;
}

double evaluate(char a[][100],int size ){//Evaluates the given prefix
     double c;
     char *en;
     int d=1;

     stackA calc= createEmptyA();//creating a stack for the evaluation process

for(int i=size-1; i>=0;i-- ){//A loop to get every number of the prefix

    if (strlen(a[i])>1){// if its a number (its length is bigger than 1) push in the stack

          pushA(calc,a[i]);


       } else if(strlen(a[i])==1&& isdigit(a[i][0])){// if its a number ( length is 1) push in the stack

          pushA(calc,a[i]);
       }

       else if(!isEmptyA(calc)) {// if its a sign
       //Pop the last two and perform the operation then push the answer back into the stack

        double d1= strtod(topA(calc),&en);
        popA(calc);

        double d2=strtod(topA(calc),&en);
        popA(calc);

        //conditions for each of the operations
        if ((a[i][0]=='-')){
            c=d1-d2;
        }else if ((a[i][0]=='*')){
            c=d1*d2;
        }else if ((a[i][0]=='+')){
            c=d1+d2;
        }else if ((a[i][0]=='/')){
             d=(int)d2;
              if (d==0)
               break;
            c=((double)d1)/((double)d2);

        }else if ((a[i][0]=='^')){
            c=pow(d1,d2);
        }

        char snum[100];

        sprintf(snum, "%f", c);//coverting the answer to a string
         pushA(calc,snum);

       }




}
  if (d==0){
    printf("invalid operation ");
  }else {
  double  res= strtod(topA(calc),&en);// converting the string to a double

  return res;}

 }













