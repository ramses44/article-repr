#include <stdlib.h>
#include "common.c"

typedef struct BNode {
    elem_t data;
    struct BNode* left;
    struct BNode* right;
    short height;
} balanced_tree_node;

short height(balanced_tree_node* p) {
	return p ? p->height : 0;
}

short bfactor(balanced_tree_node* p) {
	return height(p->right) - height(p->left);
}

void setheight(balanced_tree_node* p) {
	short hl = height(p->left);
	short hr = height(p->right);

	p->height = (hl > hr ? hl : hr) + 1;
}

balanced_tree_node* rotateright(balanced_tree_node* p) {
	balanced_tree_node* q = p->left;
	p->left = q->right;
	q->right = p;

	setheight(p);
	setheight(q);

	return q;
}

balanced_tree_node* rotateleft(balanced_tree_node* q) {
	balanced_tree_node* p = q->right;
	q->right = p->left;
	p->left = q;

	setheight(q);
	setheight(p);

	return p;
}

balanced_tree_node* balance(balanced_tree_node* p) {
	setheight(p);

	if (bfactor(p) == 2) {
		if (bfactor(p->right) < 0) {
			p->right = rotateright(p->right);
        }
		return rotateleft(p);
	}

	if (bfactor(p) == -2) {
		if (bfactor(p->left) > 0) {
			p->left = rotateleft(p->left);
        }
		return rotateright(p);
	}

	return p;
}

balanced_tree_node* insert_at(balanced_tree_node* p, elem_t data) {
	if (!p) {
        balanced_tree_node* new_node = malloc(sizeof(*new_node));
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

	if (compare(data, p->data) < 0) {
		p->left = insert_at(p->left, data);
    } else {
		p->right = insert_at(p->right, data);
    }

	return balance(p);
}

balanced_tree_node* findmin(balanced_tree_node* p) {
	return p->left ? findmin(p->left) : p;
}

balanced_tree_node* popmin(balanced_tree_node* p) {
	if (p->left == 0) {
		return p->right;
    }

	p->left = popmin(p->left);

	return balance(p);
}

balanced_tree_node* delete_at(balanced_tree_node* p, elem_t data) {
	if (!p) {
        return NULL;
    }

	if (compare(data, p->data) < 0) {
		p->left = delete_at(p->left, data);
    } else if (compare(data, p->data) > 0) {
		p->right = delete_at(p->right, data);	
    } else {
		balanced_tree_node* q = p->left;
		balanced_tree_node* r = p->right;

		free(p);

		if (!r) {
            return q;
        }

		balanced_tree_node* min = findmin(r);
		min->right = popmin(r);
		min->left = q;

		return balance(min);
	}

    return balance(p);
}