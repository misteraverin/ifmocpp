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

int  find_substr(char *a, char *b);
int  is_good(char c, int type);
void change();
void create(FILE * file, int num);
void delete(int id);
void find();
void rewrite_file();
char *get_str(FILE * file, int type);


void change(){
  int num;
  int type_oper;
  char command[30];
  char * cur_str;
  scanf("%d %s", &num, command);
  if(!strcmp(command, "number"))
    type_oper = 1;
  else
    type_oper = 0;
  cur_str = get_str(stdin, type_oper);
  if(cur_str != NULL){
    int cur_id = -1;
    int i = 0;
    for(i = 0; i < telephone_book.size; i++)
        if(telephone_book.records[i].id == num){
            cur_id = i;
            break;
        }
    if(cur_id == -1){
      printf("Error: wrong id\n");
      free(cur_str);
    }
    else{
        if(type_oper == 1)
          telephone_book.records[cur_id].telephone_number = cur_str;
        else
          telephone_book.records[cur_id].name = cur_str;
    }
    rewrite_file();
  }
  else{
    printf("Error: wrong command\n");
    free(cur_str);
  }
  return;
}


void find(){
  char *query = get_str(stdin, 2);
  if(query != NULL){
    int flag = 0;
    int i = 0;
    for(i = 0; i < telephone_book.size; i++){
      int expr =  (isdigit(query[0]) && strcmp(telephone_book.records[i].telephone_number, query) == 0);
      int expr1 = (isalpha(query[0]) && find_substr(telephone_book.records[i].name, query));
      if(expr || expr1){
        flag = 1;
        printf("%d %s %s\n", telephone_book.records[i].id, telephone_book.records[i].name, telephone_book.records[i].telephone_number);
      }
    }
    if(!flag)
     printf("Error: can't find this contact\n");
  }
  else{
   printf("Error\n");
  }
  free(query);
  return;
}


int is_good(char c, int type) {
  int mas[3];
  mas[0] = isalpha(c);
  mas[1] = isdigit(c);
  mas[2] = isalnum(c);
  return mas[type];
}

char *get_str(FILE * file, int type){
    // 0 - name, 1 - number, 2 - mixed string
    char *right_string = NULL;
    int bad = 0;
    int len = 0;
    int size = 0;
    char symb = fgetc(file);
    while(symb != EOF){
        if(symb == ' '){
            if(type == 2){
                if(isalpha(symb))
                  type = 0;
                else
                  type = 1;
            }
            if(is_good(symb, type)){
                if( (len + 1) == size){
                    size = size * 2;
                    right_string = realloc(right_string, sizeof(char) * size);
                }
                right_string[len++] = symb;
                right_string[len] = '\0';

            }
            else if((symb == '+' && len > 0) ||
                    (type == 0) || type != 0 && symb != '(' && symb != ')' && symb != '-' && symb != '+'){
                bad = 1;
            }
        }
        else if(len > 0)
          break;
        symb = fgetc(file);
    }
    if(bad){
        free(right_string);
        right_string = NULL;
        printf("Error: wrong string\n");
    }
    return right_string;
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
    printf("Error loading %d %s %s\n", num, name, number);
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
      printf("Error: can't recognize the command %s\n", command);
    }
    fflush(stdout);
  }
}
