void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

// 同一ファイル内の関数でも定義前に使うなら宣言が必要
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

// #defineは単純に文字列が置換される．
// ここでは色番号と色の対応を覚えなくて良いようにしている．
#define COL8_000000	0
#define COL8_FF0000	1
#define COL8_00FF00	2
#define COL8_FFFF00	3
#define COL8_0000FF	4
#define COL8_FF00FF	5
#define COL8_00FFFF	6
#define COL8_FFFFFF	7
#define COL8_C6C6C6	8
#define COL8_840000	9
#define COL8_008400	10
#define COL8_848400	11
#define COL8_000084	12
#define COL8_840084	13
#define COL8_008484	14
#define COL8_848484	15

void HariMain(void){
	int i; // 変数宣言．iは32bitの整数型
	char* p; // 番地変数(ポインタ)．char*なのでBYTE [...]用の番地

	init_palette(); // パレットを設定

	p = (char*)0xa0000; // VRAM開始番地

	boxfill8(p, 320, COL8_FF0000,  20,  20, 120, 120);
	boxfill8(p, 320, COL8_00FF00,  70,  50, 170, 150);
	boxfill8(p, 320, COL8_0000FF, 120,  80, 220, 180);

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

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1){
	int x, y;
	for(y=y0; y<=y1; y++){
		for(x=x0; x<=x1; x++)
			vram[y * xsize +x] = c; // 座標(x,y)の点に対応する番地は[vram(0xa0000) + y * ysize(320) + x]
	}
}
