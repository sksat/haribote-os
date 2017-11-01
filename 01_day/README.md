# 1-1 とにかくやるのだぁ
さて，圧倒的「「やるだけ」」のお時間です．

まずはバイナリエディタを入れます．
まあhexeditでいいでしょう．
```
# apt-get install hexedit
```

それではhelloos.imgを作っていきます．

```
$ touch helloos.img
$ hexedit helloos.img
```

はい．あとは，「やるだけ」です．本を見てがんばってバイナリを打ち込んでいきましょう！(ぇ


というのは嘘で，1MB超の0x00を打ち込むのは正気の沙汰ではない(といいつつ途中まではやった)ので，ちょっと楽をします．

そこそこの大きさの0x00が詰まったファイル"zero"を作っておいて，
```
$ cat helloos.img zero > tmp.img
```
とかやると，helloos.imgの末尾にzeroが追加されたファイル"tmp.img"が出来ます．
まあコピペ代わりですね．
