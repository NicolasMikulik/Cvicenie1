#include <stdio.h>
#include <string.h>
int main() {

    int size = 0, charPos = 0, indexOne = 0, indexTwo = 0, indexThree = 0; //iterators
    scanf("%d",&size);
    char str[size+1], innerStr[size+1], outerStr[size+1];
    int fib1 = 1, fib2 = 1, sum = 0, order = 1, temp = 0; //variables for counting the number of permutations
    int currentLen = size; //length of the string the program is currently working with
    bool zeroesRemaining = false, permutationRecorded = false;

    while(order<size) {
        temp = fib1 + fib2;
        fib1 = fib2;
        fib2 = temp;
        order++;
    } //fib2 is Fibonacci's number
    char res[fib2][size+1];
    for(charPos=0;charPos<size;charPos++){
        str[charPos]='1';
        res[0][charPos]='1';
    }

    for (int eachElement = 1; eachElement < fib2 ; ++eachElement) {
        res[eachElement][0] = '2';
        res[eachElement][1] = '\0';
    }
    str[size]='\0'; //prepare the string to be permutated
    res[0][size]='\0';
    strcpy(innerStr,str);
    strcpy(outerStr,str);
    printf("%s\n",str); //original string
    int startpos = 0, foundFirstOne = 0, translatedZeroes = 2, numberOfZeroes = 0;
    char change;
    char lastChar;

    for(charPos=0;charPos<(size/2);charPos++) { //the horizontal tile takes up two spaces, so maximum length of permutation full of horizontal tiles is size/2
        printf("This is the string before changing 1 and 0 and before rotation %s\n", str);
        strcpy(str,outerStr);
        str[--currentLen] = '\0';
        for (indexOne = 0; indexOne < currentLen; indexOne++) {
            if (str[indexOne] == '1') {
                str[indexOne] = '0';
                break;
            }
        }
        numberOfZeroes++; //tracking the number of zeroes in the string
        printf("This is the string after %s\n", str);
        strcpy(outerStr,str);

        permutationRecorded = false;
        for(int eachElement = 1; eachElement < fib2; eachElement++){
            if(strcmp(str,res[eachElement]) == 0){
                printf("Match found %s\n", res[eachElement]);
                permutationRecorded = true;}
        }
        if(permutationRecorded == false){
            for(int eachElement = 1; eachElement < fib2; eachElement++)
                if(res[eachElement][0] == '2'){
                    temp = eachElement;
                    strcpy(res[temp],str);
                    printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
                    break;}
            //strcpy(res[temp],str);
            //printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
        }
        else printf("Permutation found %s, but already present in record\n", str);

        //translatedZeroes = 2;
        zeroesRemaining = true;
        while(zeroesRemaining) { //this loops keeps processing and altering one string as long as all the zeroes are not on the right side to begin with, e.g. 111000
            strcpy(innerStr, str);
            for (indexThree = 0; indexThree < numberOfZeroes; ++indexThree) {
                startpos = 0;
                foundFirstOne = 0;
                printf("String before looking for first zero %s\n",str);
                for (indexOne = 0; indexOne < currentLen; ++indexOne) { //foundFirstOne == 0 //00111
                    if(str[indexOne] == '0' && foundFirstOne == 0){ //keep searching for the right 0
                        startpos++;
                        foundFirstOne = 1;
                        continue;}
                    if ((str[indexOne] == '0' && foundFirstOne == 2)) {
                        startpos++;
                        foundFirstOne = 3;
                        continue;}
                    if ((str[indexOne] == '1' && foundFirstOne == 1)) { //return to the 0 on the left
                        break;}
                    if(str[indexOne] == '1' && foundFirstOne == 0){
                        startpos++;
                        foundFirstOne = 2;
                        continue;}
                    if(str[indexOne] == '1' && foundFirstOne == 3){
                        break;}
                    startpos++;
                }
                startpos--;
                printf("Startpos %d\n", startpos);

                permutationRecorded = false;
                for(int eachElement = 1; eachElement < fib2; eachElement++){
                    if(strcmp(str,res[eachElement]) == 0){
                        printf("Match found %s\n", res[eachElement]);
                        permutationRecorded = true;}
                }
                if(permutationRecorded == false){
                    for(int eachElement = 1; eachElement < fib2; eachElement++)
                        if(res[eachElement][0] == '2'){
                            temp = eachElement;
                            strcpy(res[temp],str);
                            printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
                            break;}
                    //strcpy(res[temp],str);
                    //printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
                }
                else printf("Permutation found %s, but already present in record\n", str);

                for (indexTwo = startpos; indexTwo < currentLen - 1; indexTwo++) {    //moving the '0' to the right, creating permutations
                    change = str[indexTwo];
                    str[indexTwo] = str[indexTwo + 1];
                    str[indexTwo + 1] = change;
                    printf("%s\n", str);
                }
            }
            strcpy(str, innerStr);
            change = str[currentLen - 1];
            for (indexOne = currentLen - 1; indexOne >= 0; --indexOne) {
                str[indexOne] = str[indexOne - 1];
            }
            str[0] = change;

            translatedZeroes = 0;       //check if all zeroes are in the right side of the string, e.g. 111000, this means translatedZeroes == 2
            for (indexOne = currentLen - 1; indexOne >= 0; --indexOne) {
                if (str[indexOne] == '1' && translatedZeroes == 0) {
                    translatedZeroes = 1;
                }
                if (str[indexOne] == '0' && translatedZeroes == 1) {
                    translatedZeroes = 2;
                }
            }
            if (translatedZeroes != 2) {
                zeroesRemaining = false;
            }
            printf("Rotated string %s and translated zeroes all in the right %d\n", str, translatedZeroes);
            //strcpy(outerStr,str);
            //horizAtEnd = false;
        }
    }
    printf("%s\n",str); //original string
    strcpy(res[fib2-1],str);
    for (int eachCharacter = 0; eachCharacter < fib2; ++eachCharacter) {
        printf("%s\n",res[eachCharacter]);
    }
    return 0;
}

