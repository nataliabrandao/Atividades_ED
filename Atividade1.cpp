#include <iostream> 
#include <chrono>
#include <cstdlib>

using std:: cin; 
using std:: cout; 
using std:: string; 
using std:: endl; 
using std:: rand; 

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

typedef struct Node 
{
    int iPayload; 
    Node* ptrNext; 
    Node* ptrPrev;

}Node;

Node* createNode(int); 
void insertFront(Node**, int); 
void insertEnd(Node**, int); 
void displayList(Node*); 
void trocaValor(Node* , Node*);
void bubblesort(Node*);
void deleteAll(Node*&); 
void optimizedBubblesort(Node*);
void selectionSort(Node*); 
void optimizedSelectionSort(Node*);
Node* createRandomList(int);

int main()
{
    Node* head = nullptr;
    
    head = createRandomList(20);

    cout << "Lista duplamente encadeada original: ";
    displayList(head);

    auto timeStart = high_resolution_clock::now();
    bubblesort(head);
    auto timeStop = high_resolution_clock::now();

    cout << "Lista duplamente encadeada ordenada utilizando bubblesort : ";
    displayList(head);

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;

    cout << "============================================" << endl;

    cout << "Lista duplamente encadeada original: ";
    displayList(head);

    timeStart = high_resolution_clock::now();
    optimizedBubblesort(head); 
    timeStop = high_resolution_clock::now();

    cout << "Lista duplamente encadeada ordenada utilizando optimizedBubblesort : ";
    displayList(head);

    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;

    cout << "============================================" << endl;

    cout << "Lista duplamente encadeada original: ";
    displayList(head);

    timeStart = high_resolution_clock::now();
    selectionSort(head); 
    timeStop = high_resolution_clock::now();

    cout << "Lista duplamente encadeada ordenada utilizando selectionSort : ";
    displayList(head);

    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;

    cout << "============================================" << endl;

    cout << "Lista duplamente encadeada original: ";
    displayList(head);

    timeStart = high_resolution_clock::now();
    optimizedSelectionSort(head); 
    timeStop = high_resolution_clock::now();

    cout << "Lista duplamente encadeada ordenada utilizando optimizedSelectionSort : ";
    displayList(head);

    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;

    deleteAll(head); 

    return 0; 
}

Node* createNode(int iPayload)
    {
        Node* temp = (Node*) malloc(sizeof(Node)); 
        temp -> iPayload = iPayload;
        temp-> ptrNext = nullptr;
        temp -> ptrPrev = nullptr; 

        return temp;
        
    }

void displayList(Node* node)
{

    if (node == nullptr)
    {
        cout << "lista vazia: não é possível display " << endl;
        return;
    }
    if (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou fim da lista : não display " << endl;
        return;
    }

    Node* temp = node;
    
    while (temp != nullptr)
    {
        cout << temp -> iPayload << " "; 
        temp = temp-> ptrNext; 
    }

    cout << endl; 
}


void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload); 

    if (*head != nullptr)
    {
        newNode -> ptrPrev = nullptr; 
        (*head) -> ptrPrev = newNode; 
        newNode -> ptrNext = (*head); 
        (*head) = newNode; 

        return; 
    }

    (*head) = newNode; 
}

void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload); 
    
    if (*head == nullptr)
    {
        newNode -> ptrPrev = nullptr; 
        (*head) = newNode; 
        return; 
    }

    Node* temp = (*head); 
    
    while(temp -> ptrNext != nullptr) temp = temp -> ptrNext;
    newNode -> ptrPrev = temp;  
    temp -> ptrNext = newNode;  
}

void deleteAll(Node*& head)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current -> ptrNext; // Salva o próximo nó antes de excluir o atual
        delete current; // Libera a memória alocada para o nó atual
        current = temp; // Move para o próximo nó
    }
    head = nullptr; // Define o ponteiro da cabeça como nullptr após limpar a lista
}


