# C++ 用 UTF-8/16/32 相互変換ライブラリ

UTF-8/16/32 の相互変換を行うテンプレート ライブラリです。

処理内容は単純に

1. 変換元から 1 文字分を UTF-32 に変換して取り出す
2. 変換先へ UTF-32 から変換して出力する
3. 全て変換するまで繰り返す

を行うためのものしかありません。


# ヘッダ ファイル : utfcvt.hpp

必要なファイルは utfcvt.hpp のみで、<code>#include</code> して使用します。

名前空間は <code>utfcvt</code> で、テンプレート関数と4 つのクラスを使用します。

- utf - メソッド引数型による UTF-8/16/32 自動判別
- utf8 - UTF-8 コード処理
- utf16 - UTF-16 コード処理
- utf32 - UTF-32 コード処理


# テンプレート関数

変換関数は関数名が変換先形式で、変換元の形式は型から自動判別します。

```
// ヌル文字直前までの数 (strlen や wcslen と同様)
template <typename sT> size_t utflen(sT* s);

// UTF-8 に変換
template <typename sT> std::string to_string(sT s);
template <typename iT> std::string to_string(iT s, iT e);
template <typename sT> std::string to_string(sT* s, size_t n);

// UTF-16/32 に変換
template <typename sT> std::wstring to_wstring(sT s);
template <typename iT> std::wstring to_wstring(iT s, iT e);
template <typename sT> std::wstring to_wstring(sT* s, size_t n);

/*
 * 以下、使用可能とは限らない
 */

// UTF-8 に変換
template <typename sT> std::u8string to_u8string(sT s);
template <typename iT> std::u8string to_u8string(iT s, iT e);
template <typename sT> std::u8string to_u8string(sT* s, size_t n);

// UTF-16 に変換
template <typename sT> std::u16string to_u16string(sT s);
template <typename iT> std::u16string to_u16string(iT s, iT e);
template <typename sT> std::u16string to_u16string(sT* s, size_t n);

// UTF-32 に変換
template <typename sT> std::u32string to_u32string(sT s);
template <typename iT> std::u32string to_u32string(iT s, iT e);
template <typename sT> std::u32string to_u32string(sT* s, size_t n);
```


# クラス utf8 / utf16 / utf32 共通の静的メソッド

以下のような記述で変換します。

```
utf8::to_utf16(dest16, src8);  // UTF-8 から UTF-16 に変換
utf32::to_utf16(dest8, src32);  // UTF-32 から UTF-8 に変換
```

出力先オブジェクトには

- value_type 型
- push_back メソッド

が必須です。また、引数には 8 / 16 / 32 / 64 ビット単位の領域を渡せますが、必要なビット数未満の領域

- UTF-16 への変換に 8 ビット列を指定
- UTF-32 への変換に 8 / 16 ビット列を指定

上記条件で変換しようとすると、表現できないコードは特定のコードに置き換えられます。

相互変換は UTF-8/16/32 の 3 形式とビット列(8/16/32/64) が 4 つの 12 種の相互変換なので 144 個の変換になります。


## メソッド to_utf8 / to_utf16 / to_utf32

UTF-8/16/32 へ(クラス名)形式の指定データから変換します。

- 引数 d : 出力先
- 引数 s : 変換元データ

> [!NOTE]
> 出力先へ push_back で追記します。

返値の <code>utfcvt_result</code> には変換量やエラーが含まれています。

```
template <typename dT, typename iT> static utfcvt_result to_utf8(dT& d, iT s, iT e);
template <typename dT, typename iT> static utfcvt_result to_utf8(dT& d, iT* s, size_t n);
template <typename dT, typename sT> static utfcvt_result to_utf8(dT& d, sT& s);
template <typename dT, typename sT> static utfcvt_result to_utf8(dT& d, sT* s);
```

```
template <typename dT, typename iT> static utfcvt_result to_utf16(dT& d, iT s, iT e);
template <typename dT, typename sT> static utfcvt_result to_utf16(dT& d, sT* s, size_t n);
template <typename dT, typename sT> static utfcvt_result to_utf16(dT& d, sT& s);
template <typename dT, typename sT> static utfcvt_result to_utf16(dT& d, sT* s);
```

```
template <typename dT, typename iT> static utfcvt_result to_utf32(dT& d, iT s, iT e);
template <typename dT, typename sT> static utfcvt_result to_utf32(dT& d, sT* s, size_t n);
template <typename dT, typename sT> static utfcvt_result to_utf32(dT& d, sT& s);
template <typename dT, typename sT> static utfcvt_result to_utf32(dT& d, sT* s);
```


## メソッド to_utf8len / to_utf16len / to_utf32len

to_utf8 / to_utf16 / to_utf32 に必要な配列長を取得したいときに使用します。

```
template <typename iT> static utfcvt_result to_utf8len(iT s, iT e);
template <typename sT> static utfcvt_result to_utf8len(sT* s, size_t n);
template <typename sT> static utfcvt_result to_utf8len(sT& s);
template <typename sT> static utfcvt_result to_utf8len(sT* s);
```

```
template <typename iT> static utfcvt_result to_utf16len(iT s, iT e);
template <typename sT> static utfcvt_result to_utf16len(sT* s, size_t n);
template <typename sT> static utfcvt_result to_utf16len(sT& s);
template <typename sT> static utfcvt_result to_utf16len(sT* s);
```

