# Compilando o emulador CHIP-8

Este documento descreve como compilar o emulador CHIP-8 contido neste repositório em um sistema Linux (ex.: Ubuntu/Debian). As instruções assumem que você tem as fontes em `src/` e as ROMs em `roms/` como neste projeto.

## Pré-requisitos

1. Um compilador C++ moderno (g++). Ex.: g++ (GCC) 9+ recomendado.
2. Biblioteca SDL2 (desenvolvimento) para renderização, entrada e áudio.

No Ubuntu/Debian instale as dependências necessárias com:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev build-essential
```

> Observação: se você já tiver o SDL2 instalado por outro método (pacote, vcpkg, brew etc.), adapte conforme necessário.

## Comando de compilação (passo um)

Abra a pasta principal do projeto no VS Code (ou em um terminal) e execute o comando abaixo na raiz do repositório:

```bash
g++ src/*.cpp -I src -lSDL2 -pthread -o chip8 -lm
```

O que esse comando faz (resumo):

- `g++ src/*.cpp` — compila todos os arquivos `.cpp` em `src/`.
- `-I src` — adiciona `src/` ao caminho de inclusão para que headers locais (`*.h`) sejam encontrados.
- `-lSDL2` — linka contra a biblioteca SDL2 (dependência principal).
- `-pthread` — habilita suporte a threads (se o projeto usa threads).
- `-o chip8` — nome do executável de saída.
- `-lm` — linka a biblioteca matemática (libm) — usada por algumas operações matemáticas.

### Usando o Makefile

Na raiz do projeto você pode usar os seguintes comandos:

- Compilar (equivalente ao comando g++ acima):

```bash
make build
```

- Executar uma ROM (substitua pelo caminho da ROM):

```bash
make run ROM=roms/TETRIS
```

- Compilar com símbolos de depuração:

```bash
make debug
```

- Compilar versão otimizada (release):

```bash
make release
```

- Limpar artefatos:

```bash
make clean
```

O alvo `run` exige a variável `ROM`. Se não for fornecida, o Make exibirá a mensagem de uso.

## Saída esperada

Após a compilação bem-sucedida você terá um executável `chip8` na raiz do projeto. Se ocorrerem erros de link relacionados ao SDL2, verifique se as bibliotecas de desenvolvimento do SDL2 estão corretamente instaladas (veja seção Pré-requisitos).

## Próximos passos

- Depois de compilar, consulte `docs/README_USAR.md` para instruções de execução e mapeamento de teclas.

