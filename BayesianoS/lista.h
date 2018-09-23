#define TRUE 1
#define FALSE 0

struct Node{
    int id;
    char* nombre;
    struct Node* sig;
    double probabilidad;
    int cardinalidad; 
};

typedef struct Node NODE;
typedef NODE *lista;

lista empty()
{
    return NULL;
}

int isEmpty(lista l)
{
    return l == NULL;
}

int cardinalidad(lista l)
{
    if(isEmpty(l))
        return 0;
    else
        return cardinalidad(l->sig)+1;
}

NODE* createNode(char* name )
{
    int i = 0;
    NODE* newNodo = NULL;
    newNodo = (NODE*) malloc(sizeof(struct Node));

    if(!newNodo)
    {
        perror("Error al asignar espacio de memoria");
        exit(EXIT_FAILURE);
    }else{
        while(name[i] != '\0')
            i++;
        newNodo->nombre = (char*) malloc(sizeof(char)*(i+1));
        i = 0;
        while(name[i] != '\0')
        {
            newNodo->nombre[i] = name[i];
            i++;
        }
        newNodo->nombre[i] = '\0';
        newNodo->id = 0;
        newNodo->sig = NULL;
        return newNodo;
    }
}

void insert(lista* l, char name[] )
{
    NODE* newNodo = NULL;
    lista auxList = NULL;
    newNodo = createNode(name);
    if( isEmpty(*l))
    {
        *l = newNodo;
    }
    else
    {
        auxList = *l;
        newNodo->id = cardinalidad(*l);
        while(auxList->sig != NULL)
        {
            auxList = auxList->sig;
        }
        auxList->sig = newNodo;
    }   
}

void delete(lista* l)
{
    while(*l != NULL)
    {
        NODE* aux = (*l)->sig;
        free(*l);
        *l = aux;
    }
}

void modify(lista* l, int indice, int cardi, double prob)
{
    register int i = 0;
    NODE* auxList = *l;
    
    for (i = 0; i < indice; i++)
        auxList = auxList->sig;

    auxList->cardinalidad = cardi;
    auxList->probabilidad = prob;
}

void printList(lista l)
{
    printf("Clase\tnombre\t   Cardinalidad\t Probabilidad\n");
    while(l != NULL)
    {
        printf("%d\t%s    \t%d\t    %.3f\n",l->id,l->nombre,l->cardinalidad,l->probabilidad);
        l = l->sig;
    }
}

NODE* getNode(lista l, int indice)
{
    register int i = 0;
    NODE* newNodo = NULL;
            
    newNodo = l;

    for (i = 0; i < indice; i++)
        newNodo = newNodo->sig;
    
    return newNodo;
}
