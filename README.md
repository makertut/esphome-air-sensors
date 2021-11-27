# esphome
Hardware
1. FireBeetle ESP32-E IoT or other esp32 boards<br/>
https://www.dfrobot.com/product-2231.html
<img src="https://dfimg.dfrobot.com/store/data/DFR0654-F/DFR0654-F.jpg" width=50% height=50%> 
2. Gravity: MEMS Gas Sensor (CO, Alcohol, NO2 & NH3) - I2C - MiCS-4514<br/>
   https://www.dfrobot.com/product-2417.html
<img src="https://dfimg.dfrobot.com/store/data/SEN0377/SEN0377.jpg" width=50% height=50%>
3. Gravity: PM2.5 Air Quality Sensor<br/>
https://www.dfrobot.com/product-2439.html
<img src="https://dfimg.dfrobot.com/store/data/SEN0460/SEN0460.jpg" width=50% height=50%>

espHome YAML 
esphome:
  name: esp32-test
  platform: ESP32
  board: firebeetle32
  
  
  includes:
    - my_custom_sensor.h
    
  libraries:
    - Wire
    - "https://github.com/makertut/DFRobot_MICS"
    - "https://github.com/dfrobot/DFRobot_AirQualitySensor"
  
# Enable logging
logger:

# Enable Home Assistant API
api:

ota:
  password: "c5ae2eaebedcf9fe5a73e0b405cb8241"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Esp32-Test Fallback Hotspot"
    password: "kr8ry0mV9xzD"

captive_portal:

# Example configuration entry
sensor:
- platform: custom
  lambda: |-
    auto my_sensor = new MyCustomSensor();
    App.register_component(my_sensor);
    return {my_sensor->Carbon_Monoxide_sensor, 
            my_sensor->Methane_sensor, 
            my_sensor->Ethanol_sensor, 
            my_sensor->Hydrogen_sensor, 
            my_sensor->Ammonia_sensor, 
            my_sensor->Nitrogen_Dioxide_sensor,
            my_sensor->Pm1_0_sensor,
            my_sensor->Pm2_5_sensor,
            my_sensor->Pm10_sensor
           };

  sensors:
  - name: "Carbon Monoxide"    
    unit_of_measurement: PPM
    accuracy_decimals: 0
  - name: "Methane"    
    unit_of_measurement: PPM
    accuracy_decimals: 0
  - name: "Ethanol"    
    unit_of_measurement: PPM
    accuracy_decimals: 0
  - name: "Hydrogen"    
    unit_of_measurement: PPM
    accuracy_decimals: 0
  - name: "Ammonia"    
    unit_of_measurement: PPM
    accuracy_decimals: 0  
  - name: "Nitrogen Dioxide"    
    unit_of_measurement: PPM
    accuracy_decimals: 2  
  - name: "PM 1_0"  
    unit_of_measurement: "mg/m3"
    accuracy_decimals: 1
  - name: "PM 2_5"  
    unit_of_measurement: "mg/m3"
    accuracy_decimals: 1
  - name: "PM 10"  
    unit_of_measurement: "mg/m3"
    accuracy_decimals: 1  
