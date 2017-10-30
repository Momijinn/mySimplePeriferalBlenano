SampleBlenano2BlePeripheral
====
Blenano2をble通信のPeripheralとして使うサンプルプログラム

## Description
Blenano2をble通信のPeripheralとして使用し、2秒毎ごとに6個のデータを通知しているサンプルプログラム

## Requirement
* [BLEnano2](https://www.switch-science.com/catalog/3444/)

## Usage
* mySimplePeriferalBlenano2.inoをBLEnano2に書き込むとアドバタイジングを始めます

* 接続すると2秒毎に通知を送信します

* ticker2s.attach(task_handle, 2);

    * attachの値変えれば更新頻度を変えることができます

* ble.updateCharacteristicValue();

    * Timer関数のなかにある下記のプログラムにてNotifyの更新を行っています

## Install
1. 下記のURLに従ってBLEnano2をArduino上で書き込めるようにする
https://github.com/redbear/nRF5x/blob/master/nRF52832/docs/Arduino_Board_Package_Installation_Guide.md

2. mySimplePeriferalBlenano2.inoをBLEnano2へ書き込む

## Licence
This software is released under the MIT License, see LICENSE.

## Author
[Twitter](https://twitter.com/momijinn_aka)

[Blog](http://www.autumn-color.com/)