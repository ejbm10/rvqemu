extern void tea_encrypt(int* v, int* key);

extern void tea_decrypt(int* v, int* key);

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
    char* predefined_strings[6] = {
        "HOLA1234",
        "Mensaje de prueba para TEA",
        "Bizcocho sabroso",
        "El Boeing 777 despega hoy",
        "Ya perdi el septiembre sin fap",
        "Quien para una birra?"
    };

    int key[4] = {0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210};

    int words[64];

    int total = get_words(words, predefined_strings[0]);

    for (int i = 0; i < total; i += 2) {
        tea_encrypt(words + i, key);
    }
}

