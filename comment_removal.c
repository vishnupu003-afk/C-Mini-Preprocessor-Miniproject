#include<stdio.h>
//--------------------------------SINGLELINE COMMENT REMOVAL---------------------------
void singleLineCommentRemoval(FILE * src, FILE * dest)
{
    int ch, nextChar, currentChar;
    int stringFlag = 0, charFlag = 0;// this flags checks whether you are inside string or flag

    while ((ch = fgetc(src))!=EOF) {
        if (ch == '\'' && !stringFlag)   // if you found '  and not inside string literal 
            charFlag = !charFlag;
        if (ch == '\"' && !charFlag)     // if you found "  and not inside char   literal
            stringFlag = !stringFlag;
        if (!stringFlag && !charFlag) {
            nextChar = fgetc(src);
            if (ch == '/' && nextChar == '/')  //checks whether the current and next character both are /
            {
                fseek(src, -2, SEEK_CUR);      // go back 2 step to print spaces from there onwards
                while ((currentChar = fgetc(src)) != EOF) 
                {
                    if (currentChar == '\n')  // if the current char is newline we need to preserve the newline
                    {
                        fputc('\n', dest);
                        break;
                    }
                    fputc(' ', dest);    // if newline is not found as a current character put <spaces>
                }
                continue;  // if the <spaces> or newline pasted then continue to next iteration means , top while loop
            } 
            else       //  if the ch and next character both are not / 
            {
                fputc(ch, dest);    // then print the character
                if (nextChar != EOF) // if next character is not EOF  if ch only / 
                    fseek(src, -1, SEEK_CUR);  // go back one step
                continue; // continue to top
            }
        }
        fputc(ch, dest); // put the characters
    }
}

//--------------------------------MULTILINE COMMENT REMOVAL-----------------------------

void multiLineCommentRemoval(FILE*src,FILE *dest)
{
    int ch,nextChar,currentChar,prevChar;  // this stores the characters such as ch for checking ,current , previous and next character
    int stringFlag=0,charFlag=0,commentClosed; // flags checks such as we are inside the string , character and whether the comment is properly closed or not
    while ((ch = fgetc(src))!=EOF) 
    {
        if (ch == '\'' && !stringFlag)   // if you found '  and not inside string literal
            charFlag = !charFlag;
        if (ch == '\"' && !charFlag)     // if you found "  and not inside char   literal
            stringFlag = !stringFlag;
        if (!stringFlag && !charFlag) 
        {
            nextChar=fgetc(src);
            if(ch=='/' && nextChar=='*') //checks whether the current character is / and next character is *
            {
                fputc(' ',dest); // put <space> in the place of /
                fputc(' ',dest); // put <space> in the place of *
                commentClosed=0; // initialize the flag with 0  , means the comment started
                prevChar=fgetc(src); // read previous charcter
                while((prevChar)!=EOF) // check that is EOF , if it is then stop the process
                {
                    currentChar=fgetc(src);  // next read the current character 
                    if(prevChar=='*' && currentChar=='/')  // check the previous character is * and next character is / , because this is where comment stops 
                    {
                        fputc(' ',dest); // put <space> in the place of * 
                        fputc(' ',dest); // put <space> in the place of /
                        commentClosed=1; // set the comment flag , to say that the comment is closed properly
                        break; // break the <space> adding loop for the comment
                    }
                    // if the prevchar and currentchar is not * and / , then it comes to the next line
                    fputc(prevChar=='\n'?'\n':' ',dest); // checks the prevchar is '\n' then put '\n' or else <space>
                    prevChar=currentChar; // write the currentChar to prevChar because we are not sure that current character is EOF
                }
                if(!commentClosed) // if the comment is not properly closed , give the message and terminate
                {
                    printf("Error : Unterminated multiline comment");
                    return;
                }
                continue; // this continue is for the top while to send for next characters check
            }
            else // if any one of the character is not * or / then do else part
            {
                fputc(ch, dest); // put the character but if next character is not * then go back 1 step then go to next iteration 
                if (nextChar != EOF)
                    fseek(src, -1, SEEK_CUR); 
                continue;
            }
        }
        fputc(ch,dest);
    }
}


void commentRemoval(FILE *src,FILE *dest)
{
    FILE *temp=fopen("temp.i","w");
    singleLineCommentRemoval(src,temp);
    fclose(temp);
    temp=fopen("temp.i","r");
    multiLineCommentRemoval(temp,dest);
    fclose(temp);
}
