# WordCounter
This algorithm in C count all the words in a .txt file, shows all the different ones and count how many similar there are.

You just have to compile the code with **"make all"** then run with **"make run"**.

## All words go to a database
After the execution, two .txt files will be updated: "word_stats.txt", and "broken_text.txt".

The first one shows all words and their number in alphabetical order, while the last shows the text with all the words separated in new lines.

## Important notes
* This algorithm ignore non-alphabetical character, so, if the word is "it's", the dictionary will show "its".
* If the word is separated by other character besides space or new-line, the algorithm will identify it as a unique word.
* This algorithm don't separate lowercase and uppercase characters, so words like "The" e "the" will be considered the same.

### BUG
* If you find another bug, please contact me and I'll fix it.
