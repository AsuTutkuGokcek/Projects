#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

int main (int arc, char *arg[]) {

FILE *fp;

FILE *fp2;

FILE *fp3;
int limit = 4096;
char str[limit];
char tempStr[limit];
char input_value[limit];

char wordList[limit][1024]; //random large number that's a power of two
char wordStr[limit];

char str3[limit];

int posArray[limit];
int negArray[limit];

int posX=0;
int negX=0;
int count=0;
int wordCount=0;
int totalContaining=0;
bool foundToken=false;


//open file, check if it can't be opened.
fp = fopen("movieReviews.txt", "r");
if (fp == NULL){
printf("Error! Couldn't open file movieReviews.txt.\n");
return 1;
}

fp2 = fopen("wordList.txt", "r");
if (fp2 == NULL){
printf("Couldn't open file wordList.txt.\n");
return 1;
}

fp3 = fopen("movieReviews.txt", "r");
if (fp3 == NULL){
printf("Couldn't open file movieReviews.\n");
return 1;
}

double average=0.0f;
int tempRating=0;
//ask user for input.
printf("Enter a word: ");
scanf("%s", input_value);

//turn input to lower case.
size_t i;
for(i = 0; input_value[i] != '\0'; i++){
	input_value[i] = tolower(input_value[i]);
}

while(fgets(wordStr, limit, fp2) != NULL){
strcpy(wordList[wordCount], wordStr);
wordCount ++;
}

//Task1
//get every line, put it to str.
while(fgets(str, limit , fp ) != NULL){
	//turn str to lower case.
	size_t j;
	for(j=0; str[j] != '\0'; j++){
		str[j] = tolower(str[j]);
	}
	foundToken = false;
	//we need a tempStr to get the score when we need.
	strcpy(tempStr, str);
	char * token = strtok(str, " ");
	while(token != NULL){
	//check if the token matches the input.
	if(strcmp(token, input_value) == 0){
	count += 1;
	//add the score of tempStr to average. 
	if(tempStr != NULL){
	average += (int)str[0]-'0';
	//according to ASCII I did -'0' to get its actual value.
	}	
	foundToken = true;
	//allows me to only count the ones with right token. without this for ex a sentence with two correct matches would add 2 to the divisor but it should add 1.
}
token = strtok(NULL, " ");
}
//we add 1 to number of correct lines.
if(foundToken){
totalContaining += 1;
}
}
//fclose(fp);

//Task2
size_t x;
for(x=0; x<wordCount; x++){	//Loop through array of wordList.
fp3 = fopen("movieReviews.txt", "r"); //Open file of reviews each time. 
	if(fp3 == NULL){
	printf("Couldn't open file movieReviews.txt\n");
	return 1;
	}
	while(fgets(str3, limit, fp3) != NULL){
	size_t z;
	for(z=0; str3[z] != '\0'; z++){ 	//Lowercase it.
	str3[z] = tolower(str3[z]);
	}
	foundToken= false;
	strcpy(tempStr, str3);
	char * token = strtok(str3, " ");
	while(token != NULL){
	char temporary[strlen(wordList[x])]; 	//Remove newlines from wordList words.
	size_t u = 0;
	for(u=0; u<strlen(wordList[x])-1; u++){
	temporary[u] = tolower(wordList[x][u]);
	}
	temporary[u]='\0';
	
	char temporary2[strlen(token)];
	size_t v = 0;
	for(v=0; v<strlen(token); v++){
	if(token[v] != '\r' && token[v] != '\n'){
		temporary2[v]=tolower(token[v]);
		}
	}
	temporary2[v]= '\0';

//	printf("Checking <%s> against [%s]\n", temporary, temporary2);
if(strcmp(temporary2, temporary) == 0){
		if(tempStr != NULL){
			tempRating = (int)str3[0]-'0';		//Same ASCII conversion.
			if(tempRating >= 3){			//Positive reviews.
				if(posArray[posX] == NULL){
					posArray[posX] = 0;
				}
				posArray[posX] += 1;
			}
			else{
				if(negArray[negX] == NULL){
					negArray[negX] = 0;
				}
				negArray[negX] += 1;
			}
		}
		foundToken = true;
		}
		token =  strtok(NULL, " ");
	}
	}
//	fclose(fp3);
	posX+=1;
	negX+=1;
}

size_t xa;
size_t ya;

int largestPos = 0;
int largestNeg = 0;

int largestPosIndex = 0;
int largestNegIndex = 0;

//Find max pos and neg.
for(xa = 0; xa<posX; xa++){
if(posArray[xa]>largestPos){
largestPos=posArray[xa];
largestPosIndex=xa;
}
}

for(ya = 0; ya<negX; ya++){
if(negArray[ya]>largestNeg){
largestNeg=negArray[ya];
largestNegIndex=ya;
}
}

printf("Most occuring word in pos reviews: %s appears %d times.\n", wordList[largestPosIndex], largestPos);
printf("Most occuring word in neg reviews: %s appears %d times.\n", wordList[largestNegIndex], largestNeg);

printf("%s appears %.1f times. \n", input_value, (double)count);  
if(count<1){
	printf("The average score for reviews containing the word %s cannot be computed, as no review contain the word %s. \n", input_value, input_value);
}else{
	printf("The average score for reviews containing the word %s is %.4f. \n", input_value, ((double)average)/(double)totalContaining);
}
fclose(fp);
fclose(fp3);
return 0;
}
