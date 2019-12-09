check: check2.c
	gcc check2.c mulprec.c -o check.exe -lm -Wall -Wextra -Wuninitialized -Wcast-qual -Wformat=2 -Wcast-align -Wwrite-strings -Wconversion -Wfloat-equal -Wpointer-arith -Winit-self -Wunsafe-loop-optimizations -Wpadded -Wno-sign-compare -Wno-pointer-sign -Wno-missing-field-initializers -Wstrict-aliasing=2 -Wdisabled-optimization -Wbad-function-cast -Wredundant-decls -Winline --param max-inline-insns-single=12000 --param large-function-growth=28000 --param inline-unit-growth=400 -Wjump-misses-init -Wmissing-declarations -Wmissing-prototypes -Wshadow -Wswitch-default -pedantic -fstack-protector-all -D_FORTIFY_SOURCE=2 -ftrapv -fno-omit-frame-pointer
	# -mtune=generic  -march=x86-64 -mcmodel=32 -rdynamic
	# -mcmodel=largeにすると64ビット対応
	./check.exe