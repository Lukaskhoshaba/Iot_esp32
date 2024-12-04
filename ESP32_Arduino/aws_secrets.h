#ifndef AWS_SECRETS_H
#define AWS_SECRETS_H
#define THINGNAME "ESP32"

const char WIFI_SSID[] = "";
const char WIFI_PASSWORD[] = "";

const char AWS_IOT_ENDPOINT[] = "";

// Root CA Certificate
static const char AWS_CERT_CA[] = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----

)KEY";

// Private Key
static const char AWS_CERT_PRIVATE[] = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----

)KEY";

#endif
