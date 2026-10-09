typedef struct AVL_Tree_t {
    long long key;
    int height;
    int size;
    struct AVL_Tree_t *left;
    struct AVL_Tree_t *right;
} AVL_Tree_t;

typedef struct pool_t {
    AVL_Tree_t *pool;
    int *index;
} pool_t;

pool_t link_pool(AVL_Tree_t *pool, int *index) {
    static pool_t pool_str;
    if (!pool) return pool_str;
    pool_str.pool = pool;
    pool_str.index = index;
    return pool_str;
}

AVL_Tree_t* create_node(long long key) {
    pool_t pool = link_pool(NULL, NULL);
    AVL_Tree_t *new_node = pool.pool + (*pool.index)++;
    new_node->key = key;
    new_node->height = 1;
    new_node->size = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int get_size(AVL_Tree_t *root) {
    if (!root) return 0;
    return root->size;
}

int get_height(AVL_Tree_t *root) {
    if (!root) return 0;
    return root->height;
}

void fix_height(AVL_Tree_t *root) {
    if (!root) return;
    root->height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));
}

AVL_Tree_t* rotate_left(AVL_Tree_t *root) {
    int root_count = root->size - get_size(root->left) - get_size(root->right);
    AVL_Tree_t *new_root = root->right;
    int new_root_count = new_root->size - get_size(new_root->left) - get_size(new_root->right);
    root->right = new_root->left;
    new_root->left = root;
    root->size = root_count + get_size(root->left) + get_size(root->right);
    new_root->size = new_root_count + get_size(new_root->left) + get_size(new_root->right);
    fix_height(root);
    fix_height(new_root);
    return new_root;
}

AVL_Tree_t* rotate_right(AVL_Tree_t *root) {
    int root_count = root->size - get_size(root->left) - get_size(root->right);
    AVL_Tree_t *new_root = root->left;
    int new_root_count = new_root->size - get_size(new_root->left) - get_size(new_root->right);
    root->left = new_root->right;
    new_root->right = root;
    root->size = root_count + get_size(root->left) + get_size(root->right);
    new_root->size = new_root_count + get_size(new_root->left) + get_size(new_root->right);
    fix_height(root);
    fix_height(new_root);
    return new_root;
}

AVL_Tree_t* insert(AVL_Tree_t *root, long long key) {
    if (!root) return create_node(key);
    if (root->key == key) {
        root->size++;
        return root;
    }
    if (root->key < key) {
        root->size++;
        root->right = insert(root->right, key);
    }
    else {
        root->size++;
        root->left = insert(root->left, key);
    }
    int balance = get_height(root->left) - get_height(root->right);
    if (-1 <= balance && balance <= 1) {
        fix_height(root);
        return root;
    }
    else if (balance == -2) {
        int subtree_balance = get_height(root->right->left) - get_height(root->right->right);
        if (subtree_balance == 1) {
            root->right = rotate_right(root->right);
        }
        root = rotate_left(root);
    }
    else {
        int subtree_balance = get_height(root->left->left) - get_height(root->left->right);
        if (subtree_balance == -1) {
            root->left = rotate_left(root->left);
        }
        root = rotate_right(root);
    }
    return root;
}

int count_not_greater(AVL_Tree_t *root, long long key) {
    if (!root) return get_size(root);
    if (root->key > key) return count_not_greater(root->left, key);
    if (root->key == key) return get_size(root) - get_size(root->right);
    return get_size(root) - get_size(root->right) + count_not_greater(root->right, key);
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long long prefix = 0;
    int res = 0;
    AVL_Tree_t node_pool[numsSize + 1];
    int pool_index = 0;
    link_pool(node_pool, &pool_index);
    AVL_Tree_t *processed_prefixes = create_node(0);
    for (int i = 0; i < numsSize; ++i) {
        prefix += nums[i];
        int x = count_not_greater(processed_prefixes, prefix - lower);
        int y = count_not_greater(processed_prefixes, prefix - upper - 1);
        res += x - y;
        processed_prefixes = insert(processed_prefixes, prefix);
    }
    return res;
}