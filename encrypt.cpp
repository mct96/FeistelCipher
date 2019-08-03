#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

using byte = unsigned char;

// Extrai os bits mais significativos.
byte higherOrderBits(byte data) {
    byte mask = 0b11110000;
    return (mask & data) >> 4;
}

// Extrai os bits menos significativos.
byte lowerOrderBits(byte data) {
    byte mask = 0b00001111;
    return mask & data;
}

// Round function.
byte f(byte right, byte key) {
    return right ^ lowerOrderBits(key) & right ^ higherOrderBits(key);
}

// Realiza o round.
byte round(byte data, byte key, byte(*)(byte, byte)) {
    // Separa os bits.
    byte leftBits  = higherOrderBits(data);
    byte rightBits = lowerOrderBits(data) ;

     // Testa a divisão
    assert(((leftBits << 4) | rightBits) == data);

    // Faz o round e aplica a função aos bits à direita.
    byte newleftBits  = rightBits;
    byte newrigthBits = leftBits ^ f(rightBits, key);

    return (newleftBits << 4 | newrigthBits);
}

byte unround(byte data, byte key, byte(*)(byte, byte)) {
    // Separa os bits.
    byte leftBits  = higherOrderBits(data);
    byte rightBits = lowerOrderBits(data) ;

     // Testa a divisão
    assert(((leftBits << 4) | rightBits) == data);

    // Faz o processo inverso do round.
    byte newRightBits = leftBits;
    byte newLeftBits = rightBits ^ f(leftBits, key);

    return (newLeftBits << 4 | newRightBits);
}

// Criptografa utilizando o algoritmo de Feistel.
string encrypt(string plaintext, char key[8], int rounds) {
    string cipher = plaintext;

    // Aplica os rounds conforme específicado nos parametros.
    int keyIndex = 0;
    while (rounds--) {
        for (int i=0; i < cipher.size(); ++i) {
            byte data = (byte)cipher[i];
            byte k    = key[keyIndex];

            cipher[i] = unround(data, k, f);
        }

        keyIndex = (keyIndex + 1) % 8;
    }

    return cipher;
}

// Descriptografa utilizando o algoritmo de Feistel.
string decrypt(string cipher, char key[8], int rounds) {
    string plaintext = cipher;

    // Desfaz os rounds conforme especificado nos parametros.
    int keyIndex = (rounds - 1) % 8;
    while (rounds--) {
        for (int i=0; i < cipher.size(); ++i) {
            byte data = (byte)cipher[i];
            byte k    = key[keyIndex];

            cipher[i] = round(data, k, f);
        }

        keyIndex = (keyIndex == 0 ? 7 : keyIndex - 1);
    }

    return cipher;
}

int main(int argc, char ** argv) {

    // Chave para criptografar.
    char key[8] = "=-÷×&";

    // Texto a ser criptografado.
    string input{};

    if (argc == 2)
        cin >> input;
    else
        input = argv[2];

    // Exibe o resuldado requisitado.
    if (string{argv[1]} == "-e") {
        // Criptografa a mensagem.
        string encrypted = encrypt(input, key, 7);

        cout << encrypted << endl;
    } else if (string{argv[1]} == "-d") {
        // Descriptogra a mensagem cifrada.
        string decrypted = decrypt(input, key, 7);

        cout << decrypted << endl;
    }

    return 0;
}