/*
    TO-DO
    2) get_str
    3) change
    5) find

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct person{
    int id;
    char *name;
    char *telephone_number;
};
typedef struct person person; // now we don't use struct everywhere

struct database{
    int size;
    person *records;
};
typedef struct database database;

database telephone_book;
const char *file_name;
int global_id = 0;

int find_substr(char *a, char *b);
void change();
void create(FILE * file, int num);
void delete(int id);
void find();
void rewrite_file();
char *get_str(FILE * file, int type);


void change(){
  return;
}


void find(){
  return;
}


char *get_str(FILE * file, int type){
  return NULL;
}


void rewrite_file(){
    FILE * input_file = fopen(file_name, "a+");
    int i = 0;
    for(i = 0; i < telephone_book.size; i++)
        if(telephone_book.records[i].id != 0){
          fprintf(input_file, "%d %s %s\n", telephone_book.records[i].id, telephone_book.records[i].name, telephone_book.records[i].telephone_number);
        }
    fclose(input_file);
}


int find_substr(char *a, char *b){
    char *cur = malloc(strlen(a) * sizeof(char));
    int i = 0;
    while(a[i] != '\0'){
      cur[i] = tolower(a[i]);
      i++;
    }
    cur[i] = '\0';
    char *cur1 = malloc(strlen(b) * sizeof(char));
    i = 0;
    while(b[i] != '\0'){
      cur1[i] = tolower(b[i]);
      i++;
    }
    cur1[i] = '\0';
    int ans = (strstr(a, b) != NULL);
    free(cur);
    free(cur1);
    return ans;
}


void delete(int id){
    int cur_id = -1;
    int i = 0;
    for(i = 0; i < telephone_book.size; i++)
        if(telephone_book.records[i].id == id){
            cur_id = i;
            break;
        }
    if(cur_id == -1)
        return;
    else{
        telephone_book.records[cur_id].id = 0;
        rewrite_file();
    }
}


void create(FILE * file, int num){
  char *name = get_str(file, 0);
  char *number = get_str(file, 1);
  if(name != NULL && number != NULL){
      telephone_book.size++;
      int sz = telephone_book.size - 1;
      telephone_book.records = (person *) realloc(telephone_book.records,(telephone_book.size) * sizeof(person));
      telephone_book.records[sz].id = num;
      telephone_book.records[sz].name = name;
      telephone_book.records[sz].telephone_number = number;
      if(num > global_id){
        global_id = num;
      }
      rewrite_file();
  }
  else{
    printf("Error loading %d %s %s", num, name, number);
    free(name);
    free(number);
  }
}


int main (int argc, const char *argv[])
{

  char command[20];

  // work with file
  file_name = argv[1];
  FILE * input_file = fopen(file_name, "a+");
  if(input_file == NULL){
    printf("Error: can't open this file\n");
    return EXIT_SUCCESS;
  }
  rewind(input_file); // put pointer in the start

  // read the database from file
  telephone_book.size = 0;
  telephone_book.records = malloc(sizeof(person) * telephone_book.size);
  int cur_id = 0;
  while(fscanf(input_file, "%d", &cur_id) > 0){
     create(input_file, cur_id);
  }

  fclose(input_file);

  cur_id = 0;
  //read commands form user
  while(1){
    scanf("%s", command);
    if(!strcmp(command, "find")){
      find();
    }
    else if(!strcmp(command, "create")){
      create(stdin, global_id + 1);
    }
    else if(!strcmp(command, "delete")){
      scanf("%d", &cur_id);
      delete(cur_id);
    }
    else if(!strcmp(command, "change")){
      change();
    }
    else if(!strcmp(command, "exit")){
      free(telephone_book.records);
      return EXIT_SUCCESS;
    }
    else{
      printf("Error: can't recognize the command %s", command);
    }
    fflush(stdout);
  }
}
