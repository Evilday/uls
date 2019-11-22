#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
	if (!s)
		return NULL;
	char **words = (char **)malloc(sizeof(char*) 
	* (mx_count_words(s, c) + 1));
	int index = 0;
	int symbols = 0;
	int word_index = 0;
	int new_word = 0;
	
	for (; s[index]; index++) {
		while (s[index] != c && s[index]) {
			index++;
			new_word = ++symbols;
		}
		if (new_word) {
			words[word_index] = mx_strnew(symbols);
			mx_strncpy(words[word_index++], (s + index - symbols), symbols);
			new_word = symbols = 0;
		}
	}
	words[word_index] = NULL;
	return words;
}
