# RealNote

The RealNote application designed to... make notes!

## Introduction
Make notes, divide them into categories. What application does for you?

- just keep notes, do not bother you where they are
- keep notes historical versions in case you overriden something important
- do not bother you with questions like:
    - where should I store your notes?
    - should I save your note?
    - should I reload note changed by external app?

 it just keeps all versions in the "historical versions" box.

## Building
### Requirements:
- Linux or Windows OS (others are not tested)
- Qt 5.x
- CMake 3.13+
- Compiler that supports C++17

### Steps:

- Clone this repo **with submodules**

        git clone --recursive #paste link to this repo

- Build:
    - *Console way:*

        It may depend on your OS/generator/compiler. But if you are familiar with `CMake` basics, it should be easy.
    - *GUI way:*

        - Run `Qt Creator`
        - `File` → `Open File or Project` → select `QMakeLists.txt`
        - Select kit that meet requirements
        - Build and run

    - *Your own way*

        You may also use your favourite IDE that supports `CMake`. If there are problems, report them.