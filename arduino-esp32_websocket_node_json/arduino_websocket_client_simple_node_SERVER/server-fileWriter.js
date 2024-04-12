/*
	Express.js GET/POST example *modified*
	Shows how handle GET, POST, PUT, DELETE
	in Express.js 4.0

	created 14 Feb 2016
	by Tom Igoe
  modified 2 Mar 2024
  by Jesse Harding (with features from https://github.com/tigoe/DataloggingExamples/tree/main/WiFiDatalogger)
*/

//you'll need to install express and ws using npm in your project folder after you npm init

var express = require('express');			// include express.js
var app = express();						// a local instance of it
// var bodyParser = require('body-parser');	// include body-parser
var WebSocketServer = require('ws').Server	// include Web Socket server


// include filesystem utilities:
const fs = require("fs");
const util = require("util");
// lets us write filesystem calls using Promises:
const appendFile = util.promisify(fs.appendFile);
// line-by-line reader library:
const readline = require("readline");
let fileName = __dirname + "/data.json";


// you need a  body parser:
// app.use(bodyParser.urlencoded({extended: false})); // for application/x-www-form-urlencoded

// this runs after the server successfully starts:
function serverStart() {

	var port = server.address().port;
	console.log('Server listening on port '+ port);
}

// this is the POST handler:
// app.all('/*', function (request, response) {
// 	console.log('Got a ' + request.method + ' request');
// 	// the parameters of a GET request are passed in
// 	// request.body. Pass that to formatResponse()
// 	// for formatting:
// 	console.log(request.headers);
// 	if (request.method == 'GET') {
// 		console.log(request.query);
// 	} else {
// 		console.log(request.body);
// 	}

// 	// send the response:
// 	response.send('OK');
// 	response.end();
// });

// start the server:
var server = app.listen(8080, serverStart);

// create a WebSocket server and attach it to the server
var wss = new WebSocketServer({server: server});

wss.on('connection', function connection(ws) {
	// new connection, add message listener
	ws.on('message', function incoming(message) {
		// received a message
		// console.log('received: %s', message);
    var fileObject = fs.readFileSync(fileName, 'utf8' );
    console.log(JSON.parse(fileObject));
		// echo it back
		ws.send(JSON.stringify(JSON.parse(fileObject)));
    // let recordString = JSON.stringify(message) + "\n";
    // append the line to the file:
    // appendFile(fileName, message + "\n")
    // or overwrite and just keep most recent data:
    fs.writeFileSync(fileName, message);

	});
});
