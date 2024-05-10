/**
 * @file
 * @brief Implements level order traversal of a binary tree, also known as
 * Breadth-First Search (BFS)
 *
 * @details
 * This program systematically traverses every node in the tree, visiting all
 * nodes at a particular level before moving to the next level. It starts from
 * the root node and explores all of its neighbors at the present depth level
 * before moving to the nodes at the next level.
 *
 *
 * It is assumed that nodes and trees have been created as per create_node.c
 * It is assumed that the enQueue and deQueue functions have been initialized
 * and defined elsewhere.
 *
 * [Further Details here](https://en.wikipedia.org/wiki/Breadth-first_search)
 * @author [Diwas Dahal](https://github.com/di-was)
 */

#include <stdio.h>

void level_order_traversal(struct node *root)
{
    struct node *temp_node = root;

    while (temp_node)  // if tree is not empty
    {
        printf("%d \n", temp_node->data);
        if (temp_node->left)
        {
            enQueue(temp_node->leftNode);
        }
        if (temp_node->right)
        {
            enQueue(temp_node->rightNode);
        }

        temp_node = deQueue();
    }
}

int main(void)
{
    /* level order traversal can be done by simply invoking
       the function with a pointer to the root node given that
       enQueue and deQueue are within the scope of this program
       and function.
    */
    return 0;
}
