# Como usar o emulador CHIP-8

Este documento explica como executar ROMs com o emulador CHIP-8 compilado a partir deste repositório e traz dicas úteis para testes, mapeamento de teclas e solução de problemas.

## Executando uma ROM

Após compilar (veja `docs/README_COMPILAR.md`), execute o emulador passando o caminho da ROM como argumento. Exemplo — executar o TETRIS incluído no diretório `roms/`:

```bash
./chip8 roms/TETRIS
```

Se você preferir usar o `Makefile` incluído, pode executar:

```bash
make run ROM=roms/TETRIS
```

O alvo `run` irá compilar (se necessário) e executar o binário com a ROM fornecida.

Se quiser passar flags/argumentos adicionais para o emulador (por exemplo, `--scale 20`), há duas formas:

- Executando diretamente:

```bash
./chip8 roms/TETRIS --scale 20
```

- Usando o `Makefile` (o `run` aceita a variável `ARGS` que é passada para o binário):

```bash
make run ROM=roms/TETRIS ARGS="--scale 20"
```

Ambas as formas são equivalentes: o `Makefile` apenas automatiza a compilação antes da execução e repassa o argumento `--scale 50` para o executável.

Você pode executar qualquer ROM apontando para o arquivo desejado:

```bash
./chip8 roms/NOME_DA_ROM.ch8
# ou caminho absoluto
./chip8 /home/usuario/Downloads/roms/MAZE
```

Se não fornecer um caminho válido, o programa pode encerrar com mensagem de erro — verifique o caminho da ROM.

## ROMs incluídas

O repositório inclui algumas ROMs de exemplo em `roms/`, por exemplo:

- `TETRIS`
- `PONG`
- `MAZE`

Coloque ROMs adicionais na pasta `roms/` ou indique o caminho completo quando executar o binário.

## Mapeamento de teclas

O CHIP-8 usa um teclado hexadecimal (16 teclas: 0x0–0xF). Muitos emuladores usam o seguinte mapeamento de teclado físico para as teclas hexadecimais:

```
1 2 3 4    -> 1 2 3 C
Q W E R    -> 4 5 6 D
A S D F    -> 7 8 9 E
Z X C V    -> A 0 B F
```

Observação: esse é o mapeamento padrão em muitos emuladores, mas o mapeamento exato pode variar. Se quiser confirmar o mapeamento utilizado por este emulador, abra `src/input.cpp` (arquivo responsável pela entrada) e verifique a associação de teclas.

## Redimensionamento / Escala da janela

Exemplos de uso para redimensionar em tempo de execução (quando o binário aceita a flag `--scale`):

```bash
# direto
./chip8 roms/TETRIS --scale 20

# via make
make run ROM=roms/TETRIS ARGS="--scale 20"
```
## Referências

- Especificação CHIP-8 (procure por “CHIP-8 specification”) para entender as operações e o teclado hexadecimal.
