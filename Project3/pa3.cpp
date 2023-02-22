#include "HuffmanTree.h"

map<char, int> create_freq_map(string filename){
    ifstream file(filename, std::ios::binary);

    map<char, int> letter_freqs; 

    char c;
    while (file.get(c)) {
        if (letter_freqs.count(c) == 1){
            letter_freqs[c]++;
        } else {
            letter_freqs[c] = 1;
        }
    }

    return letter_freqs;
}

// Create the huffman tree from the letter frequencies
HuffmanTree create_tree_from_freq(map<char, int> letters){

    // create the queue with the letters and their respective frequencies
    priority_queue<Node*, vector<Node*>, node_cmp> queue;
    for (auto letter : letters) {
        Node* node = new Node(letter.first, letter.second);
        queue.push(node);
    }

    while(queue.size() != 1){
        // Removed the two lowest frequencies
        Node *left = queue.top();
        queue.pop();
        Node *right = queue.top();
        queue.pop();

        // Create a new node from the two previous nodes
        Node* node = new Node(0, left->freq + right->freq);
        node->left = left;
        node->right = right;
        queue.push(node);
    }

    // Create the huffman tree from the queue
    HuffmanTree tree = HuffmanTree(queue.top());
    tree.encode(tree.root, "");

    return tree;
}

// counts the total number of characters in the file that is being compressed
int count_chars(map<char, int> letter_freqs){
    int chars = 0;
    for (auto letter : letter_freqs) {
        chars += letter.second;
    }
    return chars;
}

// creates the code table from the compressed file and returns the index where the table ends
map<char, string> create_code_table(ifstream &file){
    map<char, string> code_table;

    int table_entries = file.get() + 1;
    int n = 1; // starting index 
    
    // variables to help with creating the code table
    char letter;
    int bin_length;
    char byte[2];
    bitset<16> bits;

    while(n <= table_entries){
        file.read(&letter, 1);
        bin_length = file.get();

        if (bin_length <= 8){ // if less than 8 bits, we only need 1 byte
            file.read(byte, 1);
            bits = (byte[0] << 8);
        } else {             // if more than 16 bits, we need 2 bytes
            file.read(byte, 2);
            bits = ((byte[0] << 8) | (byte[1] & 0xFF));
        }

        code_table[letter] = bits.to_string().substr(0, bin_length);
        n++;
    }

    return code_table;
}


// create a reverse version of the code table (key = binary code, value = letter)
map<string, char> reverse_code_table(map<char, string> code_table){
    map<string, char> code_table_rev;

    for (const auto &letter : code_table){
        code_table_rev[letter.second] = letter.first;
    }   

    return code_table_rev;
}


int main(int argc, char *argv[]) {
    if (strcmp(argv[1],"-c") == 0){// ./compressor -c some_file.ext compressed_file.cmpr
        map<char ,int> letter_freqs = create_freq_map(argv[2]);
        HuffmanTree tree = create_tree_from_freq(letter_freqs);
        tree.char_count = count_chars(letter_freqs);

        tree.create_compressed_file(argv[2], argv[3]); 
    }

    else if (strcmp(argv[1], "-u") == 0) { // ./compressor -d compressed_file.cmpr some_file.ext 
        ifstream infile(argv[2], ios::binary);

        // Create a map with the codes
        map<char, string> code_table = create_code_table(infile);
        map<string, char> reverse_table = reverse_code_table(code_table);

        ofstream outfile(argv[3]);

        // helper variables 
        char byte;
        string bin_code;
        bitset<8> bits;

        while (!infile.eof()){
            if(bool(infile.get(byte)) == 0) break; 
            bits = byte & 0xFF;

            for (int i = 0; i < 8; i++){
                bin_code += bits.to_string()[i];
                if (reverse_table.count(bin_code) == 1){

                    // bitset<8> binary(bin_code);
                    // int decimal = (int)binary.to_ulong();
                    // if (decimal == 13){
                    //     goto endOfLoop;
                    // }
                    // endOfLoop:

                    outfile.write(&reverse_table[bin_code], 1);
                    bin_code = "";
                }
            }
        }

        infile.close();
        outfile.close();
    }


    return 0;
}
