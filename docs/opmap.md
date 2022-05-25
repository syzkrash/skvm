# opmap

The [opmap](opmap) is a simple text file containing all the skvm opcodes. This
file is used to generate a header file used by skvm itself.

If you wish to add a new opcode, simply add a new line with this syntax:

```c
MY_OPCODE 0xF1
```

You can also use C-style line comments:

```c
// this is a cool opcode!
MY_OPCODE 0xF1
```

Then, to apply the changes to skvm, run the [`gen_op.py`](gen_opt.py) script.

You can feel free to use this file for external tools that need to interface
with skvm bytecode. Like a (dis)assembler or other code inspection or generation
tools.
