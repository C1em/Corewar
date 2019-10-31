.name "best champ"
.comment "woaoaaoo"

st r1, 6
live:
	live %0
	zjmp %:live

ld %505, r3
ld %0, r4
fork %:live

fork %:p2

# r2 = sti code_byte r2 r3 -> 0B 54 02 03 -> 190054915
# r3 = 507
# r4 = 0
p1:
	ld %190054915, r2
	st r2, 511
	ld %0, r15
	zjmp %499

# r2 = r4 zjmp %500 -> 04 09 01 F4 -> 67699188
# r3 = 507
# r4 = 4
p2:
	ld %4, r4
	ld %67699188, r2
	st r2, 486
	ld %0, r15
	zjmp %470
