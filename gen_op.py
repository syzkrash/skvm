OPMAP_FN    = "opmap"
HEADER_FN   = "src/opcodes.h"
HEADER_OP   = "#define OP_%s ((op)%s)\n"
HEADER_TMPL = """
// Generated with gen_op.py
// Don't edit manually
#ifndef OPCODES_H
#define OPCODES_H

typedef uint8_t op;

%s
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
			opmap[op.upper()] = val

	# write the opcodes to opcodes.h
	with open(HEADER_FN, "wt") as f:
		# pregenerate all the #define lines
		header_ops = ""
		for op, val in opmap.items():
			header_ops += HEADER_OP % (op, val)
		# write the header with the #define lines
		f.write(HEADER_TMPL % header_ops)

	return 0

if __name__ == "__main__":
	exit(main())
