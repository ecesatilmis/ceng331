
examples.o:	file format Mach-O 64-bit x86-64


Disassembly of section __TEXT,__text:

0000000000000000 _max_bst:
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: 48 89 7d f8                  	movq	%rdi, -8(%rbp)
       8: 48 c7 45 f0 00 00 00 00      	movq	$0, -16(%rbp)
      10: 48 83 7d f8 00               	cmpq	$0, -8(%rbp)
      15: 0f 84 30 00 00 00            	je	48 <_max_bst+0x4b>
      1b: e9 00 00 00 00               	jmp	0 <_max_bst+0x20>
      20: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      24: 48 83 78 10 00               	cmpq	$0, 16(%rax)
      29: 0f 84 11 00 00 00            	je	17 <_max_bst+0x40>
      2f: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      33: 48 8b 40 10                  	movq	16(%rax), %rax
      37: 48 89 45 f8                  	movq	%rax, -8(%rbp)
      3b: e9 e0 ff ff ff               	jmp	-32 <_max_bst+0x20>
      40: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      44: 48 8b 00                     	movq	(%rax), %rax
      47: 48 89 45 f0                  	movq	%rax, -16(%rbp)
      4b: 48 8b 45 f0                  	movq	-16(%rbp), %rax
      4f: 5d                           	popq	%rbp
      50: c3                           	retq
      51: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%rax,%rax)
      5b: 0f 1f 44 00 00               	nopl	(%rax,%rax)

0000000000000060 _max_btree:
      60: 55                           	pushq	%rbp
      61: 48 89 e5                     	movq	%rsp, %rbp
      64: 48 83 ec 20                  	subq	$32, %rsp
      68: 48 89 7d f8                  	movq	%rdi, -8(%rbp)
      6c: 48 b8 00 00 00 00 00 00 00 80	movabsq	$-9223372036854775808, %rax
      76: 48 89 45 f0                  	movq	%rax, -16(%rbp)
      7a: 48 83 7d f8 00               	cmpq	$0, -8(%rbp)
      7f: 0f 84 5e 00 00 00            	je	94 <_max_btree+0x83>
      85: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      89: 48 8b 00                     	movq	(%rax), %rax
      8c: 48 89 45 f0                  	movq	%rax, -16(%rbp)
      90: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      94: 48 8b 78 08                  	movq	8(%rax), %rdi
      98: e8 c3 ff ff ff               	callq	-61 <_max_btree>
      9d: 48 89 45 e8                  	movq	%rax, -24(%rbp)
      a1: 48 8b 45 e8                  	movq	-24(%rbp), %rax
      a5: 48 3b 45 f0                  	cmpq	-16(%rbp), %rax
      a9: 0f 8e 08 00 00 00            	jle	8 <_max_btree+0x57>
      af: 48 8b 45 e8                  	movq	-24(%rbp), %rax
      b3: 48 89 45 f0                  	movq	%rax, -16(%rbp)
      b7: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      bb: 48 8b 78 10                  	movq	16(%rax), %rdi
      bf: e8 9c ff ff ff               	callq	-100 <_max_btree>
      c4: 48 89 45 e8                  	movq	%rax, -24(%rbp)
      c8: 48 8b 45 e8                  	movq	-24(%rbp), %rax
      cc: 48 3b 45 f0                  	cmpq	-16(%rbp), %rax
      d0: 0f 8e 08 00 00 00            	jle	8 <_max_btree+0x7e>
      d6: 48 8b 45 e8                  	movq	-24(%rbp), %rax
      da: 48 89 45 f0                  	movq	%rax, -16(%rbp)
      de: e9 00 00 00 00               	jmp	0 <_max_btree+0x83>
      e3: 48 8b 45 f0                  	movq	-16(%rbp), %rax
      e7: 48 83 c4 20                  	addq	$32, %rsp
      eb: 5d                           	popq	%rbp
      ec: c3                           	retq
      ed: 0f 1f 00                     	nopl	(%rax)

