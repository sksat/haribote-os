; naskfunc.nas

[FORMAT "WCOFF"]		; オブジェクトファイルを作る
[BITS 32]			; 32bit

; オブジェクトファイルのための情報

[FILE "naskfunc.nas"]		; ソースファイル名

	GLOBAL	_io_hlt		; このプログラムに含まれる関数

[SECTION .text]			; textセクション

_io_hlt:	; void io_hlt(void);
	HLT
	RET
