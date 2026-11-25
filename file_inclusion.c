#include<stdio.h>
#include<string.h>
#include"fileoperation.h"

void fileInclusion(FILE *src,FILE *dest)
{
    char line[100],header[20];//
    FILE *headp,*cleanHead;// here FILE pointer *headp: used for handling headerFile   *cleanHead: is a temporary File pointer is used to remove any comment present
    int i,ch;
    while(fgets(line,sizeof(line),src))
    {
        char *headerptr=line+strspn(line," \t");// here we will skip the spaces or tabs and move headerptr to the first character

        // CHANGE: Check whether the directive is actually #include
        if(strncmp(headerptr,"#include",8)!=0)//check whether from the first char #include is not there
        {
            fputs(line,dest);// simply paste the line content in the destination
        }
        else // if #include is present
        {
            headerptr+=strlen("#include");// jump the headerpointer after #include

            //Skip spaces and tabs between #include and filename
            while(*headerptr==' ' || *headerptr=='\t')
                headerptr++;

            if(*headerptr!='"' && *headerptr!='<') // after the #include " and < not there 
            {
                fputs(line,dest);// then just simply paste content of the lines
            }
            else
            {
                if(*headerptr=='"')// if headerptr found "
                {
                    headerptr++;// go to next character
                    i=0;// for string index
                    while(*headerptr!='"' && *headerptr!='\0' && *headerptr!='\n' && i<19)// store until headerptr reaches " , \0 ,\n , and the array limit
                        header[i++]=*headerptr++;// storing the character
                    header[i]='\0';

                    if(*headerptr!='"') // when the headptr moves forward its not finding the " then it is a syntax error
                    {
                        printf("Invalid include syntax\n");
                        fputs(line,dest); // then just simply paste content of the lines
                        continue; // continue to next line
                    }

                    headp=fopen(header,"r"); // open the fileName present inside the header array in read mode 
                    if(headp==0)// if it fail to open just alert and paste the line array content into the destination
                    {
                        printf("%s is not present...\n",header);
                        fputs(line,dest); // then just simply paste content of the lines
                        continue; // continue to next line
                    }

                    cleanHead=fopen("header_temp.i","w"); // cleanHead is used to clean the comment in headerFile
                    if(cleanHead==0)// if it is not opening the temporary file
                    {
                        printf("Unable to open temporary header file\n");
                        fclose(headp);// close the headerFile
                        fputs(line,dest); // then just simply paste content of the lines
                        continue; // continue to next line
                    }

                    commentRemoval(headp, cleanHead); // comment removal of headerFile

                    fclose(headp); // close the headerFile
                    fclose(cleanHead);// close the cleaned temporary headerFile

                    cleanHead=fopen("header_temp.i","r"); // reopen the cleaned HeaderFile in read mode

                    if (cleanHead==0)// if it is not opening the cleaned HeaderFile 
                    {
                        printf("Unable to reopen temporary header file\n");
                        remove("header_temp.i");// delete the temporary cleaned headerFile
                        fputs(line,dest); // then just simply paste content of the lines
                        continue; // continue to next line
                    }

                    while((ch=fgetc(cleanHead))!=EOF)// copy the each characters of the cleaned headerFile to destination
                        fputc(ch,dest);// copy character by character to destination from cleaned headerFile
                    fclose(cleanHead);// close the cleaned temporary headerFile
                    remove("header_temp.i");//delete the temporary cleaned headerFile
                }

                else if(*headerptr=='<')// if it is < after "#include "
                {
                    fputs(line,dest);// then just simply paste content of the lines
                }
            }
        }
    }
}

