# get_next_line

Este projeto implementa a função `get_next_line`, que retorna uma linha de um descritor de arquivo por chamada, incluindo o caractere de nova linha (`\n`). Ele foi desenvolvido como parte do currículo da 42 School.

## 📚 Objetivo

Implementar uma função em C que lê uma linha de um arquivo a cada chamada, com gerenciamento adequado de memória e buffers. A versão bônus oferece suporte à leitura simultânea de múltiplos file descriptors.

## 🧠 Funcionamento

A função principal `get_next_line(int fd)`:
- Lê caracteres de um arquivo até encontrar uma quebra de linha (`\n`) ou o fim do arquivo.
- Retorna a linha lida (incluindo `\n` se presente).
- Preserva qualquer conteúdo lido além da linha atual para a próxima chamada.

## 🧩 Arquivos

| Arquivo                       | Descrição                                                                 |
|------------------------------|---------------------------------------------------------------------------|
| `get_next_line.c`            | Implementação principal da função para um único file descriptor.         |
| `get_next_line_bonus.c`      | Versão com suporte a múltiplos file descriptors simultaneamente.         |
| `get_next_line_utils.c`      | Funções auxiliares utilizadas na versão normal.                          |
| `get_next_line_utils_bonus.c`| Funções auxiliares para a versão bônus.                                  |
| `get_next_line.h`            | Cabeçalho para a versão normal.                                          |
| `get_next_line_bonus.h`      | Cabeçalho para a versão bônus.                                           |
| `LICENSE`                    | Licença do projeto.                                                      |
| `test00`                     | Arquivo de teste para simular entradas de leitura.                      |

## ⚙️ Como usar

### Compilação

```bash
# Versão normal
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o gnl

# Versão bônus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

### Execução

```bash
./gnl < test00
```

Ou, no código, abra um arquivo:

```c
int fd = open("test00", O_RDONLY);
char *line;
while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

## 🧪 Testes

Você pode compilar o arquivo de teste comentado no final dos `.c` para verificar o funcionamento com um arquivo simples. Recomenda-se usar ferramentas como o `Valgrind` para checar vazamentos de memória:

```bash
valgrind --leak-check=full ./gnl
```

## 🔄 BUFFER_SIZE

O comportamento da função pode ser alterado modificando o valor de `BUFFER_SIZE` durante a compilação. Ele define o tamanho do buffer de leitura utilizado na função `read`.

## ✅ Regras de implementação

- Não é permitido usar funções da libc além de `read`, `malloc` e `free`.
- A função deve retornar `NULL` ao atingir o EOF ou em caso de erro.
- A memória deve ser devidamente gerenciada para evitar vazamentos.

## 📜 Licença

Este projeto está licenciado sob os termos do arquivo `LICENSE`.

---

> Projeto desenvolvido por [ngomes-t@student.42sp.org.br].
