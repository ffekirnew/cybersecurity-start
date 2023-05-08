#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define KEYSIZE 16
#define STARTTIME 1523988529

int main()
{
    int i, j;
    int hour = 3600;
    char trial_key[KEYSIZE];

    // Define the target ciphertext
    char ciphertext_hex[] = "d06bf9d0dab8e8ef880660d2af65aa82";
    unsigned char ciphertext[KEYSIZE];
    for (i = 0; i < KEYSIZE; i++) {
        sscanf(&ciphertext_hex[2*i], "%2hhx", &ciphertext[i]);
    }

    // Iterate over the trial keys and check for a match
    for (i = 0; i < 2 * hour; i++)
    {
        // Generate the next trial key
        srand(STARTTIME + i);
        for (j = 0; j < KEYSIZE; j++)
        {
            trial_key[j] = rand() % 256;
        }

        // Decrypt the ciphertext using the trial key
        EVP_CIPHER_CTX *ctx;
        ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, (unsigned char*)trial_key, NULL);
        unsigned char decrypted[KEYSIZE];
        int len;
        EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, KEYSIZE);
        int decrypted_len = len;
        EVP_DecryptFinal_ex(ctx, decrypted + len, &len);
        decrypted_len += len;
        EVP_CIPHER_CTX_free(ctx);

        // Compare the decrypted plaintext with a known plaintext value
        char known_plaintext_hex[] = "255044462d312e350a25d0d4c5d80a34";
        unsigned char known_plaintext[KEYSIZE];
        for (j = 0; j < KEYSIZE; j++) {
            sscanf(&known_plaintext_hex[2*j], "%2hhx", &known_plaintext[j]);
        }

        printf("%s - ", decrypted);
        printf("%s\n", known_plaintext_hex);

        if (memcmp(decrypted, known_plaintext, KEYSIZE) == 0) {
            printf("Match found! Key: ");
            for (j = 0; j < KEYSIZE; j++) {
                printf("%.2x", (unsigned char)trial_key[j]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("No match found.\n");
    return 1;
}
