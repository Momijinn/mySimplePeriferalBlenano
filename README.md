mySimplePeripheralBlenano
====
Blenano(Blenano2)をble通信のPeripheralとして使うサンプルプログラム

## Description
Blenano(Blenano2)をble通信のPeripheralとして使用し、1秒毎ごとに5個のデータを通知しているサンプルプログラム

## Requirement
* [BLE Nano](http://amzn.to/2zlJwvZ)

    or

* [BLE Nano2](https://www.switch-science.com/catalog/3444/)

## Usage
* mySimplePeripheralBlenano.inoをBlenano(Blenano2)に書き込むとアドバタイジングを始めます

* BlenanoとBlenano2ではインクルードするライブラリが異なるので適宜切り替える

    * Blenano: #include <BLE_API.h>
    * Blenano2: #include <nRF5x_BLE_API.h>

* 接続すると1秒毎に通知を送信します

* ticker.attach(task_handle, 1);

    * attachの値変えれば更新頻度を変えることができます

* ble.updateCharacteristicValue();

    * Timer関数のなかにある下記のプログラムにてNotifyの更新を行っています

## Install
1. 下記のURLに従ってBlenano2をArduino上で書き込めるようにする
https://github.com/redbear/nRF5x/blob/master/nRF52832/docs/Arduino_Board_Package_Installation_Guide.md

    Blenano1の場合は下記のURLに従って書き込めるようにする
    https://github.com/redbear/nRF5x/tree/master/nRF51822/arduino

2. mySimplePeripheralBlenano.inoをBlenano(Blenano2)へ書き込む

## Other
以下のプログラムをダウンロードして異なるBlenanoに書き込むとBlenano間で通信をすることができます
https://github.com/Momijinn/mySimpleCentralBlenano.git

## Licence
This software is released under the MIT License, see LICENSE.

## Author
[Twitter](https://twitter.com/momijinn_aka)

[Blog](http://www.autumn-color.com/)