# Note Taking C

[![Build and test](https://github.com/ViniOcCode/note-taking-c/actions/workflows/tests.yml/badge.svg)](https://github.com/ViniOcCode/note-taking-c/actions/workflows/tests.yml)

A small filesystem-first note manager written in C. Notes are plain Markdown files organized into category directories, so they remain readable and editable without the application.

This was my final project for **Harvard CS50x 2025**. I built it to practice command-line interface design, manual memory management, filesystem traversal, process integration, and portable build tooling.

## Features

- Creates Markdown notes inside category folders.
- Opens notes with the editor configured in `EDITOR` or `VISUAL`.
- Lists the note tree in compact or detailed form.
- Shows file metadata and a preview of Markdown files in detailed listings.
- Searches every Markdown note for backlinks or keywords.
- Renames categories or individual notes.
- Removes notes or category trees after interactive confirmation.
- Stores everything under `$HOME/notes`.
- Includes end-to-end CLI tests for argument handling and core file creation.

## Commands

```text
notes new <category> [name]
notes edit [category] [name]
notes remove <category> [name]
notes rename <old-category> <new-category>
notes rename <category> <old-note> <new-note>
notes backlink <keyword>
notes ls --oneline
notes ls --full
notes --help
```

When `name` is omitted from `new`, the file is created as `new_note.md`. Running `edit` without a category opens the main notes directory.

## Build locally

The application targets POSIX-compatible systems such as Linux and macOS.

### Requirements

- A C11 compiler
- Meson
- Ninja
- A terminal editor such as Vim or Nano

```bash
git clone https://github.com/ViniOcCode/note-taking-c.git
cd note-taking-c
meson setup builddir
meson compile -C builddir
export EDITOR=vim
./builddir/notes --help
```

Run the tests with:

```bash
meson test -C builddir --print-errorlogs
```

## Docker

Build the image:

```bash
docker build -t note-taking-c .
```

List notes while persisting them on the host:

```bash
mkdir -p "$HOME/notes"
docker run --rm -it \
  -v "$HOME/notes:/root/notes" \
  note-taking-c ls --oneline
```

Create or edit a note interactively:

```bash
docker run --rm -it \
  -v "$HOME/notes:/root/notes" \
  note-taking-c new learning c-notes
```

The image uses Vim as its default editor.

## How it works

```text
CLI dispatcher (main.c)
    -> note operations (notes.c)
    -> path/editor helpers (utils.c)
    -> recursive filesystem operations (dirutils.c)
    -> $HOME/notes/*.md
```

The project deliberately uses the local filesystem rather than a database. This keeps the data portable and makes the storage model easy to inspect.

## Project structure

```text
main.c          Command parsing and dispatch
notes.c         Create, edit, rename, remove, and search operations
utils.c         Paths, directories, editor selection, and confirmation
dirutils.c      Recursive listing, preview, search, and removal
meson.build     Build and test definition
tests/          End-to-end CLI behavior checks
Dockerfile      Reproducible Linux build and runtime
```

## Scope and limitations

This is an educational CLI project. It currently assumes POSIX filesystem APIs, delegates editing to an external terminal editor, and is intended for local single-user notes rather than synchronized or encrypted data.

## License

[MIT](LICENSE)

<details>
<summary><strong>Português</strong></summary>

## Sobre o projeto

O Note Taking C é um gerenciador de anotações em terminal escrito em C. As notas são arquivos Markdown comuns, organizados por categorias dentro de `$HOME/notes`.

O projeto foi desenvolvido como meu trabalho final do **Harvard CS50x 2025**, com foco em interface de linha de comando, gerenciamento manual de memória, navegação do sistema de arquivos e integração com editores externos.

### Principais recursos

- Criação e edição de notas Markdown.
- Organização por diretórios de categoria.
- Listagem simples ou detalhada, com metadados e prévia.
- Busca de palavras em todas as notas.
- Renomeação e remoção com confirmação.
- Build com Meson/Ninja, execução com Docker e testes da CLI.

O programa foi projetado para sistemas compatíveis com POSIX, como Linux e macOS.

</details>