/*
 * for (indexThree = 0; indexThree < currentLen; ++indexThree) {//checking if the last character of string is a '0' (horizontal tile at the end of string)
            startpos = 0;
            strcpy(secondStr,str);
            printf("Second string %s VS original %s\n", secondStr,str);
            for (indexOne = 0; indexOne < currentLen; ++indexOne) { //foundFirstOne == 0
                if(str[indexOne] == '0' && foundFirstOne == 0 || str[indexOne] == '1' && foundFirstOne == 1){
                    startpos++;
                }
                if(str[indexOne] == '1' && foundFirstOne == 0 || str[indexOne] == '1' && foundFirstOne == 2){
                    break;
                }
                if(str[indexOne] == '1' && foundFirstOne == 0){
                    startpos++;
                    foundFirstOne = 1;
                }
                if(str[indexOne] == '0' && foundFirstOne == 1){
                    startpos++;
                    foundFirstOne = 2;
                }
            }
            startpos--;
            printf("Startpos %d\n",startpos);
            for (indexTwo = startpos; indexTwo < currentLen-1; indexTwo++) {    //moving the '0' to the right, creating permutations
                change = str[indexTwo];
                str[indexTwo] = str[indexTwo+1];
                str[indexTwo+1] = change;
                printf("%s\n",str);
            }
            change = secondStr[currentLen-1];   //rotating the characters of string to right, last character becomes the first one
            printf("Change %c\n",change);
            for (indexTwo = 0; indexTwo < currentLen-2; ++indexTwo) {
                secondStr[indexTwo] = secondStr[indexTwo+1];
            }
            secondStr[0]=change;
            strcpy(str, secondStr);
            if(secondStr[currentLen-1] == '0'){ //if all '0' have been moved from left to right, stop creating permutations for this combination and move on
                break;}
        }
 */

 /*
  * #include <stdio.h>
#include <string.h>
int main() {

    int size = 0, charPos = 0, indexOne = 0, indexTwo = 0, indexThree = 0, eachCharacter = 0; //iterators
    int startpos = 0, foundFirstOne = 0, translatedZeroes = 2, numberOfZeroes = 0;
    char str[size+1], innerStr[size+1], outerStr[size+1], change;
    int fib1 = 1, fib2 = 1, sum = 0, order = 1, temp = 0; //variables for counting the number of permutations
    bool zeroesRemaining = false, permutationRecorded = false;
    scanf("%d",&size);
    int currentLen = size; //length of the string the program is currently working with
    while(order<size) {
        temp = fib1 + fib2;
        fib1 = fib2;
        fib2 = temp;
        order++;
    } //fib2 is Fibonacci's number
    char res[fib2][size+1];
    for(charPos=0;charPos<size;charPos++){
        str[charPos]='1';
        res[0][charPos]='1';
    }
    for(charPos=1;charPos<fib2;charPos++){
        res[charPos][0] = '2'; //writing a placeholder
        res[charPos][1] = '\0';}
    str[size]='\0'; //prepare the string to be permutated
    res[0][size]='\0';
    strcpy(innerStr,str);
    strcpy(outerStr,str);
    printf("%s\n",str); //original string

    for(charPos=0;charPos<(size/2);charPos++) { //the horizontal tile takes up two spaces, so maximum length of permutation full of horizontal tiles is size/2
        printf("This is the string before changing 1 and 0 and before rotation %s\n", str);
        strcpy(str,outerStr);
        str[--currentLen] = '\0';
        for (indexOne = 0; indexOne < currentLen; indexOne++) {
            if (str[indexOne] == '1') {
                str[indexOne] = '0';
                break;
            }
        }
        numberOfZeroes++; //tracking the number of zeroes in the string
        printf("This is the string after %s\n", str);
        strcpy(outerStr,str);

        permutationRecorded = false;
        for(indexOne = 1; indexOne < fib2; indexOne++){
            if(strcmp(str,res[indexOne]) == 0){
                printf("Match found %s\n", res[indexOne]);
                permutationRecorded = true;}
        }
        if(permutationRecorded == false){
            for(indexOne = 1; indexOne < fib2; indexOne++)
                if(res[indexOne][0] == '2'){
                    temp = indexOne;
                    break;}
            strcpy(res[indexOne],str);
            printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
        }
        else printf("Permutation found %s, but already present in record\n", str);

        zeroesRemaining = true;
        while(zeroesRemaining == true) {
            strcpy(innerStr, str);
            for (indexThree = 0; indexThree < numberOfZeroes; ++indexThree) {
                startpos = 0;
                foundFirstOne = 0;
                printf("Looking for the first zero from left in the string %s\n", str); //problem string 1011111
                for (indexOne = 0; indexOne < currentLen; ++indexOne) {
                    if ((str[indexOne] == '0' && foundFirstOne == 0) || (str[indexOne] == '1' && foundFirstOne == 1)) { //keep on moving right
                        startpos++;
                    }
                    if ((str[indexOne] == '1' && foundFirstOne == 2)) {
                        break;
                    }
                    if (str[indexOne] == '1' && foundFirstOne == 0) {
                        startpos++;
                        foundFirstOne = 1;
                    }
                    if (str[indexOne] == '0' && foundFirstOne == 1) {
                        startpos++;
                        foundFirstOne = 2;
                    }
                }
                startpos--;
                printf("Startpos %d\n", startpos);
                for (indexTwo = startpos; indexTwo < currentLen - 1; indexTwo++) {    //moving the '0' to the right, creating permutations
                    change = str[indexTwo];
                    str[indexTwo] = str[indexTwo + 1];
                    str[indexTwo + 1] = change;
                    permutationRecorded = false;
                        for(indexOne = 1; indexOne < fib2; indexOne++){
                            if(strcmp(str,res[indexOne]) == 0){
                                printf("Match found %s\n", res[indexOne]);
                                permutationRecorded = true;}
                        }
                        if(permutationRecorded == false){
                            for(indexOne = 1; indexOne < fib2; indexOne++)
                                if(res[indexOne][0] == '2'){
                                    temp = indexOne;
                                    break;}
                            strcpy(res[indexOne],str);
                            printf("Permutation found %s and recorded in result %s\n", str, res[temp]);
                        }
                        else printf("Permutation found %s, but already present in record\n", str);
                }
            }
            strcpy(str, innerStr);
            change = str[currentLen - 1];
            for (indexOne = currentLen - 1; indexOne >= 0; --indexOne) {
                str[indexOne] = str[indexOne - 1];
            }
            str[0] = change;

            translatedZeroes = 0;       //check if all zeroes are in the right side of the string, e.g. 111000, this means translatedZeroes == 2
            for (indexOne = currentLen - 1; indexOne >= 0; --indexOne) {
                if (str[indexOne] == '1' && translatedZeroes == 0) {
                    translatedZeroes = 1;
                }
                if (str[indexOne] == '0' && translatedZeroes == 1) {
                    translatedZeroes = 2;
                }
            }
            if (translatedZeroes != 2) {
                zeroesRemaining = false;
            }
            printf("Rotated string %s and translated zeroes all in the right %d\n", str, translatedZeroes);
            //strcpy(outerStr,str);
            //horizAtEnd = false;
        }
    }
    printf("%s\n\n",str); //original string
    for(indexOne = 0; indexOne < fib2; indexOne++)
        if(res[indexOne][0]!='2'){
            printf("%s\n", res[indexOne]);
            temp++;}
    return 0;
}
  */