#include "RedBlackTree.h"

/**
 * This function copies the @param node into pointer to @param other recursively
 * The @param other stores the actual pointer to the nodes rather than a copy of the
 * pointer to the node
 * */
void RedBlackTree::copy(RBTNode *node, RBTNode** other) {
    if(node == nullptr) {
        return;
    }

    /**
     * The node at first points to the root of the rbt from where we are copying
     * The other points to the pointer on the tree where we are copying to 
     * Here, we make changes to the pointer to "other" because this will change, i.e.
     * the root node of the rbt where we are copying to.
     * 
     * If we had only passed @param other as pointer to the RBTNode then making changes
     * to the pointer @param other would only change the copy of the root node rather than
     * making changes to that exact root node
     * 
     * For example:
     * Let rbt1 be the Red-Black Tree we are copying from, and rbt2 be the Red-Black Tree
     * where we are copying to
     *              rbt1 = *B4
     *                   /  \
     *                *R4   *R5
     * and we are to copy it to rbt2, intially rbt2 = nullptr;
     * When we make copy we pass the root i.e. nullptr, we pass the address of nullptr
     * rather than the nullptr. Thus, when we make changes to the *other it changes the
     * root node of rbt2 rather than the copy of rbt2's root.
     * 
     * rbt2 = RedBlackTree(rbt1);
     * 
     * // In copy constructor
     *          RedBlackTree::copy(rbt1.root, &rbt2->root)
     * 
     * In staic copy function,
     *          Initially, node = rb1.root
     *                     other = &rbt2.root (&nullptr)
     * When the program reaches this step, the pointer that other points to changes to contain
     * a new RBTNode with color and value equal to the @param node's (rbt1.root) values
     * This causes the rbt2's root to now be a pointer to a RBTNode with values equal to that of
     * rbt1
     *     Thus changed rbt2 = *B4
     * If @param other were passed as only a pointer it wouldn't be able to change the
     * root in actual tree for this case
     * This is then recursively performed for the right and the left half with them also
     * being passed as the pointer to RBTNode pointer for the same reason.
     * 
     * After right recursion,
     *                  rbt2 = *R4
     *                            \
     *                             *R5
     * After the left recursion,
     *                  rbt2 = *R4
     *                        /   \
     *                    *R3      *R5
     */
    *other = new RBTNode{.color = node->color, .value = node->value};

    RedBlackTree::copy(node->right, &(*other)->right);
    RedBlackTree::copy(node->left, &(*other)->left);
}

RedBlackTree::RedBlackTree(const RedBlackTree &other) {
    if(other.root) {
        RedBlackTree::copy(other.root, &this->root);
    }
    this->numItems = other.numItems;
}

/**
 * Checks if a value is contained in the Red-Black Tree
 * @param value : the value to be checked for entry in RBT
 * @return bool
 */
