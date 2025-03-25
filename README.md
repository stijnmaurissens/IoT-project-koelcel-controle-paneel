# IoT-project-koelcel-controle-paneel
micro controller dat via blynk temperatuur kan zien en instellen


Documentatie: koelcel controle paneel

Met dit project zou je jou koelcel/frigo van op afstand kunnen regelen en controleren via blynk.
 
![image](https://github.com/user-attachments/assets/f9a07830-153b-4570-bec3-f95a1d8b816f)

Zoals u in deze schreenshot kan zien kan u zowel de temperatuur als de vochtigheid lezen zowel op het traditioneel display als op de grafiek.
Ook kan u door de slider de  gewenste temperatuur instellen. Dus indien de gewenste temperatuur lager licht dan de actuele temperatuur dan springen de koelelementen (blauwe LED’s) aan.  In blynk staat ook een rode LED ( de linkse led) dat brand als er licht in de koelcel is (dus als de deur open staat).
 
 ![image](https://github.com/user-attachments/assets/11e98baa-880d-4726-bbe8-952866d9c21a)


Zoals u op dit schema kunt zien is op de esp32 een LCD display gekoppeld dat ook de temperatuur en de ingestelde temperatuur laat zien
Dan is er een breadboard dat op de frigo met staat een LED dat laat zien dat de koelelementen zouden moeten aanstaan. En één buzzer dat als alarm dient indien de temperatuur te ver boven de ingestelde temperatuur komt(in dit geval 5°C er boven).
Er is ook een 2de breadboard dat in de koelcel/frigo steekt met de DHT11 dat de temperatuur en de vochtigheid uitleest, en een LDR dat detecteert of er licht is / of de deur open staat of niet. 
