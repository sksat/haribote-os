void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

// 同一ファイル内の関数でも定義前に使うなら宣言が必要
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void init_screen(char *vram, int xsize, int ysize);
void putfont8(char *vram, int xsize, int x, int y, char c, char *font);

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

struct BOOTINFO {
	char cyls, leds, vmode, reserve;
	short scrnx, scrny;
	char* vram;
};

void HariMain(void){
	struct BOOTINFO *binfo = (struct BOOTINFO *) 0x0ff0;
	static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
	};

	init_palette(); // パレットを設定
	init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
	putfont8(binfo->vram, binfo->scrnx, 10, 10, COL8_FFFFFF, font_A);

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

void init_screen(char *vram, int xsize, int ysize){
		// 背景
	boxfill8(vram, xsize, COL8_008484,	 0,		0,   xsize - 1, ysize - 29);
	// タスクバーとの分かれ目
	boxfill8(vram, xsize, COL8_C6C6C6,	 0,	ysize - 28,  xsize - 1, ysize - 28);
	boxfill8(vram, xsize, COL8_FFFFFF,	 0,	ysize - 27,  xsize - 1, ysize - 27);
	// タスクバーの背景
	boxfill8(vram, xsize, COL8_C6C6C6,	 0,	ysize - 26,  xsize - 1, ysize -  1);

	// 左のボタン
	boxfill8(vram, xsize, COL8_FFFFFF,	 3,	ysize - 24,	59,	ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF,	 2,	ysize - 24,	2,	ysize -  4);
	boxfill8(vram, xsize, COL8_848484,	 3,	ysize -  4,	59,	ysize -  4);
	boxfill8(vram, xsize, COL8_848484,	59,	ysize - 23,	59,	ysize -  5);
	boxfill8(vram, xsize, COL8_000000,	 2,	ysize -  3,	59,	ysize -  3);
	boxfill8(vram, xsize, COL8_000000,	60,	ysize - 24,	60,	ysize -  3);

	// 右のボタン
	boxfill8(vram, xsize, COL8_848484, xsize - 47,	ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 47,	ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47,	ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3,	ysize - 24, xsize -  3, ysize -  3);

}

void putfont8(char *vram, int xsize, int x, int y, char c,char *font){
	int i;
	char* p;
	char d; // data

	for(i=0; i<16; i++){			// フォントは16行あるので1行ずつ処理する
		p = vram + (y+i) * xsize + x;	// i行目の最初のVRAMの番地
		d = font[i];			// i行目のフォントデータ

		if((d & 0x80) != 0) p[0] = c;	// i行0列目のデータを取り出して，0でなければ色を設定
		if((d & 0x40) != 0) p[1] = c;	// i行1列目のデータを取り出して，0でなければ色を設定
		if((d & 0x20) != 0) p[2] = c;	// なんで0x80とか0x40なのかというと，
		if((d & 0x10) != 0) p[3] = c;	// 0x80が2進数で10000000,
		if((d & 0x08) != 0) p[4] = c;	// 0x40が2進数で01000000,
		if((d & 0x04) != 0) p[5] = c;	// 0x20が2進数で00100000,
		if((d & 0x02) != 0) p[6] = c;	// なので，各行のフォントデータとこれらの値のANDをとると
		if((d & 0x01) != 0) p[7] = c;	// それぞれの列のデータだけが残る，という理由．
	}

	return;
}
