import os, requests, json
import paho.mqtt.client as mqtt

WEB_URL = os.getenv("WEB_URL")        # e.g., https://api.example/events
WEB_TOKEN = os.getenv("WEB_TOKEN")
MQTT_URL = os.getenv("MQTT_URL")      # e.g., tcp://localhost:1883
MQTT_TOPIC = os.getenv("MQTT_TOPIC", "swarmguard/events")

def post_http(event: dict):
    if not WEB_URL: return
    headers = {"Authorization": f"Bearer {WEB_TOKEN}"} if WEB_TOKEN else {}
    try: requests.post(WEB_URL, json=event, headers=headers, timeout=3)
    except Exception: pass

def post_mqtt(event: dict):
    if not MQTT_URL: return
    host = MQTT_URL.replace("tcp://","").split(":")[0]
    port = int(MQTT_URL.split(":")[-1]) if ":" in MQTT_URL else 1883
    cli = mqtt.Client()
    try:
        cli.connect(host, port, 60)
        cli.publish(MQTT_TOPIC, json.dumps(event), qos=0, retain=False)
        cli.disconnect()
    except Exception: pass
