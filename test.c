#include<stdio.h>
int main(){
    FILE* fp = NULL;
	fp = fopen("./tst.txt", "r"); if (fp == NULL)
	{
		printf("0");
		exit(0);
	}
	char line[100]; long long id = 0; char name[100];
	//fscanf(fp,"%*[^\n]%*c",line); while(!feof(fp))
	{
		fscanf(fp, "%lld",                                  &id); 
        //fgetc(fp);
		fgets(name, 100, fp);
		printf("%s\n", name);
		name[strlen(name) - 1] = '\0'; 
    }
    fclose(fp);  
}