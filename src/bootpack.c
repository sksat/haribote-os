void io_hlt(void);	// 関数のプロトタイプ宣言(外部ファイルの関数)

void HariMain(void){
fin:
	io_hlt();	// naskfunc.nasのio_hltを実行
	goto fin;
}
