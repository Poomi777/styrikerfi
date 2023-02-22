#include "HuffmanTree.h"

Node::Node(char letter, long freq){
    this->freq = freq;
    this->letter = letter;
    this->left = nullptr;
    this->right = nullptr;
}

HuffmanTree::HuffmanTree(Node* root){
    this->root = root;
}

// Creates the tree and the leafs 
void HuffmanTree::encode(Node* root, string curr_code){
    if (root == nullptr){
        return;
    }

    if (root->left == nullptr && root->right == nullptr){
        code_table[root->letter] = curr_code;
    }

    encode(root->left, curr_code + "1");
    encode(root->right, curr_code + "0");
}

// Write the code table to the compressed file 
void HuffmanTree::write_header(ofstream &file){

    // Write the number of code table entries to the compressed file
    unsigned char num_entries = code_table.size() - 1; // test að gera -1, svo plus þegar þetta er sott
    file.write((const char*)&num_entries, sizeof(num_entries));

    bitset<16> bits;
    int bit_count = 0;

    // Write the code table on the format: LETTER - BINARY CODE LENGTH - BINARY CODE 
    for (const auto& letter : code_table){
        // Write the letter
        file.write(&letter.first, sizeof(letter.first));

        // Write the length of the letter's binary code
        unsigned char code_length = letter.second.size();
        file.write((const char*)&code_length, sizeof(code_length));

        // Write the binary code
        for (char c : letter.second) {
            if (c == '0') {
                bits.reset(15-bit_count);
            } else {
                bits.set(15-bit_count);
            }

            bit_count++;

            // If the bitset is full, write the byte to the file and restart the bitset
            if (bit_count == letter.second.length()) {
                if (bit_count <= 8){
                    unsigned char byte = (bits.to_ulong() >> 8) & 0xFF;

                    file.write((char*)&byte, 1);
                } else{ // if the string is 9-16 bits, split it in two bytes
                    unsigned long value = bits.to_ulong();
                    unsigned char upper = (value >> 8) & 0xFF;
                    unsigned char lower = value & 0xFF;

                    file.write((char*)&upper, 1);
                    file.write((char*)&lower, 1);
                }
                bit_count = 0;
            }
        }
    } 
}

// Writes the binary codes as bits to the file
void HuffmanTree::write_data(ofstream &file, string org_file){
    ifstream fin(org_file, std::ios::binary);

    char letter;
    string bin_code;

    // Bitset to store the binary representation of each character 
    bitset<8> bits;
    int bit_count = 0;

    while (!fin.eof()) {
        if(bool(fin.get(letter)) == 0) break;

        bin_code = code_table[letter];

        // Store each character of the binary code in the bitset
        for (char c : bin_code) {
            if (c == '0') {
                bits.reset(7-bit_count);
            } else {
                bits.set(7-bit_count);
            }

            bit_count++;

            // If the bitset is full, write the byte to the file and restart the bitset
            if (bit_count == 8) {
                unsigned char byte = bits.to_ulong() & 0xFF;
                file.write((char*)&byte, 1);
                bit_count = 0;
            }
        }
    }

    // If there are any bits left in the bitset, write the remaining bits as a byte padded with 0
    if (bit_count > 0) {
        bits = bits << (8 - bit_count);
        unsigned char byte = bits.to_ulong() & 0xFF;
        file.write((char*)&byte, 1);
    }
}

void HuffmanTree::create_compressed_file(string org_file, string enc_file){
    ofstream fout(enc_file, ios::binary);

    write_header(fout);
    write_data(fout, org_file);

    fout.close();
}