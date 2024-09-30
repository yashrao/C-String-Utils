# C String Utils

Some utilities I wrote for string making string manipulations easy in C. I wanted to add string manipulation features that would create a comfortable experience when dealing with strings in C.

## Usage:
Since this is a single header lib, it was designed to be used in the same way as shown below. Of course inspired by [stb](https://github.com/nothings/stb)
```C
#define SU_IMPLEMENTATION
#include "su.h"
```

## Supported functions:
Currently the supported functions are below:
```C
// Create a string from a char*
SU_String su_create_string(char* str);
// Append a SU_String with an array of chars 
void su_append_cstring(SU_String* string, char* appendage);
// append two SU_Strings and return a new SU_String
SU_String su_append_string(SU_String string1, SU_String string2);
// Used to free the char* for the SU_String
void su_free_string_ptr(SU_String string);
// Cuts the right hand portion of the string from the cut_pos (this modifies the SU_String)
void su_cut_right(SU_String* string, int cut_pos);
// Cuts the right hand portion of the string from the cut_pos (this returns a copy)
SU_String su_cut_right_copy(SU_String string, int cut_pos);
// Cuts the left hand portion of the string from the cut_pos (this modifies the SU_String)
void su_cut_left(SU_String* string, int cut_pos);
// Cuts the left hand portion of the string from the cut_pos (this returns a copy)
SU_String su_cut_left_copy(SU_String string, int cut_pos);
// creates a copy of a SU_String
SU_String su_copy_string(SU_String string);
// Splits a SU_String by a character and returns the array of SU_String structs and updates the number of 
// elements in the array provided by num
SU_String* su_split_string(SU_String string, char c, int* num);
// Checks if two SU_Strings are equal
bool su_check_eq(SU_String string1, SU_String string2);
// trims whitespace from the SU_String (this modifies the SU_String)
void su_trim(SU_String* string);
// Creates a slice of a SU_String
SU_String su_create_slice(char* string, int start_pos, int end_pos);
```
