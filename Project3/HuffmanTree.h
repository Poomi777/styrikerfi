#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

class Node{
public:
    Node(char letter, long freq);
    char letter;
    int freq;
    Node *left;
    Node *right;
};

// Used to sort the priority queue
struct node_cmp
{
    bool operator()(Node* n1, Node* n2) 
    {
        return n1->freq > n2->freq;
    }
};


class HuffmanTree{
public:
    HuffmanTree(Node* root);

    // compressing
    void encode(Node* root, string curr_code);
    void create_compressed_file(string org_file, string enc_file);

    //uncompressing
    void create_tree_from_enc(map<char, string> encoding_map);
    Node* find_letter(Node* node, string letter_encoding); // þarf ekki  -------

    // variables
    Node* root;
    map<char, string> code_table;
    int char_count;

private: 
    void write_header(ofstream &file);
    void write_data(ofstream &file, string org_file);
    void add_letter(Node* root, char letter, string letter_encoding, string og_encoding); // þarf ekki ----
};