void trocaValor(Node* node1, Node* node2)
{
    int temp = node1 -> iPayload;
    node1 -> iPayload = node2 -> iPayload;
    node2 -> iPayload = temp;
}


void bubblesort(Node* head)
{
    if (head == nullptr || head->ptrNext == nullptr)
    {
        // Se a lista estiver vazia ou contiver apenas um nó, não há nada a fazer
        return;
    }

    Node* lastNode = nullptr;
    Node* firstNode = head;

    while (firstNode -> ptrNext != nullptr)
    {
       
        Node* current = head;

        while (current->ptrNext != lastNode)
        {
            if (current->iPayload > current->ptrNext->iPayload) 
            {
                trocaValor(current, current->ptrNext);
            }
            current = current->ptrNext;
        }
        
        firstNode = firstNode->ptrNext;
        lastNode = current;
    }
}

void optimizedBubblesort(Node* head)
{
    if (head == nullptr || head -> ptrNext == nullptr)
    {
        // Se a lista estiver vazia ou contiver apenas um nó, não há nada a fazer
        return;
    }

    bool unordered = false;
    Node* lastNode = nullptr;

    do
    {
        unordered = false;
        Node* current = head;

        while (current->ptrNext != lastNode)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                trocaValor(current, current->ptrNext);
                unordered = true;
            }
            current = current->ptrNext;
        }
        // O último nó (atualmente) não precisa ser considerado na próxima iteração
        lastNode = current;

    } while (unordered);
}

void selectionSort(Node* head)
{
    if (head == nullptr || head -> ptrNext == nullptr)
    {
        // Se a lista estiver vazia ou contiver apenas um nó, não há nada a fazer
        return;
    }

    Node* current = head; // Começamos do nó inicial da lista

    while (current != nullptr)
    { // Enquanto não chegarmos ao final da lista
        Node* start = current->ptrNext; // Marca o início da iteração atual 

        while (start != nullptr ) { // Enquanto não chegarmos ao final da lista
            if (current->iPayload > start->iPayload)
            {
                trocaValor(current, start);
            }
            start = start->ptrNext; // Avançar para o próximo nó
        } 
        current = current->ptrNext; // Avançar para o próximo nó para a próxima iteração
    }
}



void optimizedSelectionSort(Node* head) {
   if (head == nullptr || head->ptrNext == nullptr)
    {
        // Se a lista estiver vazia ou contiver apenas um nó, não há nada a fazer
        return;
    }

    Node* current = head; // Ponteiro para o início da lista não ordenada
    bool bOrdered; // Variável para verificar se a lista está ordenada

    while (current->ptrNext != nullptr && !bOrdered)
    { // Enquanto houver elementos não ordenados e a lista não estiver ordenada
        bOrdered = true; // Supõe que a lista está ordenada nesta iteração
        Node* minNode = current; // Inicialmente, consideramos o nó atual como o mínimo 

        // Encontrar o nó com o menor valor a partir do nó atual
        Node* temp = current->ptrNext;
        while (temp != nullptr)
        {
            if (temp->iPayload < minNode->iPayload)
            {
                minNode = temp;
               bOrdered = false; // Se houver algum elemento menor, a lista não está ordenada
            }
            temp = temp->ptrNext;
        }

        // Trocar os valores entre o nó atual e o nó com o menor valor
        if (minNode != current)
        {
            trocaValor(current, minNode);
        }

        // Avançar para o próximo elemento não ordenado
        current = current->ptrNext;
    }
}

// Função para criar e retornar uma lista com elementos aleatórios
Node* createRandomList(int numElements) {
    Node* head = nullptr;
    //srand(time(nullptr)); // Semente para a função rand() baseada no tempo atual

    for (int i = 0; i < numElements; i++) {
        insertEnd(&head, rand() % 100); // Gera números aleatórios entre 0 e 99
    }

    return head;
}