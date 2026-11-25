#include<stdio.h>
#include<ctype.h>//for isalnum() function
#include<string.h>
typedef struct 
{
    char macroName[50];// macro Name member 
    char macroValue[100];// macro Value member
}MACRO;

//-----------------------------------MATCHED MACRO VALIDATOR--------------------------------------------------------------------

int macroCheck(char *nameAdd,char *line,int len)
{
    if(nameAdd>line && (isalnum((unsigned char)nameAdd[-1]) || nameAdd[-1]=='_'))// to check the macro is after thre beginning and the previous character is a alphanumeric or '_'
        return 0;

    if(isalnum((unsigned char)nameAdd[len]) || nameAdd[len]=='_')// if the last character is a alphanumeric or it is an '_'
        return 0;

    return 1;// otherwise its not a MACRO 
}

//------------------------------------Recursive macro replacement function-------------------------------------------------------

void recursiveReplacement(char *line,FILE *dest,MACRO table[],int index,int depth)
{
    char *macro,*nameAdd;// pointers for 
    int k,macrolength;
    int stringFlag=0,charFlag=0;// Flags to check whether we are inside the string or character literals

    if(depth>20) 
    {
        fputs(line,dest);
        return;
    }

    macro=line;

    while(*macro!='\0')
    {
        if(*macro=='"' && !charFlag) // if we found " and consider we are not inside character literal 
            stringFlag=!stringFlag; // toggle the string flag saying we are inside the string literal
        else if(*macro=='\'' && !stringFlag) // if we found ' and consider we are not inside string literal
            charFlag=!charFlag; // toggle the character flag saying we are inside the character literal

        if(stringFlag || charFlag) // if we are inside any literals we are just simply pasting the lines inside destination
        {
            fputc(*macro++,dest); // character by character will paste inside destination
            continue;
        }

        for(k=0;k<index;k++) // index have the count of no.of elements in structure array
        {
            // Search from current position
            nameAdd=strstr(macro,table[k].macroName);// nameAdd pointer get the address of first occurence in the string address

            while(nameAdd!=NULL &&/*TRUE TILL MACRO MATCH*/
                  !macroCheck(nameAdd,line,strlen(table[k].macroName))) // Compare with original line
            {
                nameAdd=strstr(nameAdd+1,table[k].macroName);// then nameAdd pointer will move forward at the address of substring
            }

            if(nameAdd==macro)// check macro is at current position
            {
                macrolength=strlen(table[k].macroName);// length of macro

                // Recursively expand the macro value
                recursiveReplacement(table[k].macroValue,dest,table,index,depth+1);

                macro+=macrolength;// after replacement pointer shift forward according macrolength
                break;
            }
        }

        if(k==index)
            fputc(*macro++,dest);// put the character to destination
    }
}

void macroReplacement(FILE *src, FILE *dest)
{
    char line[200];
    char name[50];
    char value[100],*nameAdd;
    MACRO table[50];
    int i,j,index=0,k,macrolength,found;
    int stringFlag,charFlag; // The given flags will check whether we are in string and character literals if we are in protect the macro 

    while(fgets(line,sizeof(line),src))// takes line by line store into "line array"
    {
        char *macro=line+strspn(line," \t");// NOTE : strspn is used to count the beggining spaces and tabs , set the pointer after that

        if(strncmp(macro,"#define",7)==0 && (macro[7]==' ' || macro[7]=='\t')) // here here we check #define is present or not and ( next character should be ' ' or tab)
        {
            i=0;// this is used for macro name  indexing
            j=0;// this is used for macro value indexing

            macro+=strlen("#define "); // shifting the pointer after the "#define " to get macro value
            while(*macro==' ' || *macro=='\t') // this is used to shift the pointer until we see first character
                macro++;

            while(*macro!=' ' && *macro!='\t' && *macro!='\0' && *macro!='\n' && i<49)// this used to take all the macroName until it reaches first space,tab,\0,newline and array limit
                name[i++]=*macro++;
            name[i]='\0';

            while(*macro==' ' || *macro=='\t')// this used to shift the pointer until we reach the first character
                macro++;

            while(*macro!='\0' && *macro!='\n' && j<99)// this used to take all the macroValue until it reaches first \0,newline and array limit
                value[j++]=*macro++;
            value[j]='\0';

            if(index<50)// check only upto limit of structure array
            {
                strcpy(table[index].macroName,name);// copy macroName from variable to macroName member
                strcpy(table[index].macroValue,value);// copy macroValue from variable to macroValue member
                index++;
            }
        }

        else if(*macro=='#')// other than #define comes it will do simply pasting the lines to destination
            fputs(line,dest);

        else
        {
            recursiveReplacement(line,dest,table,index,0); // this is used to replace the macroName with macroValue
        }
    }
}

