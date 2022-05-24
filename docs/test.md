# Compiling test program

The test program calls functions and uses types from [`vm.h`](src/vm.h) and
files include from within it.

This requires you to have already compiled `vm.o` and `stack.o`.

```shell
gcc -Os -Wall -Wpedantic -c src/stack.c -o bin/stack.o
gcc -Os -Wall -Wpedantic -c src/vm.c -o bin/vm.o
```

Compile those two into a shared object:

```shell
gcc -pie -shared bin/vm.o bin/stack.o -o bin/skvm.so
```

Then, compile the program with the library:

```shell
gcc -Os -Wall -Wpedantic -Lbin -lskvm src/main.c -o bin/main
```

You can now run the `bin/main` executable, provideed `skvm.so` is also present.
