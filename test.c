#include <stdio.h>
#include <string.h>



int main() {
    // Test cases
    char *test1[] = {"cat", "<<", "\"file\"", NULL};
    char *test2[] = {"cat", "<<", "'file'", NULL};
    char *test3[] = {"cat", "<<", "file", NULL};
    char *test4[] = {"cat", "<", "file", NULL};
    char *test5[] = {"cat", "file", NULL};
    char *test6[] = {"echo", "-n", "Hi", NULL};

    // Check the test cases
    printf("Check test1: %d\n", check_heredoc_quotes(test1)); // Should print 1
    printf("Check test2: %d\n", check_heredoc_quotes(test2)); // Should print 1
    printf("Check test3: %d\n", check_heredoc_quotes(test3)); // Should print 0
    printf("Check test4: %d\n", check_heredoc_quotes(test4)); // Should print 0
    printf("Check test5: %d\n", check_heredoc_quotes(test5)); // Should print 0
    printf("Check test6: %d\n", check_heredoc_quotes(test6)); // Should print 0

    return 0;
}
