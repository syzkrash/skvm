from datetime import datetime


OPMAP_FN    = "opmap"
HEADER_FN   = "src/opcodes.h"
HEADER_OP   = "#define OP_%s ((op)%s)\n"
HEADER_STUB = "uint8_t op_%s(struct VM*);\n"
HEADER_CASE = "    case OP_%s: return &op_%s;\n"
HEADER_TMPL = """
// Generated with gen_op.py [%s]
// Don't edit manually
#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef uint8_t op;
typedef uint8_t(opfunc)(struct VM*);

%s

// get_op_func returns the function corresponding to the given opcode
static opfunc *get_op_func(op opcode)
{
  switch(opcode)
  {
%s
    default: return NULL;
  }
}

#endif
""".strip()

def main() -> int:
	opmap = dict()

	# read opcode values from the opmap
	with open(OPMAP_FN, "rt") as f:
		for line in f:
			# remove possible indentation, trailing whitespace, etc
			line = line.strip()
			# ignore comments and empty lines
			if line.startswith("//") or line == "":
				continue
			# change multiple spaces to one space
			while "  " in line:
				line = line.replace("  ", " ")
			# take the first two elements and ignore rest
			op, val, *_ = line.split(" ")
			# assign to opmap
			opmap[op] = val

	# write the opcodes to opcodes.h
	with open(HEADER_FN, "wt") as f:
		# pregenerate #define's, function stubs and switch/case statement
		header_ops = ""
		header_case = ""
		for op, val in opmap.items():
			header_ops += HEADER_OP % (op.upper(), val)
			header_ops += HEADER_STUB % (op.lower())
			header_case += HEADER_CASE % (op.upper(), op.lower())
		# write the header with the #define lines
		f.write(HEADER_TMPL % (datetime.now(), header_ops, header_case))

	return 0

if __name__ == "__main__":
	exit(main())