bool RedBlackTree::Contains(int value) const {
    RBTNode* curr = this->root;

    while(curr != nullptr) {
        if(curr->value == value) {
            return true;
        } else if (curr->value < value) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return false;
}

/**
 * Gets the maximum value in the Red-Black Tree
 * @return (int) the maximum value in the Red-Black Tree
 */
int RedBlackTree::GetMax() const {
    RBTNode* curr = this->root;

    while(curr->right != nullptr) {
        curr = curr->right;
    }

    return curr->value;
}

/**
 * Gets the minimum value in the Red-Black Tree
 * @return (int) the minimum value in the Red-Black Tree
 */
int RedBlackTree::GetMin() const {
    RBTNode* curr = this->root;

    while(curr->left != nullptr) {
        curr = curr->left;
    }

    return curr->value;
}

/**
 * Returns the numbers of nodes in the Red-Black Tree
 */
unsigned  int RedBlackTree::Size() const {
    return this->numItems;
}

/**
 * Inserts a value into the RedBlack tree
 * @param value : the int value to be inserted
 * @param inserted : contains the value that is just inserted into the RedBlack Tree
 *
 * The function also provides pointer to the returned value in the argument pointer @param inserted
 *
 * For example:
 * Let a Red-Black tree be in the following situation,
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
                                               rbt = *B5
                                                     / \
                                                   *B3  *B8
                                                     \     \
                                                     *R4   *R12
 * If we perform RedBlackTree::BinaryInsert(9, &inserted), where inserted is a pointer that currently points to nullptr
 * When 9 is inserted, the tree becomes:
                                              rbt = *B5
                                                   /   \
                                                *B3     *B8
                                                   \       \
                                                    *R4     *R12
                                                           /
                                                        *R9
 * This function only inserts the value based on the Binary Search Tree condition and doesn't perform the balancing.
 * After the insertion, @param inserted points to the position of the currently inserted node.
 * Thus after RedBlackTree::BinaryInsert(9, &inserted), inserted points to R9, i.e. inserted == *R9.
 */
void RedBlackTree::BinaryInsert(int value, RBTNode** inserted) {
    RBTNode** curr = &(this->root);

    while(*curr != nullptr) {
        if((*curr)->value < value) {
            curr = &((*curr)->right);
        } else {
            curr = &((*curr)->left);
        }
    }

    *curr = new RBTNode{.value = value};
    *inserted = *curr;
}

// I think this should take a node as well, to let to know where it is removing from :)
// TODO: Add a node argument in the function definition
void RedBlackTree::BinaryRemove(int value, RBTNode* from) {
    RBTNode* curr = from;
    bool right = false;

    while(curr != nullptr) {
        if(curr->value == value) {
            break;
        } else if (curr->value < value) {
            curr = curr->right;
            right = true;
        } else {
            curr = curr->left;
            right = false;
        }
    }

    if(curr->left == nullptr && curr->right == nullptr) {
        RBTNode* parent = nullptr;
        this->get_parent(curr, &parent);

        cout << "here" << endl;

        if(right) {
            parent->right = nullptr;
        } else {
            parent->left = nullptr; 
        }

        delete curr;
    } else if (curr->left == nullptr || curr->right == nullptr) {
        RBTNode* replacement = curr->left == nullptr ? curr->right : curr->left;

        RBTNode* parent = nullptr;
        this->get_parent(curr, &parent);

        if(right) {
            parent->right = replacement;
        } else {
            parent->left = replacement;
        }

        delete curr;
    } else {
        RBTNode* successor = curr->right;
        while(successor->left != nullptr) {
            successor = successor->left;
        }
        int val = successor->value;
        this->BinaryRemove(successor->value, successor);
        curr->value = val;
    }
}

/**
 * Returns the parent of the current node
 * @param node : the node whose parent is to found
 * @param parent : the parent is stored in this pointer to a pointer
 * For example:
 * If we have a Red-Black tree with following representation:
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
 *                                                rbt = *B5
                                                        / \
                                                     *B3  *B8
                                                       \     \
                                                      *R4   *R12
 *          RBTNode* parent = nullptr;
 *          parent(*R4, &parent);
 * This will copy the pointer of parent of *R4 into parent. So, parent will be *B4, and it will point to the actual RBTNode in the RBT.
 */
void RedBlackTree::get_parent(RBTNode *node, RBTNode **parent) {
    RBTNode* curr = this->root;

    while(curr != nullptr) {
        if(*curr == *node) {
            break;
        } else if (*curr < *node) {
            *parent = curr;
            curr = curr->right;
        } else {
            *parent = curr;
            curr = curr->left;
        }
    }
}

/**
 * This function finds the pointer the @param node in the Red-Black Tree and places that pointer into @param location
 * The @param location is passed as *->*->* because this way we can change the orientation of the nodes in the Red-Black Tree
 * If @param location were only passed as *->* then *location would be changed to contain the copy of the pointer of the node in Red-Black Tree
 * By passing @param location as *->*->* then *location would contain the pointer to the actual pointer in the RBT rather than a copy of the pointer
 * pointing to the @param node
 * @param node : the node to find in the Red-Black Tree
 * @param location
 * For example:
 * If we have a Red-Black tree with following representation:
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
 *                                                rbt = *B5
                                                        / \
                                                     *B3  *B8
                                                       \     \
                                                      *R4   *R12
 *      RBTNode** location = nullptr;
 *      find(*R12, &location);
 * This will search for the pointer to R12 node in the Red-Black Tree. The location after the function call will contain
 * location = *->(*R12).
 * So when we change *location to something else, this would change the representation in the Red-Black Tree.
 * For example: if *location = *R13, then the Red-Black Tree will be changed to
 *                                                rbt = *B5
                                                        / \
                                                     *B3  *B8
                                                       \     \
                                                      *R4   *R13
 * If location was RBTNode* location = nullptr and the function definition was RedBlackTree::find(RBTNode* node, RBTNode** location)
 * and only the pointer to the location was changed
 * @param location would contain a copy to the *R12 node rather than the pointer to the actual pointer in the Red-Black tree
 */

void RedBlackTree::find(RBTNode* node, RBTNode*** location) {
    RBTNode** curr = &(this->root);

    while(*curr != nullptr) {
        if(**curr == *node) {
            *location = curr;
            break;
        } else if (**curr < *node) {
            curr = &((*curr)->right);
        } else {
            curr = &((*curr)->left);
        }
    }
}

/**
 * Returns the sibling of the parent of the node
 * @param node : the node whose parent's sibling is to be found
 * @param uncle : the uncle is stored in this pointer to a pointer
 * We get the pointer to the actual uncle member, this makes the rotation simpler
 * For example:
 * If we have a Red-Black tree with following representation:
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
 *                                                rbt = *B5
                                                        / \
                                                     *B3  *B8
                                                       \     \
                                                      *R4   *R12
 *              RBTNode* uncle = nullptr;
 *              this->get_uncle(*R12, &uncle);
 * The uncle pointer will be changed to a copy of the pointer to B3.
 */
void RedBlackTree::get_uncle(RBTNode *node, RBTNode **uncle) {
    RBTNode* parent = nullptr;
    this->get_parent(node, &parent);

    RBTNode* parent_parent = nullptr;
    this->get_parent(parent, &parent_parent);

    if(parent_parent->right == nullptr || (parent_parent->left != nullptr && (*parent == *(parent_parent->left)))) {
        *uncle = parent_parent->right;
    } else {
        *uncle = parent_parent->left;
    }
}

/**
 * Rotate the tree in leftward direction
 * @param node : a pointer that points to the actual RBTNode in the Red-Black Tree [Note: doesn't point to a copy of the RBTNode]
 * For example:
 * If we have a Red-Black tree with following representation:
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
 *                                                rbt = *B5
                                                        /  \
                                                       C    *R6
                                                           /   \
                                                          A     *R8
 * RedBlackTree::left_rotate(&(*B5)); changes the rbt into
 *                                                rbt = *R6
                                                        /  \
                                                      *B5    *R8
                                                     /   \
                                                    C     A
 */
void RedBlackTree::left_rotate(RBTNode **node) {
    RBTNode* right_left = (*node)->right->left;

    RBTNode* curr = *node;
    *node = (*node)->right;
    (*node)->left = curr;
    curr->right = right_left;
}

/**
 * Rotate the tree in the rightward direction
 * @param node : a pointer that points to the actual RBTNode in the Red-Black Tree [Note: doesn't point to a copy of the RBTNode]
 * For example:
 * If we have a Red-Black tree with following representation:
 * Here, *B5 represents that the node is a pointer to a RBTNode of color Black with value 5
 *                                                rbt = *B5
                                                        /  \
                                                     *R3    C
                                                    /   \
                                                  A     *R4
 * RedBlackTree::left_rotate(&(*B5)); changes the rbt into
 *                                                rbt = *R3
                                                        /  \
                                                       A    *B5
                                                           /   \
                                                        *R4     C
 */
void RedBlackTree::right_rotate(RBTNode **node) {
    RBTNode* left_right = (*node)->left->right;

    RBTNode* curr = *node;
    *node = (*node)->left;
    (*node)->right = curr;
    curr->left = left_right;
}

/**
 * This function performs the balacing operation based on the various balacing conditions
 * @param node : the node that was just added to the Binary Search Tree
 */
void RedBlackTree::DoBalance(RBTNode* node) {
    RBTNode* parent = nullptr; // pointer to the parent of the @param node
    RBTNode* uncle = nullptr; // sibling of parent
    RBTNode* grandparent = nullptr; // pointer to the parent of parent of the @param node

    // This gets the parent of the current node and saves it into *parent
    this->get_parent(node, &parent);

    // if the current node has no parent it must be the root node and root node is always Color::Black 
    if(parent == nullptr) {
        node->color = Color::Black;
        return;
    }

    // if the color of the parent is Color::Black, we don't need to make any changes to the Red-Black Tree
    if(parent->color == Color::Black) {
        return;
    } else {
        this->get_uncle(node, &uncle);

        // The the parent has no sibling or a Color::Black sibling then it must be rotated based on the
        // various balancing condition
        if(uncle == nullptr || uncle->color == Color::Black) {
            this->get_parent(parent, &grandparent);


            // These pointer to a pointer store the pointer to the RBTNode in Red-Black Tree
            // The reason for them to be pointer->pointer is because this way making changes to the
            // pointer pointed to by for example g_pointer, changes the pointer to point somewhere else
            // For reference please see comment on "this->find()" method
            RBTNode** g_pointer  = nullptr; // this is the pointer to the actual grandparent, not a copy of the parent pointer 
            RBTNode** p_pointer = nullptr; // this is the pointer to the actual parent, not a copy of the parent pointer

            this->find(grandparent, &g_pointer);
            this->find(parent, &p_pointer);

            if(grandparent->left == parent && parent->left == node) {
                RedBlackTree::right_rotate(g_pointer);
                /**
                 * For example:
                 *              rbt = *B5
                 *                   /   
                 *                *R4
                 *               /
                 *            *R3
                 * If after the insertion of *R3 the rbt looks as above. The tree needs to be balanced.
                 * For balance we perform right rotation and change the color of the children nodes.
                 * Here g_pointer points to the actual *B5 node and not a copy of that pointer. So, when
                 * the g_pointer is moved around during right_rotate, it changes the orientation of the entire
                 * Red-Black Tree.
                 * 
                 * After right rotation:
                 *             rbt = *R4
                 *                   /  \
                 *                *R4   *R5
                 * Here, the g_pointer will now point to the pointer *R4 rather than *R5 because g_pointer being
                 * pointer to a pointer used to point to *R5 location in RBT which has now been changed to *R4.
                 * The pointer that g_pointer used to point to has now been changed to something else 
                 * (From *R5 to *R4)
                 * , thus g_pointer now points to that changed pointer which now happens to be the grandparent
                 * After recoloration it changes into:
                 *             rbt = *B4
                 *                   /  \
                 *                *R4   *R5
                 * 
                 * This same process happens for all of the other balancing conditions.
                 */
                grandparent = *g_pointer;
                grandparent->color = Color::Black;
                grandparent->right->color = Color::Red;
                grandparent->left->color = Color::Red;
            } else if (grandparent->left == parent && parent->right == node) {
                RedBlackTree::left_rotate(p_pointer);
                RedBlackTree::right_rotate(g_pointer);
                node->right->color = Color::Red;
                node->left->color = Color::Red;
                node->color = Color::Black;
            } else if (grandparent->right == parent && parent->right == node) {
                RedBlackTree::left_rotate(g_pointer);
                grandparent = *g_pointer;
                grandparent->color = Color::Black;
                grandparent->right->color = Color::Red;
                grandparent->left->color = Color::Red;
            } else {
                RedBlackTree::right_rotate(p_pointer);
                RedBlackTree::left_rotate(g_pointer);
                node->right->color = Color::Red;
                node->left->color = Color::Red;
                node->color = Color::Black;
            }
        } else {
            parent->color = Color::Black;
            uncle->color = Color::Black;

            this->get_parent(parent, &grandparent);
            grandparent->color = Color::Red;

            this->DoBalance(grandparent);
        }
    }
}

/**
 * Inserts a value into the Red-Black Tree and performs the balance
 * @param value : value to be inserted into Red-Black Tree
 */
void RedBlackTree::Insert(int value) {
    RBTNode* node = nullptr;
    if(this->Contains(value)) {
        throw invalid_argument("Node: " + to_string(value) + " already in RBT.");

    }
    if(this->root == nullptr) {
        this->root = new RBTNode{.color = Color::Black, .value = value};
        return;
    } else {
        this->BinaryInsert(value, &node);
    }

    this->DoBalance(node);
    this->numItems++;
}

void RedBlackTree::Remove(int value) {
    RBTNode* node = nullptr;

    // TODO: Add check for the contain of the value in rbt
    this->BinaryRemove(value, this->root);
}

string RedBlackTree::ToPrefixString(const RBTNode* pos) {
    if(pos == nullptr) {
        return "";
    }

    string rtr = pos->color == Color::Black ? " B" : " R";
    rtr += to_string(pos->value) + " ";

    const RBTNode* left = pos->left;
    string left_c = RedBlackTree::ToPrefixString(left);

    const RBTNode* right = pos->right;
    string right_c = RedBlackTree::ToPrefixString(right);


    rtr = rtr
          + left_c
          + right_c;

    return rtr;
}

string RedBlackTree::ToInfixString(const RBTNode* pos) {
    if(pos == nullptr) {
        return "";
    }

    string rtr = pos->color == Color::Black ? " B" : " R";
    rtr += to_string(pos->value) + " ";

    const RBTNode* left = pos->left;
    string left_c = RedBlackTree::ToInfixString(left);

    const RBTNode* right = pos->right;
    string right_c = RedBlackTree::ToInfixString(right);


    rtr = left_c
          + rtr
          + right_c;

    return rtr;
}

string RedBlackTree::ToPostfixString(const RBTNode* pos) {
    if(pos == nullptr) {
        return "";
    }

    string rtr = pos->color == Color::Black ? " B" : " R";
    rtr += to_string(pos->value) + " ";

    const RBTNode* left = pos->left;
    string left_c = RedBlackTree::ToPostfixString(left);

    const RBTNode* right = pos->right;
    string right_c = RedBlackTree::ToPostfixString(right);


    rtr = left_c
          + right_c
          + rtr;

    return rtr;
}