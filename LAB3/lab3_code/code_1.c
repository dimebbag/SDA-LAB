#include <stdio.h>
#include <string.h>

#define MAX 100
#define URL_LEN 100

typedef struct {
    char url[URL_LEN];
} Page;

Page back_stack[MAX];
Page forward_stack[MAX];

int top_back = -1;
int top_forward = -1;

int is_empty(const int *top) {
    return *top == -1;
}

int is_full(const int *top) {
    return *top == MAX - 1;
}

int push(Page stack[], int *top, const char url[]) {
    if (is_full(top)) {
        return 0;
    }
    (*top)++;
    strncpy(stack[*top].url, url, URL_LEN - 1);
    stack[*top].url[URL_LEN - 1] = '\0';
    return 1;
}

int pop(Page stack[], int *top, char url[]) {
    if (is_empty(top)) {
        return 0;
    }
    strncpy(url, stack[*top].url, URL_LEN - 1);
    url[URL_LEN - 1] = '\0';
    (*top)--;
    return 1;
}

int peek(const Page stack[], int top, char url[]) {
    if (is_empty(&top)) {
        return 0;
    }
    strncpy(url, stack[top].url, URL_LEN - 1);
    url[URL_LEN - 1] = '\0';
    return 1;
}

void clear_stack(int *top) {
    *top = -1;
}

int main(void) {
    char input[URL_LEN + 16];
    char current_url[URL_LEN] = "";
    int has_current = 0;

    const char *keywords[4] = {"visit <url>", "back", "forward", "stop"};
    const char *descriptions[4] = {
        "Vidkryty novu storinku ta ochystyty istoriyu Vpered",
        "Povernutysya na poperednyu storinku",
        "Pereyty na nastupnu storinku",
        "Zavershyty robotu ta vyvesty potochnu storinku"
    };

    while (1) {
        printf("\nVvedit komandu (visit <url>, back, forward, stop):\n");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '\0') {
            printf("Porozhnya komanda\n");
            continue;
        }

        printf("\nSpysok klyuchovykh sliv:\n");
        for (int i = 0; i < 4; i++) {
            printf("%s - %s\n", keywords[i], descriptions[i]);
        }

        if (strcmp(input, "stop") == 0) {
            break;
        } else if (strcmp(input, "back") == 0) {
            if (!has_current || is_empty(&top_back)) {
                printf("Istoriya Nazad porozhnya\n");
            } else if (is_full(&top_forward)) {
                printf("Istoriya Vpered zapovnena\n");
            } else {
                if (push(forward_stack, &top_forward, current_url)) {
                    pop(back_stack, &top_back, current_url);
                    printf("Potochna storinka: %s\n", current_url);
                }
            }
        } else if (strcmp(input, "forward") == 0) {
            if (!has_current || is_empty(&top_forward)) {
                printf("Istoriya Vpered porozhnya\n");
            } else if (is_full(&top_back)) {
                printf("Istoriya Nazad zapovnena\n");
            } else {
                if (push(back_stack, &top_back, current_url)) {
                    pop(forward_stack, &top_forward, current_url);
                    printf("Potochna storinka: %s\n", current_url);
                }
            }
        } else if (strncmp(input, "visit ", 6) == 0) {
            const char *url = input + 6;
            if (*url == '\0') {
                printf("Porozhnya adresa storinky\n");
            } else if (has_current && is_full(&top_back)) {
                printf("Istoriya Nazad zapovnena\n");
            } else {
                if (has_current) {
                    push(back_stack, &top_back, current_url);
                }
                strncpy(current_url, url, URL_LEN - 1);
                current_url[URL_LEN - 1] = '\0';
                has_current = 1;
                clear_stack(&top_forward);
                printf("Potochna storinka: %s\n", current_url);
            }
        } else {
            printf("Nevidoma komanda\n");
        }

        if (has_current) {
            printf("\nPotochna storinka: %s\n", current_url);
        } else {
            printf("\nPotochna storinka: vidsutnya\n");
        }
    }

    if (has_current) {
        printf("\nKintseva potochna storinka: %s\n", current_url);
    } else {
        printf("\nKintseva potochna storinka: vidsutnya\n");
    }

    return 0;
}