#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char command[100];
    struct Node *next;
} Node;

Node* createNode(char command[100]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->command, command);
    newNode->next = NULL;
    return newNode;
}

void push(Node** stack, char command[100]) {
    Node* newNode = createNode(command);
    newNode->next = *stack;
    *stack = newNode;
}

// Trả về chuỗi command, cần malloc và trả về con trỏ để dùng ngoài
char* pop(Node** stack) {
    if (*stack == NULL) return NULL;

    Node* temp = *stack;
    *stack = (*stack)->next;

    char* command = (char*)malloc(100);
    strcpy(command, temp->command);
    free(temp);

    return command;
}

char* peek(Node* stack) {
    if (stack == NULL) return NULL;
    return stack->command;
}

void printStack(Node* stack) {
    Node* current = stack;
    if (!current) {
        printf("khong co lenh nao duoc thuc hien\n");
        return;
    }
    printf("danh sach lenh da duoc thuc hien:\n");
    while (current) {
        printf("- %s\n", current->command);
        current = current->next;
    }
}

void clearStack(Node** stack) {
    while (*stack != NULL) {
        Node* temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}

int main() {
    int choice;
    Node *redoStack = NULL;
    Node *executedStack = NULL;
    char command[100];

    do {
        printf("\n**********MENU**********\n");
        printf("1. them lenh moi\n");
        printf("2. hoan tac lenh\n");
        printf("3. phuc hoi lenh\n");
        printf("4. xem lenh hien tai\n");
        printf("5. danh sach lenh da thuc hien\n");
        printf("6. lam moi lich su\n");
        printf("7. thoat\n");
        printf("enter your choice : ");
        scanf("%d", &choice);
        getchar(); // bỏ ký tự newline sau scanf

        switch (choice) {
            case 1: {
                printf("Enter your command: ");
                fgets(command, 100, stdin);
                command[strcspn(command, "\n")] = '\0';
                push(&executedStack, command);
                clearStack(&redoStack);
                printf("da them lenh: %s\n", command);
                break;
            }
            case 2: {
                if (executedStack == NULL) {
                    printf("khong co lenh de hoan tac\n");
                } else {
                    char* undone = pop(&executedStack);
                    push(&redoStack, undone);
                    printf("da hoan tac lenh: %s\n", undone);
                    free(undone);
                }
                break;
            }
            case 3: {
                if (redoStack == NULL) {
                    printf("khong co lenh de phuc hoi\n");
                } else {
                    char* redone = pop(&redoStack);
                    push(&executedStack, redone);
                    printf("da phuc hoi lenh: %s\n", redone);
                    free(redone);
                }
                break;
            }
            case 4: {
                char* currentCommand = peek(executedStack);
                if (currentCommand == NULL) {
                    printf("khong co lenh hien tai\n");
                } else {
                    printf("lenh hien tai: %s\n", currentCommand);
                }
                break;
            }
            case 5: {
                printStack(executedStack);
                break;
            }
            case 6: {
                clearStack(&executedStack);
                clearStack(&redoStack);
                printf("da lam moi lich su lenh\n");
                break;
            }
            case 7: {
                clearStack(&executedStack);
                clearStack(&redoStack);
                printf("thoat chuong trinh thanh cong\n");
                break;
            }
            default: {
                printf("du lieu nhap vao khong hop le, vui long nhap lai\n");
            }
        }
    } while (choice != 7);

    return 0;
}
