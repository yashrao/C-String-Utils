
#ifndef SU_H_
#define SU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* String Utils */

typedef struct {
    int length;
    int size;
    char* ptr;
} SU_String;


static int su_calc_str_size(char* str);
SU_String su_create_string(char* str);
void su_append_cstring(SU_String* string, char* appendage);
SU_String su_append_string(SU_String string1, SU_String string2);
void su_free_string_ptr(SU_String string);
void su_cut_right(SU_String* string, int cut_pos);
SU_String su_cut_right_copy(SU_String string, int cut_pos);
void su_cut_left(SU_String* string, int cut_pos);
SU_String su_cut_left_copy(SU_String string, int cut_pos);
SU_String su_copy_string(SU_String string);
SU_String* su_split_string(SU_String string, char c, int* num);
bool su_check_eq(SU_String string1, SU_String string2);
void su_trim(SU_String* string);

#endif //SU_H_

#ifdef SU_IMPLEMENTATION

static int su_calc_str_size(char* str) {
    int size = 0;
    while(str[size] != '\0') {
        size++;
    }
    size++;
    return size;
}

SU_String su_create_string(char* str) {
    int size = su_calc_str_size(str);
    int length = size - 1;
    char* ptr = calloc(size, sizeof(char));

    for (int i = 0; i < size; i++) {
        ptr[i] = str[i];
    }

    SU_String ret = {length, size, ptr};
    return ret;
}

void su_append_cstring(SU_String* string, char* appendage) {
    int appendage_size = su_calc_str_size(appendage);
    string->ptr = realloc(string->ptr, string->length + appendage_size);
    int new_length = string->length + appendage_size - 1;
    for (int i = string->length; i < new_length; i++) {
        string->ptr[i] = appendage[i - string->length];
    }
    string->ptr[new_length] = '\0';
    string->length = new_length;
    string->size = new_length + 1;
}

SU_String su_append_string(SU_String string1, SU_String string2) {
    SU_String ret;
    ret.size = string1.length + string2.size;
    ret.length = ret.size - 1;
    bool swap = false;
    ret.ptr = calloc(ret.size, sizeof(char));
    for (int i = 0; i < ret.size; i++) {
        if (i == (string1.length)) {
            swap = true;
        }
        if (!swap) {
            ret.ptr[i] = string1.ptr[i];
        } else {
            ret.ptr[i] = string2.ptr[i - string1.length];
        }
    }
    return ret;
}

void su_free_string_ptr(SU_String string) { free(string.ptr); }

void su_cut_right(SU_String* string, int cut_pos) {
    string->length = cut_pos;
    string->size = cut_pos + 1;
    string->ptr = realloc(string->ptr, sizeof(char) * string->size);
    string->ptr[string->length] = '\0';
}

SU_String su_cut_right_copy(SU_String string, int cut_pos) {
    SU_String ret;
    ret.length = cut_pos;
    ret.size = cut_pos + 1;
    ret.ptr = calloc(ret.size, sizeof(char));
    for (int i = 0; i < ret.length; i++) {
        ret.ptr[i] = string.ptr[i];
    }
    ret.ptr[ret.length] = '\0';

    return ret;
}

void su_cut_left(SU_String* string, int cut_pos) {
    string->length = string->length - cut_pos;
    int new_size = string->size - cut_pos;
    for (int i = cut_pos; i < string->size; i++) {
        string->ptr[i - cut_pos] = string->ptr[i];
    }
    string->ptr = realloc(string->ptr, new_size);
    string->size = new_size;
    string->ptr[string->length] = '\0';
}

SU_String su_cut_left_copy(SU_String string, int cut_pos) {
    SU_String ret;
    ret.length = string.length - cut_pos;
    ret.size = string.size - cut_pos;
    ret.ptr = calloc(ret.size, sizeof(char));
    for (int i = cut_pos; i < string.size; i++) {
        ret.ptr[i - cut_pos] = string.ptr[i];
    }
    ret.ptr[ret.length] = '\0';
    return ret;
}

SU_String su_copy_string(SU_String string) {
    SU_String ret;
    ret.ptr = calloc(string.size, sizeof(char));
    ret.size = string.size;
    ret.length = string.length;
    for (int i = 0; i < string.length; i++) {
        ret.ptr[i] = string.ptr[i];
    }
    return ret;
}

SU_String* su_split_string(SU_String string, char c, int* num) {
    SU_String old_string = su_copy_string(string);
    int num_items = 1;
    for (int i = 0; i < string.size; i++) {
        char current = string.ptr[i];
        if (current == c) {
            num_items++;
        }
    }
    SU_String* ret = calloc(num_items, sizeof(SU_String));
    if (num_items == 1) {
        // return itself as an array
        ret[0] = string;
    } else {
        int diff = 0;
        int items_done = 0;
        for (int i = 0; i < string.size; i++) {
            char current = string.ptr[i];
            if (current == c) {
                ret[items_done] = su_cut_right_copy(old_string, i - diff);
                su_cut_left(&old_string, i - diff + 1);
                i++; // skip the character
                diff = i;
                items_done++;
            }
            if (items_done == num_items - 1) {
                // add the last item
                ret[items_done] = su_copy_string(old_string);
                break;
            }
        }
        // include the last item
    }
    su_free_string_ptr(old_string);
    *num = num_items;
    return ret;
}

bool su_check_eq(SU_String string1, SU_String string2) {
    if (string1.length != string2.length) {
        return false;
    } else {
        for (int i = 0; i < string1.length; i++) {
            if (string1.ptr[i] != string2.ptr[i]) {
                return false;
            }
        }
        return true;
    }
}

void su_trim(SU_String* string) {
    // TODO: fix this function
    char whitespace[3] = {' ', '\n', '\t'};
    bool start = true;
    int start_pos, end_pos = 0;
    for (int i = 0; i < string->size; i++) {
        char current = string->ptr[i];
        bool is_whitespace = false;
        for (int j = 0; j < 3; j++) {
            if (current == whitespace[j]) {
                is_whitespace = true;
                break; // break whitespace loop
            }
        }
        if (!is_whitespace && current != '\0') {
            if (start) {
                start_pos = i;
            }
            end_pos = i;
            start = false;
        }
    }
    su_cut_left(string, start_pos);
    su_cut_right(string, end_pos - start_pos + 1);
}

#endif // SU_IMPLEMENTATION

