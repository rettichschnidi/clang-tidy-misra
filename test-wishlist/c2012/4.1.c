char Ag1[] = "\x41g"; // BAD
char Ag2[] = "\x41" "g"; // GOOD
char Ag2[] = "\x41\x67"; // GOOD
int c1 = '\141t'; // BAD
int c2 = '\141\t'; // GOOD
