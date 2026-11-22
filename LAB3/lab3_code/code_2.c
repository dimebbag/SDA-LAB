#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_LEN 100

typedef struct NodeTag {
    char url[URL_LEN];
    struct NodeTag *next;
} Node;

Node *back_stack = NULL;
Node *forward_stack = NULL;

int is_empty(const Node *top) {
    return top == NULL;
}

int is_full(void) {
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL) {
        return 1;
    }
    free(temp);
    return 0;
}

int push(Node **top, const char url[]) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Pomylka vydilennya pam'yati\n");
        return 0;
    }
    strncpy(new_node->url, url, URL_LEN - 1);
    new_node->url[URL_LEN - 1] = '\0';
    new_node->next = *top;
    *top = new_node;
    return 1;
}

int pop(Node **top, char url[]) {
    if (*top == NULL) {
        return 0;
    }
    Node *temp = *top;
    strncpy(url, temp->url, URL_LEN - 1);
    url[URL_LEN - 1] = '\0';
    *top = temp->next;
    free(temp);
    return 1;
}

int peek(const Node *top, char url[]) {
    if (top == NULL) {
        return 0;
    }
    strncpy(url, top->url, URL_LEN - 1);
    url[URL_LEN - 1] = '\0';
    return 1;
}

void clear_stack(Node **top) {
    char temp_url[URL_LEN];
    while (pop(top, temp_url)) {
    }
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
            if (!has_current || is_empty(back_stack)) {
                printf("Istoriya Nazad porozhnya\n");
            } else if (is_full()) {
                printf("Nedostatnyo pam'yati\n");
            } else {
                if (push(&forward_stack, current_url)) {
                    pop(&back_stack, current_url);
                    printf("Potochna storinka: %s\n", current_url);
                }
            }
        } else if (strcmp(input, "forward") == 0) {
            if (!has_current || is_empty(forward_stack)) {
                printf("Istoriya Vpered porozhnya\n");
            } else if (is_full()) {
                printf("Nedostatnyo pam'yati\n");
            } else {
                if (push(&back_stack, current_url)) {
                    pop(&forward_stack, current_url);
                    printf("Potochna storinka: %s\n", current_url);
                }
            }
        } else if (strncmp(input, "visit ", 6) == 0) {
            const char *url = input + 6;
            if (*url == '\0') {
                printf("Porozhnya adresa storinky\n");
            } else if (is_full()) {
                printf("Nedostatnyo pam'yati\n");
            } else {
                if (has_current) {
                    push(&back_stack, current_url);
                }
                strncpy(current_url, url, URL_LEN - 1);
                current_url[URL_LEN - 1] = '\0';
                has_current = 1;
                clear_stack(&forward_stack);
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

    clear_stack(&back_stack);
    clear_stack(&forward_stack);

    return 0;
}
