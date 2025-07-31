#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char* title[100];
    char* artist[100];
    float duration;
    struct Node *left;
    struct Node *right;
}Song;

Song* createSong(char title[],char artist[],float duration) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->left = newSong->right = NULL;
    return newSong;
}
Song* insertSong(Song* root,char title[], char artist[], float duration) {
    if (root == NULL) return createSong(title, artist, duration);
    int cmp = strcmp(title, root->title);
    if (cmp < 0)
        root->left = insertSong(root->left, title, artist, duration);
    else if (cmp > 0)
        root->right = insertSong(root->right, title, artist, duration);
    else
        printf("\n");
    return root;
}

void inorderDisplay(Song* root) {
    if (root == NULL) return;
    inorderDisplay(root->left);
    printf("Title:%s, Artist:%s, Duration: %f minutes",root->title,root->artist,root->duration);
    inorderDisplay(root->right);
}
Song* searchSong (Song* root,char title[]) {
    if (root == NULL) return NULL;
    int compare=strcmp(title, root->title);
    if (compare==0) {
        return root;
    }
    else if (compare <0) {
        return searchSong(root->left,title);
    }else {
        return searchSong(root->right,title);
    }
}
Song* deleteSong(Song* root,char title[]) {

}
void freeTree(Song* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}



int main(void) {
    Song *root = NULL;
    int choice;
    char title[100], artist[50];
    float duration;
    do {
        printf("\n**********MENU**********\n");
        printf("1. Insert Song\n");
        printf("2. Print Song\n");
        printf("3. Search Song\n");
        printf("4. Delete Song\n");
        printf("5.Clculate Total Duration\n");
        printf("6.Exit\n");
        printf(" Enter your choice: ");
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 1: {
                printf("enter title:");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("enter artist:");
                fgets(artist, 50, stdin);
                artist[strcspn(artist, "\n")] = 0;
                printf("enter duration:");
                scanf("%f", &duration);
                root=insertSong(root,title,artist,duration);
                break;
            }
            case 2: {
                if (root==NULL) printf("khong tim thay bai hat");
                inorderDisplay(root);
                break;
            }
             case 3: {
            printf("enter title you want search:");
            fgets(title, 100, stdin);
            title[strcspn(title, "\n")] = 0;
            Song* found = searchSong(root, title);
            if (found == NULL)
                printf("khong tim thay bai hat\n");
            else
                printf("title: %s , Artist: %s , Duration: %.2f mi nit\n", found->title, found->artist, found->duration);
            break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                freeTree(root);
                printf("da thoat chuong trinh");
                break;
            }
            default : {
            printf("lua chon khong hop le vui long chon lai");
            }
        }
    }while (choice != 6);


    return 0;
}