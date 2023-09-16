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
bool delete(trie *head, char *str);
void free_trie(trie *head);

int main(int argc, char *argv[]){
  trie *root=createTrieNode();
  if(root==NULL){
      return 1;
  }
  //insert
  insert(root, "parse");
  insert(root, "pear");
  insert(root, "rapper");
  insert(root, "raper");
  insert(root, "rape");
  insert(root, "rap");
  insert(root, "rapist");
  insert(root, "reap");
  insert(root, "spare");
  insert(root, "spear");
  //search
  search(root, "parse");
  search(root, "pear");
  search(root, "rapper");
  search(root, "raper");
  search(root, "rape");
  search(root, "rap");
  search(root, "rapist");
  search(root, "reap");
  search(root, "spare");
  search(root, "spear");

  //print entire trie
  print_entire_trie_manager(root);

  //delete(root, "do");
  //delete(root, "trie");
  //delete(root, "ca");

  //print_entire_trie(root);

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
      if (curr->child[a]!=NULL){
          printf("%c", *str);
          curr=curr->child[a];
          str++;
      }
      else{
          printf("\nword %s not found", cpy);
          printf("\nsearch return: %d\n\n", b);
          return b;
      }
  }
  b=curr->isWord;
  if(b){
      printf("\nword %s found", cpy);
  }
  else{
      printf("\nword %s not found", cpy);
  }
  printf("\nsearch return: %d\n\n", b);
  return b;
}

bool isNull(trie *head){
  trie *curr=head;
  for(int i=0; i<CHAR_SIZE; i++){
      if(curr->child[i]!=NULL){
          // printf("node continues\n");
          return 0;
      }
  }
  // printf("all nodes are null!!!\n");
  return 1;
}

void print_entire_trie_manager(trie *head){
  trie *curr=head;
  printf("printing the entire trie tree: \n");
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
          curr->isRead=false;
      }
  }
}


// bool delete(trie *head, char *str){
//   if(head==NULL){
//       return false;
//   }
//   trie* curr=head;
//   bool a=false;
//   while(*str){
//       if (curr->child[*str-'a']!=NULL){
//           printf("%c\n", *str);
//           str++;
//           a=delete(curr->child[*str-'a'], str);
//       }
//       else{
//           printf("word not found\n");
//           return false;
//       }
//   }
//   a=curr->isWord;
//   if(a){
//       printf("word found, checking if last-letter node, %c is pointing to any nodes with values...\n", *str);
//       if(isNull(curr)){
//           printf("last-letter node %c is not pointing to any further nodes! deleting last-letter node and setting it to null...", *str);
//           free(curr);
//           curr=NULL;
//           printf("deleted last node %c and set to null!!!", *str);

//       }
//       else{
//           printf("last-letter node %c is pointing to at least one node with value, removing leaf-node attribute from last-letter node %c without deleting it...", *str, *str);
//           curr->isWord=false;
//       }
//       printf("leaf-node attribute for %c removed, deletion success...", *str);
//   }
//   else{
//       printf("word not found\n");
//   }
//   printf("search return: %d\n", a);
//   return a;
// }

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
