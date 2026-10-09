
typedef struct Node {
    char *dest;
    struct Node *next;
} Node;

typedef struct List {
    char *key;
    Node *head;
    Node *tail;
    struct List *next; 
} List;

typedef struct {
    List **lists;
    int size;
    int capacity;
} HashMap;


typedef struct {
    char **data;
    int size;
    int capacity;
} Vector;

HashMap* createHashMap(int capacity) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->lists = (List **)calloc(capacity, sizeof(List *));
    map->size = 0;
    map->capacity = capacity;
    return map;
}

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

List* getList(HashMap *map, const char *key) {
    unsigned int index = hash(key) % map->capacity;
    List *list = map->lists[index];
    while (list) {
        if (strcmp(list->key, key) == 0) return list;
        list = list->next;
    }
    return NULL;
}

void insert(HashMap *map, const char *key, const char *dest) {
    unsigned int index = hash(key) % map->capacity;
    List *list = getList(map, key);
    if (!list) {
        list = (List *)malloc(sizeof(List));
        list->key = strdup(key);
        list->head = list->tail = NULL;
        list->next = map->lists[index];
        map->lists[index] = list;
        map->size++;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    node->dest = strdup(dest);
    node->next = NULL;

    if (!list->head) {
        list->head = list->tail = node;
    } else {
        Node *prev = NULL, *curr = list->head;
        while (curr && strcmp(curr->dest, dest) <= 0) {
            prev = curr;
            curr = curr->next;
        }
        if (!prev) {
            node->next = list->head;
            list->head = node;
        } else {
            node->next = curr;
            prev->next = node;
        }
        if (!node->next) {
            list->tail = node;
        }
    }
}

void initVector(Vector *vec, int capacity) {
    vec->data = (char **)malloc(capacity * sizeof(char *));
    vec->size = 0;
    vec->capacity = capacity;
}

void pushBack(Vector *vec, const char *str) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (char **)realloc(vec->data, vec->capacity * sizeof(char *));
    }
    vec->data[vec->size++] = strdup(str);
}

void dfs(HashMap *map, const char *node, Vector *result) {
    List *list = getList(map, node);
    while (list && list->head) {
        Node *nextNode = list->head;
        list->head = list->head->next;
        if (!list->head) list->tail = NULL;
        dfs(map, nextNode->dest, result);
        free(nextNode->dest);
        free(nextNode);
    }
    pushBack(result, node);
}

char** findItinerary(char ***tickets, int ticketsSize, int *ticketsColSize, int *returnSize) {
    HashMap *map = createHashMap(1000);
    for (int i = 0; i < ticketsSize; ++i) {
        insert(map, tickets[i][0], tickets[i][1]);
    }
    Vector result;
    initVector(&result, 1000);
    dfs(map, "JFK", &result);
    for (int i = 0; i < result.size / 2; ++i) {
        char *temp = result.data[i];
        result.data[i] = result.data[result.size - i - 1];
        result.data[result.size - i - 1] = temp;
    }
    *returnSize = result.size;
    return result.data;
}