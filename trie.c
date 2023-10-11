#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>

#define CHAR_SIZE 26

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
trie* delete(trie *head, char *str_immut, char *str);
void free_trie(trie *head);

int main(int argc, char *argv[]){
  trie *root=createTrieNode();
  if(root==NULL){
      return 1;
  }
  //insert, search, delete from and print, free entire trie:
  insert(root, "car");
  insert(root, "cat");
  insert(root, "ba");
  insert(root, "do");
  insert(root, "done");
  insert(root, "Gondola");
  insert(root, "taken");
  insert(root, "trie");
  insert(root, "tried");
  insert(root, "troll");
  insert(root, "tromso");
  insert(root, "try");
  insert(root, "umbrella");
  
  search(root, "ca");
  search(root, "car");
  search(root, "cat");
  search(root, "ba");
  search(root, "do");
  search(root, "done");
  search(root, "Gondola");
  search(root, "taken");
  search(root, "trie");
  search(root, "tried");
  search(root, "troll");
  search(root, "tromso");
  search(root, "try");
  search(root, "umbrella");
  search(root, "zebra");

  //print entire trie
  print_entire_trie_manager(root);

  // //delete

  // //1. delete non-existent word
  delete(root, "Gondola", "Gondola");
  delete(root, "grandpa", "grandpa");
  delete(root, "tr", "tr");
  delete(root, "tri", "tri");

  // 2. delete unique word
  delete(root, "ba", "ba");

  // //3. delete a word which is a prefix
  delete(root, "do", "do");

  //4. delete a word which has a prefix but is not shared (other than the 2 words, 'do' & 'done', no other words have a prefix of 'do')
  delete(root, "done", "done");

  //5. delete a word which has a prefix and is shared (the prefix, 'tr' is shared by 5 words, 'trie', 'tried', 'troll', 'tromso' & 'try')
  delete(root, "tromso", "tromso");

  //print entire trie
  print_entire_trie_manager(root);

  // free entire trie
  free_trie(root);
  // free(root);

  return 0;
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
    if(*str<97 || *str>122){
      printf("unable to insert the word, \"%s\".\nyou have entered a word with invalid character, \'%c\'.\nplease enter only small-lettered alphabets\n\n", cpy, *str);
      return false;
    }
    int b=*str-97;
    if(curr->child[b]==NULL){
        curr->child[b]=createTrieNode();
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
      if(*str<97 || *str>122){
        printf("\nunable to search for the word, \"%s\".\nyou have entered a word with invalid character, \'%c\'.\nplease enter only small-lettered alphabets\n", cpy, *str);
        return false;
      }
      else{
          curr=curr->child[(*str-97)];
          if(curr==NULL){
            printf("\nword \"%s\" not found in trie", cpy);
            printf("\nsearch return: %d\n", b);
            return b;
          }
          str++;
      }
  }
  b=curr->isWord;
  if(b){
      printf("\nword \"%s\" found in trie", cpy);
  }
  else{
      printf("\nword \"%s\" not found in trie", cpy);
  }
  printf("\nsearch return: %d\n", b);
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
  char *a=malloc(2*sizeof(char));
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
    p2[p3]='\0';
    printf("%s\n", p2);
    curr->isRead=true;
  }
  if(isNull(curr)){
    return p2;
  }
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
        p2[p3]=97+i;
        p3++;
        p2=realloc(p2, p3+2);
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

trie* delete(trie *head, char *str_immut, char *str){
  if(head==NULL){
    return head;
  }
  if(strlen(str)==0){
    if(head->isWord){
      head->isWord=false;
      if(isNull(head)){
        free(head);
        head=NULL;
      }
      return head;
    }
  }
  else{
    if(*str<97 || *str>122){
        printf("\nunable to delete the word, \"%s\".\nyou have entered a word with invalid character, \'%c\'.\nplease enter only small-lettered alphabets\n", str_immut, *str);
    }
    else{
      int a=*str-97;
      if(head->child[a]!=NULL){
        head->child[a]=delete(head->child[a], str_immut, ++str);
        return head;
      }
    }
  }
  printf("unable to delete \"%s\", word not found int trie!!!\n\n", str_immut);
  return head;
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
