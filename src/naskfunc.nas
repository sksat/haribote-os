; naskfunc.nas

[FORMAT "WCOFF"]		; オブジェクトファイルを作る
[INSTRSET "i486p"]		; 486の命令まで使いたい
[BITS 32]			; 32bit

; オブジェクトファイルのための情報
[FILE "naskfunc.nas"]		; ソースファイル名

	GLOBAL	_io_hlt		; このプログラムに含まれる関数
	GLOBAL	_write_mem8

[SECTION .text]			; textセクション

_io_hlt:	; void io_hlt(void);
	HLT
	RET
