#include <stdio.h>
int fibonacci(int fibInput){
    if(fibInput == 1 || fibInput == 0)
        return fibInput;
    return fibonacci(fibInput-1) + fibonacci(fibInput-2);
}
void find(char *s, int usedTiles, int currentLen, int size, int *foundCombinations){
    if(currentLen == size){
        (*foundCombinations)++;
        printf("%s\n",s);
        return;
    }
    if((currentLen+2)<=size){
        s[usedTiles]='=';
        s[usedTiles+1]='\0';
        find(s,usedTiles+1,currentLen+2,size,foundCombinations);
    }
    if((currentLen+1)<=size){
        s[usedTiles]='|';
        s[usedTiles+1]='\0';
        find(s,usedTiles+1,currentLen+1,size,foundCombinations);
    }
}
int main() {
    int size = 0, expectedCombinations = 0, foundCombinations = 0;
    scanf("%d",&size); //user input for the horizontal size of tile array
    expectedCombinations = fibonacci(size+1);  //number of possible arrangements
    printf("%d\n",expectedCombinations);
    char s[size+1];
    s[0]='\0';
    find(s,0,0,size, &foundCombinations);
    printf("\nNumber of expected combinations: %d\nNumber of found combinations: %d\n",expectedCombinations,foundCombinations);
    return 0;
}