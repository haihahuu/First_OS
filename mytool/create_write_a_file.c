#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static const struct option longopts[] =
{
        {"file1", required_argument, NULL, 'f'},
        {"file2", required_argument, NULL, 'g'},
        {"start1", required_argument, NULL, 's'},
        {"end1", required_argument, NULL, 'e'},
        {"start2", required_argument, NULL, 'd'},
        {"end2", required_argument, NULL, 'r'}
};
static void open1(void);
static void open2(void);
static void close1(void);
static void close2(void);

int main(int argc, char* argv[])
{
        int optc;
	const char* file1 = NULL;
	const char* file2 = NULL;
	const char* start1 = NULL;
	const char* start2 = NULL;
	const char* end1 = NULL;
	const char* end2 = NULL;
    
        while((optc = getopt_long(argc, argv, "f:g:s:e:d:r:", longopts, NULL)) != -1)
		{
	       		switch (optc)
                	{
                        case 'f':
                                file1 = optarg;
                                break;
                        case 'g' :
				file2 = optarg;
                                break;
                        case 's':
				start1 = optarg;
				break;
                        case 'e':
				end1 = optarg;
				break;
                        case 'd':
				start2 = optarg;
				break;
                        case 'r':
				end2 = optarg;
                                break;
			}
		}
	printf ("%s\n%s\n%s\n%s\n%s\n%s\n",file1,file2,start1,start2,end1,end2);
	int start1_int = atoi(start1);
	int start2_int = atoi(start2);
	int end1_int = atoi(end1);
	int end2_int = atoi(end2);
	int number_of_byte_to_tranfer = end1_int - start1_int;
	int number_to_check = end2_int - start2_int;
	if (number_of_byte_to_tranfer != number_to_check)
	{
		printf ("number of file not equal");
		return 0;
	}
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen(file1,"rb");
	fp2 = fopen (file2,"r+b");
	fseek (fp1, start1_int, SEEK_SET);
	fseek (fp2, start2_int, SEEK_SET);
	char buffer[1048576]; //max 1 mb
       	fread(buffer,number_of_byte_to_tranfer,1,fp1);
	fwrite(buffer,number_of_byte_to_tranfer,1,fp2);
	fclose(fp1);
	fclose(fp2);	
	return 1;
}
