//Given any filename as input, split based on sizes of each and split based on lines for each.  
//i.e ./split -s 1K -> split into 1K units. ./split -n 1000 -> thousand lines each.  

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long parse(char* count )
{

long val = 1;
if ( count[strlen(count) - 1 ] == 75 ||  count[strlen(count) - 1 ] == 107 )   //K or k prefix
  {
    count[strlen(count) - 1  ] = 0;        //set prefix element to be null so value isn't affected
    val = 1000;
  }
else if ( count[strlen(count) - 1 ] == 77 ||  count[strlen(count) - 1 ] == 109)   //M or m prefix
   {
    count[strlen(count) - 1  ] = 0;
    val = 1000 * 1000;
  }
else
  {
    if( count[strlen(count) - 1] < 48 || count[strlen(count) - 1] > 57)    //Not a Number or K or M
   { printf("Unknown Prefix");
    return 0;
   }
 }
return val * atoi(count);
 }// Function used for size prefixes like  K(Kilo) and M(Mega)


void split_by_lines( char* file , int num)
{
 FILE *instream , *outstream ;
 instream = fopen(file , "r");
 int fno = 0;       //file number
 char filename[30];
 char temp[100];     //line string
 if (instream == NULL)
 {
	 printf("Unable to Open File");
	 return;
 }
 while( !feof(instream) )         // Go through the file
  {
   sprintf(filename , "split_by_lines_%d.txt" , fno++);
   outstream = fopen( filename , "w");
   for (int i = 0 ; i < num ; i++)
   {
     fgets(temp , 100 , instream);        // Copy line by line to to the new file while limiting the number of lines 
     fputs(temp , outstream);
    if( feof(instream) )
	break;
   }
 fclose(outstream);
 }
fclose(instream);
printf("File split by lines successfully!");
} // Function used to split the source file by number of lines



void split_by_size(char* file , int size)
{

 FILE *instream , *outstream;
 instream = fopen(file , "r");
 int fno = 0;        //file number
 char filename[30];
 char temp;          
 if (instream == NULL)
 {
	 printf("Unable to Open File");
	 return;
 }
 while( !feof(instream) )           // Go through the file 
 {
  sprintf(filename , "split_by_size_%d.txt" , fno++);  
  outstream = fopen( filename , "w" );
  int currsize = 0;       //Newly generated file size initialized to zero
  while( currsize < size ) 
  {
    temp =  fgetc(instream);   //copy char by char wile keeping track of size
    fputc(temp , outstream);
    currsize++;
    if( feof(instream) )
       break;
  }
  fclose(outstream);
 }
fclose(instream);
printf("File split by size successfully!");
}// Function used to split the source file by size


int main(int argc , char* argv[])
{
  if(argc == 4)
   {
    if( strcmp(argv[2], "N") == 0|| strcmp(argv[2], "n") == 0)
       {
       int num = atoi(argv[3]);      //string to number of lines
        split_by_lines( argv[1] , num );
          }
    else if (  strcmp(argv[2], "S") == 0 || strcmp(argv[2], "s") == 0 )
	{
        int size = parse(argv[3]);        // string to size while supporting prefixes
         if(size)
           split_by_size( argv[1] , size );
        }
    else
     printf("Invalid Mode");    //Use N or S
  }
  else
   printf("Arguments size invalid");  //<filename> <mode> <size/number>
}

