trie:trie.o
	gcc -g3 -Wall trie.o -o trie.exe
trie.o:trie.c
	gcc -g3 -Wall -c trie.c -o trie.o
clear:
	rm *.o
clean:
	rm *.o *.exe


# trie:trie.o lib.o
# 	gcc -g3 -Wall trie.o lib.o -o trie.exe

# trie.o:trie.c
# 	gcc -g3 -Wall -c trie.c -o trie.o

# lib.o:lib.c
# 	gcc -g3 -Wall -c lib.c -o lib.o

# clear:
# 	rm *.o
   
# clean:
# 	rm *.o *.exe