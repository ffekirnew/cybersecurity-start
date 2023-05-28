from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes


def main():
    key = bytearray.fromhex("95fa2030e73ed3f8da761b4eb805dfd7")
    ciphertext = bytearray.fromhex('d06bf9d0dab8e8ef880660d2af65aa82')
    iv = bytearray.fromhex('09080706050403020100A2B2C2D2E2F2')


    cipher = Cipher(algorithms.AES(bytes(key)), modes.CBC(iv))
    decryptor = cipher.decryptor()
    guess = decryptor.update(ciphertext)+ decryptor.finalize()

    print(guess)

if __name__ == "__main__":
    main()

