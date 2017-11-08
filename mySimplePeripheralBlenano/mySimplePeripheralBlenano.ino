//BLE nano1
// #include <BLE_API.h>

//BLE nano 2
#include <nRF5x_BLE_API.h>


#define TXRX_BUF_LEN 5
#define DEVICE_NAME  "MyBlePeripheral"

BLE ble;

//Timer
Ticker ticker;

//データの格納する配列
//uint8_t = 0~255
static uint8_t tx_buf[TXRX_BUF_LEN];

// The Nordic UART Service
static const uint8_t uart_base_uuid_rev[]   = {0x1E, 0x94, 0x8D, 0xF1, 0x48, 0x31, 0x94, 0xBA, 0x75, 0x4C, 0x3E, 0x50, 0, 0, 0x3D, 0x71};
static const uint8_t service_uuid[]        = {0x71, 0x3D, 0, 0, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};
static const uint8_t service_chars_uuid[] = {0x71, 0x3D, 0, 1, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};

uint8_t chars_value[TXRX_BUF_LEN] = {0}; //初期化

//Notifyのみもらう
GattCharacteristic characteristic(service_chars_uuid, chars_value, 1, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY);
GattCharacteristic *uartChars[] = {&characteristic};
GattService uartService(service_uuid, uartChars, sizeof(uartChars) / sizeof(GattCharacteristic *));


//connect task
void connectionCallBack( const Gap::ConnectionCallbackParams_t *params ) {
  Serial.println("Conect");
   if(params->role == Gap::PERIPHERAL) {
    Serial.println("Peripheral ");
  }
}

//disconect tack
void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *params) {
  Serial.print("Disconnected hande : ");
  Serial.println(params->handle);
  Serial.print("Disconnected reason : ");
  Serial.println(params->reason);
  Serial.println("Restart advertising ");
  ble.startAdvertising();
}

//Timer Task(Notify Task)
void task_handle(void) {
  for(int i=0;i<TXRX_BUF_LEN; i++){
    tx_buf[i] += 1;
  }

  //Change Notify Data
  ble.updateCharacteristicValue(characteristic.getValueAttribute().getHandle(), tx_buf, TXRX_BUF_LEN);
}


void SetAdvertisement(){
  // A list of Advertising Data types commonly used by peripherals.
  ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
  // Add complete 128bit_uuid to advertisement
  ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,(const uint8_t *)uart_base_uuid_rev, sizeof(uart_base_uuid_rev));
  // Add complete device name to scan response data
  ble.accumulateScanResponse(GapAdvertisingData::COMPLETE_LOCAL_NAME,(const uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME) - 1);
}

void setup() {
  Serial.begin(115200);

  //BLE設定
  ble.init();
  ble.onConnection(connectionCallBack);
  ble.onDisconnection(disconnectionCallBack);

  //set advertisement
  SetAdvertisement();

  // set adv_type
  ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
  // add service
  ble.addService(uartService);
  // set device name
  ble.setDeviceName((const uint8_t *)DEVICE_NAME);
  // set tx power,valid values are -40, -20, -16, -12, -8, -4, 0, 4
  ble.setTxPower(4);
  // set adv_interval, 100ms in multiples of 0.625ms.
  ble.setAdvertisingInterval(160);
  // set adv_timeout, in seconds
  ble.setAdvertisingTimeout(0);
  // start advertising
  ble.startAdvertising();


  //Initialize Data
  for(int i=0;i<TXRX_BUF_LEN; i++){
    tx_buf[i] = 0;
  }

  // Start Task
  ticker.attach(task_handle, 1);
}

void loop() {
  ble.waitForEvent();
}
