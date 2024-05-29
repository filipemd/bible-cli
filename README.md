# Bible CLI

![Bible CLI](screenshots/screenshot1.png)

Um simples programa de Bíblia escrito em C e a biblioteca [cJSON](https://github.com/DaveGamble/cJSON).

Os dados em JSON da Bíblia foram extraídos usando o [PyBible](https://github.com/filipemd/PyBible).

## Como compilar

São suportadas estas plataformas:
 - Linux;
 - MacOS;
 - BSD (por enquanto, apenas o FreeBSD foi testado).

### Instale um compilador de C/C++

Tanto o MacOS, quanto o FreeBSD já vem com um compilador C/C++ instalado (no caso o Clang), você pode verificar digitando no terminal:

```
clang --version
```

A maior parte das distros Linux também vem com um com um compilador C/C++ instalado (no caso o GCC). Você pode verificar digitando no terminal:

```
gcc --version
```

### Instale o Qt

#### MacOS

Para instalar o Qt no MacOS, digite no terminal (caso tenha o Homebrew instalado. Caso contrário, baixe o Homebrew):

```
brew install qt
```

#### Linux

Caso você use uma distro que tenha como interface gráfica ambientes de desktop baseados em Qt, como o KDE Plasma e o LXQt, você pode pular esta etapa.

Para instalar o Qt em distros baseadas no Debian:

```
sudo apt install qt6-base-dev
```

Para instalar o Qt em distros baseadas no Fedora:

```
sudo dnf install qt6-qtbase
```

Para instalar o Qt em distros baseadas no Arch:

```
sudo pacman -S qt6-base
```

### Instale o Make

O Make vem pré-instalado no Linux, no MacOS e no FreeBSD, mas a versão do FreeBSD tem uma sintaxe diferente, então instale o GMake:

```
sudo pkg install gmake
```

## Como utilizar a versão CLI

Digitando `./bible` na pasta do programa, vai aparecer isto:

```
Usage: 
bible <version> <book> <chapter> <verse>
```

 - version  - versão
 - book     - livro
 - chapter  - capítulo
 - verse    - versículo

Se você não colocar o versículo, vai aparecer o capítulo inteiro.