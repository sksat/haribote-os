void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)
void write_mem8(int addr, int data);

void HariMain(void){
	int i; // 変数宣言．iは32bitの整数型
	char* p; // 番地変数(ポインタ)．char*なのでBYTE [...]用の番地

	for(i=0xa0000; i<= 0xaffff; i++){
		p = (char*) i;		// 番地変数pに番地を代入
		*p = i & 0x0f;		// pの番地のメモリに色番号を代入

		// これでwrite_mem8(i, i & 0x0f); の代わりになる
	}

	for(;;){
		io_hlt();
	}
}
