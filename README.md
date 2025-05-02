# ComplementaryFilter
6軸IMUのデータを相補フィルターを用いて角度に変換するコードです

重力加速度のノルムを計算することで、加速度が信頼できるときのみ相補フィルターの計算を行っています 

## SampleCode

### センサーからのデータ取得

6軸以上のIMUを使用してください

データは配列にxyzの順番で入れてください
```cpp
float accel[3];
float gyro[3];
```

### 実装

起動時に1回実行される部分とメインループに分けて書いてありますが、それぞれの環境に合わせて書いてください

割り込み等を使用する場合は、割り込み処理でSetData()のみを実行し、計算とデータ取得は割り込み外で行うことをおすすめします
```cpp

#include "ComplementaryFilter.h"）
//include Sensorlibrary

float accel[3] = {};
float gyro[3] = {};
float angle[3] = {};
float gain = 0.98; //角速度の重みの値(0.8~0.98程度を推奨）
float time = 0.0001;　//データの取得間隔

ComplementaryFilter filter(gain, time);

void init(){

  //SensorInit
}

void loop(){

  //GetSensorData

  filter.SetData(accel, gyro, time);
  filter.Calc();
  filter.GetAngle(angle);

  //SendAngleData
}
```
