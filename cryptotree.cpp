/**
* Programming Assignment 3
*  Retrieve information from a given crypto fork tree.
 * CS210 - Summer 2024
 * 06/21/24
 * @author Sean Hedgecock
 * Single Programmer Affidavit
* I, the undersigned, promise that the submitted assignment is my own work.
* While I was free to discuss ideas with others, the work contained is my own.
* I recognize that, should this not be the case;
* I will be subject to penalties as outlined in the course syllabus.

Name: Sean Hedgecock
Red ID: 814087593
*/

#include "cryptotree.h"

#include <iostream>

/**
 * Check if a crypto fork node is present in a crypto fork tree. 
 * 
 * @param  head the head / root CryptoForkNode of the crypto fork tree
 * @param  forkName the crypto fork name being searched
 * @return      true or false
 * @see         
 */
bool CryptoForkTree::isCryptoForkNodePresent(CryptoForkNode* head, string forkName) {//good
    //second approach, using divide and conquer for a recursive algorithm
    if (head==nullptr)//bc1, empty tree
    {
        return false;
    }
    if (forkName==head ->getCryptoForkName())//bc2, actually found the fork
    {
        return true;
    }
    vector<CryptoForkNode*> successors = head->getDirectForks();//search fork in subtrees of head
    for (int i = 0; i < successors.size(); ++i)
    {
        if (isCryptoForkNodePresent(successors[i],forkName))
        {
            return true;
        }
    }
return false;
    // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // base case 1: empty tree, return false

  // base case 2: if the fork is found, return true

  // search fork in each subtree of the head
  // return true if the fork is found in one of the child subtree

  // if not found, return false
  //return false;
}

/**
 * Find all previous forks leading to a crypto fork node. 
 * 
 * @param  head          the head / root CryptoForkNode of the crypto fork tree
 * @param  forkName      the crypto fork name being searched
 * @param  previousforks a vector of fork names of all previous forks for the fork node
 *                       in the ascending order of their tree height
 *                       i.e., forks along the path starting from direct parent fork 
 *                       to the root node
 *                       If the fork tree is empty, or forkName is the head, or 
 *                       is not in the tree, previousForks should be empty after the search. 
 * @return               is crypto fork found
 * @see         
 */
bool CryptoForkTree::findPreviousForksLeadingToACryptoFork(CryptoForkNode* head, 
                                                           string forkName, 
                                                           vector<string> &previousForks) {//good
    if (head==nullptr)//bc1, empty tree
    {
        return false;
    }
    if (forkName==head ->getCryptoForkName())//bc2, if fork is the head
    {
        return true;
    }
    vector<CryptoForkNode*> successors=head->getDirectForks();//searches for fork in subtree of the head
    for (int i = 0; i<successors.size();++i)
    {
        if (findPreviousForksLeadingToACryptoFork(successors[i],forkName,previousForks))//if it is found, we add current head to previous forks
        {
            previousForks.push_back(head ->getCryptoForkName());
            return true;
        }
    }
    return false;

//uses recursion to search for the fork name in the tree starting from the root. if the forkname is found it backtracks
    //and adds the current nodes name to the vector. If not found, returns false. This approach makes sure
    //the previous names of all the previous forks leading to the one we want in ascending order of their tree height.

  // The implementation should be similar to isCryptoForkNodePresent
  
  // Search subtrees from the head, after all subtrees are searched, 
  // if fork e_id is found:
  // the head should be inserted to the previousForks vector along 
  // the backtracking process of recursive calls

  // The above comment means that when searching the subtrees (children) 
  // from where you are searching, if the recursive call to 
  // findPreviousForksLeadingToACryptoFork returns true, you would know that 
  // the head in the current findPreviousForksLeadingToACryptoFork call would 
  // be a previous fork (or the fork itself) along the ancestor path 
  // of the fork you are searching, so you would like to append it 
  // to the previousForks vector. 

  // Note:
  // do NOT add the fork's own name to the passed-in previousForks vector

  // return false if fork is not found
  //return false;
}

