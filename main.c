extern void tea_encrypt(int* v, int* key);

extern void tea_decrypt(int* v, int* key);

int main() {
    int word[2] = {0x484F4C41, 0x31323334};

    int key[4] = {0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210};

    tea_encrypt(word, key);

    while(1) {
        __asm__ volatile ("nop");
    }
}

