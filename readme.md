# IoT Projekt: Temperaturövervakning med ESP32, AWS IoT och Grafana

## Beskrivning
Detta projekt övervakar temperatur och luftfuktighet med hjälp av en **ESP32**-mikrokontroller och en **DHT11-sensor**. Data skickas till **AWS IoT Core** via MQTT, lagras i **DynamoDB**, och visualiseras i **Grafana**.

---

## Funktioner
- Insamling av sensordata (temperatur och luftfuktighet).
- Säker kommunikation med AWS IoT Core via MQTT.
- Lagring av data i DynamoDB.
- Realtidsvisualisering i Grafana.

---

## Arkitektur
1. **ESP32** samlar in data från DHT11-sensorn.
2. Data skickas till AWS IoT Core.
3. AWS IoT Core lagrar data i DynamoDB via IoT-regler.
4. Grafana hämtar data via en API Gateway och Lambda.
![Esp32_DHT11](https://github.com/user-attachments/assets/160020f5-0bb5-4b00-8a75-2cd808081e1f)
![Grafana_aws](https://github.com/user-attachments/assets/c749c7d6-f583-465b-aa00-d4c3b6cbfc45)
![Grafana_aws](https://github.com/user-attachments/assets/38842b85-1588-46e4-8c1d-b36bac2d5ff1)



---

## Fysisk Uppkoppling
### Komponenter
- **ESP32**-mikrokontroller
- **DHT11-sensor**
- Breadboard och kopplingskablar


### Kopplingsschema
1. **DHT11-sensor**:
   - VCC → 3.3V på ESP32
   - GND → GND på ESP32
   - Signal → GPIO 21 på ESP32

2. **ESP32**:
   - Ansluten till dator via USB.


3. ## Molnteknologi
Projektet använder sig av **AWS Cloud** för att möjliggöra skalbar, säker och pålitlig hantering av sensordata. Molnteknologin ger följande fördelar:
- **Global tillgänglighet**: Data kan nås och hanteras från vilken plats som helst.
- **Flexibilitet**: Dynamisk anpassning av resurser baserat på behov.


4. ## Säkerhet
Säkerhet är en viktig del av detta projekt för att skydda sensordata och förhindra obehörig åtkomst. Följande åtgärder har implementerats:

### 1. Kommunikation
- **TLS/SSL-kryptering** används för alla MQTT-meddelanden mellan ESP32 och AWS IoT Core.
- Certifikatbaserad autentisering används för att säkerställa att endast godkända enheter kan kommunicera med AWS.

### 2. API Gateway
- **Authorization Header** används för att begränsa åtkomst till API Gateway.
- Endast klienter med en giltig nyckel har åtkomst till data.

### 3. AWS IAM Policy
- **Minsta möjliga behörighet** har tilldelats IoT-regeln och Lambda-funktionen för att begränsa åtkomst till DynamoDB-tabellen.
- IoT-policyer är begränsade till specifika IoT-resurser (t.ex. `/telemetry`-topic).

### 4. DynamoDB
- **Åtkomstkontroll**: Endast auktoriserade Lambda-funktioner kan skriva och läsa data.
- Data i DynamoDB är krypterad vid vila.

### 5. Grafana
- **API-säkerhet**: Grafana Infinity Data Source använder API Gateway URL med en säker `Authorization Header`.
- Användarbehörigheter är begränsade till enbart läs- eller visningsåtkomst.

---



## Problemlösning
### 1. Vanliga Problem
401 Unauthorized från Lambda

### 2. Kontrollera att Authorization Header i Postman eller Grafana är korrekt inställd.
Säkerställ att Lambda-miljövariabeln allowedHeader matchar det du skickar som Authorization Header.
404 URL Not Found

### 3. Kontrollera att du använder rätt URL från API Gateway.

### 4. Kontrollera att Lambda-funktionen är korrekt kopplad till API Gateway och att rätt rutt används (t.ex. /items om du använder den i koden).

### 5. Kontrollera att IoT-regeln har rätt filter och actions inställda.

### 6. Kontrollera din USB kabel
Jag upplevde att min ESP32 inte fungerade som förväntat. Efter mycket felsökning upptäckte jag att problemet låg i USB-kabeln.
