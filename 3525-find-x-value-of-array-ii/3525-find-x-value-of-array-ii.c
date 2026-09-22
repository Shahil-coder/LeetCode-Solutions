#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int prod;
    int* cnt;
} Node;

typedef struct {
    int* tree_prod;
    int* tree_cnt;
    int n;
    int k;
} SegmentTree;

Node create_node(int k) {
    Node node;
    node.prod = 1;
    node.cnt = (int*)calloc(k, sizeof(int));
    return node;
}

void free_node(Node* node) {
    if (node->cnt) {
        free(node->cnt);
        node->cnt = NULL;
    }
}

Node merge_nodes(Node left, Node right, int k) {
    Node res = create_node(k);
    res.prod = (left.prod * right.prod) % k;
    
    for (int r = 0; r < k; r++) {
        res.cnt[r] = left.cnt[r];
    }
    
    for (int r = 0; r < k; r++) {
        if (right.cnt[r] > 0) {
            int rem = (left.prod * r) % k;
            res.cnt[rem] += right.cnt[r];
        }
    }
    
    return res;
}

void build(SegmentTree* st, int* nums, int node, int l, int r) {
    int k = st->k;
    if (l == r) {
        int val = nums[l] % k;
        st->tree_prod[node] = val;
        memset(&st->tree_cnt[node * k], 0, k * sizeof(int));
        st->tree_cnt[node * k + val] = 1;
        return;
    }
    int mid = l + (r - l) / 2;
    build(st, nums, 2 * node + 1, l, mid);
    build(st, nums, 2 * node + 2, mid + 1, r);
    
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    
    st->tree_prod[node] = (st->tree_prod[left_node] * st->tree_prod[right_node]) % k;
    
    int* p_cnt = &st->tree_cnt[node * k];
    int* l_cnt = &st->tree_cnt[left_node * k];
    int* r_cnt = &st->tree_cnt[right_node * k];
    
    for (int r_idx = 0; r_idx < k; r_idx++) {
        p_cnt[r_idx] = l_cnt[r_idx];
    }
    
    for (int r_idx = 0; r_idx < k; r_idx++) {
        if (r_cnt[r_idx] > 0) {
            int rem = (st->tree_prod[left_node] * r_idx) % k;
            p_cnt[rem] += r_cnt[r_idx];
        }
    }
}

void update(SegmentTree* st, int node, int l, int r, int idx, int val) {
    int k = st->k;
    if (l == r) {
        int v = val % k;
        st->tree_prod[node] = v;
        memset(&st->tree_cnt[node * k], 0, k * sizeof(int));
        st->tree_cnt[node * k + v] = 1;
        return;
    }
    int mid = l + (r - l) / 2;
    if (idx <= mid) {
        update(st, 2 * node + 1, l, mid, idx, val);
    } else {
        update(st, 2 * node + 2, mid + 1, r, idx, val);
    }
    
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    
    st->tree_prod[node] = (st->tree_prod[left_node] * st->tree_prod[right_node]) % k;
    
    int* p_cnt = &st->tree_cnt[node * k];
    int* l_cnt = &st->tree_cnt[left_node * k];
    int* r_cnt = &st->tree_cnt[right_node * k];
    
    for (int r_idx = 0; r_idx < k; r_idx++) {
        p_cnt[r_idx] = l_cnt[r_idx];
    }
    
    for (int r_idx = 0; r_idx < k; r_idx++) {
        if (r_cnt[r_idx] > 0) {
            int rem = (st->tree_prod[left_node] * r_idx) % k;
            p_cnt[rem] += r_cnt[r_idx];
        }
    }
}

Node query(SegmentTree* st, int node, int l, int r, int ql, int qr) {
    int k = st->k;
    if (ql <= l && r <= qr) {
        Node res = create_node(k);
        res.prod = st->tree_prod[node];
        memcpy(res.cnt, &st->tree_cnt[node * k], k * sizeof(int));
        return res;
    }
    int mid = l + (r - l) / 2;
    if (qr <= mid) {
        return query(st, 2 * node + 1, l, mid, ql, qr);
    }
    if (ql > mid) {
        return query(st, 2 * node + 2, mid + 1, r, ql, qr);
    }
    Node left = query(st, 2 * node + 1, l, mid, ql, qr);
    Node right = query(st, 2 * node + 2, mid + 1, r, ql, qr);
    Node res = merge_nodes(left, right, k);
    free_node(&left);
    free_node(&right);
    return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultArray(int* nums, int numsSize, int k, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    SegmentTree st;
    st.n = numsSize;
    st.k = k;
    st.tree_prod = (int*)malloc(4 * numsSize * sizeof(int));
    st.tree_cnt = (int*)calloc(4 * numsSize * k, sizeof(int));
    
    build(&st, nums, 0, 0, numsSize - 1);
    
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int idx = queries[i][0];
        int val = queries[i][1];
        int start = queries[i][2];
        int x = queries[i][3];
        
        update(&st, 0, 0, numsSize - 1, idx, val);
        Node res = query(&st, 0, 0, numsSize - 1, start, numsSize - 1);
        result[i] = res.cnt[x];
        free_node(&res);
    }
    
    free(st.tree_prod);
    free(st.tree_cnt);
    return result;
}