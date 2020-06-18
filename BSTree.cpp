/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it 
 * tests
 */

 
#include <iostream>
#include <cstdlib>
#include "BSTree.h"

using namespace std;


 
/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */
 
 
void BST::find(int item_key, node **prnt, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *prnt = NULL;
        return;
    }
    if (item_key == root->key_value)
    {
        *loc = root;
        *prnt = NULL;
        return;
    }
    if (item_key < root->key_value)
        ptr = root->p_left;
    else
        ptr = root->p_right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item_key == ptr->key_value)
        {
            *loc = ptr;
            *prnt = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item_key < ptr->key_value)
            ptr = ptr->p_left;
	else
	    ptr = ptr->p_right;
    }
    *loc = NULL;
    *prnt = ptrsave;
}
 
/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
    if (root == NULL)// if (we are at root)
    {
        // Just create a single node for root to point to,
        //    with all the data in it.
        root = newnode;
        return;
    }
    // if (there is already a node with our key value)
    node *parent, *location;
    find(newnode->key_value, &parent, &location);
    if (location != NULL)
    {
        //Just return
        return; 
    }
    else {
    if(newnode->key_value < tree->key_value) //if (the new node is less than the current node)
    {
        if (tree->p_left != NULL)//if (see if something is already a child on the left)
        {
            // if so, the recurse insert at this subtree 	
            insert(tree->p_left,newnode);
      	}
      	else
      	{
            // otherwise the new node goes here as a leaf (ie no children)
            tree->p_left = newnode;
            return;
        }
    }
    else  // it must be to the right
    {
        if (tree->p_right != NULL)//if (is there already a child on right?)
        {
            // if so, the recurse insert at this subtree 
            insert(tree->p_right,newnode);
        }
        else
        {
            // otherwise the new node goes here as a leaf (ie no children)
            tree->p_right = newnode;
            return;
        }	
    }
    }
    return;
}
 
/*
 * Delete Element from the tree
 */
void BST::remove(int item)
{
    node *parent, *location;
    if (root == NULL)
    {
        cout<<"Tree empty"<<endl;
        return;
    }
    find(item, &parent, &location);
    if (location == NULL)
    {
        cout<<"Item not present in tree"<<endl;
        return;
    }
    if (location->p_left == NULL && location->p_right == NULL) //if (there is no child on left or right)
    {
        case_0(parent, location);
    }
    if (location->p_left != NULL && location->p_right == NULL) //if (there is one child on left only)
    {
        case_1(parent, location);
    }
    if (location->p_left == NULL && location->p_right != NULL) //if (there is one child on right only)
        {
          case_1(parent, location);
        }
   if (location->p_left != NULL && location->p_right != NULL) // if (there are childred on left and right)
   {
        case_2(parent, location);
   }
   // free(location);
    return;
}
 
/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(node *prnt, node *loc )
{
    if (loc == root) //if (we are at the root)
    {
        //update the root
        root = NULL;
    }
    else
    {
      // otherwise simply remove node
      loc = NULL;
    }
    return;
}
 
/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(node *prnt, node *loc)
{
    node *child;
   // cout << "remove case 1 " << loc->key_value << endl;
    if (loc->p_left != NULL) //if (the child is on the left?)
    {
        //point left
        child = loc->p_left;
    }
    else // else  // must be the right side has child
    {
        // point right
        child = loc->p_right;
    }
    if (loc == root)//if (we are at the root handle specialy)
    {
       // update the root
       if (loc->p_left != NULL)
       {
         root = loc->p_left;
       }
       else
       {
         root = loc->p_left;
       }
    }
    else
    {
        if (prnt->p_left == loc)//if (the node is left child of parent)
        {
            //promote the left
            prnt->p_left = child;
        }
        else //else // the node is right of parent
        {
            //promote the right
            prnt->p_right = child;
          
        }
    }
    return;
    
}
 
/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(node *prnt, node *loc)
{
  if (loc->p_right->p_left == NULL)
  {
    loc->key_value = loc->p_right->key_value;
    loc->p_right = loc->p_right->p_right;
  }
  else
  {
    node *successor;
    successor = loc->p_right;
    node *successorParent;
    successorParent = loc;
    
    while(successor->p_left != NULL)
    {
      successorParent = successor;
      successor = successor->p_left;
    }
    
    loc->key_value = successor->key_value;
    successorParent->p_left = successor->p_right;
  }
  return;
}
 

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->p_right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:  ";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
	}
        cout<<ptr->key_value;
        display(ptr->p_left, level+1);
    }
}