00000000000000f0 _collect_into:
      f0: 55                           	pushq	%rbp
      f1: 48 89 e5                     	movq	%rsp, %rbp
      f4: 48 83 ec 30                  	subq	$48, %rsp
      f8: 48 89 7d f0                  	movq	%rdi, -16(%rbp)
      fc: 48 89 75 e8                  	movq	%rsi, -24(%rbp)
     100: 48 89 55 e0                  	movq	%rdx, -32(%rbp)
     104: 48 83 7d f0 00               	cmpq	$0, -16(%rbp)
     109: 0f 84 0b 00 00 00            	je	11 <_collect_into+0x2a>
     10f: 48 83 7d e0 00               	cmpq	$0, -32(%rbp)
     114: 0f 8f 0d 00 00 00            	jg	13 <_collect_into+0x37>
     11a: 48 c7 45 f8 00 00 00 00      	movq	$0, -8(%rbp)
     122: e9 94 00 00 00               	jmp	148 <_collect_into+0xcb>
     127: 48 8b 45 f0                  	movq	-16(%rbp), %rax
     12b: 48 8b 78 08                  	movq	8(%rax), %rdi
     12f: 48 8b 75 e8                  	movq	-24(%rbp), %rsi
     133: 48 8b 55 e0                  	movq	-32(%rbp), %rdx
     137: e8 b4 ff ff ff               	callq	-76 <_collect_into>
     13c: 48 89 45 d8                  	movq	%rax, -40(%rbp)
     140: 48 8b 45 d8                  	movq	-40(%rbp), %rax
     144: 48 3b 45 e0                  	cmpq	-32(%rbp), %rax
     148: 0f 85 0d 00 00 00            	jne	13 <_collect_into+0x6b>
     14e: 48 8b 45 d8                  	movq	-40(%rbp), %rax
     152: 48 89 45 f8                  	movq	%rax, -8(%rbp)
     156: e9 60 00 00 00               	jmp	96 <_collect_into+0xcb>
     15b: 48 8b 45 f0                  	movq	-16(%rbp), %rax
     15f: 48 8b 00                     	movq	(%rax), %rax
     162: 48 8b 4d e8                  	movq	-24(%rbp), %rcx
     166: 48 8b 55 d8                  	movq	-40(%rbp), %rdx
     16a: 48 89 04 d1                  	movq	%rax, (%rcx,%rdx,8)
     16e: 48 8b 45 f0                  	movq	-16(%rbp), %rax
     172: 48 8b 78 10                  	movq	16(%rax), %rdi
     176: 48 8b 45 e8                  	movq	-24(%rbp), %rax
     17a: 48 8b 4d d8                  	movq	-40(%rbp), %rcx
     17e: 48 c1 e1 03                  	shlq	$3, %rcx
     182: 48 01 c8                     	addq	%rcx, %rax
     185: 48 05 08 00 00 00            	addq	$8, %rax
     18b: 48 8b 4d e0                  	movq	-32(%rbp), %rcx
     18f: 48 2b 4d d8                  	subq	-40(%rbp), %rcx
     193: 48 81 e9 01 00 00 00         	subq	$1, %rcx
     19a: 48 89 c6                     	movq	%rax, %rsi
     19d: 48 89 ca                     	movq	%rcx, %rdx
     1a0: e8 4b ff ff ff               	callq	-181 <_collect_into>
     1a5: 48 89 45 d0                  	movq	%rax, -48(%rbp)
     1a9: 48 8b 45 d8                  	movq	-40(%rbp), %rax
     1ad: 48 05 01 00 00 00            	addq	$1, %rax
     1b3: 48 03 45 d0                  	addq	-48(%rbp), %rax
     1b7: 48 89 45 f8                  	movq	%rax, -8(%rbp)
     1bb: 48 8b 45 f8                  	movq	-8(%rbp), %rax
     1bf: 48 83 c4 30                  	addq	$48, %rsp
     1c3: 5d                           	popq	%rbp
     1c4: c3                           	retq
