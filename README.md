# MPA

MPA は長野高専 3J の授業内で作成した多倍長整数演算ができるプログラムです．Written by C.

## Installation

clone してください．

## Usage

Archimedes フォルダ内の`main.c`を gcc か clang でコンパイル，実行するといい感じに円周率が計算されます．絶望的に遅いので気を付けて．

```
gcc main.c mulprec.c -o output
```

パラメータは`mulprec.h`の`#define`を変更してね．

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
