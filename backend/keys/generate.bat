keytool -genkey -keyalg RSA -alias VitoshaTrade -keystore VitoshaTrade -storepass VitoshaTrade -validity 360 -keysize 2048
keytool -export -alias VitoshaTrade -file VitoshaTrade.crt -keystore VitoshaTrade
