#include <Ethernet.h>
#include <SPI.h>

/*
Simple Ethernet Test
Arduino server outputs simple text to browser
and controlling LED with simple checkbox
The circuit:
* Arduino Duemilanove
* Arduino Ethernet shield
By Minde http://www.sciencprog.com/
*/

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 100, 177 }; // ip in lan
byte gateway[] = { 192, 168, 100, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port
String readString; //string for fetching data from address
double vout;
int dnint;
int outPin = 9;

void setup() {
  Serial.println("test");
	//start Ethernet
	Ethernet.begin(mac, ip, gateway, subnet);
	//enable serial datada print
	Serial.begin(9600);
 pinMode(outPin, OUTPUT);
}

void loop() {
	// Create a client connection
	EthernetClient client = server.available();
	if (client) {
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				//read char by char HTTP request
				if (readString.length() < 30) {
					//store characters to string
					readString.concat(c);
				}
				//output chars to serial port
				//Serial.print(c);
				//if HTTP request has ended
				if (c == '\n') {
					// now output HTML data starting with standart header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println();
					client.print("<body>");
					client.println("<h1>Output data</h1>");
					client.println("<font size='5'>Data: ");
					client.print(readString); // full string from client
					client.println("<br />");
					// find parts in readString value
					String data;
					char datatable[6];
					char* dntable;
					char* uptable;
					String up, dn;

					if (readString.indexOf("up=") > 0) {
						char up_start = readString.indexOf("up=") + 3;
						char up_end = readString.indexOf("&dn=");
						up = readString.substring(up_start, up_end);
						char dn_start = readString.indexOf("dn=") + 3;
						char dn_end = readString.indexOf(" ", dn_start);
						dn = readString.substring(dn_start, dn_end);
						data = String(up + "#" + dn);

						
						// print data serial
						Serial.println(data);

						dnint = dn.toInt();
						setVolt(dnint);
					
						// print html
						client.println("Up: ");
						client.print(up); // up value
						client.println("<br />");
						client.println("Down: ");
						client.print(dn);// down value
						client.println("<br />");
						client.println("</font>");
					}
					client.println("</body></html>");
					//clearing string for next read
					readString = "";
					//stopping client
					client.stop();
				}
			}
		}
	}
}

void setVolt(double dndouble)
{
	vout = dndouble*255/100;
	Serial.println(vout);
	analogWrite(outPin, vout);

}
