#include<stdio.h>
#include<string.h>
char a[73][20]={"A",".-","B","-...","C","-.-.","D","-..",
"E",".","F","..-.","G","--.","H","....","I","..","J",".---",
"K","-.-","L",".-..","M","--","N","-.","O","---","P",".--.",
"Q","--.-","R",".-.","S","...","T","-","U","..-","V","...-",
"W",".--","X","-..-","Y","-.--","Z","--..","1",".----","2",
"..---","3","...--","4","....-","5",".....","6","-....","7",
"--...","8","---..","9","----.","0","-----"};

int main()
{
	char c;
	c=getch();
	if(c=='1')
	{
		int i,j,d=0;
		char t[50],s[50],*p=t,f;
		while(1)
		{
			
			scanf("%s",s);
			f=getchar();
				
			
			for(j=0;j<strlen(s);j++)
			for(i=0;i<71;i++)
			{
				if(s[j]==a[i][0])
				{
					strcpy(p,a[i+1]);
					while(*p!='\0')p++;
					*p=' ';
					p++;
					break;
				}
			}
			if(f=='\n')
			{
				*p='\0';
				printf("%s\n",t);
				p=t;
			}
		}
	}
	else if(c=='2')
	{
		int i,j;
		char t[50],s[50],*p=t,f;
		while(1)
		{
			scanf("%s",s);
			f=getchar();

				for(i=0;i<72;i++)
				{
					if(strcmp(s,a[i])==0)
					{
						strcpy(p,a[i-1]);
						while(*p!='\0')p++;
						*p=' ';
						p++;
						break;
					}
				}
			
			if(f=='\n')
			{
				*p='\0';
				printf("%s\n",t);
				p=t;
			}
		}
	}
} 
