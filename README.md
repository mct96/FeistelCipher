# Feistel Cipher
Implementação do algoritmo de Feistel (Utilizado no DES) - Criptografia de chave simétrica.

# Como funciona?
  - Divida o bloco em duas partes: leftBlock e rightBlock.
  - O rightBlock é deslocado para o leftBlock, tornando-se o rightBlock'.
  - O leftBlock' é atribuído ao resultado de: ```leftBlock XOR F(rightBlock, Key)```. O resultado é deslocado para a direita.
  - Esse processo se repete ```N``` vezes, onde ```N``` é o número de rounds.

# Características
 :straight_ruler: Chave de 56 bits.\
 :closed_lock_with_key: Criptografia e Descripgrafia implementados.\
 :loop: 7 Rounds.\

# Como utilizar
  ```
  git clone https://github.com/MatheusCTeixeira/FeistelCipher
  cd FeistelCipher
  make
  ```

# Demonstração
![Demonstração](https://github.com/DarkMCT/host_images/blob/master/feistel/deepin-screen-recorder_dde-file-manager_20190803171123.gif?raw=true)
