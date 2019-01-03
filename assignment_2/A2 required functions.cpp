/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into an array
* @param ignoreWordFile - filename (the file storing ignore words)
* @param ignoreWords - store ignore words from the file (pass by
reference) * @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(char *ignoreWordFileName, string ignoreWords[]);

/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param ignoreWords - the array of strings storing ignore/stop words *
@return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, string ignoreWords[]);

/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array
(including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including
repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length);

/*
* Function name: arraySort
* Purpose: sort an array of wordItems, increasing, by their count
fields * @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem list[], int length);

/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of
wordItems * @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);