/**
 * Find the level of a crypto fork in a crypto fork tree. 
 * 
 * <p>
 * The root node has a level of 0.
 * children of the head node passed in have
 * a level of the head plus 1, and so on and so forth... 
 * 
 * <p>
 * Assumption: forkName is unique among all fork names
 *
 * @param  head      the head / root CryptoForkNode of the fork tree
 * @param  forkName  the crypto fork name being searched
 * @param  headLevel the level of the head fork passed in 
 * @return  level of the CryptoForkNode in the fork tree
 *          returns CryptoForkNode::NOT_FOUND if forkName is not present
 * @see         
 */
int CryptoForkTree::findCryptoForkNodeLevel(CryptoForkNode* head, 
                                            string forkName, 
                                            int headLevel) {//good
    if (head==nullptr)//bc1, empty tree
    {
        return CryptoForkNode::NOT_FOUND;
    }
    if (forkName==head ->getCryptoForkName())//bc2, found fork so return its level
    {
        return headLevel;
    }
    vector<CryptoForkNode*> successors=head ->getDirectForks();
    for (int i=0;i<successors.size();++i)//search fork from each child of the head
    {
        int level = findCryptoForkNodeLevel(successors[i],forkName,headLevel+1);
        if (level !=CryptoForkNode::NOT_FOUND)
        {
            return level;
        }
    }
    return CryptoForkNode::NOT_FOUND;
}


  // Write your recursive implementation here. 

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.
  
  // base case 1: empty tree


  // base case 2: the fork is found, returns the fork level


  // search fork from each child of the head

  // if not found
//   return CryptoForkNode::NOT_FOUND;
// }

/**
 * Find the closest shared ancestor of two forks f1 and f2. 
 * 
 * <p>
 * There are two possible fork relationships between two forks in the tree:
 * case 1: f1 or f2 is an ancestor of the other fork node; 
 * case 2: f1 or f2 is not an ancestor of the other fork node, 
 *         then they have at least one shared ancestor
 *
 * <p>
 * Assumption: f1_name and f2_name are unique among all fork names
 *
 * @param  head    the head / root CryptoForkNode of the fork tree
 * @param  f1_name name of fork node 1 being searched
 * @param  f2_name name of fork node 2 being searched 
 * @return   closest shared ancestor in the fork tree between fork node 1 and fork node 2
 *           if head is nullptr, returns nullptr
 *           if neither f1 nor f2 is present, returns nullptr           
 *           if f1 is present and f2 is not, returns f1
 *           if f2 is present and f1 is not, returns f2
 *           if f1 and f2 both are present, returns their closest shared ancestor
 *              if f1 is an ancestor of f2, returns f1
 *              else if f2 is an ancestor of f1, returns f2
 *              else returns the closest shared ancestor of f1 and f2
 * @see         
 */
CryptoForkNode* CryptoForkTree::findClosestSharedAncestor(CryptoForkNode* head, 
                                                          string f1_name, string f2_name) {
    if (head==nullptr)//bc1, empty tree
    {
        return nullptr;
    }
    if(f1_name==head ->getCryptoForkName() || f2_name==head ->getCryptoForkName())//bc2, either f1_name or f2_name is the same as the head / root
    {
        return head;
    }
    CryptoForkNode* foundLeft=nullptr;
    CryptoForkNode* foundRight=nullptr;
    vector<CryptoForkNode*> successors=head ->getDirectForks();//recursive search through fork subtree of the head
    for (int i=0; i<successors.size(); ++i)//to find where exactly f1 anf f2 are located
    {
        CryptoForkNode* found=findClosestSharedAncestor(successors[i],f1_name,f2_name);//recursive call
        if (found !=nullptr)
        {
            if (foundLeft==nullptr)
            {
                foundLeft =found;
            }
            else
            {
                foundRight = found;
            }
        }
    }
    if (foundLeft !=nullptr &&foundRight !=nullptr)//Scenario 1, if f1 is found in one subtree and f2 is found in another
    {
        return head;
    }
    if (foundLeft !=nullptr)//scenario 2, either f1 or f2 is first found in one subtree, but the other fork isnt found from any other.
    {
        return foundLeft;
    }
    if (foundRight !=nullptr)
    {
        return foundRight;
    }
    return nullptr;//scenario 3, neither f1/f2 is found in tree so return null

  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // base case 1: empty tree


  // base case 2: either f1_name or f2_name is the same as the head / root


  // Recursively traverse through each fork subtree of the head to find 
  // where f1 and f2 are
  
  /*
     For each recursive call (starting from the root), you need to handle three possible scenarios:
     1) if f1 is found in one subtree, and f2 is found from another subtree; 
        the head at that recursive step would be the closest shared ancestor of f1 and f2.

        you can use the returned pointer (being NOT NULL) from findClosestSharedAncestor 
        to see if f1 or f2 is found from a subtree (one of the base cases).

     2) if either f1 or f2 is first found in one subtree (following one subtree), 
        but the other fork is NOT found from any other subtree, then the found 
        fork must either be an ancestor of the other fork, or the other fork 
        is NOT in the tree; in either case, the first found fork should be 
        returned as the shared ancestor.

     3) if neither f1 or f2 is found in the tree, return nullptr
  */

  //return nullptr;
}

