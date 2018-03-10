void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)
void write_mem8(int addr, int data);

void HariMain(void){
	int i; // 変数宣言．iは32bitの整数型
	char* p; // 番地変数(ポインタ)．char*なのでBYTE [...]用の番地

	p = (char*)0xa0000; // VRAM開始番地

	for(i=0; i<= 0xffff; i++){
		p[i] = i & 0x0f; // 0xa0000 + i番地にi & 0x0fを代入
	}

	for(;;){
		io_hlt();
	}
}
