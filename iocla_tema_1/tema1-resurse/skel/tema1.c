#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

void reverseString(char *s,int length)
{
	int start = 0;
	int end = length - 1;
	char temp;

	while(start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		start++;
		end--;
	}
}

char *myItoa(int n,char *s,int base)
{
	int i = 0;
	int is_negative = 0;

	//0 case
	if(n == 0)
	{
		s[i++] = '0';
		s[i] = '\0';
		return s;
	}

	//check if negative
	if(n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	
	//process each digit
	while (n != 0) 
    { 
        int rem = n % base; 
        s[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        n = n / base; 
    } 
   
   	//add '-'
	if(is_negative == 1)
		s[i++] = '-';

	s[i] = '\0';
	//reverse string
	reverseString(s,i);

	return s;
}

int iocla_printf(const char *format, ...)
{
	/* TODO */
	FILE *out = fopen("printf","wt");
	va_list args;
	va_start(args,format);
	int i;
	int d;
	unsigned int u;
	char c;
	char *s = calloc(strlen(format),sizeof(char));//used to print strings
	char *s_1 = calloc(strlen(format),sizeof(char));//used to print numbers
	int characters_printed = 0;

	for(i = 0; format[i] != '\0'; i++)
	{
		//check for '%' and find out the specifer
		if(format[i] == '%')
		{
			if(format[i+1] == 'd')
			{
				d = va_arg(args,int);
				write_stdout(myItoa(d,s_1,10),strlen(myItoa(d,s_1,10)));
				characters_printed += strlen(myItoa(d,s_1,10));
			}

			if(format[i+1] == 'u')
			{
				u = va_arg(args,unsigned int);
				write_stdout(myItoa(u,s_1,10),strlen(myItoa(u,s_1,10)));
				characters_printed += strlen(myItoa(u,s_1,10));
			}

			if(format[i+1] == 'x')
			{
				u = va_arg(args,unsigned int);
				write_stdout(myItoa(u,s_1,16),strlen(myItoa(u,s_1,16)));
				characters_printed += strlen(myItoa(u,s_1,16));
			}

			if(format[i+1] == 'c')
			{
				c = (char)va_arg(args,int);
				write_stdout(&c,1);
				characters_printed++;
			}

			if(format[i+1] == 's')
			{
				s = va_arg(args,char *);
				fprintf(out, "%s\n",s);
				write_stdout(s,strlen(s));
				characters_printed += strlen(s);
				//s = NULL;
			}

			if(format[i+1] == '%')
			{
				char percent = '%';
				write_stdout(&percent,1);
				characters_printed++;
			}

			i = i + 2;
		}
		write_stdout(&format[i],1);
		characters_printed++;
	}

	va_end(args);
	//free(s);
	free(s_1);
	return characters_printed;
}


int main()
{
	iocla_printf("%s","ceva");
	return 0;
}
