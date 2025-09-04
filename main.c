/**
 * Tea Encrypt
 * 
 * Uses TEA for encrypting a block of two words using a given key.
 * It is defined in tea_encrypt.s
 */
extern void tea_encrypt(int* v, int* key);

/**
 * Tea Decrypt
 * 
 * Uses TEA for decrypting a block of two words using a given key.
 * It is defined in tea_decrypt.s
 */
extern void tea_decrypt(int* v, int* key);

void print_char(char c) {
    // In a real bare-metal environment, this would write to UART
    // For now, this is just a placeholder
    volatile char *uart = (volatile char*)0x10000000;
    *uart = c;
}

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

/**
 * Print words
 * 
 * Extract the characters inside array of words and calls print_char
 */
void print_words(const int* words, int count) {
    for (int i = 0; i < count; i++) {
        int word = *(words + i);

        char c1 = (word >> 24) & 0xFF;
        char c2 = (word >> 16) & 0xFF;
        char c3 = (word >> 8) & 0xFF;
        char c4 = (word) & 0xFF;

        if (c1) print_char(c1);
        if (c2) print_char(c2);
        if (c3) print_char(c3);
        if (c4) print_char(c4);
    }

    print_char('\n');
}

/**
 * Get words
 * 
 * Translates a string to 32-bit words and stores them in array.
 * Uses zero-padding for completing 8-byte blocks.
 */
int get_words(int* words, const char* string) {
    const char* s = string;
    while (*s) s++;

    int len = s - string;
    int total_words = (len + 3) / 4;

    if (total_words % 2 != 0) total_words++;

    for (int i = 0; i < total_words; i++) {
        int w1 = (i*4 + 0 < len) ? ((unsigned char)string[i*4 + 0] << 24) : 0;
        int w2 = (i*4 + 1 < len) ? ((unsigned char)string[i*4 + 1] << 16) : 0;
        int w3 = (i*4 + 2 < len) ? ((unsigned char)string[i*4 + 2] << 8)  : 0;
        int w4 = (i*4 + 3 < len) ? ((unsigned char)string[i*4 + 3])       : 0;

        words[i] = w1 | w2 | w3 | w4;
    }

    return total_words;
}

int main() {

    // Predefined strings for user to choose.
    char* predefined_strings[6] = {
        "HOLA1234",
        "Mensaje de prueba para TEA",
        "Bizcocho sabroso",
        "El Boeing 777 despega hoy",
        "Ya perdi el septiembre sin fap",
        "Quien para una birra?"
    };

    // Availables keys for encryption and decryption.
    int key[4] = {0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210};  // Clave original: 0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210

    int words[64];

    print_string("\nPruebas:\n");

    for (int i = 0; i < 6; i++) {
        int total = get_words(words, predefined_strings[i]);

        // Printing the string the user chose
        print_string("\nCadena original:\n");
        print_words(words, total);

        for (int i = 0; i < total; i += 2) {
            tea_encrypt(words + i, key); // Calling encryption
        }

        // Printing result of encryption
        print_string("Encriptada:\n");
        print_words(words, total);

        for (int i = 0; i < total; i += 2) {
            tea_decrypt(words + i, key); // Calling decryption
        }

        // Printing result of decryption (should be the same as the original string)
        print_string("Decriptada:\n");
        print_words(words, total);
    }

    // Infinite loop to keep QEMU running.
    while (1) {
        __asm__ volatile ("nop");
    }
}

