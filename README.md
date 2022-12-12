# Serial updatable sample for nRF9160

Nordic nRF9160でUART(シリアルポート)経由でファームウェアのアップデートを行えるように構成するサンプルです。

J-Link等のデバッガハードウェアが無くてもアプリケーション部分をPCから更新できるよう構成します。

## 概要

nRF9160のSDKであるnRF Connect SDKで採用しているブートローダー`MCU Boot`をシリアルアップデート機能を有効にしてビルドする構成のサンプルです。

主な内容は以下の2点です。

* ボード定義ファイルでブートローダーのモード切り替えに使用する入力ピンの指定とLEDに使用する出力ピンの指定
* MCU Bootのビルド設定のオーバーライド

### ターゲットデバイス

| ボード名 | 説明 |
|----|----|
| SCM-LTEM1NRF | [さくらのモノプラットフォーム開発キット DIP型LTEモジュール基板](https://iot.sakura.ad.jp/platform/service/dev-kit/) |

詳細については[Wikiページ](https://github.com/sakura-internet/nrf9160_sample_serial_updatable/wiki)を参照ください。
