#include <stdio.h>

#define SU_IMPLEMENTATION
#include "su.h"

int main(int argc, char** argv) {
    SU_String test = su_create_string("test-");
    printf("%s: %d %d\n", test.ptr, test.length, test.size);
    su_append_cstring(&test, "abcde-kek");
    printf("%s: %d %d\n", test.ptr, test.length, test.size);
    SU_String new = su_cut_right_copy(test, 3);
    printf("%s: %d %d\n", new.ptr, new.length, new.size);

    int result;
    SU_String* kek = su_split_string(test, '-', &result);
    for (int i = 0; i < result; i++) {
        printf("i: %i; %s: %d %d\n", result, kek[i].ptr, kek[i].length, kek[i].size);
    }

    SU_String trim_test = su_create_string("     THIS IS A TEST        ");
    su_trim(&trim_test);
    printf("%s: %d %d\n", trim_test.ptr, trim_test.length, trim_test.size);


    SU_String append_su = su_create_string("test-");
    SU_String append_su2 = su_create_string("kek");
    SU_String combined = su_append_string(append_su, append_su2);
    printf("append> %s: %d %d\n", combined.ptr, combined.length, combined.size);
    su_free_string_ptr(append_su);
    su_free_string_ptr(append_su2);

    char* test_case = "test-case";
    SU_String test_case_su = su_create_string(test_case);
    printf("this is a test-case: %s\n", test_case_su.ptr);

    // create slice
    SU_String slice = su_create_slice(test_case_su.ptr, 5, 7);
    printf("this is a slice: %s\n", slice.ptr);

    su_free_string_ptr(slice);
    su_free_string_ptr(test_case_su);
    su_free_string_ptr(test);
    su_free_string_ptr(new);
    free(kek);
    return 0;
}
