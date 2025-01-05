/**
 * Start of a driver file to test cryptotree.cpp
 * CS 210 Summer 2024
 * @author 
 * @date Jun 2024
 */

#include "cryptotree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MANY CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

// cypto fork / branch consts used for testing
const vector<string> forks = {"singularity", 
                              "cash", 
                              "gold", 
                              "xt", 
                              "unlimited", 
                              "diamond", 
                              "private", 
                              "sv", 
                              "atom",
                              "boy",
                              "b2x",
                              "supercoin",
                              "blvck",
                              "abc",
                              "girl",
                              "candy",
                              "hot",
                              "stealth"};

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following tree for testing
     * numbers are the indices into the const forks vector above.
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     * 
     *                  cash
     *           /        \       \
     *          gold        xt    unlimited
     *          / \         / \      \
     *     rivatediamond p sv atom  boy
     *         /   \                 \
     *       b2x supercoin           blvck
     * 
     * post order traversal order:
     *   b2x diamond supercoin private gold sv atom xt blvck boy unlimited cash
     * 
     */

    CryptoForkNode *head = new CryptoForkNode(forks[1], vector<string>{forks[2], forks[3], forks[4]});
    CryptoForkNode *f2 = head->getDirectForks().at(0);
    CryptoForkNode *f3 = head->getDirectForks().at(1);
    CryptoForkNode *f4 = head->getDirectForks().at(2);

    f2->addForks(vector<string>{forks[5], forks[6]});
    f3->addForks(vector<string>{forks[7], forks[8]});
    f4->addFork(forks[9]);

    CryptoForkNode *f5 = f2->getDirectForks().at(0);
    CryptoForkNode *f6 = f2->getDirectForks().at(1);
    CryptoForkNode *f9 = f4->getDirectForks().at(0);

    f5->addFork(forks[10]);
    f6->addFork(forks[11]);
    f9->addFork(forks[12]);

    // IMPORTANT: This part will be autograded as well as manually inspected for grading

    // Begin Testing ---------------------------------------------------------------------
    // A few sample testing code are provided below
    
    // TODO: Test all CryptoForkTree functions
    //       according to the specifications in the comment section ABOVE each function signature. 
    // IMPORTANT: IN ADDITION to the TODOs below, 
    //            You MUST also construct at least one different tree 
    //            that is similar to the given example tree above for all your tests
    // Also make sure to check edge cases, such as empty tree, or one fork tree.

    // Test isCryptoForkNodePresent function ---------------------------------------------
    bool forkPresent = CryptoForkTree::isCryptoForkNodePresent(head, forks[6]);
    asserts(forkPresent, "Fork " + forks[6] + 
            " is present in tree, your code returned " + 
            (forkPresent ? "true" : "false"));
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(head, forks[0]);
    asserts(forkPresent == false, "Fork " + forks[0] + 
            " is not present in tree, your code returned " + 
            (forkPresent ? "true" : "false"));

    //my tests isCryptoForkNodePresent
    //T1:empty tree
    CryptoForkNode *emptyTree = nullptr;
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(emptyTree, forks[1]);
    asserts(forkPresent == false, "Fork " + forks[1] + " is not present in an empty tree");
    //T2: single node tree
    CryptoForkNode *singleNodeTree = new CryptoForkNode(forks[0], vector<string>{});
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(singleNodeTree, forks[0]);
    asserts(forkPresent, "Fork " + forks[0] + " is present in single node tree");
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(singleNodeTree, forks[1]);
    asserts(forkPresent == false, "Fork " + forks[1] + " is not present in single node tree");
    //T3:node at root
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(head, forks[1]);
    asserts(forkPresent, "Fork " + forks[1] + " root is present in tree");
    //T4: node in intermediate level
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(head, forks[2]);
    asserts(forkPresent, "Fork " + forks[2] + " intermediate is present in tree");
    //T5: leaf node
    forkPresent = CryptoForkTree::isCryptoForkNodePresent(head, forks[12]);
    asserts(forkPresent, "Fork " + forks[12] + " leaf is present in tree");

    // TODO - your code for testing isCryptoForkNodePresent using the given sample tree above

    // Test findPreviousForksLeadingToACryptoFork function --------------------------------
    vector<string> previousForks; 
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(head, forks[11], previousForks);
    asserts(forkPresent, "Fork " + forks[11] + " present in tree, your code returned " +
            (forkPresent ? "true" : "false")); 

    vector<string> expected_previous_forks{ forks[6], forks[2], forks[1] };
    asserts(previousForks == expected_previous_forks, 
            "Your code should return (" + forks[6] + " " + 
            forks[2] + " " + forks[1] + ") as ancestors of fork " + forks[11]);
    
    previousForks.clear();
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(head, forks[0], previousForks);
    asserts(previousForks.size() == 0, "Fork " + forks[0] + 
            " is not present in tree, its ancestors should be empty");

    //my tests findPreviousForksLeadingToACryptoFork
    //T1:root node, should return empty
    previousForks.clear();
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(head, forks[1], previousForks);
    asserts(forkPresent, "Fork " + forks[1] + " root is present in tree, your code returned " +
            (forkPresent ? "true" : "false"));
    asserts(previousForks.empty(), "Fork " + forks[1] + " is the root, so previous forks should be empty");
    //T2:intermediate node
    previousForks.clear();
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(head, forks[6], previousForks);
    asserts(forkPresent, "Fork " + forks[6] + " intermediate is present in tree, your code returned " +
            (forkPresent ? "true" : "false"));
    vector<string> expected_previous_forks_intermediate{ forks[2], forks[1] };
    asserts(previousForks == expected_previous_forks_intermediate,
            "Your code should return (" + forks[2] + " " + forks[1] +
            ") as ancestors of fork " + forks[6]);
    //T3:leaf node
    previousForks.clear();
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(head, forks[10], previousForks);
    asserts(forkPresent, "Fork " + forks[10] + " leaf is present in tree, your code returned " +
           (forkPresent ? "true" : "false"));

    vector<string> expected_previous_forks_leaf{ forks[5], forks[2], forks[1] };
    asserts(previousForks == expected_previous_forks_leaf,
            "Your code should return (" + forks[5] + " " + forks[2] + " " + forks[1] +
            ") as ancestors of fork " + forks[10]);
    //T4:empty tree
    CryptoForkNode *emptyTree_test = nullptr;
    previousForks.clear();
    forkPresent = CryptoForkTree::findPreviousForksLeadingToACryptoFork(emptyTree_test, forks[1], previousForks);
    asserts(!forkPresent, "Fork " + forks[1] + " is not present in an empty tree, your code returned " +
            (forkPresent ? "true" : "false"));
    asserts(previousForks.empty(), "Empty tree should return empty previous forks vector");

    // TODO - your code for testing findPreviousForksLeadingToACryptoFork using the given sample tree above

    // Test findCryptoForkNodeLevel function ------------------------------------------------
    int forkLevel = CryptoForkTree::findCryptoForkNodeLevel(head, forks[4], 0);
    asserts(forkLevel == 1, "Level of Fork " + forks[4] + " should be 1, your code returns " +  
            to_string(forkLevel));

    //my tests findCryptoForkNodeLevel
    //T1:root node test
    forkLevel = CryptoForkTree::findCryptoForkNodeLevel(head, forks[1], 0);
    asserts(forkLevel == 0, "Level of Fork " + forks[1] + " root should be 0, your code returns " +
            to_string(forkLevel));
    //T2:intermediate node
    forkLevel = CryptoForkTree::findCryptoForkNodeLevel(head, forks[6], 0);
    asserts(forkLevel == 2, "Level of Fork " + forks[6] + " intermediate should be 2, your code returns " +
            to_string(forkLevel));
    //T3:non existent node
    forkLevel = CryptoForkTree::findCryptoForkNodeLevel(head, "nonexistent", 0);
    asserts(forkLevel == CryptoForkNode::NOT_FOUND, "Level of Fork nonexistent should be " +
            to_string(CryptoForkNode::NOT_FOUND) + ", your code returns " + to_string(forkLevel));
    //T4:leaf node test
    CryptoForkNode leafNode = CryptoForkNode("blah");
    forkLevel = CryptoForkTree::findCryptoForkNodeLevel(&leafNode, "blah", 0);
    asserts(forkLevel == 0, "findCryptoForkNodeLevel() leaf node test failed");

    // TODO - your code for testing findCryptoForkNodeLevel using the given sample tree above

    // Test findClosestSharedAncestor function ----------------------------------------------
    // Call the function with combinations of the arguments
    // Assert / verify the returned CryptoForkNode* has the expected CryptoForkNode

    //my tests findClosestSharedAncestor
    //T1: here i test that both nodes are leaf nodes with common ancestor
    CryptoForkNode* sharedAncestor = CryptoForkTree::findClosestSharedAncestor(head, forks[10], forks[11]);
    asserts(sharedAncestor->getCryptoForkName() == forks[2],
            "Closest shared ancestor of " + forks[10] + " and " + forks[11] + " should be " + forks[2] +
            ", your code returned " + sharedAncestor->getCryptoForkName());
    //T2:one node is an ancestor of the other
    sharedAncestor = CryptoForkTree::findClosestSharedAncestor(head, forks[2], forks[10]);
    asserts(sharedAncestor->getCryptoForkName() == forks[2],
            "Closest shared ancestor of " + forks[2] + " and " + forks[10] + " should be " + forks[2] +
            ", your code returned " + sharedAncestor->getCryptoForkName());
    //T3: nodes have the root as common ancestor
    sharedAncestor = CryptoForkTree::findClosestSharedAncestor(head, forks[6], forks[9]);
    asserts(sharedAncestor->getCryptoForkName() == forks[1],
            "Closest shared ancestor of " + forks[6] + " and " + forks[9] + " should be " + forks[1] +
            ", your code returned " + sharedAncestor->getCryptoForkName());


    // TODO - your code for testing findClosestSharedAncestor

    // Test findNumOfAncestorsBetween function -----------------------------------------------
    int numAncestors = CryptoForkTree::findNumOfAncestorsBetween(head, forks[10], forks[11]);
    asserts(numAncestors == 3, "Ancestors between " + forks[10] + " and " + forks[11] + 
            " should be 3, your code returns " + to_string(numAncestors));
    //my tests
    //T1:one node is an ancestor of the other
    numAncestors = CryptoForkTree::findNumOfAncestorsBetween(head, forks[2], forks[10]);
    asserts(numAncestors == 1, "Ancestors between " + forks[2] + " and " + forks[10] +
            " should be 1, your code returns " + to_string(numAncestors));
    //T2:nodes with the root as common ancestor
    numAncestors = CryptoForkTree::findNumOfAncestorsBetween(head, forks[6], forks[9]);
    asserts(numAncestors == 3, "Ancestors between " + forks[6] + " and " + forks[9] +
            " should be 3, your code returns " + to_string(numAncestors));


    // TODO - your code for testing findNumOfAncestorsBetween using the given sample tree above

    // Test deleteCryptoForkTree function ----------------------------------------------------
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteCryptoForkTree function at the end of this driver testing code
    // to delete all the allocated memory for the nodes in the tree. 

    CryptoForkTree::deleteCryptoForkTree(head);

    // Use the printed forks along the sequence of deletion to verify your implementation
    
    // TODO IMPORTANT: IN ADDITION to the TODOs above, 
    //                 You MUST also construct at least one different tree 
    //                 that is similar to the given example tree above for all your tests

        //my additional tree, using eth forks
        //switch from head, to head2 in order to test
    CryptoForkNode *head2 = new CryptoForkNode("root", vector<string>{"frontier", "homestead"});
    CryptoForkNode *child1 = head2->getDirectForks().at(0);
    CryptoForkNode *child2 = head2->getDirectForks().at(1);
    child1->addFork("classic");
    child2->addFork("spurious_dragon");

    CryptoForkTree::deleteCryptoForkTree(head2);//mitigate memory leak

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}