```
template <typename iT> static utfcvt_result to_utf32len(iT s, iT e);
template <typename sT> static utfcvt_result to_utf32len(sT* s, size_t n);
template <typename sT> static utfcvt_result to_utf32len(sT& s);
template <typename sT> static utfcvt_result to_utf32len(sT* s);
```


## メソッド getcodelen

1 コード分のデータ量を、先頭のデータから判定して返します。

```
template <typename cT> static size_t getcodelen(cT c);
```

| クラス | 最小 | 最大 |
|:-:|:-:|:-:|
| utf8 | 1 | 6 |
| utf16 | 1 | 2 |
| utf32 | 1 | 1 |

エラー時は 0 を返します。


## メソッド getcode

指定されたデータ列の先頭から 1 コード分を取得して返します。

<code>utfcvt_getcres</code> にはデータ量やエラーが含まれています。

```
template <typename iT> static utfcvt_getcres getcode(iT s, iT e);
template <typename sT> static utfcvt_getcres getcode(sT* s, size_t n);
template <typename sT> static utfcvt_getcres getcode(sT& s);
template <typename sT> static utfcvt_getcres getcode(sT* s);
```


## メソッド nextcode

指定されたデータ列の先頭から 1 コード分を取得し、引数の <code>s</code> やサイズ <code>n</code> を変更して返します。

<code>utfcvt_getcres</code> にはデータ量やエラーが含まれています。

```
template <typename iT> static utfcvt_getcres nextcode(iT& s, iT e);
template <typename sT> static utfcvt_getcres nextcode(sT*& s, size_t& n);
template <typename sT> static utfcvt_getcres nextcode(sT*& s);
```


## メソッド putcodelen

1 コード分のデータ量を返します。範囲は getcodelen と同じです。

```
template <typename cT> static size_t putcodelen(cT c);
```


## メソッド putcode

1 コード分のデータを出力します。

- 引数 d : 出力先
- 引数 c : コード

```
template <typename dT, typename cT> static size_t putcode(dT& d, cT c);
```


## メソッド replacement_character

エラーなどで置換する文字を返します。

```
static std::uint8_t utf8::replacement_character();   // U+003F = '?'
static std::uint16_t utf16::replacement_character(); // U+FFFD
static std::uint32_t utf32::replacement_character(); // U+FFFD
```


# クラス utf の静的メソッド

[クラス utf8 / utf16 / utf32 共通の静的メソッド](#%E3%82%AF%E3%83%A9%E3%82%B9-utf8--utf16--utf32-%E5%85%B1%E9%80%9A%E3%81%AE%E9%9D%99%E7%9A%84%E3%83%A1%E3%82%BD%E3%83%83%E3%83%89)と同じものが使用可能ですが、引数 s (変換元データ) の型に応じて UTF-8/16/32 を自動判別します。


## メソッド cvt

引数の型に従った UTF-8/16/32 相互変換を行います。

- 引数 d : 出力先 (型より UTF-8/16/32 を自動判定)
- 引数 s : 変換元データ (型より UTF-8/16/32 を自動判定)

引数 s から、utf8 / utf16 / utf32 を選択し、引数 d から to_utf8 / to_utf16 / to_utf32 を選択します。

> [!NOTE]
> 出力先へ push_back で追記します。

```
template <typename dT, typename iT> static utfcvt_result cvt(dT& d, iT s, iT e);
template <typename dT, typename sT> static utfcvt_result cvt(dT& d, sT* s, size_t n);
template <typename dT, typename sT> static utfcvt_result cvt(dT& d, sT& s);
template <typename dT, typename sT> static utfcvt_result cvt(dT& d, sT* s);
```


## メソッド cvtlen

メソッド <code>cvt</code> の出力に必要な領域を調査する目的で使用します。<code>cvt</code> と同様の処理を行いますが出力しません。

```
template <typename dT, typename iT> static utfcvt_result cvtlen(dT& d, iT s, iT e);
template <typename dT, typename sT> static utfcvt_result cvtlen(dT& d, sT* s, size_t n);
template <typename dT, typename sT> static utfcvt_result cvtlen(dT& d, sT& s);
template <typename dT, typename sT> static utfcvt_result cvtlen(dT& d, sT* s);
```

引数 d は出力先の形式を指定するために使用します。


## メソッド getcode / nextcode

変換元の引数を <code>const void *</code> とします。メモリ内容とテンプレート引数の型は一致してなければなりません。

```
template <typename cT> utfcvt_getcres getcode(const void* s, const void* e);
template <typename cT> utfcvt_getcres nextcode(const void*& s, const void* e);
```

以下の関数ポインタ型に

```
typedef utfcvt_getcres (*utfcvt_getcode)(const void* s, const void* e);
typedef utfcvt_getcres (*utfcvt_nextcode)(const void*& s, const void* e);
```

- getcode
  - UTF-8 : <code>utf::getcode&lt;char8_t&gt;</code>
  - UTF-16 : <code>utf::getcode&lt;cahr16_t&gt;</code>
  - UTF-32 : <code>utf::getcode&lt;char32_t&gt;</code>
- nextcode
  - UTF-8 : <code>utf::nextcode&lt;char8_t&gt;</code>
  - UTF-16 : <code>utf::nextcode&lt;cahr16_t&gt;</code>
  - UTF-32 : <code>utf::nextcode&lt;char32_t&gt;</code>

などを代入できます。
