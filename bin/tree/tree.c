#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
void tree(const char *route, int level);

void tree(const char *route, int level)
{
    DIR *dir;
    struct dirent *input;
    struct stat info;
   
    dir = opendir(route);
    if(dir == NULL)
    {
        return;
    }
    while ((input = readdir(dir)) != NULL) 
    {
        if (strcmp(input->d_name, ".") == 0) continue;
        if (strcmp(input->d_name, "..") == 0) continue;

        char whole_route[1024];
        snprintf(whole_route, sizeof(whole_route), "%s/%s", route, input->d_name);
        lstat(whole_route, &info);

        for( int i = 0; i < level; i++ )
        {
            printf("   ");
        }
        printf("--- %s", input->d_name);
        if(S_ISLNK(info.st_mode))
        {
            printf("--- %s@\n", input->d_name);    
        }
        else if(S_ISDIR(info.st_mode))
        {
            printf("/\n");
            tree(whole_route, level + 1);
        }
        else
        {
             printf("\n");
        }
     }
   closedir(dir);
}

int main(int argc, char *argv[])
{
   const char *route = ".";
   if(argc > 1)
   {
      route = argv[1];
   }
   printf("%s\n", route);
   tree(route, 0);
   return 0;
}
