#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

/*
https://www.techiedelight.com/trie-implementation-insert-search-delete/

https://www.youtube.com/watch?v=-urNrIAQnNo

tests:

  //insert, search, delete from and print, free entire trie:
  insert(root, "car");
  insert(root, "done");
  insert(root, "try");
  insert(root, "cat");
  insert(root, "trie");
  insert(root, "do");
  search(root, "ca");
  search(root, "zebra");
  search(root, "try");
  search(root, "card");

  print_entire_trie(root);

  //delete(root, "do");
  //delete(root, "trie");
  //delete(root, "ca");

  //print_entire_trie(root);
  free_trie(root);

*/

#define CHAR_SIZE 5

struct node{
  bool isWord;
  bool isRead;
  struct node *child[CHAR_SIZE];
};

typedef struct node trie;

//test5
int lookup_char(char p1);
char lookup_int(int p1);

trie* createTrieNode();
bool insert(trie *head, char* str);
bool search(trie *head, char *str);
void print_entire_trie_manager(trie *head);
char* print_entire_trie(trie *head, char[], int);
void reset_isRead_key(trie *head);
bool isNull(trie *head);
trie* delete(trie *head, char *str);
void free_trie(trie *head);

int main(int argc, char *argv[]){
  trie *root=createTrieNode();
  if(root==NULL){
      return 1;
  }
  //insert
  insert(root, "er");
  insert(root, "pear");
  insert(root, "pears");
  insert(root, "rapper");
  insert(root, "rape");
  insert(root, "rap");
  insert(root, "rapist");
  insert(root, "reap");
  insert(root, "spare");
  insert(root, "spear");

  //search
  search(root, "er");
  search(root, "pear");
  search(root, "pears");
  search(root, "rapper");
  search(root, "rape");
  search(root, "rap");
  search(root, "rapist");
  search(root, "reap");
  search(root, "spare");
  search(root, "spear");

  //print entire trie
  print_entire_trie_manager(root);

  //delete

  //1. delete non-existent word
  delete(root, "beras");

  //2. delete unique word
  delete(root, "er");

  //3. delete a word which is a prefix
  delete(root, "rap");

  //4. delete a word which has a prefix but is not shared
  delete(root, "pears");

  //5. delete a word which has a prefix and is shared
  delete(root, "rapper");

  //print_entire_trie(root);

  //print entire trie
  print_entire_trie_manager(root);

  //free entire trie
  free_trie(root);

  return 0;
}

//test5
int lookup_char(char p1){
  char blah[CHAR_SIZE]={'a', 'e', 'p', 'r', 's'};
  for(int i=0; i<CHAR_SIZE; i++){
    if(blah[i]==p1){
      return i;
    }
  }
  return -1;
}

char lookup_int(int p1){
  char blah[CHAR_SIZE]={'a', 'e', 'p', 'r', 's'};
  if(p1>=0 && p1<=CHAR_SIZE){
    return blah[p1];
  }
  return '\0';
}

// Function that returns a new Trie node
trie* createTrieNode(){
  trie* node=malloc(sizeof(trie));
  if (node==NULL){
      printf("unable to allocate memory to create node to be inserted into trie\n");
      exit(1);
  }
  node->isWord=false;
  node->isRead=false;
  for (int i=0; i<CHAR_SIZE; i++) {
      node->child[i]=NULL;
  }
  return node;
}

bool insert(trie *head, char *str){
  trie* curr=head;
  int a=strlen(str)+1;
  char cpy[a];
  strcpy(cpy, str);
  while (*str){
      int b=lookup_char(*str);
      if(b==-1){
        printf("you have entered a word with invalid character, \'%c\'.\nunable to insert the word, \"%s\".\nplease enter only a, e, p, r or s\n\n", *str, cpy);
        return false;
      }
      if(curr->child[b]==NULL){
          curr->child[b]=createTrieNode();
          printf("letter %c inserted into trie\n", *str);
      }
      else{
        printf("letter %c exists in trie\n", *str);
      }
      curr = curr->child[b];
      str++;
  }
  curr->isWord=1;
  printf("word %s has been added into trie\n\n", cpy);
  return true;  
}

bool search(trie *head, char *str){
  trie* curr=head;
  int a=strlen(str)+1;
  char cpy[a];
  strcpy(cpy, str);
  bool b=false;
  while(*str){
      int a=lookup_char(*str);
      if(a==-1){
        printf("\nyou have entered a word with invalid character, \'%c\'.\nunable to search for the word, \"%s\".\nplease enter only a, e, p, r or s\n\n", *str, cpy);
        return false;
      }
      else{
          printf("%c", *str);
          curr=curr->child[a];
          str++;
      }
  }
  b=curr->isWord;
  if(b){
      printf("\nword %s found", cpy);
  }
  else{
      printf("\nword %s not found", cpy);
  }
  printf("\n\nsearch return: %d\n", b);
  return b;
}

bool isNull(trie *head){
  trie *curr=head;
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
          return false;
      }
  }
  return true;
}

void print_entire_trie_manager(trie *head){
  trie *curr=head;
  printf("\nprinting the entire trie tree: \n");
  char *a=calloc(2, sizeof(char));
  if(a==NULL){
    printf("unable to allocate memory in function print_entire_trie_manager\n");
    return;
  }
  int b=0;
  a=print_entire_trie(curr, a, b);
  if(a==NULL){
    return;
  }
  free(a);
  reset_isRead_key(head);
  printf("\n");
}

char* print_entire_trie(trie *head, char *p2, int p3){
  if(head==NULL){
      return NULL;
  }
  trie* curr=head;
  if(curr->isWord && !curr->isRead){
    printf("%s\n", p2);
    curr->isRead=true;
  }
  if(isNull(curr)){
    return p2;
  }
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
        char a=lookup_int(i);
        p2[p3]=a;
        p3++;
        p2=realloc(p2, p3+2);
        *(p2+(p3+1))='\0';
        p2=print_entire_trie(curr->child[i], p2, p3);
        p3--;
      }
  }
  return p2;
}

void reset_isRead_key(trie *head){
  if(head==NULL){
      return;
  }
  trie* curr=head;
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
        reset_isRead_key(curr->child[i]);
      }
  }
  curr->isRead=false;
}


trie* delete(trie *head, char *str){
  trie *curr=head;
  char *ptr=str;
  int length=strlen(ptr);
  if(length==0){
    if(curr->isWord){
      curr->isWord=false;
      if(isNull(curr)){
        free(curr);
        curr=NULL;
      }
      printf("deleted!!\n");
    }
    else{
      printf("unable to delete, word not found int trie!!!\n");
    }
  }
  else{
    int c_to_i=lookup_char(ptr[0]);
    if(c_to_i!=-1){
        if(curr->child[c_to_i]!=NULL){
          curr->child[c_to_i]=delete(curr->child[c_to_i], ++ptr);
        }
        else{
          printf("unable to delete, word not found int trie!!!\n");
        }
    }
    else{
        printf("unable to delete, word not found int trie!!!\n");
    }

  }
  return curr;
}

void free_trie(trie *head){
  if(head==NULL){
      return;
  }
  trie* curr=head;
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
          free_trie(curr->child[i]);
      }
  }
  free(curr);
}
