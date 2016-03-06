// RUN: %clang++ -std=c++03 -Wtrigraphs -fsyntax-only -ferror-limit=0 -Xclang -verify %s

char trigraphRaute[] = "??= -> #";      // expected-warning {{trigraph converted to '#' character}}
char trigraphBackslash[] = "??/" -> \""; // expected-warning {{trigraph converted to '\' character}}

char trigraphCaret[] = "??' -> ^"; // expected-warning {{trigraph converted to '^' character}}

char trigraphOpenBracket[] = "??( -> ["; // expected-warning {{trigraph converted to '[' character}}

char trigraphCloseBracket[] = "??) -> ]"; // expected-warning {{trigraph converted to ']' character}}

char trigraphPipe[] = "??! -> |"; // expected-warning {{trigraph converted to '|' character}}

char trigraphOpenBrace[] = "??< -> {"; // expected-warning {{trigraph converted to '{' character}}

char trigraphCloseBrace[] = "??> -> }"; // expected-warning {{trigraph converted to '}' character}}

char trigraphTile[] = "??- -> ~"; // expected-warning {{trigraph converted to '~' character}}
