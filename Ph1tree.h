
/*
  * File Name: Ph1tree.h
  * Name: Asmatullah Yaree
  * Assignment: 1
  * Problem: 1
  * Date: March 28, 2013
  *
  * This is the interface file for the tree module. It 
  * includes the constants, types, and function prototypes. 
  * Documentation on how the function prototypes should be 
  * used by a main program are included.
  */
 
 /* begin header file "wrap" */
 #ifndef _h5tree_h
 #define _h5tree_h
 
 #define MAX_NAME 30  /* maximum name length */
 
 typedef int treeKeyT;
 
 /* tree value data structure */
 typedef struct {
   char name[MAX_NAME+1];  /* one extra for null character */
   int number;            /* the telephone number */
 } treeValueT;
 
 /* tree element data structure */
 typedef struct {
   treeKeyT key;
   treeValueT value;
 } treeElementT;
 
 typedef struct treeCDT *treeADT;
 
 /*
  * Function: TreeCreate
  * Usage: tree = TreeCreate();
  * ---------------------------
  * This procedure creates and initializes the root tree node.
  */
 treeADT TreeCreate(void);
 
 /*
  * Function: TreeDestroy
  * Usage: TreeDestroy(tree);
  * -------------------------
  * This procedure deallocates the memory used up by a tree.
  */
 void TreeDestroy(treeADT tree);
 
 /*
  * Function: TreeAdd
  * Usage: TreeAdd(tree,element);
  * -----------------------------
  * This procedure adds an element to the tree.
  */
 void TreeAdd(treeADT tree, treeElementT element);
 
 /*
  * Function: TreeDelete
  * Usage: element = TreeDelete(tree,key);
  * ----------------------------
  * This procedure deletes an element from a tree and returns it.
  */
 treeElementT TreeDelete(treeADT tree, treeKeyT key);
 
 /*
  * Function: TreeFind
  * Usage: found = TreeFind(tree,key);
  * ----------------------------------
  * This procedure attempts to find an element in the tree
  * with a corresponding key. If found, it returns a pointer
  * to that element. If not, it returns NULL.
  */
 treeElementT *TreeFind(treeADT tree, treeKeyT key);
 
 /*
  * Function: TreePrint
  * Usage: TreePrint(tree,outfileP);
  * --------------------------------
  * This procedure prints out the elements of a tree
  * using preorder traversal.
  */
 void TreePrint(treeADT tree, FILE *outfileP);
 
 /*
  * Function: PrintElement
  * Usage: PrintElement(element,outfileP);
  * --------------------------------------
  * PrintElement is not defined here in the tree module, it is
  * only prototyped here. It must be defined in the main program
  * to be used by TreePrint in the implementation module.
  */
 void PrintElement(treeElementT element, FILE *outfileP);
 
 /* end header file "wrap" */
 #endif

