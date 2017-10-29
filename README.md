# SampleBlenano2BlePeripheral
Blenano2をble通信のPeripheralとして使うサンプルプログラム

## 環境
Blenano2をArduino上で使用できるようにしています

Arduino化する方法は下記を参照

https://github.com/redbear/nRF5x/blob/master/nRF52832/docs/Arduino_Board_Package_Installation_Guide.md

# プログラム
Blenano2はPeripheralとして動作し、2秒毎に6つのデータ(tx_buf)を送信しています

* ticker2s.attach(task_handle, 2);

    attachの値変えれば更新頻度を変えることができます

*  ble.updateCharacteristicValue();

    Timer関数のなかにある下記のプログラムにてNotifyの更新を行っています