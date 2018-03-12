void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

// 同一ファイル内の関数でも定義前に使うなら宣言が必要
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

void HariMain(void){
	int i; // 変数宣言．iは32bitの整数型
	char* p; // 番地変数(ポインタ)．char*なのでBYTE [...]用の番地

	init_palette(); // パレットを設定

	p = (char*)0xa0000; // VRAM開始番地

	for(i=0; i<= 0xffff; i++){
		p[i] = i & 0x0f; // 0xa0000 + i番地にi & 0x0fを代入
	}

	for(;;){
		io_hlt();
	}
}

void init_palette(void){
	// static charはデータ専用のDB相当
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	//  0:黒
		0xff, 0x00, 0x00,	//  1:明るい赤
		0x00, 0xff, 0x00,	//  2:明るい緑
		0xff, 0xff, 0x00,	//  3:明るい黄色
		0x00, 0x00, 0xff,	//  4:明るい青
		0xff, 0x00, 0xff,	//  5:明るい紫
		0x00, 0xff, 0xff,	//  6:明るい水色
		0xff, 0xff, 0xff,	//  7:白
		0xc6, 0xc6, 0xc6,	//  8:明るい灰色
		0x84, 0x00, 0x00,	//  9:暗い赤
		0x00, 0x84, 0x00,	// 10:暗い緑
		0x84, 0x84, 0x00,	// 11:暗い黄色
		0x00, 0x00, 0x84,	// 12:暗い青
		0x84, 0x00, 0x84,	// 13:暗い紫
		0x00, 0x84, 0x84,	// 14:暗い水色
		0x84, 0x84, 0x84	// 15:暗い灰色
	};

	set_palette(0, 15, table_rgb);
	return;
}

void set_palette(int start, int end, unsigned char *rgb){
	int i, eflags;
	eflags = io_load_eflags();	// 割り込み許可フラグの値を記録
	io_cli();			// 割り込み許可フラグを0にして割り込み禁止にする

	io_out8(0x03c8, start);
	for(i=start; i<=end; i++){
		io_out8(0x03c9, rgb[0] / 4); // 赤成分を設定
		io_out8(0x03c9, rgb[1] / 4); // 緑成分を設定
		io_out8(0x03c9, rgb[2] / 4); // 青成分を設定
		rgb += 3; // 次の色へ
	}

	io_store_eflags(eflags);
	return;
}
