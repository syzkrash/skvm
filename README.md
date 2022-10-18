# SKVM

SKVM (feel free to pronounce it "scum") is a VM designed specifically for the
[Skol][skol] language.

## Current status

The VM is not yet functional, but major parts, such as the [Object][object_c]
system and the [Stack][stack_c] are somewhat finished. Not yet tested though.

## How does it work?

SKVM uses 2 registers to perform all operations: P and S. Values can be taken
out of and put into these registers via a stack. Values can also be stored for
later use in locals.

For example, an `add` instruction would be equivalent to `P += S`, and a
`sub` instruction would be equivalent to `P -= S`. Since there are two registers,
operations may result in values in both registers. For example, a `divmod`
instruction would be equivalent to `P = P0 / S0; S = P0 % S0` where P0 and S0
are P and S before the instruction.

## Compilation

Simply run `make`. If you want extra debugging information, run `make DEBUG=1`.
Because it is (current year), the Makefile works both on Windows and Unix
systems. (provided you have [Clang][clang] installed of course)

[skol]: https://syzkrash.github.io/skol/
[object_c]: src/Object.c
[stack_c]: src/Stack.c
[clang]: https://clang.llvm.org/
