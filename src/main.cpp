#include <SDL.h>

#include <stdio.h>

#include <stdlib.h>

#include<SDL_ttf.h>

 

// Structure pour représenter un nœud de la liste doublement chaînée

struct Node {

    int data;

    struct Node* prev;

    struct Node* next;

};

 

// Fonction pour créer un nouveau nœud

struct Node* createNode(int data) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;

    newNode->prev = NULL;

    newNode->next = NULL;

    return newNode;

}

 

// Fonction pour ajouter un nœud à la fin de la liste doublement chaînée

void appendNode(struct Node** headRef, int data) {

    struct Node* newNode = createNode(data);

    if (*headRef == NULL) {

        *headRef = newNode;

    } else {

        struct Node* current = *headRef;

        while (current->next != NULL) {

            current = current->next;

        }

        current->next = newNode;

        newNode->prev = current;

    }

}

 

// Fonction pour échanger les données de deux nœuds

void swapData(struct Node* node1, struct Node* node2) {

    int temp = node1->data;

    node1->data = node2->data;

    node2->data = temp;

}

 

 

//fonction pour afficher la valeurs dans les rectangles

void renderText(SDL_Renderer* renderer, TTF_Font* font, int x, int y, const char* text) {

    SDL_Color color = {0, 0, 0, 255}; // Couleur du texte (noir dans cet exemple)

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

 

    SDL_Rect rect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &rect);

 

    SDL_FreeSurface(surface);

    SDL_DestroyTexture(texture);

}

 

 

// Fonction pour trier la liste doublement chaînée par sélection

void selectionSort(struct Node* head, SDL_Renderer* renderer, SDL_Window* window) {

    struct Node *i, *j, *minNode;

 

    for (i = head; i != NULL; i = i->next) {

        minNode = i;

 

        for (j = i->next; j != NULL; j = j->next) {

            if (j->data < minNode->data) {

                minNode = j;

            }

        }

 

        // Échanger les données des nœuds

        swapData(i, minNode);

 

        // Afficher la liste à chaque étape du tri

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

 

        struct Node* current = head;

        int xPos = 200;

 

        while (current != NULL) {

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

            SDL_Rect rect = {xPos, 300 - current->data * 10, 20, current->data * 10};

            SDL_RenderFillRect(renderer, &rect);//la couleur dans lesrectongles

            // Afficher la valeur du nœud

            char nodeValue[10];

           

            snprintf(nodeValue, sizeof(nodeValue), "%d", current->data);

            renderText(renderer, font, xPos + 5, 300 - current->data * 10 - 20, nodeValue);

            xPos += 30;

            current = current->next;

        }

 

        SDL_RenderPresent(renderer);

        SDL_Delay(500); // Attendre 500 millisecondes entre chaque étape

    }

}

 

int main(int argc,char*argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

 

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

 

    // Création d'une liste doublement chaînée non triée

    struct Node* head = NULL;

    appendNode(&head, 4);

    appendNode(&head, 2);

    appendNode(&head, 7);

    appendNode(&head, 1);

    appendNode(&head, 8);

    appendNode(&head, 1);

    appendNode(&head, 21);

    appendNode(&head, 5);

    appendNode(&head, 9);

    appendNode(&head, 19);

     appendNode(&head, 5);

    appendNode(&head, 30);

    appendNode(&head, 60);

    appendNode(&head, 0);

    appendNode(&head, 8);

    appendNode(&head, 7);

    appendNode(&head, 33);

    appendNode(&head, 12);

    appendNode(&head, 90);

    appendNode(&head, 100);

 

 

    printf("Liste doublement chaînée non triée\n");

 

    // Afficher la liste avant le tri

    struct Node* current = head;

    while (current != NULL) {

        printf("%d ", current->data);

        current = current->next;

    }

    printf("\n");

 

    // Tri par sélection avec visualisation

    selectionSort(head, renderer, window);

 

    printf("Liste doublement chaînée triée\n");

 

    // Afficher la liste après le tri

    current = head;

    while (current != NULL) {

        printf("%d ", current->data);

        current = current->next;

    }

    printf("\n");

 

    // Attendre que l'utilisateur ferme la fenêtre

    SDL_Delay(2000);

        int quit = 0;

    SDL_Event e;

 

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {

                quit = 1;

            }

        }

    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

 

    return 0;

}
}
