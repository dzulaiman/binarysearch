/*
  * File Name: Ph1tree.c
  * Name: Asmatullah Yaree, Mohd Dzul Aiman, Nursuliza, Maryam Adinehnia
  * Assignment: 1
  * Problem: 1
  * Date: March April, 2013
  *
  * This is the implementation file for the tree module. It
  * contains the functions needed to perform tree operations.
  */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include "Ph1tree.h"
 
 
 /* tree node data structure */
 typedef struct treeNodeTag {
   treeElementT element;      /* tree element */
   struct treeNodeTag *left;  /* left tree link */
   struct treeNodeTag *right; /* right tree link */
 } treeNodeT;
 
 /* treeCDT data structure */
 typedef struct treeCDT {
   treeNodeT *root;
 } treeCDT;
 
 /*
  * HELPER FUNCTION PROTOTYPES
  */
 static void RecTreePrint(treeNodeT *root, FILE *outfileP);
 static void RecTreeDestroy(treeNodeT *root);
 static treeNodeT *FindCurrentNode(treeADT tree, treeKeyT key);
 static treeNodeT *FindParentNode(treeADT tree, treeKeyT key);
 static treeNodeT *FindMaxNode(treeNodeT *root);
 
 /*
  * Function: TreeCreate
  * --------------------
  * This procedure initializes an empty tree by setting 
  * the pointer to the root of the tree equal to NULL.
  */
 treeADT TreeCreate(void)
 {
    treeADT tree;  /* pointer to a treeCDT */
 
    tree = (treeADT)malloc(sizeof(treeCDT));
 
    /* if allocation fails, print an error message and exit */
    if (tree == NULL) 
    {
       fprintf(stderr,"Insufficient memory for new tree.\n");
       exit(1);  /* exit, returning error code. */
    }
 
    tree->root = NULL;   /* initialize root pointer of the tree */
    return tree;
 }
 
 /*
  * Function: TreeDestroy
  * ---------------------
  * This procedure calls a recursive function to free the memory
  * used up by the tree nodes and resets the root pointer of the
  * tree to NULL.
  */
 void TreeDestroy(treeADT tree)
 {
    RecTreeDestroy(tree->root);   /* start at root of tree */
    tree->root = NULL;   /* reset root pointer to NULL */
    
    /* free structure which holds information about tree */
    free(tree);
 }
 
 /*
  * Function: RecTreeDestroy
  * ------------------------
  * This procedure uses a postorder traversal of the tree
  * and recursively calls itself to free the tree nodes in
  * a postorder manner so that links to other nodes are not
  * lost if the root is deleted.
  */
 static void RecTreeDestroy(treeNodeT *root)
 {
    if (root == NULL) /* base case to stop recursing */
       return;
    else
    {
       RecTreeDestroy(root->left);   /* traverse left */
       RecTreeDestroy(root->right);  /* traverse right */
       free(root);  /* deallocate memory */
    }
 }
 
 /*
  * Function: TreeAdd
  * -----------------
  * This procedure adds a new node to a tree to the 
  * bottom of the tree. If the element is already in 
  * the tree, it just adds the element.
  */
 void TreeAdd(treeADT tree, treeElementT element)
 {
    treeNodeT *new_tree_node,  /* new tree node */
              *currentP,       /* pointer to the current tree node */
              *parentP;        /* pointer to parent of current node */

 
    /* check to see if element's key is already in the tree */
    currentP = FindCurrentNode(tree,element.key);
 
    /* if element's key is already in the tree, just */
    /* add the new element and exit the function     */
    if (currentP != NULL)
    {
       printf("Serial number already exist");
       //currentP->element = element;
       return;  /* exit the function */
    }
    
    /* if the element's key is not already in the tree, search for */
    /* an empty branch onto which the new leaf node will be added  */
    
    parentP = NULL;
    currentP = tree->root;  /* start at root of tree */
 
    /* search for empty branch to add an element */
    while (currentP != NULL)
    {
       parentP = currentP;
       if (element.key == currentP->element.key)
          break;
       else if (element.key < currentP->element.key)
          currentP = currentP->left;
       else if (element.key > currentP->element.key)
          currentP = currentP->right;
    }
    
    /* attempt to allocate space in memory for a new tree node */
    new_tree_node = (treeNodeT *) malloc(sizeof(treeNodeT));
 
    /* print error message if allocation fails */
    if (new_tree_node == NULL)
    {
       fprintf(stderr,"Insufficient memory to add a new tree node.\n");
       TreeDestroy(tree);
       exit(1);
    }
    else
    {
       /* add the element to the new tree node */
       new_tree_node->element = element;
       new_tree_node->left = NULL;
       new_tree_node->right = NULL;
 
       /* connect the new tree node with the rest of the tree */
       /* depending on whether or not it is the root or it is */
       /* less than or greater than the root                  */
       if (parentP == NULL)
          tree->root = new_tree_node;
       else if (new_tree_node->element.key < parentP->element.key)
          parentP->left = new_tree_node;
       else if (new_tree_node->element.key > parentP->element.key)
          parentP->right = new_tree_node;
    }
 }
 
 /*
  * Function: TreeDelete
  * --------------------
  * This procedure deletes an element from a tree, depending
  * on whether the element is a leaf, has only one connecting
  * branch, or is a root node.
  */
 treeElementT TreeDelete(treeADT tree, treeKeyT key)
 {
    treeNodeT *currentP,       /* pointer to node to be deleted */
              *parentP,        /* pointer to parent of node to be deleted */
              *max_nodeP,      /* pointer to node with largest key */
              *max_node_parP,  /* pointer to parent of node with largest key */
              *temp_node;
 
    treeElementT deleted;   /* element that is deleted from the tree */
 
    if (tree->root == NULL)
    {
       printf("Error!! There are no tree nodes to be deleted.\n");
       TreeDestroy(tree);   /* deallocate memory used by tree */
       exit(1);  /* exit program, returning error code */
    }
    else 
    {
       /* find the node to be deleted */
       currentP = FindCurrentNode(tree,key);
       if (currentP == NULL)
       {
          printf("Error!! The key to be deleted does not exist in the tree.\n");
          TreeDestroy(tree);   /* deallocate memory used by tree */
          exit(1);  /* exit program, returning error code */
       }
       else 
       {
          /* if the node exists, find it's parent node */
          parentP = FindParentNode(tree,key);
 
          /* copy deleted node's element into a variable to return */
          deleted = currentP->element;
 
          /* case for deletion if node is a leaf */
          if ((currentP->left == NULL) && (currentP->right == NULL))
          {
		   if(parentP==NULL)
           tree->root=NULL;
	       else
               if(currentP==parentP->left)
                   parentP->left=NULL;
		       else
		           parentP->right=NULL;
	            }
             /* set left and right pointers of parent node to NULL */
           /*  if (parentP->left == currentP)
                parentP->left = NULL;
             else if (parentP->right == currentP)
                parentP->right = NULL;
          }*/
       
	

	/* case for deletion if node has a left branch and no right branch */
          else if ((currentP->left != NULL) && (currentP->right == NULL))
          {
		
             if (parentP->left == currentP)
                parentP->left = currentP->left;
             else if (parentP->right == currentP)
                parentP->right = currentP->left;
          }

          /* case for deletion if node has a right branch and no left branch */
          else if ((currentP->right != NULL) && (currentP->left == NULL))
          {
             if (parentP->left == currentP)
                parentP->left = currentP->right;
             else if (parentP->right == currentP)
                parentP->right = currentP->right;
          }
          /* case for deletion if node has two branches */
         else if ((currentP->left != NULL) && (currentP->right != NULL))
          {
             /* this type of deletion involves finding the largest key node in the    */
             /* left subtree and basically swaps the element of the largest node      */
             /* with the node to be deleted, relinks the tree, and frees the max node */
             
             /* find largest key node and its parent in left subtree */
             max_nodeP = FindMaxNode(currentP->left);
             max_node_parP = FindParentNode(tree,max_nodeP->element.key);
 
             /* if maximum key node is a leaf and it's parent is not equal      */
             /* to current, then set the left and right pointers of the parent  */
             /* to NULL, else just have the parent's left pointer point to NULL */
             /* so that the right subtree of the deleted node is not lost.      */
  


		/* The deletion code below is not right */


        /* Dzul's refine */
        
           if ((max_node_parP->right == max_nodeP) && (max_nodeP->left == NULL))
           {
              /* swap max node element into deleted node */
              currentP->element = max_nodeP->element;  
             /* have current point to max to free the maximum key node */
             currentP = max_nodeP;                     
             
             max_node_parP->right = NULL;                                     
           }
           
           else if ((max_node_parP->right == max_nodeP) && (max_nodeP->left != NULL))
           {
               temp_node->right = max_nodeP->left;
               
             /* swap max node element into deleted node */
              currentP->element = max_nodeP->element;  
             /* have current point to max to free the maximum key node */
             currentP = max_nodeP;     
             
             max_node_parP->right = temp_node;
             
           }
           
           else if ((max_node_parP->left == max_nodeP) && (max_nodeP->left == NULL))
           {
                /* swap max node element into deleted node */
              currentP->element = max_nodeP->element;  
             /* have current point to max to free the maximum key node */
             currentP = max_nodeP;                     
             max_node_parP->left = NULL;                                     
                }
                
           else if ((max_node_parP->left == max_nodeP) && (max_nodeP->left != NULL))
           {
              temp_node = max_nodeP->left;
               
             /* swap max node element into deleted node */
              currentP->element = max_nodeP->element;  
             /* have current point to max to free the maximum key node */
             currentP = max_nodeP;     
             
             max_node_parP->left = temp_node;
             max_nodeP == NULL;   
                }
           
           /*
             if ((max_nodeP->left == NULL) && (max_nodeP->right == NULL))
             {   

                if (max_node_parP != currentP)
                {
                  max_node_parP->left = NULL;
                   max_node_parP->right = NULL;
                
		
                }
                else 
                   max_node_parP->left = NULL;
             }               
             else
                max_node_parP->right = NULL;
 
             /* swap max node element into deleted node */
            /*currentP->element = max_nodeP->element;  */
             /* have current point to max to free the maximum key node */
             /*currentP = max_nodeP;   */
          }        
       }
    }
    //free(max_nodeP);  /* deallocate memory of current node */
    return deleted;
 }
 
 /*
  * Function: TreeFind
  * ------------------
  * This procedure takes in a key and searches the tree for an
  * element with that key. If it finds an element with the key,
  * it returns a pointer to that element. If not, the function
  * will return NULL.
  */
 treeElementT *TreeFind(treeADT tree, treeKeyT key)
 {
    treeNodeT *currentP;  /* pointer to the current tree node */
 
    currentP = tree->root;  /* set current to the root of the tree */
 
    /* search for the key */
    while (currentP != NULL)
    {
       if (key == currentP->element.key)
          return &currentP->element;  /* return pointer to element if key's match */
       /* move current left or right if keys don't match */
       else if (key < currentP->element.key)
          currentP = currentP->left;
       else if (key > currentP->element.key)
          currentP = currentP->right;         
    }
    return NULL;
 }
 
 /*
  * Function: TreePrint
  * -------------------
  * This procedure checks if the tree is empty. If empty, an
  * error message is printed, otherwise RecTreePrint is called
  * to print the elements of the tree in preorder.
  */
 void TreePrint(treeADT tree, FILE *outfileP)
 {
    if (tree->root == NULL)
       printf("Error!! There are no elements in the tree to be printed.\n\n");
        /* ^^ Not an error condition -- TF */
    else
      RecTreePrint(tree->root,outfileP);
 }
 
 /*
  * Function: RecTreePrint
  * ----------------------
  * This procedure is a recursive function which prints out
  * elements of a tree in preorder.
  */
 static void RecTreePrint(treeNodeT *root, FILE *outfileP)
 {
    if (root == NULL)  /* base case to stop recursing */
       return;
   else
    {
       PrintElement(root->element,outfileP);  /* print root element */
       RecTreePrint(root->left,outfileP);     /* traverse left node */
       RecTreePrint(root->right,outfileP);    /* traverse right node */
    }
 }
 
 /*
  * Function: FindCurrentNode
  * -------------------------
  * This is a helper function which returns
  * a pointer to a key's node.
  */
 static treeNodeT *FindCurrentNode(treeADT tree, treeKeyT key)
 {
    treeNodeT *currentP;  /* pointer to the current tree node */
 
    currentP = tree->root;  /* set current to the root node of the tree */
 
    while (currentP != NULL)
    {
       if (key == currentP->element.key)
          return currentP;
       /* move current left or right accordingly */
       else if (key < currentP->element.key)
          currentP = currentP->left;
       else if (key > currentP->element.key)
          currentP = currentP->right;         
    }
    return NULL;
 }
 
 /*
  * Function: FindParentNode
  * ------------------------
  * This is a helper function which returns
  * a pointer to the parent of a key's node.
  */
 static treeNodeT *FindParentNode(treeADT tree, treeKeyT key)
 {
    treeNodeT *currentP,  /* pointer to the current tree node */
              *parentP;   /* pointer to the parent of the current node */
 
    parentP = NULL;
    currentP = tree->root;  /* set current to the root node of the tree */
 
    while (currentP != NULL)
    {
       if (key == currentP->element.key)
          return parentP;
       /* increment parent and current pointers accordingly */
       else if (key < currentP->element.key)
       {
          parentP = currentP;
          currentP = currentP->left;
       }
       else if (key > currentP->element.key)
       {
          parentP = currentP;
          currentP = currentP->right;  
       }
    }
    return NULL;
 }
 
 /*
  * Function: FindMaxNode
  * ---------------------
  * This is a helper function which returns a 
  * pointer to the largest key node in a tree.
  */ 
 static treeNodeT *FindMaxNode(treeNodeT *root)
 {
    if (root != NULL)
       while (root->right != NULL)
          root = root->right;
 
    return root;
 }