/**
 * Calculate the number of ancestors between fork node 1 and fork node 2. 
 * 
 * <p>
 * The number of ancestors between fork node 1 and fork node 2 can be calculated by: 
 *  number of edges between fork node 1 and closest shared ancestor + 
 *  number of edges between fork node 2 and closest shared ancestor - 1
 *
 * <p>
 * Assumption: f1_name and f2_name are unique among all fork names
 *
 * @param  head    the head / root CryptoForkNode of the fork tree
 * @param  f1_name name of fork node 1 being searched
 * @param  f2_name name of fork node 2 being searched 
 * @return   number of ancestors between fork node 1 and fork node 2
 *           returns CryptoForkNode::NOT_FOUND if either f1 or f2 is 
 *           not present in the chart
 * @see         
 */
int CryptoForkTree::findNumOfAncestorsBetween(CryptoForkNode* head, string f1_name, string f2_name) {//iterative
    if (!isCryptoForkNodePresent(head, f1_name) || !isCryptoForkNodePresent(head, f2_name)) {
        return CryptoForkNode::NOT_FOUND;//are both the fork nodes present in the tree?
    }
    CryptoForkNode* sharedAncestor = findClosestSharedAncestor(head, f1_name, f2_name);//finds the closest shared ancestor here
    if (sharedAncestor==nullptr) {
        return CryptoForkNode::NOT_FOUND;
    }
    int f1_level=findCryptoForkNodeLevel(head,f1_name,0);//find levels of f1/f2 names and their shared level
    int f2_level=findCryptoForkNodeLevel(head,f2_name,0);
    int both_in_level=findCryptoForkNodeLevel(head,sharedAncestor->getCryptoForkName(),0);
    int numAncestors=(f1_level-both_in_level)+(f2_level-both_in_level)-1;//number of ancestors between f1/f2 calculation using edges
    return numAncestors;




  // Write your implementation here. You do NOT need to use recursive approach here.

  // Use the above functions wherever you need to implement this function.  

  // Continue only if both fork nodes f1_name and f2_name are in the tree
  // otherwise, return CryptoForkNode::NOT_FOUND
  //return CryptoForkNode::NOT_FOUND;

  // The number of ancestors between fork f1 and fork f2 can be calculated by: 
  // number of edges between f1 and closest shared ancestor + 
  // number of edges between f2 and closest shared ancestor - 1
   
}

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 
 *
 * DO NOT worry about removing them from the vector directForks
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its fork name and a new line
 *     The print here is for verifying the order of the deletion
 *
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following tree, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root CryptoForkNode of the crypto fork tree
 * @return   None 
 * 
 * @see         
 */
void CryptoForkTree::deleteCryptoForkTree (CryptoForkNode* head) {//good
    if (head==nullptr)//bc1, empty tree
    {
        return;
    }
    vector<CryptoForkNode*> successors=head ->getDirectForks();//post order traversal deletes children
    for (int i=0;i <successors.size();++i)//recursive approach. Can use range based for loop as well.
    {
        deleteCryptoForkTree(successors[i]);
    }
    cout << head ->getCryptoForkName() << endl;//PRINT current node's fork name and a new line
    delete head;//delete the current node after deleting its children

//recursively deletes the tree starting form the head node. post order traversal is used.
    //First it deletes all the children of the curr node
    //then it prints the current nodes for name
    //finally it deletes the curr node, all in a recursive approach.

    // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // base case: empty tree

  // delete children recursively with post order traversal
  
  // PRINT current node's fork name and a new line
  // delete the current node after deleting its children
  
}
