; Haribote OS

	ORG	0xc200		; このプログラムがどこに読み込まれるか

	MOV	AL,0x13		; VGAグラフィックス，320*200*8bitカラー
	MOV	AH,0x00
	INT	0x10		; ビデオBIOSファンクション呼び出し

fin:
	HLT
	JMP	fin
