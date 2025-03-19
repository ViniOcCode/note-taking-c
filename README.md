# DISCLAIMER 

This was made by me, and only in 1 week for CS50.
Most of the time, I had no idea what I was doing. Therefore, if you find something horrendous or awful that violates all coding principles, feel free to make your own modifications!

# What is note-taking-c?

Note-taking-c is exactly what the name suggests—a note-taking application entirely written in C.

---

## Why?

This project was developed as a Final Project for Harvard's CS50 2025!  

---

## Docker!

Compiling C programs can be a bit tedious, so I've prepared a Docker image that installs everything you need to run the application inside a container.

### How to use it

First, make sure you have Docker properly installed.
Then, in your preferred terminal, run the following commands:

```bash
git clone https://github.com/ViniOcCode/note-taking-c.git
cd note-taking-c
docker run --rm -v $(pwd):/app -it vinioc/note-taking-c
```

In Powershell is the same thing but, you have change (pwd) to {pwd}:

```powershell
git clone https://github.com/ViniOcCode/note-taking-c.git
cd note-taking-c
docker run --rm -v ${pwd}:/app -it vinioc/note-taking-c
```

This way, you can use the application without installing Python, Python venv, Meson, and Ninja on your system.

---

## USING THE APPLICATION WITH DOCKER

Every time you want to use the application, execute the following command:

```bash
meson setup builddir && ninja -C builddir
export EDITOR=vim // set you favorite terminal
./builddir/notes <command> <args>
```

---

## NOTES COMMANDS

### **new <category> <name>** — Create a new note

Creating a note is simple. You need to specify a category (the folder where the note will be created).  
You can choose a name for the note; if no name is provided, it will default to `new_note.md`.

### **edit <category> <name>** — Edit an existing note

Editing follows the same logic. Specify the category and note name to open it.  
If you just use the `edit` command without arguments, it will open the main notes folder.

### **remove <category> <name>** — Remove a note

You can remove an entire category folder with all its notes or just a specific note.

### **rename <old> <new> <newnamenote>** — Rename a category or note

The `rename` command might seem a bit confusing, but it's the best approach I could think of.  

- If you provide **two arguments** (`<old>` and `<new>`), you are renaming a folder:

```bash
notes rename oldname newname
```
This renames the folder `oldname` to `newname`.

- If you provide **three arguments** (`<folder> <old>` and `<new>`), you are renaming a note inside a folder:

```bash
notes rename folder oldname newname
```
This renames the note `oldname.md` to `newname.md` inside the `folder`.

### **backlink <keyword>** — Search for a given keyword

Provide a keyword to find where it appears across your notes.

### **ls --oneline** — List notes in a simple format

Displays a list of categories and notes in a straightforward, one-line format.

### **ls --full** — List notes with details

Displays detailed information, including the content of the notes.

---

If you need more help or further adjustments, just let me know!
