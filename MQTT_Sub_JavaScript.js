/*
    To install the NPM Package:
    npm i mqtt
*/

//Latitude
/*
const mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://MQTT_SERVER_IP_ADDRESS:1883')
var topic_LAT = 'GPS/Latitude'

client.on('connect', function(){
    client.subscribe(topic_LAT);
    console.log('Latitude_Subscribed');
});

client.on('message', function(topic, message){
    console.log(message.toString());
})
*/


//Longitude

const mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://MQTT_SERVER_IP_ADDRESS:1883')
var topic_LON = 'GPS/Longitude'

client.on('connect', function(){
    client.subscribe(topic_LON);
    console.log('Longitude_Subscribed');
});

client.on('message', function(topic, message){
    console.log(message.toString());
})
