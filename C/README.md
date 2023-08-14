# ARVORE BINARIA EM C

## Compilar e Rodar (UNIX)

### Como compilar

```
gcc main.c tree.c treeNode.c -o binary_tree 
```

### Como rodar

```
./binary_tree 
```

## Compilar e Rodar (WINDOWS)

### Criar imagem (DOCKER)

```
docker build -t tigredomexico/gcc:1.0 .
```

### Como rodar

```
docker run -i -t -v "%cd%":/source tigredomexico/gcc:1.0 make /source/binary_tree
docker run -i -t -v "%cd%":/source tigredomexico/gcc:1.0 ./binary_tree
```

