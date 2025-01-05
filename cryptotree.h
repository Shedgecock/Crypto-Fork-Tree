#ifndef CRYPTOTREE_H
#define CRYPTOTREE_H

#include <ctype.h>  // character manipualtion, e.g. tolower()
#include <stdio.h> 
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>

using namespace std;

// An CryptoForkNode class to store an crypto fork tree (tree) node
class CryptoForkNode {

private:
  string forkName;
  vector<CryptoForkNode*> directForks; // children from current node

public:  
  // empty fork name indicate an empty CryptoForkNode ID
  static const string EMPTY_FORKNAME; 

  // -1 indicate NOT found
  static const int NOT_FOUND = -1; 

  // default constructor
  CryptoForkNode() {
  }

  // Constructor for instantiating an CryptoForkNode instance with a fork name.
  // Assume fork name argument is unique among all fork names.
  CryptoForkNode(string forkName) {
    this -> forkName = forkName;
  }
  
  // Constructor for instantiating an CryptoForkNode instance with a fork name
  // and all direct fork descendants to this CryptoForkNode.
  CryptoForkNode(string forkName, vector<string> forks) {
    this -> forkName = forkName;
    for (string d : forks) {
      this -> directForks.push_back(new CryptoForkNode(d));
    }
  }

  //Add a direct fork to the CryptoForkNode
  //Assume fork name argument is unique among all fork names.
  void addFork(string forkName) {
    this -> directForks.push_back(new CryptoForkNode(forkName));
  }
  
  //Add a group of direct forks to the CryptoForkNode
  void addForks(vector<string> dForks) {
    for (string d : dForks) {
      this -> directForks.push_back(new CryptoForkNode(d));
    }
  }

  // Getters
  string getCryptoForkName() {
    return this -> forkName;
  }
  
  vector<CryptoForkNode*> getDirectForks() {
    return this -> directForks;
  }

  // No destructor here
  // Use a recursive function to delete the fork tree
  // See below 
 
};

class CryptoForkTree  {

public:
  /**
   * Check if a crypto fork node is present in a crypto fork tree. 
   * 
   * @param  head the head / root CryptoForkNode of the crypto fork tree
   * @param  forkName the crypto fork name being searched
   * @return      true or false
   * @see         
   */
  static bool isCryptoForkNodePresent(CryptoForkNode* head, string forkName);

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
  static bool findPreviousForksLeadingToACryptoFork(CryptoForkNode* head, 
                                                    string forkName, 
                                                    vector<string> &previousForks);

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
  static int findCryptoForkNodeLevel(CryptoForkNode* head, 
                                     string forkName, 
                                     int headLevel);

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
  static CryptoForkNode* findClosestSharedAncestor(CryptoForkNode* head, 
                                                   string f1_name, string f2_name);

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
  static int findNumOfAncestorsBetween(CryptoForkNode* head, string f1_name, string f2_name);

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
  static void deleteCryptoForkTree (CryptoForkNode* head);

};

#endif