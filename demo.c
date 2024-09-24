#include <stdio.h>

#define SU_IMPLEMENTATION
#include "su.h"

int main(int argc, char** argv) {
    String test = su_create_string("test-");
    printf("%s: %d %d\n", test.ptr, test.length, test.size);
    su_append_string(&test, "abcde-kek");
    printf("%s: %d %d\n", test.ptr, test.length, test.size);
    String new = su_cut_right_copy(test, 3);
    printf("%s: %d %d\n", new.ptr, new.length, new.size);

    int result;
    String* kek = su_split_string(test, '-', &result);
    for (int i = 0; i < result; i++) {
        printf("i: %i; %s: %d %d\n", result, kek[i].ptr, kek[i].length, kek[i].size);
    }

    String trim_test = su_create_string("     THIS IS A TEST        ");
    su_trim(&trim_test);
    printf("%s: %d %d\n", trim_test.ptr, trim_test.length, trim_test.size);

    su_free_string_ptr(test);
    su_free_string_ptr(new);
    free(kek);
    return 0;
}
